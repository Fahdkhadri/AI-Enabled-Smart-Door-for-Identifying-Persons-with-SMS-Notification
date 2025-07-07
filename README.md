AI-Enabled Smart Door for Identifying Persons with SMS Notification

Overview
This project implements a smart door security system that leverages artificial intelligence to identify individuals using facial recognition and notifies homeowners via SMS in real-time. It is designed as a low-cost, offline, and reliable alternative to traditional sensor-based systems, making it suitable for both residential and institutional access control.

The system integrates an ESP32-CAM module for capturing images, a CNN-optimized facial recognition model using LBPH for real-time identity verification, an Arduino Uno microcontroller for process control, and a SIM800C GSM module for sending SMS alerts. It also features a 16x2 LCD for local status messages and a buzzer for immediate on-site notification.

Core Features
Facial detection using Haar Cascade algorithm

Real-time facial recognition using Local Binary Pattern Histogram (LBPH)

SMS alert system via SIM800C GSM module

Offline operation without dependency on internet or cloud APIs

LCD display for real-time feedback (e.g., "Person Detected", "SMS Sent")

Buzzer alarm for local audible notifications

Modular and expandable system architecture

Low-power and cost-effective embedded design

Hardware Components
ESP32-CAM module

Arduino Uno

SIM800C GSM module

16x2 LCD display

Piezo buzzer

Power supply (12V 1A DC adapter)

Optional: PIR sensor for motion detection

Software Stack
OpenCV for image processing

Python (with serial communication for GSM interface)

Arduino IDE for microcontroller programming

Haar Cascade for face detection

LBPH for facial recognition

AT commands for GSM control

Advantages
Works effectively under various lighting conditions and angles

Achieves over 90% facial recognition accuracy in real-world scenarios

Sends SMS alerts within 3–5 seconds of detection

Operates without internet connectivity, ensuring privacy and reliability

Easily deployable with a total cost under ₹3,500 (approx. $42)

Use Cases
Home security

Office access control

Monitoring restricted areas

Deployments in areas with limited or no internet connectivity

Future Enhancements
Anti-spoofing techniques (blink detection, thermal sensing)

Cloud integration for remote access logs and video feeds

Mobile app interface for monitoring and configuration

Multi-factor authentication (face + voice or PIN)

Solar-powered operation for energy efficiency
