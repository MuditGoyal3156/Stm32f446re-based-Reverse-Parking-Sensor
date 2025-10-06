# STM32 Ultrasonic Proximity Sensor

A real-time proximity sensor project using an STM32F446re microcontroller and an HC-SR04 ultrasonic sensor. The device measures distance and provides multi-level feedback through LEDs and a variable-rate buzzer. All peripherals are configured using direct register access (bare-metal) in C for maximum efficiency.

---

## Description

This project turns an STM32 development board into a smart and responsive distance-measuring tool. It continuously triggers an ultrasonic sensor, measures the pulse duration of the returning echo, and converts this time into a precise distance in centimeters.

The system provides immediate feedback to the user in three ways:

1.  **Visual Alert**: A set of three LEDs (Green, Yellow, Red) light up to indicate different distance ranges (far, medium, near).
2.  **Auditory Alert**: A piezo buzzer creates a "Geiger-counter" effect, with the beeping frequency increasing dramatically as an object gets closer.
3.  **Serial Data**: For debugging and data logging, the exact distance is streamed over UART to a connected computer.

The entire project is written in C, manipulating the microcontroller's registers directly without HAL or other abstraction layers. This makes it an excellent learning resource for understanding the low-level operation of STM32 peripherals like GPIO, Timers (for PWM), and UART.

---

## Features

* **Real-Time Measurement**: Uses the DWT cycle counter for precise microsecond-level timing.
* **Multi-Level Visual Feedback**: LEDs indicate different proximity zones.
* **Dynamic Auditory Feedback**: PWM-driven buzzer with a variable beep rate.
* **Serial Data Streaming**: UART output at 115200 baud for live monitoring.
* **Modular Code**: Clean, reusable drivers for the HC-SR04 sensor, UART, timing, and buzzer.
* **Bare-Metal Implementation**: No libraries or HAL, just direct register access.

---

## Hardware & Software Requirements

### Hardware
* STM32F446re Nucleo Development Board
* HC-SR04 Ultrasonic Distance Sensor
* 3x 5mm LEDs (Green, Yellow, Red)
* 1x Piezo Buzzer
* Breadboard and Jumper Wires

### Software
* An ARM GCC toolchain.
* An IDE like STM32CubeIDE or Keil.
* A serial terminal program (e.g., PuTTY, Tera Term, or Realterm).

---

## Wiring Guide

Connect the components to the STM32 board as follows:

| Component        | STM32 Pin |
| ---------------- | --------- |
| HC-SR04 **TRIG** | `PA1`     |
| HC-SR04 **ECHO** | `PA0`     |
| HC-SR04 **VCC** | `5V`      |
| HC-SR04 **GND** | `GND`     |
| Red LED Anode    | `PA5`     |
| Yellow LED Anode | `PA6`     |
| Green LED Anode  | `PA7`     |
| Buzzer Positive  | `PB6`     |

*Note: The Cathode of each LED should be connected to GND.*

---

## Setup & Installation

1.  **Clone the Repository**:
    ```bash
   git clone https://github.com/MuditGoyal3156/Stm32f446re-based-Reverse-Parking-Sensor.git
    ```

2.  **Open the Project**: Open the source code in your preferred STM32 development environment.

3.  **Compile & Flash**: Compile the project and flash the resulting binary to your STM32 board.

4.  **Connect and Run**: Power the board. To see the serial output, connect to the board via USB and open a terminal session with the following settings:
    * **Baud Rate**: `115200`
    * **Data Bits**: `8`
    * **Parity**: `None`
    * **Stop Bits**: `1`

---

## Future Improvements

* **Interrupt-Based Sensing**: Convert the blocking `while` loop for the ECHO pin to an EXTI interrupt to free up the CPU.
* **Signal Filtering**: Implement a moving average or median filter to smooth out noisy sensor readings.
* **Add an LCD/OLED Display**: Make the device standalone by showing the distance on a small screen.
* **User Controls**: Add buttons or a potentiometer to set custom alarm distances.
