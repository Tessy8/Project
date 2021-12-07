program PWM_MOTOR_CONTROL


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

                -----------                   ----------
                | ATmega328 |                 |   LCD    |
                |           |                 |          |
                |        PD7|---------------->|D7        |
                |        PD6|---------------->|D6        |
                |        PD5|---------------->|D5        |
                |        PD4|---------------->|D4        |
                |           |                 |D3        |
                |           |                 |D2        |
                |           |                 |D1        |
                |           |                 |D0        |
                |           |                 |          |
                |        PB1|---------------->|E         |
                |           |         GND --->|RW        |
                |        PB0|---------------->|RS        |
                 -----------                   ----------
 
// LCD interface (should agree with the diagram above)
//   make sure that the LCD RW pin is connected to GND
#define lcd_D7_port     PORTD                   // lcd D7 connection
#define lcd_D7_bit      PORTD7
#define lcd_D7_ddr      DDRD

#define lcd_D6_port     PORTD                   // lcd D6 connection
#define lcd_D6_bit      PORTD6
#define lcd_D6_ddr      DDRD

#define lcd_D5_port     PORTD                   // lcd D5 connection
#define lcd_D5_bit      PORTD5
#define lcd_D5_ddr      DDRD

#define lcd_D4_port     PORTD                   // lcd D4 connection
#define lcd_D4_bit      PORTD4
#define lcd_D4_ddr      DDRD

#define lcd_E_port      PORTB                   // lcd Enable pin
#define lcd_E_bit       PORTB1
#define lcd_E_ddr       DDRB

#define lcd_RS_port     PORTB                   // lcd Register Select pin
#define lcd_RS_bit      PORTB0
#define lcd_RS_ddr      DDRB

// LCD module information
#define lcd_LineOne     0x00                    // start of line 1
#define lcd_LineTwo     0x40                    // start of line 2
//#define   lcd_LineThree   0x14                  // start of line 3 (20x4)
//#define   lcd_lineFour    0x54                  // start of line 4 (20x4)
//#define   lcd_LineThree   0x10                  // start of line 3 (16x4)
//#define   lcd_lineFour    0x50                  // start of line 4 (16x4)

// LCD instructions
#define lcd_Clear           0b00000001          // replace all characters with ASCII 'space'
#define lcd_Home            0b00000010          // return cursor to first position on first line
#define lcd_EntryMode       0b00000110          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0b00001000          // turn display off
#define lcd_DisplayOn       0b00001100          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0b00110000          // reset the LCD
#define lcd_FunctionSet4bit 0b00101000          // 4-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0b10000000          // set cursor position

// Function Prototypes
void lcd_write_4(uint8_t);
void lcd_write_instruction_4d(uint8_t);
void lcd_write_character_4d(uint8_t);
void lcd_write_string_4d(uint8_t *);
void lcd_init_4d(void);


' Declarations section 
symbol HiA = RC1_bit
symbol LowA = RC2_bit
symbol HiB = RC0_bit
symbol LowB = RC3_bit
symbol MOTOR_FW = RC4_bit
symbol MOTOR_Rev = RC5_bit   'reverse
symbol OFF = 0
symbol M_FORWORD = 1
symbol M_REVERSE = 2
symbol ERROR_OC = 3
symbol M_BREAK = 4
symbol PIRIAD = 255

'--------------------------------------------
   ' variables declarations
 dim fbrak_fw, fbrak_rev as byte
 dim motor_stat, interruptcont, cont20m as byte
 dim current, maxcurrent, avgcurrent as word
 dim adccont, flags25Pwm as byte
 dim OCdlay, maxwidth as byte
 dim PWM_F, PWM_R as byte
 dim softdl as byte
 '-----------
 dim setcurrent as word
     setPWM as byte
'----------------------------------------------
 ' procedures declarations
 sub procedure Initpwm()
    OPTION_REG = OPTION_REG and 0xc2    ' Assign prescaler to TMR0
    T0IE_bit = 1
    GIE_bit = 1
 end sub
 '----------------------------------------------
 sub procedure interrupt
  if(T0IF_bit = 1)then

    if( motor_stat =  M_FORWORD)then

      if( HiB = 1)then

           TMR0 = PIRIAD - PWM_F
           HiB = 0

      else
        TMR0 = PWM_F
        HiB = 1
      end if
    else
      if(  motor_stat =  M_REVERSE)then

         if( HiA = 1)then
           TMR0 = PIRIAD - PWM_R
           HiA = 0
         else
           TMR0 = PWM_R
           HiA = 1
         end if

      end if
    end if
    T0IF_bit = 0  'Clear the interrupt
  end if
  interruptcont = 1
end sub
main:

    // configure the microprocessor pins for the data lines
    lcd_D7_ddr |= (1<<lcd_D7_bit);                  // 4 data lines - output
    lcd_D6_ddr |= (1<<lcd_D6_bit);
    lcd_D5_ddr |= (1<<lcd_D5_bit);
    lcd_D4_ddr |= (1<<lcd_D4_bit);

    // configure the microprocessor pins for the control lines
    lcd_E_ddr |= (1<<lcd_E_bit);                    // E line - output
    lcd_RS_ddr |= (1<<lcd_RS_bit);                  // RS line - output

    // initialize the LCD controller as determined by the defines (LCD instructions)
    lcd_init_4d(); 
    
    ' Main program
     ANSEL = %00000111
     ADCON0 = %10000001
     ADCON1 = %00000000
     CMCON = $07
     VRCON = 0x00
     WPUA = 0
     ADC_Init()  ' Initialize ADC module
     PORTA = 0
     PORTC = %001111
     TRISA = %000111
     TRISC = %110000
     fbrak_fw = 0  fbrak_rev = 0
     motor_stat =  OFF
     interruptcont = 0  cont20m = 0
     OCdlay = 0
     PWM_F = 0
     PWM_R = 0
     softdl = 10
     flags25Pwm = 0
     current = 0  maxcurrent = 0  avgcurrent = 0
     adccont = 0
     setcurrent = 0   setPWM = 0
     Initpwm()
     
     maxwidth =  PIRIAD - 1
     lcd_write_string_4d(maxwidth);
     lcd_write_instruction_4d(lcd_SetCursor | lcd_LineTwo);
     delay_ms(1000)
    '---------------- looop for ever ----------------------
     while(1)
     
        if( interruptcont = 1) then
           interruptcont = 0
           
           select case( motor_stat)
         
            case OFF      '---- MOTOR OFF
               maxwidth =  PIRIAD - 1
               current = 0
               avgcurrent = 0
               maxcurrent = 0
               flags25Pwm = 0
               
               HiA = 1     ' OFF
               HiB = 1     'OFF
               nop
               nop
               delay_ms(10)
               LowA = 1    'OFF
               LowB = 1    'OFF
               delay_ms(10)
               '--- test SW 1
               if( MOTOR_FW = 1)then
                 delay_ms(200)
                 if( MOTOR_FW = 1)then
                     LowA = 0  'ON
                     motor_stat =  M_FORWORD
                  end if
               else
                 PWM_F = 0
               end if
                 '--- test SW 2
              if(  MOTOR_Rev = 1)then
                delay_ms(200)
                if(  MOTOR_Rev = 1)then
                   LowB = 0   'ON
                   motor_stat =  M_REVERSE
                end if
              else
                  PWM_R = 0
              end if
              
            case M_FORWORD     '----->>
           
                '--- test SW 1
                if( MOTOR_FW = 0)then
                  delay_ms(100)
                  if( MOTOR_FW = 0)then
                    '  maxwidth = PIRIAD - 3
                    lcd_write_string_4d(maxwidth);
                     motor_stat =  M_BREAK
                  end if
                else
                   if( flags25Pwm = 255)then
                      PWM_F = setPWM
                   else
                     if(PWM_F < maxwidth) then
                       inc(PWM_F )
                     end if
                     delay_ms(1)
                   end if
                end if
                
            case  M_REVERSE    '<<-----
           
                   '--- test SW 2
                if( MOTOR_Rev = 0)then
                  delay_ms(100)
                  if( MOTOR_Rev = 0)then
                    ' maxwidth = PIRIAD - 3
                    lcd_write_string_4d(maxwidth);
                     motor_stat =  M_BREAK
                  end if
                else
                   if( flags25Pwm = 255)then
                      PWM_R = setPWM
                   else
                     if(PWM_R < maxwidth)then
                       inc(PWM_R)
                     end if
                     delay_ms(1)
                   end if
                end if
                
            case M_BREAK      '>>---<<
            
                  while ( PWM_R > 0)
                    dec(PWM_R )
                     delay_us(100)
                  wend
                  
                  while ( PWM_F > 0)
                     dec( PWM_F)
                     delay_us(100)
                  wend
                  LowA = 1    'OFF
                  LowB = 1    'OFF
                  delay_us(100)

                  HiA = 0     'ON
                  HiB = 0     'ON
                  delay_ms(10)    'break time
                  
                  motor_stat =  OFF
          
           end select   'end of the ( select case( motor_stat))
           
           current = ADC_Read(2)
           if(current > maxcurrent)then
              maxcurrent = current
           end if
           inc(adccont)
           if(adccont > 4)then   '128
             adccont = 0
             avgcurrent = maxcurrent
             maxcurrent = 0
           end if
           if( avgcurrent > setcurrent )then
             flags25Pwm = 255
           else
              flags25Pwm = 0
           end if
           if( avgcurrent > 600 )then
            ' motor_stat =  M_BREAK
           end if
           setcurrent = ADC_Read(1) >> 2
           setPWM = ADC_Read(0) >> 2
           if(setPWM < 100)then
              setPWM =  100
           end if
        end if 'end of the ( interruptcont)
        
     wend   ' end of the looop for ever
end.



void lcd_init_4d(void)
{
// Power-up delay
    _delay_ms(100);                                 // initial 40 mSec delay

// Set up the RS and E lines for the 'lcd_write_4' subroutine.
    lcd_RS_port &= ~(1<<lcd_RS_bit);                // select the Instruction Register (RS low)
    lcd_E_port &= ~(1<<lcd_E_bit);                  // make sure E is initially low

// Reset the LCD controller
    lcd_write_4(lcd_FunctionReset);                 // first part of reset sequence
    _delay_ms(10);                                  // 4.1 mS delay (min)

    lcd_write_4(lcd_FunctionReset);                 // second part of reset sequence
    _delay_us(200);                                 // 100uS delay (min)

    lcd_write_4(lcd_FunctionReset);                 // third part of reset sequence
    _delay_us(200);                                 // this delay is omitted in the data sheet

    lcd_write_4(lcd_FunctionSet4bit);               // set 4-bit mode
    _delay_us(80);                                  // 40uS delay (min)

// Function Set instruction
    lcd_write_instruction_4d(lcd_FunctionSet4bit);   // set mode, lines, and font
    _delay_us(80);                                  // 40uS delay (min)


// Display On/Off Control instruction
    lcd_write_instruction_4d(lcd_DisplayOff);        // turn display OFF
    _delay_us(80);                                  // 40uS delay (min)

// Clear Display instruction
    lcd_write_instruction_4d(lcd_Clear);             // clear display RAM
    _delay_ms(4);                                   // 1.64 mS delay (min)

// ; Entry Mode Set instruction
    lcd_write_instruction_4d(lcd_EntryMode);         // set desired shift characteristics
    _delay_us(80);                                  // 40uS delay (min)

// Display On/Off Control instruction
    lcd_write_instruction_4d(lcd_DisplayOn);         // turn the display ON
    _delay_us(80);                                  // 40uS delay (min)
}


void lcd_write_string_4d(uint8_t theString[])
{
    volatile int i = 0;                             // character counter*/
    while (theString[i] != 0)
    {
        lcd_write_character_4d(theString[i]);
        i++;
        _delay_us(80);                              // 40 uS delay (min)
    }
}



void lcd_write_character_4d(uint8_t theData)
{
    lcd_RS_port |= (1<<lcd_RS_bit);                 // select the Data Register (RS high)
    lcd_E_port &= ~(1<<lcd_E_bit);                  // make sure E is initially low
    lcd_write_4(theData);                           // write the upper 4-bits of the data
    lcd_write_4(theData << 4);                      // write the lower 4-bits of the data
}

void lcd_write_instruction_4d(uint8_t theInstruction)
{
    lcd_RS_port &= ~(1<<lcd_RS_bit);                // select the Instruction Register (RS low)
    lcd_E_port &= ~(1<<lcd_E_bit);                  // make sure E is initially low
    lcd_write_4(theInstruction);                    // write the upper 4-bits of the data
    lcd_write_4(theInstruction << 4);               // write the lower 4-bits of the data
}


void lcd_write_4(uint8_t theByte)
{
    lcd_D7_port &= ~(1<<lcd_D7_bit);                        // assume that data is '0'
    if (theByte & 1<<7) lcd_D7_port |= (1<<lcd_D7_bit);     // make data = '1' if necessary

    lcd_D6_port &= ~(1<<lcd_D6_bit);                        // repeat for each data bit
    if (theByte & 1<<6) lcd_D6_port |= (1<<lcd_D6_bit);

    lcd_D5_port &= ~(1<<lcd_D5_bit);
    if (theByte & 1<<5) lcd_D5_port |= (1<<lcd_D5_bit);

    lcd_D4_port &= ~(1<<lcd_D4_bit);
    if (theByte & 1<<4) lcd_D4_port |= (1<<lcd_D4_bit);

// write the data
                                                    // 'Address set-up time' (40 nS)
    lcd_E_port |= (1<<lcd_E_bit);                   // Enable pin high
    _delay_us(1);                                   // implement 'Data set-up time' (80 nS) and 'Enable pulse width' (230 nS)
    lcd_E_port &= ~(1<<lcd_E_bit);                  // Enable pin low
    _delay_us(1);                                   // implement 'Data hold time' (10 nS) and 'Enable cycle time' (500 nS)
}

 
