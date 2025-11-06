# Air_Mouse_python
# 🖱️ Air Mouse — Wireless Motion-Controlled Mouse System

### 📡 Overview
**Air Mouse** is a Wi-Fi–based smart input system that lets you control your computer's mouse cursor with hand movements.  
Built using **ESP8266 (NodeMCU)**, **MPU6050 motion sensor**, and **Python**, this project transforms your hand gestures into real-time cursor movements.

When you tilt or move your hand, the MPU6050 detects the motion and sends data through the ESP8266 to your computer over Wi-Fi.  
A Python program receives the data and moves the cursor accordingly.

---

## ⚙️ Features
- 🎯 Wireless motion-controlled mouse
- 🖐️ Real-time hand gesture tracking using MPU6050
- 🧠 Two physical buttons for **Left** and **Right click**
- 🌐 Wi-Fi communication between ESP8266 and PC
- 🧩 Python + Arduino integration

---

## 🧰 Components Used
| Component | Description |
|------------|-------------|
| **ESP8266 (NodeMCU)** | Wi-Fi microcontroller used for data transmission |
| **MPU6050** | 3-axis gyroscope and accelerometer sensor |
| **Push Buttons (x2)** | For left and right mouse clicks |
| **PC (Python Script)** | Receives motion data and moves the mouse |

---

## 🔌 Circuit Connection

| MPU6050 Pin | ESP8266 Pin |
|--------------|-------------|
| VCC | 3.3V |
| GND | GND |
| SCL | D1 |
| SDA | D2 |
| Left Button | D5 → GND |
| Right Button | D6 → GND |

---

## 🧾 Arduino Code (ESP8266 Side)

👉 [View Full Code Here](air_mouse_esp8266.ino)

**Key Tasks:**
- Initialize MPU6050 and Wi-Fi
- Calibrate gyro data
- Send hand movement and button press data to PC via Wi-Fi socket

---

## 💻 Python Code (PC Side)

👉 [View Full Code Here](air_mouse_pc.py)

**Key Tasks:**
- Create TCP server on port 5000
- Receive (dx, dy, left, right) data from ESP8266
- Move mouse cursor using `pyautogui`
- Perform left/right click actions

---

## 🧩 Installation (PC Side)

### 1️⃣ Create environment (optional)
```bash
conda create -n airmouse python=3.10 -y
conda activate airmouse
