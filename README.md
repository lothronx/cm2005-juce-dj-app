# 🎧 Otodecks - JUCE DJ Application

![JUCE](https://img.shields.io/badge/JUCE-Framework-blue?style=for-the-badge&logo=juce)
![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-Build-064F8C?style=for-the-badge&logo=cmake)
![DSP](https://img.shields.io/badge/Digital%20Signal%20Processing-Audio-green?style=for-the-badge)
![OOP](https://img.shields.io/badge/Object%20Oriented-Programming-orange?style=for-the-badge)

A feature-rich DJ application built with JUCE framework as part of my Object-Oriented Programming coursework. This project demonstrates advanced C++ programming, real-time audio processing, and modern GUI design principles.

## 🎬 Live Demo

<div align="center">

[![Watch Demo](https://img.shields.io/badge/Watch-Demo-red?style=for-the-badge&logo=youtube)](https://www.youtube.com/watch?v=2rwMRsjn-B4&ab_channel=WuYue)

[![Watch Demo](Report/0.png)](https://www.youtube.com/watch?v=2rwMRsjn-B4&ab_channel=WuYue)

</div>

## ✨ Features

### 🎵 Core DJ Functionality

- **Dual Deck System** - Load and play two audio tracks simultaneously
- **Real-time Mixing** - Crossfader for seamless track blending
- **Speed Control** - Variable playback speed (-50% to +50%)
- **Loop Controls** - Seamless track looping capabilities

### 🎛️ Professional Audio Tools

- **3-Band Equalizer** - Bass, Mid, and Treble frequency control using IIR filters
- **VU Meters** - Real-time volume level visualization
- **Interactive Waveform** - Visual track representation with position control
- **Jog Wheels** - Vinyl-style turntable simulation

### 🎨 Modern Interface

- **Custom Look & Feel** - Professional DJ software aesthetic
- **Responsive Design** - Intuitive layout with visual feedback
- **Color-coded Decks** - Sky blue and salmon theme for easy identification
- **Toggle Buttons** - Visual state indicators for all controls

## 🛠️ Technical Skills Demonstrated

### Object-Oriented Programming

- **Encapsulation** - Modular component design with clear interfaces
- **Inheritance** - Custom GUI components extending JUCE base classes
- **Polymorphism** - Event handling and observer pattern implementation
- **Design Patterns** - Observer/Listener pattern for state management

### Audio Programming

- **Digital Signal Processing** - Real-time audio filtering and manipulation
- **Audio Pipeline** - Multi-layered audio source architecture
- **Real-time Processing** - Low-latency audio callback implementation
- **DSP Filters** - IIR filter implementation for EQ functionality

### C++ Advanced Concepts

- **Modern C++** - Smart pointers, RAII, and memory management
- **Event-Driven Programming** - Asynchronous event handling
- **Template Programming** - JUCE template-based DSP processors
- **Multi-threading** - Audio thread safety and GUI updates

### GUI Development

- **Custom Rendering** - OpenGL-accelerated graphics programming
- **Component Architecture** - Hierarchical GUI component system
- **Event Handling** - Mouse, keyboard, and timer-based interactions
- **State Management** - Reactive UI updates based on audio state

## 🏗️ Architecture

```
MainComponent
├── DeckGUI (Left & Right)
│   ├── WaveformDisplay
│   ├── JogWheel
│   ├── TransportControls
│   ├── SpeedSlider
│   ├── Knobs (EQ)
│   └── VUMeter
├── Crossfader
└── CustomLookAndFeel
```

## 🚀 Getting Started

### Prerequisites

- JUCE Framework 6.0+
- C++17 compatible compiler
- CMake 3.15+

### Building

```bash
git clone https://github.com/yourusername/otodecks.git
cd otodecks
mkdir build && cd build
cmake ..
make
```

### Running

```bash
./Otodecks
```

## 📚 Learning Outcomes

This project enhanced my understanding of:

- **Real-time Audio Programming** - Working with audio buffers, sample rates, and DSP
- **Advanced C++ Patterns** - Observer pattern, RAII, and template metaprogramming
- **GUI Architecture** - Component-based design and custom rendering
- **Software Engineering** - Modular design, code organization, and documentation
- **Digital Signal Processing** - Filter design, frequency domain manipulation

## 🎯 Project Highlights

- **Custom DSP Pipeline** - Implemented 3-band EQ using IIR filters with proper coefficient calculation
- **Real-time Visualization** - VU meters and jog wheels with smooth 60fps updates
- **Professional UX** - Interface inspired by industry-standard DJ software (VirtualDJ)
- **Modular Codebase** - Clean separation of concerns with reusable components

## 📁 File Structure

```
├── Source/
│   ├── Audio/
│   │   └── DJAudioPlayer.cpp/h     # Core audio processing
│   ├── GUI/
│   │   ├── DeckGUI.cpp/h           # Main deck interface
│   │   ├── WaveformDisplay.cpp/h   # Audio visualization
│   │   ├── JogWheel.cpp/h          # Turntable simulation
│   │   ├── Knobs.cpp/h             # EQ controls
│   │   └── VUMeter.cpp/h           # Volume visualization
│   └── MainComponent.cpp/h         # Application entry point
├── Report/                         # Detailed project documentation
└── CMakeLists.txt                  # Build configuration
```

---

### 🔗 Connect with me

[![LinkedIn](https://img.shields.io/badge/LinkedIn-yuewuxd-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/yuewuxd/)

---

_This project showcases the practical application of Object-Oriented Programming principles in creating a professional-grade audio application._
