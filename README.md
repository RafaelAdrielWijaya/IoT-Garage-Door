# IoT-Garage-Door
Create an IoT system for controlling and monitoring garage door
Skills: Analytical & Problem Solving, Leadership, Project Management, Teamwork, and Arts & Crafts
Hardware: ESP32 microcontroller; Ultrasonic Sensors(2); SG60 Servo(2); Jumper cables; Breadboard; PVC boards (For Mock-Up)
Software: Arduino IDE and Blynk IoT Application
Steps:
1. Ultrasonic Sensor detects object and calculate the range
2. The range then being fed to the microcontroller
3. Using the code uploaded, the microcontroller sends the range to both the servo for opening the garage and Blynk IoT Application for remote monitoring

Logic:
1. If an object was detected at a certain range (In this case 5 cm) or less, the servo will open the garage
2. If an object was detected beyond the certain range, the servo will close the garage
