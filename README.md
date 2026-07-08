It is a IOT Based Smoke Detection System using ESP32

Project Overview:-
This project is an IoT-Based Smoke Detection System developed using ESP32 and MQ-2 Smoke Sensor. The system detects smoke in real time and activates a buzzer. It sends notifications through the Blynk application, stores event logs in Firebase Realtime Database, and sends a Telegram alert to a neighbour if the owner does not acknowledge the alert.

## Features:-
- Real-time Smoke Detection
- ESP32 Microcontroller
- MQ-2 Smoke Sensor
- Buzzer Alert
- Blynk Mobile Notification
- Firebase Realtime Database
- Telegram Alert System
- Owner Acknowledgement (ACK)
- Cloud Data Logging

## Hardware Used:-
- ESP32
- MQ-2 Smoke Sensor
- Buzzer
- Breadboard
- Jumper Wires

## Software Used:-
- Arduino IDE
- Blynk IoT
- Firebase Realtime Database
- Telegram Bot API

## Technologies:-
- IoT
- ESP32
- Embedded C/C++
- Firebase
- Blynk
- Wi-Fi


Output:-

 1. Normal Monitoring

Description:
- This screen shows the normal working condition of the smoke detection system.
- The smoke sensor value is within the safe range.
- No smoke is detected, so the system status is "NORMAL".
- No alert is sent to the user.



 2. Smoke Detected

Description:
- This screen shows that smoke has been detected.
- The sensor value has crossed the threshold.
- The system activates the smoke alert and updates the status.



 3. Blynk Notification

Description:
- A real-time notification is sent through the Blynk application when smoke is detected.
- This helps the user receive an instant alert.



 4. Telegram Alert

Description:
- If the owner does not acknowledge the alert within 60 seconds, a Telegram notification is sent to the neighbour/other person.
- This ensures that emergency information reaches the user.



 5. Firebase Database blynk

Description:
- Firebase Realtime Database stores the smoke level, risk level, timestamp, and action taken.
- All records are saved for monitoring and analysis.



 6. Smoke Detected - Firebase realtime database

Description:
- This shows the database entry created after smoke detection.
- The event details are stored automatically in Firebase.



 7.Firebase database telegram 

 Description:
 - Firebase Realtime Database stores the smoke level, risk level, timestamp, and action taken.
 - If the owner did not acknowledge within 60 seconds in blynk app then telegram notification automatically send to the the neighbour.
