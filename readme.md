# Embedded Systems Repository
By Alex Kondracki, Fall Quarter 2023

## Table of Contents
- [Embedded Systems Repository](#embedded-systems-repository)
  - [Table of Contents](#table-of-contents)
  - [Intro](#intro)
  - [Phase A](#phase-a)
  - [Phase B](#phase-b)
  - [Phase D](#phase-d)

## Intro
This repository is a collection of projects done for an Embedded Systems class at the University of Denver, CO in Fall 2023. Phase C does not exist. The professor was [Goncalo Martins](https://github.com/gfm16617)

Phase A and B consist of making a Kitchen Timer, Phase D is a realtime audio visualizer.

The projects are structured in the following way.

```
./PHASE #
├───Note
├───PCB_Design
└───uP_code
```

Notes contains parts lists, schematics, block diagrams, photos, images, and reports depending on the phase.
PCB_Design contains the KiCAD project folder for the PCB. It also contains files which can be sent to companies for manufacturing.
uP_code contains the code for the project. In phase D it contains the STM32 project folder and the code will be found in ./Core/Src/ relative to that folder.

## Phase A
Phase A involves making a Kitchen Timer as a PCB shield for the Arduino. The timer is interrupt driven with Button 1 incrementing and Button 2 starting and stopping the item. The PCB shield used was designed by the Professor.

![Phase A Top](https://github.com/alexk-school/ENCE-3220_Class_2023/blob/main/Phase%20A/Notes/phaseA_1.jpg?raw=true)

![Phase A Bottom](https://github.com/alexk-school/ENCE-3220_Class_2023/blob/main/Phase%20A/Notes/phaseA_2.jpg?raw=true)


## Phase B
Phase B involved making a Wireless Kitchen Timer using an ATmega, and ESP32. The PCB was designed and soldered by me. The ATmega and ESP32 communicate via UART. The ATmega manages the timer using interrupt flags. A while loop checks for the status and runs a command based on the flag. The ESP32 (and it's hosted webpage) was coded by the Professor.

![Phase B](https://github.com/alexk-school/ENCE-3220_Class_2023/blob/main/Phase%20B/Notes/phaseB_1.jpg?raw=true)

Note the ESP32 is not attached.

## Phase D
Phase D involved making a realtime audio visualizer using a MEMS microphone on a STM32 board and a 1 inch I2C OLED Display. The data on the MEMS microphone is converted from PDM to PCM and the PDM data is graphed on the OLED display using an I2C library from [4ilo](https://github.com/4ilo/ssd1306-stm32HAL)

![Phase D Setup](https://github.com/alexk-school/ENCE-3220_Class_2023/blob/main/Phase%20D/Notes/Photos/setup.jpg?raw=true)

![Phase D Impulse](https://github.com/alexk-school/ENCE-3220_Class_2023/blob/main/Phase%20D/Notes/Photos/impulse.gif?raw=true)

