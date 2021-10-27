Instructions for fixing the code.

Key Differences:

1. WorkingSensoriFLOOD.ino is the working code for a module that uses a GPRSBee transmitter and sends data to the iFLOOD website
	- In this 
2. WorkingSensorMMW.ino is the working code for a module that uses a DigiXBee LTE transmitter and sends data to the MMW (monitormywatershed) website

Directions:
- Edit the WorkingSensorMMW.ino code to send data to the iFLOOD website instead of the MMW website

Notes: 
- Both of these transmitters are attached to the Mayfly data logger (https://github.com/envirodiy) 
- The module's sensor is the MaxBotix Ultrasonic Sensor (https://envirodiy.github.io/ModularSensors/group__sensor__maxbotix.html)
- Both codes work, it is only a matter of editing the second code to send data to the first website
- Both modules use Hologram IO sim card
- Line 97 of WoringSensoriFLOOD.ino is the link that is used to send data
- The only difference between the two modules is one uses the GPRSBee transmitter and the other uses the DigiXBee LTE transmitter