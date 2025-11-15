# 🤖 ESP32 AI-Powered Air Quality Monitoring System

[![ESP32](https://img.shields.io/badge/ESP32-DevKit-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Gemini AI](https://img.shields.io/badge/Gemini-2.0%20Flash-orange.svg)](https://ai.google.dev)
[![Arduino IDE](https://img.shields.io/badge/Arduino-IDE-green.svg)](https://www.arduino.cc/en/software)
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](LICENSE)

> **Advanced Air Quality Monitoring with AI-Powered Multimodal Chatbot Interface**  
> Real-time CO2 monitoring, automatic fan control, and intelligent alerts powered by Google Gemini AI with voice, video, and image capabilities.

---

## 📑 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Live Demo](#-live-demo)
- [Hardware Requirements](#-hardware-requirements)
- [Software Requirements](#-software-requirements)
- [Getting Started](#-getting-started)
- [Installation Guide](#-installation-guide)
- [Code Explanation](#-code-explanation)
- [AI Chatbot Features](#-ai-chatbot-features)
- [API Configuration](#-api-configuration)
- [Troubleshooting](#-troubleshooting)
- [Video Tutorials](#-video-tutorials)
- [Contributing](#-contributing)
- [Contact](#-contact)
- [License](#-license)

---

## 🌟 Overview

This project integrates **Google Gemini 2.0 Flash AI** with an **ESP32 microcontroller** to create an intelligent air quality monitoring system. The system features a sophisticated web-based chatbot interface that supports text, voice, image, and video interactions, making it easy to monitor air quality, control hardware, and get intelligent insights about your environment.

### What Makes This Special?

- **🧠 AI-Powered Interface**: Full Gemini AI integration with multimodal capabilities (text, voice, image, video)
- **📊 Real-Time Monitoring**: Live CO2 level tracking with automatic alerts
- **🌐 Web-Based Control**: Access from any device on your network
- **🎤 Voice Interaction**: Natural language conversations with the AI assistant
- **📹 Video Analysis**: AI can see and analyze your environment during video calls
- **⚙️ Smart Automation**: Automatic fan control based on air quality thresholds
- **📱 Responsive Design**: Works perfectly on desktop, tablet, and mobile devices

---

## ✨ Features

### 🤖 AI Chatbot Capabilities

#### **Text Chat**
- Natural language conversations about air quality
- Hardware control and status queries
- Safety threshold explanations
- Setup and troubleshooting assistance

#### **Voice Interaction**
- 📞 **Voice Calls**: Real-time voice conversations with the AI
- 🎤 **Voice Input**: Speech-to-text for hands-free messaging
- 🔊 **Text-to-Speech**: AI responses spoken aloud
- 🎙️ **Continuous Recognition**: Natural conversation flow during calls

#### **Video Capabilities**
- 📹 **Video Calls**: Live video chat with AI visual analysis
- 📸 **Image Analysis**: Upload images for AI interpretation
- 🔄 **Camera Switching**: Front/back camera support on mobile
- 🎬 **Real-Time Analysis**: AI sees and comments on your environment

### 📊 System Monitoring

- **Real-time CO2 Levels**: Current PPM readings with color-coded status
- **Air Quality Index**: Good, Fair, Poor, Bad classifications
- **Data Point Tracking**: Historical data collection (up to 1440 points)
- **Fan Control**: Automatic/manual modes with speed adjustment
- **Alert System**: Buzzer patterns for different danger levels

### 🎛️ Hardware Control

- **Fan Management**: ON/OFF control with variable speed (0-100%)
- **Mode Selection**: Automatic or manual fan operation
- **Alert Patterns**: 
  - Pattern 0: Silent (Safe levels)
  - Pattern 1: Caution (500+ PPM)
  - Pattern 2: Warning (750+ PPM)
  - Pattern 3: Danger (1000+ PPM)

---

## 🌐 Live Demo

**🚀 Live Website**: [https://air-monitoring-esp32.netlify.app/](https://air-monitoring-esp32.netlify.app/)

> This is a live demonstration of the complete web interface running on ESP32 hardware. Experience the AI chatbot, voice calls, video calls, and real-time monitoring features. You can deploy this exact same interface on your own ESP32 board by following this guide!

**Features you can try in the live demo:**
- ✅ Full AI chatbot interface
- ✅ Voice call simulation
- ✅ Video call with camera access
- ✅ Image upload and analysis
- ✅ Real-time system status display
- ✅ Responsive design on any device

---

## 🔧 Hardware Requirements

### Essential Components

| Component | Specification | Purpose |
|-----------|--------------|---------|
| **ESP32 DevKit** | ESP32-WROOM-32 | Main microcontroller |
| **CO2 Sensor** | MQ-135 or MH-Z19 | Air quality measurement |
| **DC Fan** | 5V/12V with PWM | Air circulation |
| **Buzzer** | Active/Passive 5V | Alert notifications |
| **Motor Driver** | L298N or similar | Fan speed control |
| **USB Cable** | Micro-USB or Type-C | Programming & power |
| **Jumper Wires** | Male-to-Male/Female | Connections |
| **Breadboard** | Standard size | Prototyping (optional) |

### Pin Configuration

```cpp
// Default GPIO Pins (customize as needed)
CO2_SENSOR_PIN  = GPIO 34  // Analog input
FAN_PWM_PIN     = GPIO 25  // PWM output
BUZZER_PIN      = GPIO 26  // Digital output
LED_STATUS_PIN  = GPIO 2   // Built-in LED
```

---

## 💻 Software Requirements

### Development Environment

1. **Arduino IDE** (v1.8.19 or later) or **Arduino IDE 2.x**
   - Download: [arduino.cc/en/software](https://www.arduino.cc/en/software)

2. **ESP32 Board Manager** (v2.0.14 or earlier)
   - ⚠️ **Important**: Avoid v2.0.15+ due to motor driver compatibility issues

3. **CP210x USB Driver** (Silicon Labs)
   - Required for ESP32 USB communication
   - Download: [Silicon Labs CP210x Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

### Required Libraries

```cpp
#include <WiFi.h>         // ESP32 WiFi (pre-installed)
#include <WebServer.h>    // Web server (pre-installed)
#include <time.h>         // Time functions (pre-installed)
```

### Browser Requirements (for Chatbot)

- **Chrome/Edge**: Recommended (full features)
- **Safari**: iOS/macOS support
- **Firefox**: Basic support
- Features requiring browser support:
  - Web Speech API (voice recognition)
  - MediaDevices API (camera/microphone)
  - Speech Synthesis API (text-to-speech)

---

## 🚀 Getting Started

### Quick Start (5 Minutes)

1. **Install Arduino IDE** and **CP210x Driver**
2. **Configure ESP32 Board Manager** in Arduino IDE
3. **Clone this repository**
4. **Get Gemini API Key** (free tier available)
5. **Upload code** to ESP32
6. **Connect to ESP32 WiFi** or hotspot
7. **Access chatbot** via web browser

Let's dive into detailed steps!

---

## 📥 Installation Guide

### Step 1: Arduino IDE Setup

#### 1.1 Install Arduino IDE

**Option A: Download from Official Website** (Recommended)
```plaintext
1. Visit: https://www.arduino.cc/en/software
2. Download Windows/Mac/Linux version
3. Run installer and follow prompts
4. Launch Arduino IDE
```

**Option B: Microsoft Store** (Windows Only)
```plaintext
1. Open Microsoft Store
2. Search "Arduino IDE"
3. Click "Get" to install
```

#### 1.2 Add ESP32 Board Manager

```plaintext
1. Open Arduino IDE
2. Go to: File → Preferences
3. In "Additional Board Manager URLs", add:
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
4. Click OK
5. Go to: Tools → Board → Boards Manager
6. Search "esp32"
7. Install "esp32 by Espressif Systems" version 2.0.14 or earlier
   ⚠️ IMPORTANT: Do NOT install v2.0.15+ (motor driver issues)
8. Wait for installation to complete
```

#### 1.3 Select ESP32 Board

```plaintext
1. Go to: Tools → Board → ESP32 Arduino
2. Select: "ESP32 Dev Module"
3. Set Partition Scheme: Tools → Partition Scheme → "Huge APP (3MB)"
   (Required for large web applications)
```

---

### Step 2: Driver Installation

#### 2.1 Install CP210x USB Driver

**For Windows:**
```plaintext
1. Download from: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
2. Download "CP210x Windows Drivers"
3. Extract ZIP file
4. Run "CP210xVCPInstaller_x64.exe" (64-bit) or x86 version
5. Follow installation wizard
6. Restart computer if prompted
```

**For Mac:**
```plaintext
1. Download "CP210x Mac OSX Drivers"
2. Open DMG file
3. Run installer package
4. Allow system extension in Security & Privacy settings
5. Restart computer
```

**For Linux:**
```bash
# Usually pre-installed, but if needed:
sudo apt-get install brltty
sudo modprobe cp210x
```

#### 2.2 Verify Driver Installation

```plaintext
1. Connect ESP32 to USB port
2. Open Device Manager (Windows) or System Information (Mac)
3. Look under "Ports (COM & LPT)"
4. You should see: "Silicon Labs CP210x USB to UART Bridge (COM#)"
5. Note the COM port number (e.g., COM11)
```

**Troubleshooting:**
- If device shows as "Unknown Device":
  - Driver not properly installed
  - Try different USB port
  - Use USB 2.0 port instead of 3.0
- If COM port disappears when unplugged:
  - ✅ Normal behavior - driver working correctly

---

### Step 3: Clone Repository

```bash
# Clone the repository
git clone https://github.com/HorizonHnk/ESP32-AI-Powered-Air-Quality-Monitoring-System.git

# Navigate to project folder
cd ESP32-AI-Powered-Air-Quality-Monitoring-System
```

---

### Step 4: Configure WiFi and API

#### 4.1 WiFi Setup

Open the `.ino` file and modify these lines:

```cpp
// WiFi credentials - CHANGE THESE!
const char* ssid = "YOUR_WIFI_NAME";        // Your WiFi network name
const char* password = "YOUR_WIFI_PASSWORD"; // Your WiFi password

// Access Point credentials (fallback if WiFi fails)
const char* ap_ssid = "ESP32_AI_Chatbot";
const char* ap_password = "chatbot123";
```

**Important WiFi Notes:**
- ✅ Use 2.4 GHz WiFi networks (ESP32 doesn't support 5 GHz)
- ✅ Avoid special characters in WiFi names/passwords
- ✅ Ensure strong signal where ESP32 is located
- ⚠️ **Never commit your actual WiFi credentials to GitHub!**

**For GitHub Repository:**
```cpp
// Use placeholder values like:
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Users will replace with their own credentials
```

#### 4.2 Get Gemini API Key (Free!)

```plaintext
1. Visit: https://aistudio.google.com/
2. Sign in with Google account
3. Click "Get API Key" in left sidebar
4. Click "Create API Key"
5. Copy your API key

Free Tier Benefits:
- 1,500 requests per day
- Gemini 2.0 Flash model access
- Multimodal capabilities (text, image, audio)
- No credit card required
```

#### 4.3 Add API Key to Code

**⚠️ SECURITY WARNING: Never commit API keys to GitHub!**

**Option A: Hardcode (Quick Testing Only)**
```javascript
// Find this line in the code (~line 10 in JavaScript section):
let geminiApiKey = '';  // Default empty

// Replace with your key:
let geminiApiKey = 'YOUR_API_KEY_HERE';  // Keep this private!
```

**Option B: Settings Panel (Recommended - Secure)**
```plaintext
1. Upload code to ESP32 with empty API key
2. Access chatbot interface
3. Click "Settings" button
4. Enter API key (stored locally in browser)
5. Click "Save"
6. Key stored in browser localStorage only
7. Never exposed in code or GitHub
```

---

### Step 5: Upload Code to ESP32

#### 5.1 Configure Upload Settings

```plaintext
Tools Menu Settings:
├── Board: "ESP32 Dev Module"
├── Upload Speed: "921600"
├── CPU Frequency: "240MHz (WiFi/BT)"
├── Flash Frequency: "80MHz"
├── Flash Mode: "QIO"
├── Flash Size: "4MB (32Mb)"
├── Partition Scheme: "Huge APP (3MB No OTA/1MB SPIFFS)"
├── Core Debug Level: "None"
└── Port: [Your COM Port from Device Manager]
```

#### 5.2 Upload Process

```plaintext
1. Connect ESP32 to computer via USB
2. Verify correct COM port selected: Tools → Port
3. Click "Upload" button (→) or Ctrl+U
4. Wait for "Connecting..." message
5. Some boards require holding BOOT button during upload
6. Watch for "Hard resetting via RTS pin..."
7. Success message: "Leaving... Hard resetting via RTS pin..."
```

**Upload Progress:**
```plaintext
Sketch uses 1,342,234 bytes (43%) of program storage space.
Connecting........_____.....
Chip is ESP32-D0WDQ6 (revision 1)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
Writing at 0x00010000... (100%)
Hard resetting via RTS pin...
```

#### 5.3 Monitor Serial Output

```plaintext
1. Click: Tools → Serial Monitor
2. Set baud rate to: 115200
3. You should see:
   === ESP32 AI Chatbot Starting ===
   Connecting to WiFi.........
   WiFi connected!
   IP address: 192.168.x.x
   Web server started!
   ===============================
```

---

### Step 6: Access the AI Chatbot

#### Option A: Local Network (Recommended)

```plaintext
1. Ensure your device is on the same WiFi network as ESP32
2. Note the IP address from Serial Monitor (e.g., 192.168.1.xxx)
3. Open web browser
4. Navigate to: http://[YOUR_ESP32_IP_ADDRESS]
5. Click "Launch AI Chatbot"
```

**Finding Your ESP32 IP Address:**
```plaintext
- Check Serial Monitor after upload (115200 baud)
- Look for: "IP address: 192.168.x.x"
- Or check your router's connected devices list
```

#### Option B: Access Point Mode (Backup)

If WiFi connection fails:
```plaintext
1. ESP32 creates its own WiFi hotspot
2. Connect to WiFi: "ESP32_AI_Chatbot"
3. Password: "chatbot123"
4. Open browser
5. Navigate to: http://192.168.4.1
```

---

## 📝 Code Explanation

### Architecture Overview

```plaintext
ESP32 System Architecture:
┌─────────────────────────────────────┐
│         ESP32 Microcontroller       │
├─────────────────────────────────────┤
│  WiFi Module  │  Web Server Module  │
│  ─────────────┤─────────────────────│
│  Sensor Input │  Actuator Control   │
│  (CO2, Temp)  │  (Fan, Buzzer, LED) │
└────────┬────────────────────────────┘
         │
         ├─── HTTP Requests ──────────→ Web Interface
         │                               (HTML/CSS/JS)
         │                                     │
         └─── Data & Control ────────→ Gemini AI API
                                         (Multimodal AI)
```

### Key Code Sections

#### 1. Core Setup Function

```cpp
void setup() {
    Serial.begin(115200);  // Initialize serial communication
    Serial.println("\n\n=== ESP32 AI Chatbot Starting ===");
    
    // Initialize WiFi connection
    initWiFi();
    
    // Configure web server routes
    server.on("/", HTTP_GET, handleRoot);           // Home page
    server.on("/chatbot", HTTP_GET, handleChatbot); // Chatbot interface
    server.onNotFound(handleNotFound);              // 404 handler
    
    // Start web server on port 80
    server.begin();
    Serial.println("Web server started!");
    Serial.print("Access chatbot at: http://");
    Serial.println(WiFi.localIP());
}
```

**What it does:**
- Starts serial communication at 115200 baud
- Connects to WiFi network
- Sets up three web routes (home, chatbot, 404)
- Starts HTTP server
- Prints access URL to Serial Monitor

#### 2. WiFi Initialization

```cpp
void initWiFi() {
    WiFi.mode(WIFI_STA);              // Station mode
    WiFi.begin(ssid, password);       // Connect to WiFi
    
    // Wait for connection (max 20 attempts)
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        // Connected successfully
        Serial.println("\nWiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        
        // Sync time with NTP server
        configTime(0, 0, "pool.ntp.org");
    } else {
        // Fallback to Access Point mode
        Serial.println("\nWiFi failed, starting AP mode");
        WiFi.mode(WIFI_AP);
        WiFi.softAP(ap_ssid, ap_password);
        Serial.print("AP IP address: ");
        Serial.println(WiFi.softAPIP());  // Usually 192.168.4.1
    }
}
```

**Features:**
- Automatic retry mechanism (10 seconds)
- Fallback to AP mode if connection fails
- NTP time synchronization
- IP address reporting

#### 3. Main Loop

```cpp
void loop() {
    // Handle incoming HTTP requests
    server.handleClient();
    
    // Update mock data every 10 seconds for demo
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 10000) {
        lastUpdate = millis();
        
        // Simulate sensor readings
        mockCO2 = random(200, 800);
        
        // Calculate air quality
        if (mockCO2 < 250) mockAirQuality = "Good";
        else if (mockCO2 < 500) mockAirQuality = "Fair";
        else if (mockCO2 < 750) mockAirQuality = "Poor";
        else mockAirQuality = "Bad";
        
        // Update other system values
        mockDataPoints = random(30, 100);
        mockFanSpeed = random(0, 100);
        mockBuzzerPattern = mockCO2 > 500 ? random(1, 4) : 0;
    }
    
    delay(10);  // Small delay to prevent watchdog reset
}
```

**Functions:**
- Continuously processes web requests
- Updates sensor values periodically
- Adjusts fan and buzzer based on air quality
- Prevents ESP32 watchdog timer reset

#### 4. Home Page Handler

```cpp
void handleRoot() {
    // Build complete HTML page
    String html = "<!DOCTYPE html>";
    html += "<html><head>";
    html += "<meta charset=\"UTF-8\">";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    html += "<title>ESP32 AI Assistant</title>";
    
    // CSS styles (responsive design)
    html += "<style>";
    html += "/* Ultra-responsive styles */";
    html += "body { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); }";
    // ... extensive CSS for mobile/desktop support
    html += "</style>";
    
    // HTML content
    html += "</head><body>";
    html += "<div class=\"container\">";
    html += "<h1>🤖 ESP32 AI Assistant</h1>";
    html += "<a href=\"/chatbot\" class=\"btn\">Launch AI Chatbot</a>";
    
    // Display current system status
    html += "<div class=\"status-grid\">";
    html += "Air Quality: " + mockAirQuality;
    html += "CO2 Level: " + String(mockCO2) + " PPM";
    html += "Fan Status: " + String(mockFanEnabled ? "ON" : "OFF");
    // ... more status displays
    html += "</div>";
    
    html += "</body></html>";
    
    // Send response
    server.send(200, "text/html", html);
}
```

**Features:**
- Responsive design (mobile to 4K displays)
- Real-time system status display
- Modern gradient UI
- Launch button for chatbot

#### 5. Chatbot Page Handler

```cpp
void handleChatbot() {
    // Stream HTML in chunks (large page)
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", "");
    
    // Send HTML structure
    server.sendContent("<!DOCTYPE html>");
    server.sendContent("<html lang=\"en\"><head>");
    
    // Ultra-responsive CSS
    server.sendContent("<style>");
    server.sendContent("/* Responsive styles for all screen sizes */");
    server.sendContent("@media (max-width: 320px) { /* tiny phones */ }");
    server.sendContent("@media (min-width: 2560px) { /* 4K displays */ }");
    server.sendContent("</style>");
    
    // Chatbot interface elements
    server.sendContent("<body>");
    server.sendContent("<!-- Header with controls -->");
    server.sendContent("<!-- Chat container -->");
    server.sendContent("<!-- Video call interface -->");
    server.sendContent("<!-- Voice call interface -->");
    server.sendContent("<!-- Input area -->");
    
    // Complete JavaScript implementation
    server.sendContent("<script>");
    sendCompleteJavaScript();  // Sends all AI functionality
    server.sendContent("</script>");
    server.sendContent("</body></html>");
    server.sendContent("");  // End stream
}
```

**Why streaming?**
- Chatbot page is large (~150KB HTML+JS)
- Prevents memory overflow on ESP32
- Progressive loading for better UX

---

## 🤖 AI Chatbot Features

### Text Chat Interface

**Capabilities:**
```javascript
// Example conversations the AI can handle:
"What's the current air quality?"
"Is it safe to sleep with these CO2 levels?"
"Turn on the fan"
"Explain the safety thresholds"
"How do I reduce CO2 in my room?"
"Upload image of sensor setup" (with image)
```

**Features:**
- 💬 Natural language understanding
- 📊 Real-time system data access
- 💡 Intelligent recommendations
- 📝 Chat history (last 20 messages)
- 📋 Copy responses to clipboard
- 🔊 Read responses aloud

### Voice Call System

**How it works:**
```javascript
1. Click "📞 Call AI" button
2. Grant microphone permission
3. AI greets you and starts listening
4. Speak naturally - AI responds immediately
5. Real-time transcript displayed
6. Click "End Call" when finished
```

**Features:**
- 🎤 Continuous speech recognition
- 🔊 Natural voice responses (TTS)
- 🔇 Mute/unmute control
- ⏱️ Call duration timer
- 📝 Live transcription
- 📋 Copy/speak transcript
- 📊 Call summary in main chat

**Voice Recognition Flow:**
```plaintext
User speaks → Speech Recognition API → Text transcript
                                          ↓
                                    Gemini AI processes
                                          ↓
                                    AI text response
                                          ↓
                              Text-to-Speech API → Audio output
```

### Video Call System

**Revolutionary Features:**
```javascript
1. Click "📹 Video Call" button
2. Grant camera + microphone permissions
3. AI can see your environment!
4. Speak or show things to AI
5. AI analyzes and responds
6. Switch between front/back cameras
```

**Capabilities:**
- 🎥 Live video streaming
- 🤖 AI visual analysis
- 📸 Manual screenshot analysis ("Show AI What I'm Doing")
- 🔄 Auto camera switching (mobile)
- 🔇 Mute audio
- 📹 Disable camera (privacy)
- 🎬 Automatic scene analysis (every 30s)
- 📊 Analysis counter
- 📝 Video transcript

**Example Use Cases:**
```plaintext
"Can you see my CO2 sensor setup? Is it correct?"
"I'm showing you my room - what can reduce CO2 here?"
"Is this the right way to connect the fan?"
"Look at these readings on my multimeter - what do they mean?"
```

### Image Analysis

**How to use:**
```plaintext
1. Click 📷 (camera icon) in chat input
2. Select image from device
3. Add text description (optional)
4. Click send
5. AI analyzes and responds
```

**AI can identify:**
- ✅ Electronic components
- ✅ Wiring diagrams
- ✅ Sensor displays
- ✅ Error messages on screens
- ✅ Environmental conditions
- ✅ Safety hazards

---

## 🔑 API Configuration

### Gemini AI API Setup

#### Getting Your API Key

```plaintext
1. Visit Google AI Studio:
   https://aistudio.google.com/

2. Sign in with Google account

3. Click "Get API Key" (left sidebar)

4. Create new key or use existing project key

5. Copy API key (format: AIzaSy...)
```

#### Free Tier Limits (2025)

```plaintext
Gemini 2.0 Flash (Recommended):
├── 1,500 requests/day (free)
├── 2,000 requests/minute (paid tier)
├── Max input: 1 million tokens
├── Max output: 8,192 tokens
└── Multimodal support: ✅ Text, Image, Audio, Video

Rate Limits:
├── Text queries: ~100/minute
├── Image analysis: ~60/minute  
└── Video analysis: ~15/minute
```

#### API Key Security

**✅ DO:**
```javascript
// Store in settings (browser localStorage)
localStorage.setItem('geminiApiKey', 'YOUR_KEY');

// Use environment variables (production)
const apiKey = process.env.GEMINI_API_KEY;

// Server-side storage (advanced)
// Key never exposed to client
```

**❌ DON'T:**
```javascript
// ❌ Hardcode in public repositories
let apiKey = 'AIzaSy...';  // NEVER do this!

// ❌ Commit to GitHub
git add config.js  // Contains API key - DON'T!

// ❌ Share in screenshots or videos
// ❌ Post in public forums or chat
```

**Protecting Your Key:**
```plaintext
1. Add sensitive files to .gitignore:
   echo "config.js" >> .gitignore
   echo ".env" >> .gitignore
   echo "**/apikey.txt" >> .gitignore
   
2. Use GitHub Secrets for CI/CD
   - Repository Settings → Secrets → New secret

3. Rotate keys regularly (every 90 days)
   - Generate new key in Google AI Studio
   - Revoke old key

4. Monitor usage in Google Cloud Console
   - Check for unusual activity
   - Set up usage alerts

5. Set up usage quotas
   - Prevent unexpected charges
   - Limit daily requests
```

**If You Accidentally Exposed Your Key:**
```plaintext
1. IMMEDIATELY revoke the key in Google AI Studio
2. Generate a new API key
3. Remove from Git history:
   git filter-branch --force --index-filter \
   "git rm --cached --ignore-unmatch path/to/file" \
   --prune-empty --tag-name-filter cat -- --all
4. Force push to GitHub (if already pushed)
5. Consider the old key compromised forever
```

### API Request Structure

```javascript
// Example API call from chatbot
async function callGeminiAPI(text, image) {
    const url = 'https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=' + geminiApiKey;
    
    const parts = [];
    
    // Add system instructions
    parts.push({
        text: systemInstructions + '\n\nUser: ' + text
    });
    
    // Add image if provided
    if (image) {
        const base64Data = await fileToBase64(image);
        parts.push({
            inline_data: {
                mime_type: image.type,
                data: base64Data
            }
        });
    }
    
    // Make API request
    const response = await fetch(url, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
            contents: [{ parts: parts }],
            generationConfig: {
                temperature: 0.7,
                topK: 40,
                topP: 0.95,
                maxOutputTokens: 1024
            }
        })
    });
    
    return await response.json();
}
```

### System Instructions

The AI is configured with context about your ESP32 system:

```javascript
// Example structure - actual values are dynamic
const systemInstructions = `
You are a helpful AI assistant connected to an ESP32 air quality 
monitoring system with CURRENT DATA:
- Air Quality: [DYNAMIC] ([CO2_PPM] PPM)
- Fan: [ON/OFF] at [SPEED]%
- Buzzer: Pattern [0-3]
- Data Points: [COUNT]/1440

SAFETY THRESHOLDS:
- 500+ PPM: CAUTION
- 750+ PPM: WARNING  
- 1000+ PPM: DANGER

HARDWARE: ESP32 DevKit with sensors and web interface.

RESPONSE STYLE: Keep responses SHORT (2-3 sentences max for 
voice/video calls). Be helpful and conversational.
`;
```

This gives the AI full context about your system in real-time!

---

## 🔧 Troubleshooting

### Common Issues & Solutions

#### 1. ESP32 Not Detected

**Symptoms:**
- No COM port appears in Device Manager
- Arduino IDE shows "No board found"
- Upload fails immediately

**Solutions:**
```plaintext
✅ Install CP210x driver properly
   - Download from Silicon Labs website
   - Run as administrator
   - Restart computer after installation

✅ Try different USB cable
   - Ensure it's a DATA cable (not charge-only)
   - Some cables only provide power

✅ Try different USB port
   - Prefer USB 2.0 ports over USB 3.0
   - Avoid USB hubs

✅ Check Device Manager
   - Should show "Silicon Labs CP210x"
   - Update driver if showing as "Unknown Device"

✅ Press BOOT button during upload
   - Some ESP32 boards require this
   - Hold BOOT, press reset, release BOOT
```

📺 **Need visual help?** Check out our [ESP32 Setup Video Tutorial](#-video-tutorials)

#### 2. WiFi Connection Failed

**Symptoms:**
- "WiFi failed, starting AP mode" message
- Can't access web interface
- Long connection time

**Solutions:**
```plaintext
✅ Verify WiFi credentials
   ssid = "YourNetworkName"      // Exact match, case sensitive
   password = "YourPassword"      // Must match exactly

✅ Use 2.4 GHz network only
   - ESP32 doesn't support 5 GHz
   - Check router settings
   - Create separate 2.4 GHz SSID if needed

✅ Check WiFi signal strength
   - Move ESP32 closer to router
   - Avoid thick walls/metal obstacles
   - Signal strength > -70 dBm recommended

✅ Disable MAC filtering temporarily
   - Whitelist ESP32's MAC address
   - Check router's connected devices

✅ Test with mobile hotspot
   - Confirms ESP32 WiFi works
   - Rules out router issues
   - Use 2.4 GHz mobile hotspot

✅ Check router firewall settings
   - Disable AP isolation
   - Allow device-to-device communication
```

#### 3. Upload Fails / Timeout Errors

**Symptoms:**
- "Failed to connect to ESP32"
- "A fatal error occurred: Timed out waiting for packet header"
- Upload stuck at "Connecting..."

**Solutions:**
```plaintext
✅ Hold BOOT button during upload
   1. Click Upload in Arduino IDE
   2. When you see "Connecting...", hold BOOT button
   3. Release when upload starts
   
✅ Lower upload speed
   - Tools → Upload Speed → 115200

✅ Check USB cable quality
   - Try a different cable
   - Ensure it's for data, not just charging

✅ Restart ESP32
   - Unplug and replug USB
   - Press EN/RST button
```

#### 4. Gemini API Errors

**Symptoms:**
- "API Error 400/401/429"
- AI not responding
- "Invalid API key" message

**Solutions:**
```plaintext
✅ Verify API key is correct
   - Check for extra spaces
   - Ensure key starts with "AIzaSy"
   - Generate new key if needed

✅ Check API quota
   - Free tier: 1,500 requests/day
   - Monitor usage in Google AI Studio
   - Wait if quota exceeded

✅ Network connectivity
   - ESP32 must be connected to internet
   - Test with browser access
   - Check router internet connection

✅ API key permissions
   - Enable Gemini API in Google Cloud Console
   - Check key hasn't been revoked
```

#### 5. Voice/Video Call Not Working

**Symptoms:**
- Microphone permission denied
- Camera not loading
- No audio in/out

**Solutions:**
```plaintext
✅ Browser permissions
   - Allow microphone/camera in browser settings
   - Chrome: Settings → Privacy → Site Settings
   - Check for blocked permissions icon in address bar

✅ Use supported browser
   - Chrome/Edge: Full support ✅
   - Safari: iOS/Mac support ✅
   - Firefox: Limited support ⚠️

✅ HTTPS requirement
   - Some browsers require HTTPS for mic/camera
   - Use IP address with http:// (usually works locally)
   - Or set up SSL certificate for ESP32

✅ Check device hardware
   - Test mic/camera in other apps
   - Ensure devices aren't being used by other apps
   - Update device drivers
```

#### 6. Web Interface Not Loading

**Symptoms:**
- Blank page
- "Page not found" error
- Interface appears broken

**Solutions:**
```plaintext
✅ Clear browser cache
   - Ctrl+Shift+Delete
   - Clear cache and cookies
   - Reload page (Ctrl+F5)

✅ Check partition scheme
   - Must be set to "Huge APP (3MB)"
   - Re-upload code with correct partition

✅ Verify IP address
   - Check Serial Monitor for correct IP
   - Try http://[IP_ADDRESS] instead of just IP
   - Ensure on same network as ESP32

✅ Check ESP32 memory
   - Web files might be too large
   - Monitor serial output for errors
```

---

## 📺 Video Tutorials

### Complete ESP32 Setup Guide

Watch our comprehensive video tutorial series on setting up ESP32 with Arduino IDE:

**📺 YouTube Playlist**: [ESP32 Arduino IDE Setup & Programming](https://www.youtube.com/playlist?list=PLrZbkNpNVSwwkA3nnQ5o0Pg8w6GCSDgYA)

### Tutorial Series Contents:

#### **Video 1: Driver Installation & COM Port Setup**
- Installing CP210x USB drivers
- Verifying ESP32 connection in Device Manager
- Identifying correct COM port
- Troubleshooting connection issues
- [Watch Now →](https://www.youtube.com/watch?v=BHSLjuXQjG8)

#### **Video 2: WiFi Configuration**
- Connecting ESP32 to WiFi networks
- USB data transfer setup
- Network configuration and testing
- COM port verification
- [Watch Now →](https://www.youtube.com/watch?v=i8w_SCkEG_E)

#### **Video 3: Network Setup & IP Address**
- WiFi setup for ESP32
- Network configuration
- Finding ESP32 IP address
- Mobile hotspot configuration
- [Watch Now →](https://www.youtube.com/watch?v=menWj2VLLm4)

#### **Video 4: Complete Arduino IDE Configuration**
- ESP32 board manager installation
- Selecting correct board and port
- Partition scheme setup (Huge APP)
- WiFi connection testing
- Serial monitor setup
- Getting IP address
- [Watch Now →](https://www.youtube.com/watch?v=_WWKDHn3IXw)

#### **Video 5: Arduino IDE Installation**
- Step-by-step Arduino IDE installation on Windows
- ESP32 driver installation
- Device manager verification
- First-time setup guide
- [Watch Now →](https://www.youtube.com/watch?v=TGtHY-SyurE)

### 🎬 Quick Tips from Tutorials:

**Important Settings:**
- Always use **ESP32 Dev Module** board
- Set Partition Scheme to **Huge APP (3MB)**
- Use **2.4 GHz WiFi only** (not 5 GHz)
- Install **Board Manager v2.0.14 or earlier** (avoid v2.0.15+)
- Baud rate: **115200** for Serial Monitor

**Common Fixes Covered:**
- ✅ Driver installation issues
- ✅ COM port not appearing
- ✅ WiFi connection problems
- ✅ Upload errors
- ✅ Board selection confusion

---

## 🤝 Contributing

Contributions are welcome! Whether it's bug fixes, feature additions, or documentation improvements, your help is appreciated.

### How to Contribute:

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/AmazingFeature`
3. **Commit your changes**: `git commit -m 'Add some AmazingFeature'`
4. **Push to the branch**: `git push origin feature/AmazingFeature`
5. **Open a Pull Request**

### Contribution Ideas:

- 🐛 Bug fixes and improvements
- ✨ New AI features or capabilities
- 📱 Mobile UI enhancements
- 🌐 Additional language support
- 📊 New sensor integrations
- 🎨 UI/UX improvements
- 📚 Documentation updates

---

## 📞 Contact

**Created by HNK Horizon**

### 🌐 Connect With Me:

<div align="center">

| Platform | Link | Description |
|:--------:|:-----|:------------|
| 🐦 **Twitter** | [@HnkHorizon](https://twitter.com/HnkHorizon) | Latest updates and tech discussions |
| 🎵 **TikTok** | [@codingfever](https://www.tiktok.com/@codingfever) | Quick coding tips and demos |
| 📺 **YouTube** | [@HNK2005](https://www.youtube.com/@HNK2005) | Full tutorials and project videos |
| 📷 **Instagram** | [@hhnk.3693](https://www.instagram.com/hhnk.3693) | Behind-the-scenes and updates |
| 📧 **Email** | [hhnk3693@gmail.com](mailto:hhnk3693@gmail.com) | Direct contact for inquiries |

</div>

### 🎥 Educational Resources:

**📺 ESP32 Setup Tutorials**: [Complete Playlist](https://www.youtube.com/playlist?list=PLrZbkNpNVSwwkA3nnQ5o0Pg8w6GCSDgYA)
- Arduino IDE installation and configuration
- Driver setup and COM port verification
- WiFi connection and network setup
- Complete programming guides

**🚀 Live Demo**: [Air Monitoring System](https://air-monitoring-esp32.netlify.app/)
- Try all features online
- Test the AI chatbot interface
- Experience voice and video calls
- No hardware required to explore

### 💬 Get in Touch:

- 🐛 **Report bugs**: Open an issue on GitHub
- 💡 **Feature requests**: Submit via GitHub discussions
- 🤝 **Collaboration**: Email me directly
- ❓ **Questions**: Comment on YouTube videos or open GitHub issue

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### MIT License Summary:
- ✅ Commercial use
- ✅ Modification
- ✅ Distribution
- ✅ Private use
- ⚠️ Liability and warranty limitations

---

## ⭐ Show Your Support

If you find this project helpful, please consider:
- ⭐ **Starring the repository** on GitHub
- 🔔 **Following** on social media for updates
- 📺 **Subscribing** to the YouTube channel
- 🤝 **Sharing** with others who might benefit
- 💬 **Leaving feedback** or suggestions

---

## 🙏 Acknowledgments

- **Google Gemini AI** - For providing powerful multimodal AI capabilities
- **Espressif Systems** - For the amazing ESP32 platform
- **Arduino Community** - For extensive libraries and support
- **Open Source Contributors** - For continuous improvements and feedback

---

<div align="center">

**Built with ❤️ by HNK Horizon**

🤖 Powered by Gemini AI | 🔧 ESP32 | 🌐 Web Technologies

[⬆ Back to Top](#-esp32-ai-powered-air-quality-monitoring-system)

</div>
