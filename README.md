# ESP Bill Checker

An ESP32-based project for monitoring electricity prices in real time using online API data.

The purpose of the project is to explore how low-cost IoT hardware can be used to visualize electricity prices and provide simple real-time feedback using LEDs.

The ESP32 connects to WiFi, retrieves electricity pricing information from an external API, and changes LED colors depending on the current electricity cost.

The project was mainly created as a learning and experimentation project involving:
- ESP32 development
- WiFi communication
- REST APIs
- IoT systems
- real-time data handling
- LED control and automation

The implementation is intentionally kept relatively simple and readable for experimentation and further development.

---

# Features

- Real-time electricity price fetching
- ESP32 WiFi connectivity
- LED color indication system
- Automatic API polling
- Price-based visual feedback
- PlatformIO project structure
- Serial monitor debugging output

---

# Technologies

- ESP32
- PlatformIO
- Arduino Framework
- C++
- WiFi APIs

---

# How It Works

The ESP32 periodically fetches electricity price data from an online API.

Depending on the price level:
- Low electricity price → LED turns blue
- High electricity price → LED turns red

This allows quick visual monitoring of electricity cost levels without opening an app or website.

---

# Example Device States

## High Electricity Price (Red)

```md
![High Price State](images/high_price_red.jpg)
```

## Low Electricity Price (Blue)

```md
![Low Price State](images/low_price_blue.jpg)
```

Place your device images inside an `images/` folder in the repository.

Example structure:

```text
images/
├── high_price_red.jpg
└── low_price_blue.jpg
```

---

# Running the Project

## Requirements

- ESP32 board
- PlatformIO
- USB connection
- WiFi network

---

## Build and Upload

```bash
pio run
pio run --target upload
```

---

## Serial Monitor

```bash
pio device monitor
```

---

# Repository Structure

```text
src/
include/
lib/
platformio.ini
```

---

# Project Goal

The goal of the project is not to create a finished commercial product, but rather to explore:
- IoT communication
- embedded systems
- API integration
- simple real-time automation
- hardware/software interaction

---

# Notes

This project is experimental and continues to evolve as new ideas and features are tested.
