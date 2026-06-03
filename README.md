# Smart Carbon Monoxide (CO) Monitoring and Safety System

## Overview

The Smart Carbon Monoxide (CO) Monitoring and Safety System is an IoT-based safety project developed using an ESP32 microcontroller and an MQ-7 Carbon Monoxide sensor. The system continuously monitors CO levels in the environment and provides real-time visual and audible alerts when dangerous gas concentrations are detected.

To enhance safety, the system automatically activates a relay-controlled ventilation device (such as an exhaust fan) when CO levels exceed predefined thresholds.

---

## Features

* Real-time Carbon Monoxide (CO) monitoring
* OLED display for live sensor readings
* Three-level safety status indication:

  * Safe
  * Warning
  * Danger
* Audible alarm using buzzer
* Automatic relay control for ventilation systems
* Sensor value smoothing for stable readings
* Compact and low-cost embedded safety solution

---

## Hardware Components

| Component                          | Quantity    |
| ---------------------------------- | ----------- |
| ESP32 Development Board            | 1           |
| MQ-7 CO Gas Sensor                 | 1           |
| SSD1306 OLED Display (128x64, I2C) | 1           |
| Active Buzzer                      | 1           |
| Relay Module                       | 1           |
| Breadboard                         | 1           |
| Jumper Wires                       | As Required |
| Power Supply (5V USB)              | 1           |

---

## System Architecture

MQ-7 Sensor → ESP32 → OLED Display

```
              ↓

    Safety Decision Logic

              ↓

 Buzzer + Relay Activation
```

---

## Circuit Connections

### MQ-7 Sensor

| MQ-7 Pin | ESP32 Pin |
| -------- | --------- |
| VCC      | 5V        |
| GND      | GND       |
| AOUT     | GPIO 34   |

### OLED Display (I2C)

| OLED Pin | ESP32 Pin |
| -------- | --------- |
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO 21   |
| SCL      | GPIO 22   |

### Buzzer

| Buzzer Pin | ESP32 Pin |
| ---------- | --------- |
| Positive   | GPIO 25   |
| Negative   | GND       |

### Relay Module

| Relay Pin | ESP32 Pin |
| --------- | --------- |
| IN        | GPIO 26   |
| VCC       | 5V        |
| GND       | GND       |

---

## Working Principle

1. ESP32 continuously reads analog values from the MQ-7 sensor.
2. Multiple readings are averaged to reduce sensor noise.
3. The measured CO value is displayed on the OLED screen.
4. The system evaluates the sensor reading against predefined thresholds.

### Safe State

* CO value below warning threshold
* OLED displays SAFE
* Buzzer OFF
* Relay OFF

### Warning State

* CO value exceeds warning threshold
* OLED displays WARNING
* Slow buzzer alert
* Relay activated

### Danger State

* CO value exceeds danger threshold
* OLED displays DANGER
* Fast buzzer alert
* Relay activated immediately

---

## Threshold Configuration

```cpp
int SAFE_LIMIT = 1200;
int WARNING_LIMIT = 2000;
int DANGER_LIMIT = 3000;
```

These values can be calibrated according to the specific MQ-7 sensor and environmental conditions.

---

## Software Requirements

* Arduino IDE
* ESP32 Board Package
* Required Libraries:

  * Wire.h
  * Adafruit_GFX
  * Adafruit_SSD1306

### Install Libraries

Arduino IDE → Library Manager

Install:

* Adafruit GFX Library
* Adafruit SSD1306 Library

---

## Installation

### Clone Repository

```bash
git clone https://github.com/your-username/co-monitoring-system.git
```

### Open Project

```bash
CO_Monitoring_System.ino
```

### Configure ESP32 Board

1. Open Arduino IDE
2. Select:

```text
Tools → Board → ESP32 Dev Module
```

3. Select correct COM Port

### Upload Code

Click Upload and wait for successful compilation.

---

## Example OLED Output

```text
CO Monitor

1050

SAFE
```

```text
CO Monitor

2350

WARNING
```

```text
CO Monitor

3420

DANGER!
```

---

## Applications

* Smart homes
* Industrial safety monitoring
* Parking garages
* Laboratories
* Underground facilities
* Boiler rooms
* Vehicle emission monitoring
* Air quality monitoring systems

---

## Future Improvements

* Wi-Fi-based remote monitoring
* Mobile application integration
* Cloud data logging
* Telegram/Email alerts
* Real-time dashboard using MQTT
* Multiple gas sensor integration
* Battery backup system
* AI-based gas concentration prediction

---

## Project Highlights

* Embedded Systems
* Internet of Things (IoT)
* ESP32 Programming
* Sensor Integration
* Automation and Control
* Air Quality Monitoring
* Safety Systems
* Real-Time Monitoring

---

## Author

Vinit Sheetal

B.Tech Computer Science Engineering

Interests:

* IoT Development
* Artificial Intelligence
* Embedded Systems
* Robotics
* Cybersecurity

---

## License

This project is licensed under the MIT License.

Feel free to use, modify, and distribute this project for educational and research purposes.
