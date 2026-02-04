
# ♟️ ESP32-Based Digital Chess Clock

A feature-rich digital chess clock built using the **ESP32 microcontroller**, **dual OLED displays**, and **five tactile buttons**. This project supports increment timing, intuitive player switching, and modular, readable C++ code—perfect for hobbyists and embedded systems learners.

## 🧠 Features

- ⏱️ Dual player timers with independent countdowns  
- ➕ Increment time support after each move  
- 🧭 Intuitive configuration interface with Mode, Increment, and Decrement buttons  
- 📟 Dual SSD1306 OLED Displays (128x64)  
- 🔄 Real-time player switching with hardware interrupts  
- 🧱 Breadboard-friendly prototype

## 🔧 Hardware Requirements

| Component                   | Quantity |
|----------------------------|----------|
| ESP32 Dev Board            | 1        |
| SSD1306 OLED (I2C, 128x64) | 2        |
| Push Buttons               | 5        |
| 4.7kΩ Resistors            | 5        |
| Breadboard & Jumper Wires  | As needed |
| USB Cable (for programming) | 1        |


## 💡 How It Works

1. **Setup Mode**: On boot, configure initial times and increment using Mode, Increment, and Decrement buttons.
2. **Starting the Game**: The player with black presses their button to start the opponent's timer.
3. **Switching Turns**: Players press their button after each move—automatically pausing their clock and starting the opponent's.
4. **Ending**: Game ends when one player's timer reaches zero.

## 🧱 Software Architecture

- `main.ino` – Initializes setup and handles main loop.
- `ChessClock.h/.cpp` – Core functionality, display logic, and button handling.
- `ChessClockGlobals.h` – Shared global variables and flags.
- `ChessClockTimer.cpp` – Timer countdown, increment handling, and state management.


## 🚧 Challenges Faced

- Handling interrupts and debouncing button presses reliably
- Managing two timers concurrently without drift
- Preventing flickering during OLED updates
- Organizing modular code for scalability and maintainability

## 📹 Demonstration
https://youtu.be/Bvfug5DLUNo

## 📘 License
This project is open-source under the MIT License. Feel free to use, modify, and share!
