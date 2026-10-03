# Ultra Trend

A sleek black-and-white animated dashboard prototype built in C++ with SFML.

It simulates an AI trend intelligence app that highlights what people are searching and doing each day.

## Features
- Minimal black-and-white interface
- Smooth motion and animated UI panels
- Trend cards with real-time-looking momentum indicators
- AI insight panel summarizing daily activity
- CMake build configuration

## Requirements
- C++17
- CMake 3.16+
- SFML 2.6+

## Debian / Ubuntu
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake libsfml-dev
```

## Build
```bash
cmake -S . -B build
cmake --build build
```

## Run
```bash
./build/ultra_trend
```
