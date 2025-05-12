# Heater Control System - Arduino Implementation

## 🔧 Objective
Design and implement a simple heater control system that simulates heating using a temperature sensor and controls a heating actuator with feedback mechanisms.

---

## 📦 Components Used
| Component       | Function                                  |
|----------------|-------------------------------------------|
| Arduino UNO     | Main microcontroller                     |
| TMP36/DS18B20   | Temperature sensor (used both)           |
| 5 LEDs          | State indication (Idle, Heating, etc.)   |
| Buzzer          | Overheat alert                           |
| Relay (Simulated) | Disconnect power on overheat           |

---

## ⚙️ System States
| State            | LED Color | Description                          |
|------------------|-----------|--------------------------------------|
| **IDLE**         | Blue      | System on, no heating                |
| **HEATING**      | Green     | Heater ON, temperature rising        |
| **STABILIZING**  | Yellow    | Near target, heater cycles           |
| **TARGET REACHED** | Orange  | Temp reached, heater OFF             |
| **OVERHEAT**     | Red       | Critical, buzzer ON, relay OFF       |

---

## 🔁 Actuator Simulation
- A heater is simulated via a GPIO pin (`heaterPin`).
- When active, a `simulatedTemp` variable increases.
- A **relay pin** (`relayPin`) disconnects the heater during overheat.

---

## 🧪 Simulation History

### TinkerCAD (Initial Phase)
- Used to verify basic logic and circuit behavior.
- Helped design and test the state transitions with LEDs and temperature logic.
> **TinkerCAD Simulation Link**: https://www.tinkercad.com/things/bLwauZPdw8U-tmp36-temperature-sensor-with-arduino


### Wokwi (Final Phase)
- Used for final integration of:
  - 5 LED indicators
  - Heater output pin simulation
  - Buzzer for overheat alert
  - Relay pin control
- Final testing was done with Wokwi for accurate timing, pin mapping, and logging.

> **Wokwi Simulation Link**: https://wokwi.com/projects/430372342260459521

---

## 🧰 Future Roadmap
- Port to **ESP32** using **ESP-IDF**.
- Add **BLE advertisement** of state.
- Integrate **FreeRTOS** for better multitasking.
- Replace simulated temp with **actual sensor feedback** in full system.

