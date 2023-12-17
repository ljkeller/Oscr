# Oscr
Open source coin rotator using ESP32

## Overview
This repository contains the source code and design schematics for an open-source coin rotating display, Oscr, a fun ESP32 project designed to showcase coins in a dynamic manner. The 3d printed device is driven by an ESP32 microcontroller and controls a single FS90R continuous servo for rotation with the ESP-IDF Motor Control Pulse Width Modulator (MCPWM) API. All other components are designed and 3D printed using a [Bambu Lab X1C 3D printer](https://us.store.bambulab.com/products/x1-carbon-combo).

## Features
- **ESP32 Powered⚡:** Utilizes the powerful and versatile ESP32 microcontroller for control logic
- **FS90R Servo Motor:** Employs a single, cheap FS90R continous servo for rotation
- **3D Printed Design🖨:** The coin display was designed in [Fusion 360](https://www.autodesk.com/products/fusion-360/personal) and printed on a Bambu Lab X1C 3D printer
- **PlatformIO Open Source:** The entire project is open source, and uses [PlatformIO](https://platformio.org/) for simple project bootstrapping

## Hardware Requirements
- [ESP32 Microcontroller](https://www.amazon.com/Teyleten-Robot-ESP-WROOM-32-Development-Microcontroller/dp/B08246MCL5/ref=sr_1_1?keywords=esp32%2Bdevkit&qid=1702702951&sr=8-1&th=1) , [breakout board](https://www.amazon.com/Compatible-Development-Bluetooth-Microcontroller-ESP-WROOM-32/dp/B09XM2TZVT) optional
- [FS90R Continuous Servo](https://www.amazon.com/FEETECH-FS90R-Pack-Continuous-Helicopter/dp/B07FVLQ94C)
- Power supply suitable for the ESP32 and servo (fs90r max current draw is 700mA at 6V)
- Miscellaneous wires and connectors

## Software Requirements
- The source code is written in C, using the ESP-IDF API. Compile and uploaded with PlatformIO.

## File Structure
- `/src`: Contains the C source code for the ESP32.
- `/schematics`: Includes the 3d printing files

## Setup and Installation
1. **Printing:** Follow the schematics in `/schematics` to print the necessary components.
3. **Programming:** Compile and upload the code from `/src` to the ESP32.
4. **Assembly:** Assemble 3D printed components and electronics after verifying each step

## Contribution
Contributions are welcome! If you'd like to contribute, please fork the repository and use a feature branch. Pull requests are warmly welcome.

## Licensing
Open source under the MIT [license](LICENSE).

---
Useful Resources:
- [ESP32 Pinout](https://lastminuteengineers.com/esp32-pinout-reference/) *for my specific devkit*
- [ESP-IDF Motor Control Pulse Width Modulation API](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/mcpwm.html)
- **Feetech FS90R v2 specs** (datasheet links seem to pop up and disappear quickly)
  
![image](https://github.com/ljkeller/Oscr/assets/44109284/0fa2289b-dd1d-40e2-ae83-aa0f0912089c)


**Enjoy the Open Source Coin Rotator!** Let me know if you build something similar 😄
