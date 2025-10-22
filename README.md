# 🐾 Smart Pet Feeder Project
Author: Heera Arora 
1st Year UTS Software Engineering

An automated pet feeder system that dispenses food at set intervals, detects pet presence, and logs environmental data (temperature and humidity) using STM32 and Arduino components.

## 🚀 Overview

This project integrates two main systems:
- **Arduino subsystem:** Controls the feeder servo and buzzer.
- **STM32 subsystem:** Logs temperature and humidity data from a DHT11 sensor to an SD card.

## 🧠 Features

- Automatic feeding mechanism using a servo motor.
- Buzzer notifications to signal feeding time.
- Pet presence detection via analog sensor input.
- Environmental monitoring (temperature and humidity).
- Data logging to SD card using FATFS.

## 🧰 Components Used

| Component | Description |
|------------|-------------|
| Arduino Uno | Servo & buzzer control |
| STM32F4 | SD card data logging |
| Servo Motor | Controls feeder lid |
| DHT11 | Measures temperature and humidity |
| LDR/IR Sensor | Detects pet presence |
| Buzzer | Audible alert |
| SD Card Module | Data storage |
PetFeeder/
├── arduino/
│   ├── buzzer_test.ino
│   ├── feeder_control.ino
│   └── README.md
├── stm32/
│   ├── main.c
│   ├── ff.c
│   ├── ff.h
│   ├── diskio.c
│   ├── diskio.h
│   └── README.md
├── LICENSE
├── README.md
└── images/
    ├── schematic.png
    ├── wiring_diagram.png
    └── pet_feeder_demo.jpg

