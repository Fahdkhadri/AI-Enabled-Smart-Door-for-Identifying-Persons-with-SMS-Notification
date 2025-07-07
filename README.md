# AI-Enabled Smart Door with SMS Notification

A low-cost, AI-powered smart door system using ESP32-CAM, facial recognition, and GSM technology for real-time SMS alerts. Designed for residential and institutional access control without internet dependency.

## 🔍 Overview

This project integrates computer vision and embedded systems to identify visitors through facial recognition and notify homeowners via SMS using a GSM module. It is designed for reliable, real-time, offline security—ideal for environments with limited internet connectivity.

## 🎯 Objectives

- Detect and recognize human faces using AI on ESP32-CAM.
- Identify authorized persons and send SMS alerts to predefined phone numbers.
- Provide on-site feedback through buzzer and LCD display.
- Operate without relying on cloud or internet services.

## 🧰 Hardware Requirements

- ESP32-CAM (face detection and capture)
- Arduino Uno (central controller)
- SIM800C GSM module (SMS alerts)
- 16x2 LCD Display (status updates)
- Piezo buzzer (local alerts)
- Power supply: 12V 1A DC adapter
- Optional: PIR sensor

## 💻 Software Requirements

- Python 3.8+
- OpenCV
- Arduino IDE
- Serial communication libraries (e.g., `pyserial`)
- Haar Cascade Classifier for face detection
- LBPH algorithm for face recognition

## 🧠 System Architecture

- ESP32-CAM captures the face image.
- Arduino Uno triggers recognition and sends AT commands to GSM.
- LCD shows system messages like "Person Detected" or "SMS Sent".
- Buzzer rings on detection.
- SMS is sent to the registered number via SIM800C.

## 🧪 Sample Python Code

```python
import cv2
import serial
import time

gsm = serial.Serial('/dev/ttyUSB0', baudrate=9600, timeout=1)
time.sleep(2)

cam = cv2.VideoCapture(0)
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

def send_sms(message):
    gsm.write(b'AT+CMGF=1\r')
    time.sleep(1)
    gsm.write(b'AT+CMGS="+911234567890"\r')  # Replace with your number
    time.sleep(1)
    gsm.write(message.encode() + b"\r")
    time.sleep(1)
    gsm.write(bytes([26]))  # CTRL+Z
    time.sleep(3)

print("System Ready. Scanning for faces...")

while True:
    ret, frame = cam.read()
    if not ret:
        continue

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5)

    if len(faces) > 0:
        print("Face detected!")
        send_sms("Alert: Person detected at your door!")
        time.sleep(10)

    cv2.imshow("Camera", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cam.release()
cv2.destroyAllWindows()
