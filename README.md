# 🤖 ESP32 AI-Powered Air Quality Monitoring System

> **Advanced air quality monitoring system with integrated Google Gemini AI chatbot featuring voice calls, video calls, image analysis, and real-time sensor data visualization.**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![ESP32](https://img.shields.io/badge/ESP32-DevKit-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Gemini AI](https://img.shields.io/badge/Gemini-2.0%20Flash-orange.svg)](https://ai.google.dev/)
[![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D.svg)](https://www.arduino.cc/)

---

## 🌟 Live Demo

**🌐 Live Website:** [air-monitoring-esp32.netlify.app](https://air-monitoring-esp32.netlify.app/)

Access the full AI chatbot interface with text, voice, video, and image capabilities - no hardware required!

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Hardware Requirements](#-hardware-requirements)
- [Software Requirements](#-software-requirements)
- [Installation](#-installation)
- [Configuration](#-configuration)
- [Usage](#-usage)
- [AI Capabilities](#-ai-capabilities)
- [Safety Thresholds](#-safety-thresholds)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)
- [Contact](#-contact)
- [License](#-license)

---

## 🎯 Overview

This project integrates **Google Gemini AI** into an **ESP32-based air quality monitoring system**, creating an intelligent IoT device that can:

- Monitor real-time CO2 levels and air quality
- Control fans and alert systems automatically
- Interact via AI chatbot with voice, video, and text
- Analyze images and provide intelligent insights
- Operate standalone on ESP32 hardware or via web interface

**Key Innovation:** This is one of the first open-source projects to successfully integrate Gemini 2.0 Flash AI directly into ESP32 hardware with full multimodal capabilities.

---

## ✨ Features

### 🎙️ AI Communication
- **💬 Text Chat** - Natural language conversations with AI
- **📷 Image Analysis** - Upload and analyze images with AI vision
- **🎤 Voice Input** - Speech-to-text for hands-free messaging
- **📞 Voice Calls** - Real-time voice conversations with AI
- **📹 Video Calls** - Live video with AI visual analysis
- **🔄 Camera Switching** - Front/back camera support on mobile

### 📊 Air Quality Monitoring
- **Real-time CO2 measurement** (PPM)
- **Air quality classification** (Good/Fair/Poor/Bad)
- **Automatic fan control** (PWM speed regulation)
- **Audio alerts** with buzzer patterns
- **24-hour data logging** (1440 data points)
- **Web-based dashboard**

### 🔧 Technical Features
- **Ultra-responsive design** - Works on all screen sizes (320px to 4K)
- **Persistent chat history** - Saved in browser localStorage
- **Offline fallback** - Access Point mode when WiFi unavailable
- **Low memory footprint** - Optimized for ESP32 constraints
- **Secure HTTPS** - Compatible with Gemini API requirements

---

## 🛠️ Hardware Requirements

### Essential Components

| Component | Description | Quantity |
|-----------|-------------|----------|
| **ESP32 DevKit** | Main microcontroller board | 1 |
| **MQ-135 Sensor** | Air quality/CO2 sensor | 1 |
| **12V DC Fan** | Ventilation control | 1 |
| **L298N Motor Driver** | PWM fan speed control | 1 |
| **Buzzer** | Audio alerts (5V active) | 1 |
| **USB Cable** | Micro-USB or Type-C (data) | 1 |
| **Breadboard** | Prototyping | 1 |
| **Jumper Wires** | Connections | 20+ |
| **Power Supply** | 5V 2A for ESP32 + 12V for fan | 1 |

### Optional Components
- **DHT22 Sensor** - Temperature and humidity monitoring
- **OLED Display** - Local data visualization
- **SD Card Module** - Extended data logging

### Wiring Diagram

```
ESP32 DevKit Pinout:
├── GPIO34 (ADC1_6) ──> MQ-135 Analog Out
├── GPIO25 (DAC1)   ──> Buzzer Signal
├── GPIO26 (PWM)    ──> L298N Enable (Fan Speed)
├── GPIO27          ──> L298N IN1 (Fan Direction)
├── GPIO14          ──> L298N IN2 (Fan Direction)
├── 5V              ──> MQ-135 VCC, Buzzer VCC
└── GND             ──> All GNDs

L298N Motor Driver:
├── OUT1, OUT2      ──> 12V DC Fan
├── +12V            ──> External 12V power supply
└── GND             ──> Common ground with ESP32
```

---

## 💻 Software Requirements

### Required Software

1. **Arduino IDE** (v2.0 or later)
   - Download: [arduino.cc/en/software](https://www.arduino.cc/en/software)

2. **CP2102 USB Driver** (Silicon Labs)
   - Required for ESP32 USB communication
   - Download: [silabs.com/developers/usb-to-uart-bridge-vcp-drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

3. **ESP32 Board Package**
   - Install via Arduino IDE Board Manager
   - Version: **2.0.14** (recommended - avoid 2.0.15+ for motor driver compatibility)

### Arduino IDE Setup Video Tutorial

📺 **Complete Arduino IDE + ESP32 Setup Guide:**  
[YouTube Playlist - ESP32 Tutorials](https://www.youtube.com/playlist?list=PLrZbkNpNVSwwkA3nnQ5o0Pg8w6GCSDgYA)

**Topics Covered:**
1. Installing Arduino IDE
2. Installing CP2102 USB drivers
3. Adding ESP32 board support
4. Configuring COM ports
5. Setting up WiFi connection
6. Uploading your first program

---

## 📥 Installation

### Step 1: Install Arduino IDE

1. Download Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Install for your operating system (Windows/Mac/Linux)
3. Launch Arduino IDE

### Step 2: Install CP2102 Driver

1. Download driver from [Silicon Labs website](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
2. Extract and run installer:
   - **Windows:** `CP210x_Windows_Drivers.exe`
   - **Mac:** `CP210x_VCP_Mac.dmg`
   - **Linux:** Follow included instructions
3. Restart your computer

### Step 3: Add ESP32 Board Support

1. Open Arduino IDE
2. Go to **File → Preferences**
3. In "Additional Board Manager URLs" add:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Click **OK**
5. Go to **Tools → Board → Board Manager**
6. Search for "ESP32"
7. Install **"esp32 by Espressif Systems"** version **2.0.14** ⚠️
   - ⚠️ **Important:** Do NOT use version 2.0.15+ (motor driver compatibility issues)

### Step 4: Configure Board Settings

1. Connect ESP32 to computer via USB
2. Go to **Tools → Board** and select:
   - **"ESP32 Dev Module"**
3. Go to **Tools → Port** and select:
   - Windows: `COM3`, `COM4`, etc.
   - Mac: `/dev/cu.usbserial-XXXX`
   - Linux: `/dev/ttyUSB0`
4. Go to **Tools → Partition Scheme** and select:
   - **"Huge APP (3MB No OTA/1MB SPIFFS)"**
   - ⚠️ This is crucial for web interface storage!

### Step 5: Upload the Code

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/esp32-air-monitoring-ai.git
   cd esp32-air-monitoring-ai
   ```

2. Open `air_monitoring_esp32.ino` in Arduino IDE

3. **Configure WiFi credentials** (lines 7-8):
   ```cpp
   const char* ssid = "YOUR_WIFI_NAME";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
   ⚠️ **Important:** Use **2.4GHz WiFi only** (ESP32 doesn't support 5GHz)

4. Click **Upload** button (→) or press `Ctrl+U`

5. Wait for upload to complete (typically 30-60 seconds)

6. Open **Serial Monitor** (`Ctrl+Shift+M`) at **115200 baud**

7. You should see:
   ```
   === ESP32 AI Chatbot Starting ===
   Connecting to WiFi....
   WiFi connected!
   IP address: 192.168.1.XXX
   Web server started!
   ```

---

## ⚙️ Configuration

### WiFi Setup

#### Option 1: Home WiFi (Recommended)

Edit lines 7-8 in the Arduino code:
```cpp
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";
```

#### Option 2: Mobile Hotspot

1. Enable mobile hotspot on your phone
2. Set to **2.4GHz frequency**
3. Use hotspot name and password in code

#### Option 3: Access Point Mode (Offline)

If WiFi connection fails after 10 seconds, ESP32 automatically creates its own network:
- **Network Name:** `ESP32_AI_Chatbot`
- **Password:** `chatbot123`
- **IP Address:** `192.168.4.1`

### Gemini AI API Key

1. Visit [Google AI Studio](https://aistudio.google.com/)
2. Sign in with Google account
3. Click **"Get API Key"**
4. Copy your API key
5. In the web interface, click **Settings**
6. Paste your API key and click **Save**

**Note:** A default API key is included for testing, but it's recommended to use your own.

### Voice & Speech Settings

Available in the web interface **Settings** panel:
- **Voice Selection:** Choose from 50+ TTS voices
- **Speech Rate:** 0.5x to 2.0x speed
- **Auto-speak:** Automatically read AI responses

---

## 🚀 Usage

### Accessing the Interface

After uploading code and connecting to WiFi:

1. **Find your ESP32's IP address:**
   - Check Serial Monitor (115200 baud)
   - Or check your router's connected devices
   - Example: `192.168.1.105`

2. **Open web browser and navigate to:**
   ```
   http://192.168.1.105
   ```

3. **You'll see the home page with:**
   - System status (CO2, Air Quality, Fan, Buzzer)
   - Feature list
   - "Launch AI Chatbot" button

4. **Click "Launch AI Chatbot"** to access full AI interface

### Using the AI Chatbot

#### Text Chat
1. Type your message in the input box
2. Press `Enter` or click send button (➤)
3. AI responds with intelligent answers about air quality or general topics

**Example queries:**
- "What's my current air quality?"
- "Is 600 PPM dangerous?"
- "How do I improve ventilation?"
- "Explain the safety thresholds"

#### Image Analysis
1. Click camera icon (📷)
2. Select image from device
3. Optionally add text description
4. Send to AI for analysis

**Use cases:**
- Analyze room layout for ventilation
- Identify air quality issues visually
- Get setup recommendations

#### Voice Input
1. Click microphone icon (🎤)
2. Speak your message
3. Speech converts to text automatically
4. Edit if needed, then send

#### Voice Calls
1. Click **"📞 Call AI"** button
2. Grant microphone permission
3. AI greets you and starts listening
4. Have a natural conversation
5. Click **"📞 End Call"** when done

**Call features:**
- Real-time speech recognition
- Natural conversation flow
- Mute/unmute button
- Call transcript
- Copy transcript
- Text-to-speech playback

#### Video Calls
1. Click **"📹 Video Call"** button
2. Grant camera and microphone permissions
3. AI can see and hear you
4. Use camera controls:
   - 🎤 Mute/unmute microphone
   - 📹 Turn camera on/off
   - 🔄 Switch front/back camera (mobile)
   - 📸 Capture and analyze what you're showing
   - 📋 Copy transcript
   - 🔊 Read transcript aloud

**Video call features:**
- Automatic visual analysis every 30 seconds
- Manual "Show AI what I'm doing" button
- Real-time conversation with visual context
- Call duration timer
- Complete transcript

---

## 🧠 AI Capabilities

### Gemini 2.0 Flash Integration

This project uses **Google Gemini 2.0 Flash**, the latest multimodal AI model:

**Model Features:**
- ⚡ **Fast responses** (optimized for real-time interactions)
- 🖼️ **Vision capabilities** (image analysis)
- 🎤 **Audio processing** (via Web Speech API)
- 📊 **Context awareness** (remembers conversation history)
- 🌍 **Multilingual support** (100+ languages)

### AI Instructions

The AI is configured with specialized knowledge:

```
Current System Context:
├── Air Quality Status: Real-time PPM readings
├── Fan Control: Speed and mode (auto/manual)
├── Buzzer Patterns: Alert status
├── Safety Thresholds: Predefined danger levels
└── Hardware Setup: ESP32 DevKit + MQ-135

AI Capabilities:
├── Answer air quality questions
├── Explain safety thresholds
├── Provide ventilation recommendations
├── Troubleshoot hardware issues
├── Analyze images for air quality factors
└── General conversation on any topic
```

### Conversation Examples

**Air Quality Monitoring:**
```
User: What's my current CO2 level?
AI: Your current CO2 level is 350 PPM, which is in the "Good" 
range. This is normal indoor air quality and safe for prolonged 
exposure. Your fan is running at 25% in auto mode.
```

**Safety Inquiry:**
```
User: Is 750 PPM dangerous?
AI: 750 PPM is in the WARNING range. While not immediately 
dangerous, it indicates poor air quality. I recommend increasing 
ventilation or moving to a well-ventilated area. Your system 
should be alerting you with buzzer pattern 2.
```

**Hardware Help:**
```
User: How do I wire the MQ-135 sensor?
AI: Connect the MQ-135 as follows:
- VCC to ESP32 5V pin
- GND to ESP32 GND pin  
- Analog Out (A0) to ESP32 GPIO34 (ADC1_6)
Make sure the sensor is powered for 24-48 hours before first 
use for accurate readings.
```

**Image Analysis:**
```
User: [uploads photo of room] "Is this room well ventilated?"
AI: Based on the image, I can see a closed room with one small 
window. For better ventilation, I recommend: 1) Opening the 
window, 2) Adding a fan near the window for air circulation, 
3) Keeping the door slightly open for cross-ventilation. Your 
current CO2 is 520 PPM which is elevated for this room size.
```

---

## ⚠️ Safety Thresholds

### CO2 Level Classifications

| PPM Range | Status | Icon | Description | Action |
|-----------|--------|------|-------------|--------|
| **< 250** | Excellent | 🟢 | Outdoor-level fresh air | None needed |
| **250-500** | Good | 🟢 | Normal indoor levels | Monitor regularly |
| **500-750** | ⚠️ CAUTION | 🟡 | Elevated, ventilation recommended | Open windows, increase fan |
| **750-1000** | ⚠️ WARNING | 🟠 | Poor air quality | Immediate ventilation required |
| **> 1000** | 🚨 DANGER | 🔴 | Hazardous levels | Evacuate room, maximum ventilation |

### Automated Responses

The system automatically responds to CO2 levels:

```cpp
Air Quality Status:
├── Good (< 500 PPM)
│   ├── Fan: Auto mode (25-50%)
│   └── Buzzer: Silent
│
├── Caution (500-750 PPM)
│   ├── Fan: Auto mode (50-75%)
│   └── Buzzer: Pattern 1 (slow beep)
│
├── Warning (750-1000 PPM)
│   ├── Fan: Auto mode (75-100%)
│   └── Buzzer: Pattern 2 (medium beep)
│
└── Danger (> 1000 PPM)
    ├── Fan: Maximum speed (100%)
    └── Buzzer: Pattern 3 (rapid alarm)
```

### Health Effects Reference

**Extended Exposure to Elevated CO2:**

| PPM | Symptoms |
|-----|----------|
| 600-1000 | Drowsiness, poor concentration |
| 1000-2500 | Headaches, fatigue, reduced cognitive function |
| 2500-5000 | Increased heart rate, nausea |
| > 5000 | Serious health risk, oxygen deprivation |

---

## 🔧 Troubleshooting

### ESP32 Not Detected

**Problem:** Computer doesn't recognize ESP32

**Solutions:**
1. ✅ Install CP2102 USB driver
2. ✅ Try different USB cable (must be data cable, not charge-only)
3. ✅ Try different USB port
4. ✅ Check Device Manager (Windows) or `ls /dev/tty*` (Mac/Linux)
5. ✅ Press and hold **BOOT** button while uploading

### Upload Failed / Timeout

**Problem:** Code won't upload to ESP32

**Solutions:**
1. ✅ Select correct board: **ESP32 Dev Module**
2. ✅ Select correct COM port
3. ✅ Lower upload speed: Tools → Upload Speed → **115200**
4. ✅ Hold **BOOT** button during "Connecting..." message
5. ✅ Press **EN** (reset) button after "Connecting..." appears

### WiFi Won't Connect

**Problem:** ESP32 can't connect to WiFi

**Solutions:**
1. ✅ Verify SSID and password are correct
2. ✅ Use **2.4GHz WiFi only** (not 5GHz)
3. ✅ Check WiFi signal strength (move closer to router)
4. ✅ Disable MAC address filtering on router
5. ✅ Try mobile hotspot instead
6. ✅ Use Access Point mode (automatic fallback)

### Speech Recognition Errors

**Problem:** "Network error" in speech recognition

**Solutions:**
1. ✅ Requires **stable internet connection**
2. ✅ Use **HTTPS** (required for Web Speech API)
3. ✅ Grant microphone permissions in browser
4. ✅ Use **Chrome, Edge, or Safari** (Firefox not fully supported)
5. ✅ Check firewall isn't blocking microphone

### Camera Not Working (Video Calls)

**Problem:** Camera not detected or permission denied

**Solutions:**
1. ✅ Grant camera and microphone permissions
2. ✅ Use **HTTPS** (required for getUserMedia API)
3. ✅ Close other apps using camera (Zoom, Skype, etc.)
4. ✅ Restart browser
5. ✅ Check browser camera settings

### AI Not Responding

**Problem:** Chatbot doesn't reply or gives errors

**Solutions:**
1. ✅ Verify API key in Settings
2. ✅ Check internet connection
3. ✅ Ensure not exceeding API rate limits
4. ✅ Check browser console for errors (F12)
5. ✅ Try refreshing the page

### Sensor Reading Issues

**Problem:** MQ-135 shows incorrect or unstable readings

**Solutions:**
1. ✅ **Preheat sensor** for 24-48 hours before first use
2. ✅ Check wiring connections
3. ✅ Verify 5V power supply
4. ✅ Calibrate in fresh air (outdoor reading should be ~400 PPM)
5. ✅ Replace sensor if damaged

### Memory / Upload Size Errors

**Problem:** "Sketch too big" or memory errors

**Solutions:**
1. ✅ Select partition scheme: **Huge APP (3MB No OTA/1MB SPIFFS)**
2. ✅ Update to ESP32 board version **2.0.14**
3. ✅ Clear Arduino IDE cache: Delete `AppData/Local/Arduino15/tmp`

---

## 🤝 Contributing

We welcome contributions! Here's how you can help:

### Ways to Contribute

1. **🐛 Report Bugs**
   - Open an issue with detailed description
   - Include error messages and screenshots
   - Specify ESP32 board version and Arduino IDE version

2. **💡 Suggest Features**
   - Open an issue labeled "enhancement"
   - Describe use case and benefits
   - Provide examples if possible

3. **📝 Improve Documentation**
   - Fix typos or unclear instructions
   - Add translations
   - Create video tutorials

4. **💻 Submit Code**
   - Fork the repository
   - Create feature branch: `git checkout -b feature-name`
   - Make changes and test thoroughly
   - Commit: `git commit -m "Add feature"`
   - Push: `git push origin feature-name`
   - Open Pull Request

### Development Guidelines

- **Code Style:** Follow Arduino C++ conventions
- **Testing:** Test on actual ESP32 hardware
- **Documentation:** Update README for new features
- **Comments:** Add clear code comments
- **Commit Messages:** Use descriptive messages

---

## 📞 Contact

**Developer:** HNK Horizon

**Social Media:**
- 🐦 **Twitter:** [@HnkHorizon](https://twitter.com/HnkHorizon)
- 📱 **TikTok:** [@codingfever](https://tiktok.com/@codingfever)
- 📺 **YouTube:** [@HNK2005](https://youtube.com/@HNK2005)
- 📷 **Instagram:** [@hhnk.3693](https://instagram.com/hhnk.3693)
- 📧 **Email:** hhnk3693@gmail.com

**Project Links:**
- 🌐 **Live Demo:** [air-monitoring-esp32.netlify.app](https://air-monitoring-esp32.netlify.app/)
- 📺 **Setup Tutorials:** [YouTube Playlist](https://www.youtube.com/playlist?list=PLrZbkNpNVSwwkA3nnQ5o0Pg8w6GCSDgYA)
- 💻 **GitHub:** [This Repository](https://github.com/HorizonHnk/ESP32-AI-Powered-Air-Quality-Monitoring-System/)

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2025 HNK Horizon

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 🙏 Acknowledgments

- **Google Gemini AI** - For providing the powerful Gemini 2.0 Flash API
- **Espressif Systems** - For the ESP32 platform and Arduino support
- **Arduino Community** - For libraries and documentation
- **Contributors** - Everyone who has helped improve this project

---

## 🌟 Star History

If you find this project helpful, please consider giving it a ⭐ star on GitHub!

---

## 📊 Project Stats

- **Lines of Code:** ~2,500 (Arduino C++)
- **HTML/CSS/JS:** ~3,500 lines
- **Features:** 20+ including AI, IoT, sensors
- **Supported Devices:** All modern browsers, ESP32 boards
- **API Calls:** Optimized for Gemini 2.0 Flash
- **Response Time:** < 2 seconds average

---

## 🔮 Future Roadmap

- [ ] **MQTT Integration** for IoT cloud platforms
- [ ] **Mobile App** (Flutter) for remote monitoring
- [ ] **Multiple Sensor Support** (temperature, humidity, PM2.5)
- [ ] **Historical Data Graphs** with Chart.js
- [ ] **Email/SMS Alerts** for critical conditions
- [ ] **Voice Commands** ("Alexa, what's my air quality?")
- [ ] **Machine Learning** predictions for air quality trends
- [ ] **Solar Power Option** for off-grid operation

---

## 📚 Additional Resources

### Tutorials
- [ESP32 Getting Started Guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [MQ-135 Sensor Calibration](https://lastminuteengineers.com/mq135-gas-sensor-arduino-tutorial/)
- [Google Gemini AI Documentation](https://ai.google.dev/docs)

### Related Projects
- [ESP32 Weather Station](https://github.com/yourusername/esp32-weather)
- [Arduino Air Quality Monitor](https://github.com/yourusername/arduino-air-monitor)
- [IoT Home Automation](https://github.com/yourusername/iot-home)

---

<div align="center">

**Made with ❤️ by HNK Horizon**

⭐ **Star this repo** if you found it useful! ⭐

[Report Bug](https://github.com/yourusername/esp32-air-monitoring-ai/issues) · [Request Feature](https://github.com/yourusername/esp32-air-monitoring-ai/issues) · [Documentation](https://github.com/yourusername/esp32-air-monitoring-ai/wiki)

</div>
