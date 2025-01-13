# Colorimeter Project

A precise and accessible **colorimeter** designed to identify the predominant hue of unknown samples. Developed as part of an academic project at **Universitat Politècnica de Catalunya**, this system combines **hardware-based measurements** and **MATLAB-based data processing** to deliver reliable color analysis.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [How It Works](#how-it-works)
- [Usage Instructions](#usage-instructions)
- [Example Results](#example-results)
- [Contributors](#contributors)
- [License](#license)

---

## Introduction

The **Colorimeter Project** is an educational initiative to build a device that measures and identifies the predominant color of an unknown sample. By using an **Arduino Leonardo**, five LEDs (red, orange, yellow, green, and blue), and a phototransistor. The device calculates color properties, particularly the **hue**, whilst eliminating effects from brightness and saturation.

This project highlights the **integration of hardware and software**, utilizing MATLAB to process and analyze data for accurate color identification.

---

## Features

- **Accurate Color Detection**: Identifies the hue of unknown samples by transforming raw data into hue-only information.
- **Compact Design**: Utilizes minimal hardware, making it suitable for educational puprposes and for personal projects.
- **Calibration System**: Ensures consistent results by normalizing measurements against a white reference card.
- **MATLAB Integration**: Automates data processing for detailed color analysis.

---

## Hardware Requirements

To replicate this project, the following components are required:

- Arduino Leonardo
- 5 LEDs (Red, Orange, Yellow, Green, Blue) with resistors
- 1µF capacitor
- Phototransistor
- Operational amplifier
- Resistors: 470Ω, 8.2kΩ, 10kΩ, 22kΩ, 82kΩ
- Cylindrical light shield (black cardboard for instance)
- Colored cards: white, red, orange, yellow, green, blue, black

For detailed circuit design, refer to the **Circuit Schematic** section in the provided documentation.

---

## Software Requirements

- **Arduino IDE**: To upload the control code to the Arduino Leonardo.
- **MATLAB**: For data normalization, hue calculation, and result interpretation.

The repository includes:

- **`main.ino`**: Arduino code for controlling LEDs, reading sensor data, and generating output.
- **`main.m`**: MATLAB script for processing the output from Arduino and determining the color.

---

## How It Works

1. **Hardware Setup**:
   - The sample is placed under a cylindrical light shield to prevent external light interference.
   - LEDs sequentially illuminate the sample, and a phototransistor records the reflected light.

2. **Data Collection**:
   - The Arduino code calculates the time taken for a capacitor to charge under each LED's light.
   - These times are sent to the Serial Monitor.

3. **Data Processing**:
   - MATLAB normalizes the raw data using the white reference card.
   - It removes brightness and saturation effects, focusing solely on hue.
   - Euclidean distances between the sample and reference colors determine the closest match.

---

## Usage Instructions

### Arduino Setup
1. Connect the circuit as described in the documentation.
2. Upload the `main.ino` file to the Arduino using the Arduino IDE.
3. Open the Serial Monitor to follow the calibration and measurement instructions.

### MATLAB Processing
1. Copy the calibration (white card) vector and the unknown sample vector from the Serial Monitor.
2. Run the `main.m` script in MATLAB.
3. Input the copied vectors when prompted. The script will output the closest matching color.

---

## Example Results

Here are some example outputs from the project:

- **Input Vectors**:
  - White Card: `[55, 363, 1354, 1174, 7]`
  - Unknown Card: `[56, 299, 1650, 2475, 39]`

- **Output**:
  ```
  norm_red = 0.6215
  norm_orange = 0.1688
  norm_yellow = 0.5337
  norm_green = 1.9202
  norm_blue = 2.1576
  norm_black = 1.3923
  ```

The smallest norm corresponds to **orange**, indicating the sample is closest to this color.

---

## License

This project is licensed under the **GNU General Public License v3.0**. See the [LICENSE](LICENSE) file for details.