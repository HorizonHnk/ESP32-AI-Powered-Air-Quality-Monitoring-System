#include <WiFi.h>
#include <WebServer.h>
#include <time.h>

// WiFi credentials
const char* ssid = "Hotspot-Name";              // Change to your hotspot name
const char* password = "Hotspot-Password";     // Change to your hotspot password

// Access Point credentials (fallback)
const char* ap_ssid = "ESP32_AI_Chatbot";
const char* ap_password = "chatbot123";

// Web server
WebServer server(80);

// Mock system data for the chatbot
int mockCO2 = 350;
String mockAirQuality = "Good";
int mockDataPoints = 45;
bool mockFanEnabled = true;
int mockFanSpeed = 25;
bool mockFanManual = false;
int mockBuzzerPattern = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("\n\n=== ESP32 AI Chatbot Starting ===");
    
    // Initialize WiFi
    initWiFi();
    
    // Set up web routes
    server.on("/", HTTP_GET, handleRoot);
    server.on("/chatbot", HTTP_GET, handleChatbot);
    server.onNotFound(handleNotFound);
    
    // Start web server
    server.begin();
    Serial.println("Web server started!");
    Serial.print("Access chatbot at: http://");
    Serial.println(WiFi.localIP());
    Serial.println("===============================\n");
}

void loop() {
    server.handleClient();
    
    // Update mock data periodically for demo
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 10000) { // Every 10 seconds
        lastUpdate = millis();
        mockCO2 = random(200, 800);
        if (mockCO2 < 250) mockAirQuality = "Good";
        else if (mockCO2 < 500) mockAirQuality = "Fair";
        else if (mockCO2 < 750) mockAirQuality = "Poor";
        else mockAirQuality = "Bad";
        
        mockDataPoints = random(30, 100);
        mockFanSpeed = random(0, 100);
        mockBuzzerPattern = mockCO2 > 500 ? random(1, 4) : 0;
    }
    
    delay(10);
}

void initWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    Serial.print("Connecting to WiFi");
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        
        // Set up time
        configTime(0, 0, "pool.ntp.org");
    } else {
        Serial.println("\nWiFi failed, starting AP mode");
        WiFi.mode(WIFI_AP);
        WiFi.softAP(ap_ssid, ap_password);
        Serial.print("AP IP address: ");
        Serial.println(WiFi.softAPIP());
    }
}

void handleRoot() {
    String html = "<!DOCTYPE html>";
    html += "<html><head><meta charset=\"UTF-8\">";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    html += "<title>ESP32 AI Assistant</title>";
    html += "<style>";
    
    // Reset and base styles
    html += "* { margin: 0; padding: 0; box-sizing: border-box; }";
    html += "body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, sans-serif; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); min-height: 100vh; display: flex; align-items: center; justify-content: center; padding: clamp(8px, 2vw, 16px); }";
    
    // Ultra-responsive container
    html += ".container { width: 100%; max-width: clamp(280px, 85vw, 550px); background: rgba(255, 255, 255, 0.98); backdrop-filter: blur(15px); padding: clamp(16px, 4vw, 32px); border-radius: clamp(12px, 3vw, 20px); text-align: center; box-shadow: 0 15px 35px rgba(0,0,0,0.1); border: 1px solid rgba(255,255,255,0.3); }";
    
    // Typography - fully responsive
    html += "h1 { color: #2d3748; margin-bottom: clamp(12px, 3vw, 20px); font-size: clamp(18px, 4.5vw, 28px); font-weight: 700; letter-spacing: -0.3px; line-height: 1.2; }";
    html += ".subtitle { color: #4a5568; margin-bottom: clamp(16px, 4vw, 24px); font-size: clamp(13px, 3vw, 16px); line-height: 1.4; font-weight: 400; }";
    
    // Ultra-responsive button
    html += ".btn { background: linear-gradient(45deg, #4f46e5, #7c3aed); color: white; padding: clamp(10px, 2.5vw, 16px) clamp(16px, 4vw, 28px); text-decoration: none; border-radius: clamp(20px, 5vw, 40px); font-size: clamp(13px, 3vw, 16px); font-weight: 600; display: inline-block; margin: clamp(8px, 2vw, 12px) 0; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); border: none; cursor: pointer; text-transform: uppercase; letter-spacing: 0.3px; }";
    html += ".btn:hover { background: linear-gradient(45deg, #3730a3, #6d28d9); transform: translateY(-1px); box-shadow: 0 8px 20px rgba(79, 70, 229, 0.4); }";
    html += ".btn:active { transform: translateY(0); }";
    
    // Status section - ultra-responsive grid
    html += ".status { background: linear-gradient(145deg, #f7fafc, #edf2f7); padding: clamp(12px, 3vw, 20px); border-radius: clamp(10px, 2.5vw, 16px); margin-top: clamp(16px, 4vw, 24px); border: 1px solid #e2e8f0; }";
    html += ".status h3 { color: #2d3748; margin-bottom: clamp(10px, 2.5vw, 16px); font-size: clamp(15px, 3.5vw, 20px); font-weight: 600; }";
    
    // Ultra-responsive status grid
    html += ".status-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(clamp(90px, 25vw, 120px), 1fr)); gap: clamp(8px, 2vw, 12px); margin-top: clamp(8px, 2vw, 12px); }";
    html += ".status-item { background: white; padding: clamp(8px, 2vw, 12px); border-radius: clamp(6px, 1.5vw, 10px); border: 1px solid #e2e8f0; box-shadow: 0 2px 4px rgba(0,0,0,0.04); }";
    html += ".status-label { font-size: clamp(9px, 2vw, 11px); color: #718096; font-weight: 500; margin-bottom: 3px; text-transform: uppercase; letter-spacing: 0.3px; }";
    html += ".status-value { font-size: clamp(11px, 2.5vw, 14px); color: #2d3748; font-weight: 600; }";
    
    // Feature highlights - ultra-responsive
    html += ".features { margin-top: clamp(16px, 4vw, 24px); }";
    html += ".features h4 { color: #4a5568; font-size: clamp(13px, 3vw, 15px); margin-bottom: clamp(8px, 2vw, 12px); font-weight: 600; }";
    html += ".feature-list { display: flex; flex-wrap: wrap; justify-content: center; gap: clamp(6px, 1.5vw, 10px); }";
    html += ".feature-tag { background: rgba(79, 70, 229, 0.1); color: #4f46e5; padding: clamp(3px, 0.8vw, 5px) clamp(6px, 1.5vw, 10px); border-radius: clamp(10px, 2.5vw, 16px); font-size: clamp(9px, 2vw, 11px); font-weight: 500; border: 1px solid rgba(79, 70, 229, 0.2); }";
    
    // Ultra-responsive breakpoints
    html += "@media (max-width: 320px) { ";
    html += ".container { padding: 12px; }";
    html += ".status-grid { grid-template-columns: 1fr; }";
    html += ".feature-list { flex-direction: column; align-items: center; }";
    html += "h1 { font-size: 16px; }";
    html += ".subtitle { font-size: 12px; }";
    html += ".btn { font-size: 12px; padding: 8px 14px; }";
    html += "}";
    
    html += "@media (min-width: 321px) and (max-width: 480px) { ";
    html += ".status-grid { grid-template-columns: repeat(2, 1fr); }";
    html += "}";
    
    html += "@media (min-width: 481px) and (max-width: 768px) { ";
    html += ".container { max-width: 80vw; }";
    html += ".status-grid { grid-template-columns: repeat(3, 1fr); }";
    html += "}";
    
    html += "@media (min-width: 769px) and (max-width: 1024px) { ";
    html += ".container { max-width: 65vw; }";
    html += "}";
    
    html += "@media (min-width: 1025px) { ";
    html += ".container { max-width: 550px; }";
    html += "h1 { font-size: 28px; }";
    html += ".subtitle { font-size: 16px; }";
    html += ".btn { font-size: 16px; padding: 16px 28px; }";
    html += "}";
    
    html += "@media (min-width: 1440px) { ";
    html += ".container { max-width: 600px; padding: 40px; }";
    html += "h1 { font-size: 32px; }";
    html += ".subtitle { font-size: 18px; }";
    html += ".btn { font-size: 18px; padding: 18px 32px; }";
    html += "}";
    
    html += "@media (min-width: 2560px) { ";
    html += ".container { max-width: 700px; padding: 50px; }";
    html += "h1 { font-size: 36px; }";
    html += ".subtitle { font-size: 20px; }";
    html += ".btn { font-size: 20px; padding: 20px 36px; }";
    html += "}";
    
    html += "</style></head><body>";
    html += "<div class=\"container\">";
    html += "<h1>🤖 ESP32 AI Assistant</h1>";
    html += "<p class=\"subtitle\">Advanced AI chatbot with voice, video, and image capabilities. Connect with your ESP32 system for real-time monitoring and intelligent assistance.</p>";
    html += "<a href=\"/chatbot\" class=\"btn\">Launch AI Chatbot</a>";
    
    html += "<div class=\"features\">";
    html += "<h4>Available Features</h4>";
    html += "<div class=\"feature-list\">";
    html += "<span class=\"feature-tag\">💬 Text Chat</span>";
    html += "<span class=\"feature-tag\">📷 Image Analysis</span>";
    html += "<span class=\"feature-tag\">🎤 Voice Input</span>";
    html += "<span class=\"feature-tag\">📞 Voice Calls</span>";
    html += "<span class=\"feature-tag\">📹 Video Calls</span>";
    html += "<span class=\"feature-tag\">📊 System Monitor</span>";
    html += "</div></div>";
    
    html += "<div class=\"status\">";
    html += "<h3>System Status</h3>";
    html += "<div class=\"status-grid\">";
    
    html += "<div class=\"status-item\">";
    html += "<div class=\"status-label\">Air Quality</div>";
    html += "<div class=\"status-value\">" + mockAirQuality + "</div>";
    html += "</div>";
    
    html += "<div class=\"status-item\">";
    html += "<div class=\"status-label\">CO2 Level</div>";
    html += "<div class=\"status-value\">" + String(mockCO2) + " PPM</div>";
    html += "</div>";
    
    html += "<div class=\"status-item\">";
    html += "<div class=\"status-label\">Data Points</div>";
    html += "<div class=\"status-value\">" + String(mockDataPoints) + "/1440</div>";
    html += "</div>";
    
    html += "<div class=\"status-item\">";
    html += "<div class=\"status-label\">Fan Status</div>";
    html += "<div class=\"status-value\">" + String(mockFanEnabled ? "ON" : "OFF") + "</div>";
    html += "</div>";
    
    html += "<div class=\"status-item\">";
    html += "<div class=\"status-label\">Fan Speed</div>";
    html += "<div class=\"status-value\">" + String(mockFanSpeed) + "%</div>";
    html += "</div>";
    
    html += "<div class=\"status-item\">";
    html += "<div class=\"status-label\">Buzzer</div>";
    html += "<div class=\"status-value\">Pattern " + String(mockBuzzerPattern) + "</div>";
    html += "</div>";
    
    html += "</div></div></div></body></html>";
    
    server.send(200, "text/html", html);
}

void handleChatbot() {
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", "");
    
    // Send HTML head
    server.sendContent("<!DOCTYPE html><html lang=\"en\"><head>");
    server.sendContent("<meta charset=\"UTF-8\">");
    server.sendContent("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    server.sendContent("<title>ESP32 AI Assistant</title>");
    
    // Ultra-responsive CSS with all screen sizes covered
    server.sendContent("<style>");
    server.sendContent("* { margin: 0; padding: 0; box-sizing: border-box; }");
    server.sendContent("@import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap');");
    server.sendContent("body { font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif; background: #ffffff; color: #1a202c; min-height: 100vh; display: flex; flex-direction: column; font-weight: 400; letter-spacing: -0.01em; }");
    
    // Ultra-responsive header
    server.sendContent(".header { background: linear-gradient(90deg, #e2e8f0, #f1f5f9); padding: clamp(8px, 2vw, 16px) clamp(12px, 3vw, 20px); display: flex; justify-content: space-between; align-items: center; box-shadow: 0 2px 10px rgba(0,0,0,0.1); color: #1a202c; border-bottom: 1px solid #d1d5db; flex-wrap: wrap; gap: clamp(8px, 2vw, 12px); }");
    server.sendContent(".header h1 { font-size: clamp(14px, 3.5vw, 20px); font-weight: 600; order: 1; }");
    server.sendContent(".header-controls { display: flex; gap: clamp(4px, 1vw, 8px); align-items: center; flex-wrap: wrap; order: 2; }");
    
    // Ultra-responsive buttons
    server.sendContent(".nav-btn, .call-btn, .video-call-btn, .clear-btn { background: linear-gradient(45deg, #4f46e5, #7c3aed); border: none; color: white; padding: clamp(6px, 1.5vw, 10px) clamp(10px, 2.5vw, 16px); border-radius: clamp(12px, 3vw, 20px); cursor: pointer; font-size: clamp(10px, 2.2vw, 14px); font-weight: 500; display: flex; align-items: center; gap: clamp(4px, 1vw, 6px); transition: all 0.3s ease; text-decoration: none; white-space: nowrap; }");
    server.sendContent(".call-btn { background: linear-gradient(45deg, #10b981, #059669); }");
    server.sendContent(".video-call-btn { background: linear-gradient(45deg, #7c3aed, #6d28d9); }");
    server.sendContent(".clear-btn { background: linear-gradient(45deg, #f59e0b, #d97706); }");
    server.sendContent(".settings-btn { background: rgba(79, 70, 229, 0.1); border: none; color: #4f46e5; padding: clamp(6px, 1.5vw, 8px) clamp(10px, 2.5vw, 14px); border-radius: clamp(10px, 2.5vw, 16px); cursor: pointer; font-size: clamp(10px, 2.2vw, 13px); transition: all 0.3s ease; }");
    
    server.sendContent(".nav-btn:hover, .call-btn:hover, .video-call-btn:hover, .clear-btn:hover { transform: translateY(-1px); box-shadow: 0 4px 12px rgba(0,0,0,0.2); }");
    server.sendContent(".settings-btn:hover { background: rgba(79, 70, 229, 0.2); color: #3730a3; }");
    server.sendContent(".call-btn.calling, .video-call-btn.calling { background: linear-gradient(45deg, #ef4444, #dc2626); animation: pulse-call 2s infinite; }");
    server.sendContent("@keyframes pulse-call { 0%, 100% { transform: scale(1); } 50% { transform: scale(1.05); } }");
    
    // Ultra-responsive video call interface
    server.sendContent(".video-call-interface { display: none; position: fixed; top: 0; left: 0; width: 100%; height: 100%; background: #1a1a1a; z-index: 2000; flex-direction: column; color: white; }");
    server.sendContent(".video-call-header { padding: clamp(8px, 2vw, 16px); text-align: center; background: rgba(0,0,0,0.3); }");
    server.sendContent(".video-call-content { flex: 1; display: flex; position: relative; overflow: hidden; }");
    server.sendContent(".video-main { flex: 1; display: flex; align-items: center; justify-content: center; position: relative; min-height: 50vh; }");
    server.sendContent(".user-video { width: 100%; height: 100%; object-fit: cover; background: #2a2a2a; }");
    server.sendContent(".video-sidebar { width: 100%; background: rgba(0,0,0,0.5); display: flex; flex-direction: column; padding: clamp(8px, 2vw, 16px); max-height: 50vh; overflow-y: auto; }");
    server.sendContent(".ai-video-avatar { width: clamp(50px, 10vw, 80px); height: clamp(50px, 10vw, 80px); border-radius: 50%; background: linear-gradient(45deg, #10b981, #059669); display: flex; align-items: center; justify-content: center; font-size: clamp(20px, 5vw, 32px); margin: 0 auto clamp(8px, 2vw, 16px); animation: breath 3s ease-in-out infinite; }");
    server.sendContent("@keyframes breath { 0%, 100% { transform: scale(1); } 50% { transform: scale(1.1); } }");
    server.sendContent(".video-status { text-align: center; margin-bottom: clamp(4px, 1vw, 8px); font-size: clamp(12px, 2.5vw, 16px); }");
    server.sendContent(".video-duration { text-align: center; opacity: 0.8; margin-bottom: clamp(8px, 2vw, 16px); font-size: clamp(10px, 2vw, 14px); }");
    server.sendContent(".video-controls { display: flex; gap: clamp(6px, 1.5vw, 10px); justify-content: center; margin-bottom: clamp(8px, 2vw, 16px); flex-wrap: wrap; }");
    server.sendContent(".video-control-btn { width: clamp(32px, 6vw, 45px); height: clamp(32px, 6vw, 45px); border-radius: 50%; border: none; cursor: pointer; display: flex; align-items: center; justify-content: center; font-size: clamp(14px, 3vw, 18px); transition: all 0.3s ease; color: white; }");
    server.sendContent(".video-mute-btn, .video-camera-btn, .video-switch-camera-btn { background: rgba(255, 255, 255, 0.2); }");
    server.sendContent(".video-mute-btn.muted, .video-camera-btn.off { background: #ef4444; }");
    server.sendContent(".video-switch-camera-btn { background: rgba(34, 197, 94, 0.8); }");
    server.sendContent(".video-switch-camera-btn:hover { background: rgba(34, 197, 94, 1); transform: scale(1.1); }");
    server.sendContent(".video-screenshot-btn { background: rgba(124, 58, 237, 0.8); }");
    server.sendContent(".video-screenshot-btn:hover { background: rgba(124, 58, 237, 1); transform: scale(1.1); }");
    server.sendContent(".video-end-btn { background: #ef4444; }");
    server.sendContent(".video-end-btn:hover { background: #dc2626; transform: scale(1.1); }");
    server.sendContent(".video-transcript { flex: 1; background: rgba(255, 255, 255, 0.1); border-radius: clamp(8px, 2vw, 12px); padding: clamp(8px, 2vw, 12px); overflow-y: auto; font-size: clamp(10px, 2vw, 13px); line-height: 1.4; min-height: 80px; }");
    server.sendContent(".video-analysis-indicator { position: absolute; top: clamp(8px, 2vw, 16px); left: clamp(8px, 2vw, 16px); background: rgba(124, 58, 237, 0.9); color: white; padding: clamp(6px, 1.5vw, 10px) clamp(8px, 2vw, 12px); border-radius: clamp(12px, 3vw, 16px); display: none; align-items: center; gap: clamp(4px, 1vw, 6px); font-size: clamp(10px, 2vw, 12px); font-weight: 500; }");
    server.sendContent(".analysis-pulse { width: clamp(6px, 1.2vw, 8px); height: clamp(6px, 1.2vw, 8px); background: white; border-radius: 50%; animation: pulse 1.5s infinite; }");
    server.sendContent(".video-capture-canvas { display: none; }");
    
    // Call interface - ultra-responsive
    server.sendContent(".call-interface { display: none; position: fixed; top: 0; left: 0; width: 100%; height: 100%; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); z-index: 2000; flex-direction: column; justify-content: center; align-items: center; color: white; padding: clamp(16px, 4vw, 32px); }");
    server.sendContent(".call-content { text-align: center; max-width: clamp(280px, 80vw, 400px); padding: clamp(16px, 4vw, 32px); }");
    server.sendContent(".call-avatar { width: clamp(80px, 15vw, 120px); height: clamp(80px, 15vw, 120px); border-radius: 50%; background: rgba(255, 255, 255, 0.2); display: flex; align-items: center; justify-content: center; font-size: clamp(32px, 7vw, 50px); margin: 0 auto clamp(16px, 4vw, 24px); animation: breath 3s ease-in-out infinite; }");
    server.sendContent(".call-status { font-size: clamp(18px, 4vw, 24px); font-weight: 600; margin-bottom: clamp(6px, 1.5vw, 10px); }");
    server.sendContent(".call-duration { font-size: clamp(14px, 3vw, 18px); opacity: 0.9; margin-bottom: clamp(16px, 4vw, 24px); }");
    server.sendContent(".call-controls { display: flex; gap: clamp(12px, 3vw, 18px); justify-content: center; margin-bottom: clamp(16px, 4vw, 24px); flex-wrap: wrap; }");
    server.sendContent(".call-control-btn { width: clamp(45px, 8vw, 60px); height: clamp(45px, 8vw, 60px); border-radius: 50%; border: none; cursor: pointer; display: flex; align-items: center; justify-content: center; font-size: clamp(18px, 4vw, 24px); transition: all 0.3s ease; }");
    server.sendContent(".mute-btn { background: rgba(255, 255, 255, 0.2); color: white; }");
    server.sendContent(".mute-btn.muted { background: #ef4444; }");
    server.sendContent(".end-call-btn { background: #ef4444; color: white; }");
    server.sendContent(".end-call-btn:hover { background: #dc2626; transform: scale(1.1); }");
    server.sendContent(".call-transcript { background: rgba(255, 255, 255, 0.1); border-radius: clamp(10px, 2.5vw, 15px); padding: clamp(12px, 3vw, 20px); max-height: clamp(150px, 30vh, 200px); overflow-y: auto; text-align: left; font-size: clamp(12px, 2.5vw, 14px); line-height: 1.5; }");
    server.sendContent(".transcript-entry { margin-bottom: clamp(8px, 2vw, 12px); padding: clamp(6px, 1.5vw, 10px); border-radius: clamp(6px, 1.5vw, 8px); }");
    server.sendContent(".transcript-user { background: rgba(255, 255, 255, 0.1); }");
    server.sendContent(".transcript-ai { background: rgba(255, 255, 255, 0.05); }");
    
    // Status indicators - ultra-responsive
    server.sendContent(".listening-indicator, .speaking-indicator { position: fixed; bottom: clamp(16px, 4vw, 30px); left: 50%; transform: translateX(-50%); color: white; padding: clamp(8px, 2vw, 12px) clamp(12px, 3vw, 20px); border-radius: clamp(12px, 3vw, 20px); display: none; align-items: center; gap: clamp(6px, 1.5vw, 8px); font-weight: 500; box-shadow: 0 4px 16px rgba(0,0,0,0.3); font-size: clamp(12px, 2.5vw, 14px); }");
    server.sendContent(".listening-indicator { background: rgba(16, 185, 129, 0.9); }");
    server.sendContent(".speaking-indicator { background: rgba(79, 70, 229, 0.9); }");
    server.sendContent(".listening-pulse { width: clamp(8px, 2vw, 12px); height: clamp(8px, 2vw, 12px); background: white; border-radius: 50%; animation: pulse 1.5s infinite; }");
    server.sendContent(".speaking-bars { display: flex; gap: clamp(2px, 0.5vw, 3px); align-items: center; }");
    server.sendContent(".speaking-bar { width: clamp(2px, 0.5vw, 3px); height: clamp(8px, 2vw, 12px); background: white; border-radius: 1px; animation: speaking 0.8s ease-in-out infinite; }");
    server.sendContent(".speaking-bar:nth-child(2) { animation-delay: 0.1s; } .speaking-bar:nth-child(3) { animation-delay: 0.2s; } .speaking-bar:nth-child(4) { animation-delay: 0.3s; }");
    server.sendContent("@keyframes speaking { 0%, 100% { height: clamp(3px, 0.8vw, 4px); } 50% { height: clamp(12px, 3vw, 16px); } }");
    
    // Chat container - ultra-responsive
    server.sendContent(".chat-container { flex: 1; overflow-y: auto; padding: clamp(8px, 2vw, 16px); max-width: clamp(280px, 95vw, 900px); margin: 0 auto; width: 100%; }");
    server.sendContent(".message { margin-bottom: clamp(12px, 2.5vw, 18px); display: flex; gap: clamp(6px, 1.5vw, 12px); animation: fadeIn 0.3s ease-in; }");
    server.sendContent("@keyframes fadeIn { from { opacity: 0; transform: translateY(10px); } to { opacity: 1; transform: translateY(0); } }");
    server.sendContent(".message-avatar { width: clamp(24px, 5vw, 32px); height: clamp(24px, 5vw, 32px); border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: clamp(12px, 2.5vw, 16px); flex-shrink: 0; }");
    server.sendContent(".user-avatar { background: linear-gradient(45deg, #4f46e5, #7c3aed); }");
    server.sendContent(".bot-avatar { background: linear-gradient(45deg, #10b981, #059669); }");
    server.sendContent(".message-content { flex: 1; background: #f1f5f9; padding: clamp(8px, 2vw, 14px) clamp(12px, 3vw, 18px); border-radius: clamp(10px, 2.5vw, 15px); border: 1px solid #d1d5db; position: relative; color: #1a202c; }");
    server.sendContent(".user-message .message-content { background: linear-gradient(45deg, #4f46e5, #7c3aed); color: white; }");
    server.sendContent(".bot-message .message-content { background: #f1f5f9; color: #1a202c; }");
    server.sendContent(".message-text { white-space: pre-wrap; line-height: 1.5; color: inherit; font-size: clamp(12px, 2.5vw, 15px); }");
    server.sendContent(".message-image { max-width: clamp(200px, 60vw, 300px); max-height: clamp(150px, 40vh, 250px); border-radius: clamp(6px, 1.5vw, 10px); margin-top: clamp(6px, 1.5vw, 10px); border: 1px solid #d1d5db; height: auto; }");
    server.sendContent(".message-actions { display: flex; gap: clamp(6px, 1.5vw, 8px); margin-top: clamp(6px, 1.5vw, 10px); padding-top: clamp(6px, 1.5vw, 10px); border-top: 1px solid #e2e8f0; flex-wrap: wrap; }");
    server.sendContent(".action-btn { background: none; border: 1px solid #d1d5db; color: #64748b; padding: clamp(3px, 0.8vw, 5px) clamp(6px, 1.5vw, 10px); border-radius: clamp(8px, 2vw, 12px); cursor: pointer; font-size: clamp(9px, 2vw, 11px); transition: all 0.2s; }");
    server.sendContent(".action-btn:hover { color: #4f46e5; border-color: #4f46e5; background: rgba(79, 70, 229, 0.05); }");
    
    // Input area - ultra-responsive
    server.sendContent(".input-area { background: #f8fafc; border-top: 1px solid #d1d5db; padding: clamp(8px, 2vw, 16px); }");
    server.sendContent(".input-container { max-width: clamp(280px, 95vw, 900px); margin: 0 auto; display: flex; flex-direction: column; gap: clamp(8px, 2vw, 12px); }");
    server.sendContent(".input-row { display: flex; gap: clamp(6px, 1.5vw, 10px); align-items: flex-end; background: #ffffff; border: 1px solid #d1d5db; border-radius: clamp(12px, 3vw, 20px); padding: clamp(6px, 1.5vw, 10px) clamp(8px, 2vw, 12px); box-shadow: 0 2px 4px rgba(0,0,0,0.05); }");
    server.sendContent(".input-controls { display: flex; gap: clamp(4px, 1vw, 6px); }");
    server.sendContent(".control-btn { background: none; border: none; color: #64748b; cursor: pointer; padding: clamp(4px, 1vw, 6px); border-radius: 50%; transition: all 0.2s; font-size: clamp(14px, 3vw, 16px); min-width: clamp(28px, 6vw, 36px); min-height: clamp(28px, 6vw, 36px); display: flex; align-items: center; justify-content: center; }");
    server.sendContent(".control-btn:hover { color: #4f46e5; background: rgba(79, 70, 229, 0.1); }");
    server.sendContent(".control-btn.active { color: #4f46e5; background: rgba(79, 70, 229, 0.15); }");
    server.sendContent(".message-input { flex: 1; background: none; border: none; color: #1a202c; font-size: clamp(13px, 2.8vw, 15px); resize: none; outline: none; min-height: 18px; max-height: clamp(80px, 20vh, 120px); line-height: 1.4; }");
    server.sendContent(".message-input::placeholder { color: #64748b; }");
    server.sendContent(".send-btn { background: #4f46e5; border: none; color: white; padding: clamp(4px, 1vw, 6px); border-radius: 50%; cursor: pointer; display: flex; align-items: center; justify-content: center; transition: all 0.2s; min-width: clamp(28px, 6vw, 36px); min-height: clamp(28px, 6vw, 36px); }");
    server.sendContent(".send-btn:hover:not(:disabled) { background: #3730a3; transform: scale(1.05); }");
    server.sendContent(".send-btn:disabled { background: #9ca3af; cursor: not-allowed; }");
    
    // Other components - ultra-responsive
    server.sendContent(".image-preview { display: none; max-width: clamp(120px, 25vw, 150px); max-height: clamp(90px, 20vh, 120px); border-radius: clamp(6px, 1.5vw, 10px); border: 2px solid #d1d5db; }");
    server.sendContent(".recording-indicator { display: none; align-items: center; gap: clamp(6px, 1.5vw, 8px); color: #dc2626; font-size: clamp(11px, 2.2vw, 13px); padding: clamp(6px, 1.5vw, 8px) clamp(8px, 2vw, 12px); background: rgba(220, 38, 38, 0.1); border-radius: clamp(10px, 2.5vw, 16px); }");
    server.sendContent(".pulse { width: clamp(6px, 1.2vw, 8px); height: clamp(6px, 1.2vw, 8px); background: #dc2626; border-radius: 50%; animation: pulse 1.5s infinite; }");
    server.sendContent("@keyframes pulse { 0%, 100% { opacity: 1; } 50% { opacity: 0.3; } }");
    server.sendContent(".typing-indicator { display: none; gap: clamp(8px, 2vw, 12px); margin-bottom: clamp(12px, 2.5vw, 18px); }");
    server.sendContent(".typing-dots { display: flex; gap: clamp(3px, 0.8vw, 4px); padding: clamp(8px, 2vw, 12px) clamp(12px, 3vw, 16px); background: #f1f5f9; border-radius: clamp(10px, 2.5vw, 15px); border: 1px solid #d1d5db; }");
    server.sendContent(".typing-dot { width: clamp(4px, 1vw, 6px); height: clamp(4px, 1vw, 6px); background: #64748b; border-radius: 50%; animation: typing 1.5s infinite; }");
    server.sendContent(".typing-dot:nth-child(2) { animation-delay: 0.2s; } .typing-dot:nth-child(3) { animation-delay: 0.4s; }");
    server.sendContent("@keyframes typing { 0%, 60%, 100% { transform: translateY(0); } 30% { transform: translateY(clamp(-6px, -1.5vw, -8px)); } }");
    server.sendContent(".hidden-input { display: none; }");
    server.sendContent(".welcome-message { text-align: center; padding: clamp(16px, 4vw, 32px) clamp(12px, 3vw, 20px); color: #64748b; }");
    server.sendContent(".welcome-message h2 { margin-bottom: clamp(6px, 1.5vw, 10px); color: #4f46e5; font-size: clamp(16px, 3.5vw, 22px); }");
    server.sendContent(".welcome-message p { font-size: clamp(12px, 2.5vw, 15px); }");
    
    // Settings panel - ultra-responsive
    server.sendContent(".settings-panel { display: none; position: fixed; top: 0; left: 0; width: 100%; height: 100%; background: rgba(0,0,0,0.8); z-index: 1000; justify-content: center; align-items: center; padding: clamp(16px, 4vw, 32px); }");
    server.sendContent(".settings-content { background: #f8fafc; padding: clamp(16px, 4vw, 30px); border-radius: clamp(10px, 2.5vw, 15px); width: min(clamp(280px, 85vw, 500px), 90vw); max-height: 90vh; overflow-y: auto; border: 1px solid #d1d5db; box-shadow: 0 10px 25px rgba(0,0,0,0.15); color: #1a202c; }");
    server.sendContent(".settings-content h3 { margin-bottom: clamp(12px, 3vw, 20px); color: #4f46e5; font-size: clamp(16px, 3.5vw, 20px); }");
    server.sendContent("input[type=\"password\"], input[type=\"text\"], input[type=\"range\"], select { background: #ffffff; border: 1px solid #d1d5db; color: #1a202c; padding: clamp(6px, 1.5vw, 10px); border-radius: clamp(6px, 1.5vw, 8px); width: 100%; margin-bottom: clamp(6px, 1.5vw, 10px); font-size: clamp(12px, 2.5vw, 14px); }");
    server.sendContent("input[type=\"password\"]:focus, input[type=\"text\"]:focus, select:focus { outline: 2px solid #4f46e5; outline-offset: 2px; }");
    server.sendContent("label { display: block; margin-bottom: clamp(3px, 0.8vw, 5px); color: #64748b; font-size: clamp(11px, 2.2vw, 13px); }");
    server.sendContent(".form-group { margin-bottom: clamp(12px, 3vw, 18px); }");
    server.sendContent(".close-btn, .save-btn { border: none; color: white; padding: clamp(6px, 1.5vw, 10px) clamp(12px, 3vw, 18px); border-radius: clamp(6px, 1.5vw, 8px); cursor: pointer; font-size: clamp(11px, 2.2vw, 13px); }");
    server.sendContent(".close-btn { background: #ef4444; float: right; }");
    server.sendContent(".save-btn { background: #4f46e5; margin-right: clamp(6px, 1.5vw, 10px); }");
    server.sendContent("small { color: #64748b; font-size: clamp(9px, 2vw, 11px); }");
    server.sendContent("a { color: #4f46e5; } a:hover { color: #3730a3; text-decoration: underline; }");
    
    // Ultra-responsive breakpoints for complex layouts
    server.sendContent("@media (max-width: 320px) { ");
    server.sendContent(".header { flex-direction: column; text-align: center; }");
    server.sendContent(".header-controls { justify-content: center; }");
    server.sendContent(".video-call-content { flex-direction: column; }");
    server.sendContent(".video-sidebar { width: 100%; max-height: 40vh; }");
    server.sendContent(".video-controls { gap: 4px; }");
    server.sendContent(".call-controls { gap: 8px; }");
    server.sendContent("}");
    
    server.sendContent("@media (min-width: 321px) and (max-width: 480px) { ");
    server.sendContent(".header-controls { flex-wrap: wrap; justify-content: center; }");
    server.sendContent(".video-call-content { flex-direction: column; }");
    server.sendContent(".video-sidebar { width: 100%; max-height: 45vh; }");
    server.sendContent("}");
    
    server.sendContent("@media (min-width: 481px) and (max-width: 768px) { ");
    server.sendContent(".video-call-content { flex-direction: row; }");
    server.sendContent(".video-sidebar { width: clamp(250px, 40vw, 300px); max-height: 100vh; }");
    server.sendContent("}");
    
    server.sendContent("@media (min-width: 769px) and (max-width: 1024px) { ");
    server.sendContent(".video-sidebar { width: clamp(300px, 35vw, 350px); }");
    server.sendContent("}");
    
    server.sendContent("@media (min-width: 1025px) { ");
    server.sendContent(".video-sidebar { width: 350px; }");
    server.sendContent(".header h1 { font-size: 20px; }");
    server.sendContent(".call-btn, .video-call-btn, .clear-btn, .nav-btn { font-size: 14px; padding: 10px 16px; }");
    server.sendContent(".settings-btn { font-size: 13px; padding: 8px 14px; }");
    server.sendContent("}");
    
    server.sendContent("@media (min-width: 1440px) { ");
    server.sendContent(".chat-container, .input-container { max-width: 1000px; }");
    server.sendContent(".header h1 { font-size: 22px; }");
    server.sendContent(".call-btn, .video-call-btn, .clear-btn, .nav-btn { font-size: 15px; padding: 12px 18px; }");
    server.sendContent("}");
    
    server.sendContent("@media (min-width: 2560px) { ");
    server.sendContent(".chat-container, .input-container { max-width: 1200px; }");
    server.sendContent(".header { padding: 20px 30px; }");
    server.sendContent(".header h1 { font-size: 24px; }");
    server.sendContent(".call-btn, .video-call-btn, .clear-btn, .nav-btn { font-size: 16px; padding: 14px 20px; }");
    server.sendContent("}");
    
    server.sendContent("</style></head><body>");

    // Enhanced header with navigation and controls
    server.sendContent("<div class=\"header\">");
    server.sendContent("<h1>🤖 ESP32 AI Assistant</h1>");
    server.sendContent("<div class=\"header-controls\">");
    server.sendContent("<a href=\"/\" class=\"nav-btn\" title=\"Return to Home\">🏠 Home</a>");
    server.sendContent("<button class=\"clear-btn\" onclick=\"clearChat()\" title=\"Clear Chat History\">🗑️ Clear</button>");
    server.sendContent("<button class=\"call-btn\" id=\"callBtn\">📞 Call AI</button>");
    server.sendContent("<button class=\"video-call-btn\" id=\"videoCallBtn\">📹 Video Call</button>");
    server.sendContent("<button class=\"settings-btn\" onclick=\"openSettings()\">Settings</button>");
    server.sendContent("</div></div>");

    // Video Call Interface
    server.sendContent("<div class=\"video-call-interface\" id=\"videoCallInterface\">");
    server.sendContent("<div class=\"video-call-header\">");
    server.sendContent("<div class=\"video-status\" id=\"videoCallStatus\">Connecting...</div>");
    server.sendContent("<div class=\"video-duration\" id=\"videoCallDuration\">00:00</div>");
    server.sendContent("</div>");
    server.sendContent("<div class=\"video-call-content\">");
    server.sendContent("<div class=\"video-main\">");
    server.sendContent("<video id=\"userVideo\" class=\"user-video\" autoplay muted playsinline></video>");
    server.sendContent("<canvas id=\"videoCaptureCanvas\" class=\"video-capture-canvas\"></canvas>");
    server.sendContent("<div class=\"video-analysis-indicator\" id=\"videoAnalysisIndicator\">");
    server.sendContent("<div class=\"analysis-pulse\"></div>AI Analyzing...");
    server.sendContent("</div></div>");
    server.sendContent("<div class=\"video-sidebar\">");
    server.sendContent("<div class=\"ai-video-avatar\" id=\"videoCallAvatar\">🤖</div>");
    server.sendContent("<div class=\"video-controls\">");
    server.sendContent("<button class=\"video-control-btn video-mute-btn\" id=\"videoMuteBtn\" onclick=\"toggleVideoMute()\" title=\"Mute/Unmute\">🎤</button>");
    server.sendContent("<button class=\"video-control-btn video-camera-btn\" id=\"videoCameraBtn\" onclick=\"toggleCamera()\" title=\"Camera On/Off\">📹</button>");
    server.sendContent("<button class=\"video-control-btn video-switch-camera-btn\" id=\"switchCameraBtn\" onclick=\"switchCamera()\" title=\"Switch Camera\">🔄</button>");
    server.sendContent("<button class=\"video-control-btn video-screenshot-btn\" onclick=\"captureAndAnalyze()\" title=\"Show AI What I'm Doing\">📸</button>");
    server.sendContent("<button class=\"video-control-btn\" onclick=\"copyVideoTranscript()\" title=\"Copy Conversation\">📋</button>");
    server.sendContent("<button class=\"video-control-btn\" onclick=\"speakVideoTranscript()\" title=\"Read Conversation\">🔊</button>");
    server.sendContent("<button class=\"video-control-btn video-end-btn\" onclick=\"endVideoCall()\" title=\"End Call\">📞</button>");
    server.sendContent("</div>");
    server.sendContent("<div class=\"video-transcript\" id=\"videoTranscript\">");
    server.sendContent("<div class=\"transcript-entry transcript-ai\">");
    server.sendContent("<strong>AI:</strong> Hi! I can see and hear you now. How can I help you today?");
    server.sendContent("</div></div></div></div></div>");

    // Call Interface
    server.sendContent("<div class=\"call-interface\" id=\"callInterface\">");
    server.sendContent("<div class=\"call-content\">");
    server.sendContent("<div class=\"call-avatar\" id=\"callAvatar\">🤖</div>");
    server.sendContent("<div class=\"call-status\" id=\"callStatus\">Connecting...</div>");
    server.sendContent("<div class=\"call-duration\" id=\"callDuration\">00:00</div>");
    server.sendContent("<div class=\"call-controls\">");
    server.sendContent("<button class=\"call-control-btn mute-btn\" id=\"muteBtn\" onclick=\"toggleMute()\" title=\"Mute/Unmute\">🎤</button>");
    server.sendContent("<button class=\"call-control-btn\" onclick=\"copyCallTranscript()\" title=\"Copy Conversation\">📋</button>");
    server.sendContent("<button class=\"call-control-btn\" onclick=\"speakCallTranscript()\" title=\"Read Conversation Aloud\">🔊</button>");
    server.sendContent("<button class=\"call-control-btn end-call-btn\" onclick=\"endCall()\" title=\"End Call\">📞</button>");
    server.sendContent("</div>");
    server.sendContent("<div class=\"call-transcript\" id=\"callTranscript\">");
    server.sendContent("<div class=\"transcript-entry transcript-ai\">");
    server.sendContent("<strong>AI:</strong> Hi! I'm ready to talk. How can I help you today?");
    server.sendContent("</div></div></div></div>");

    // Status Indicators
    server.sendContent("<div class=\"listening-indicator\" id=\"listeningIndicator\">");
    server.sendContent("<div class=\"listening-pulse\"></div>Listening...");
    server.sendContent("</div>");
    server.sendContent("<div class=\"speaking-indicator\" id=\"speakingIndicator\">");
    server.sendContent("<div class=\"speaking-bars\">");
    server.sendContent("<div class=\"speaking-bar\"></div><div class=\"speaking-bar\"></div>");
    server.sendContent("<div class=\"speaking-bar\"></div><div class=\"speaking-bar\"></div>");
    server.sendContent("</div>AI Speaking...</div>");

    // Chat container with welcome and system status
    server.sendContent("<div class=\"chat-container\" id=\"chatContainer\">");
    server.sendContent("<div class=\"welcome-message\">");
    server.sendContent("<h2>Hello! I'm your ESP32 AI Assistant</h2>");
    server.sendContent("<p>I can help with text, images, voice, calls, and video calls. Upload images or ask about your system!</p>");
    server.sendContent("</div>");

    // Current System Status from ESP32
    server.sendContent("<div class=\"message bot-message\">");
    server.sendContent("<div class=\"message-avatar bot-avatar\">🤖</div>");
    server.sendContent("<div class=\"message-content\">");
    server.sendContent("<div class=\"message-text\"><strong>Current System Status:</strong><br><br>");
    server.sendContent("Air Quality: " + mockAirQuality + " (" + String(mockCO2) + " PPM)<br>");
    server.sendContent("Buzzer: Pattern " + String(mockBuzzerPattern));
    if (mockBuzzerPattern == 0) server.sendContent(" (Silent)");
    else if (mockBuzzerPattern == 1) server.sendContent(" (Caution Alert)");
    else if (mockBuzzerPattern == 2) server.sendContent(" (Warning Alert)");
    else server.sendContent(" (Danger Alert)");
    server.sendContent("<br>");
    server.sendContent("Fan: " + String(mockFanEnabled ? "ON" : "OFF") + " - " + String(mockFanSpeed) + "% (" + String(mockFanManual ? "Manual" : "Auto") + ")<br>");
    server.sendContent("Data Points: " + String(mockDataPoints) + "/1440<br><br>");
    server.sendContent("Ask me about safety thresholds, hardware setup, upload images, or try voice/video calls!</div>");
    server.sendContent("</div></div>");
    server.sendContent("</div>");

    // Typing indicator
    server.sendContent("<div class=\"typing-indicator\" id=\"typingIndicator\">");
    server.sendContent("<div class=\"message-avatar bot-avatar\">🤖</div>");
    server.sendContent("<div class=\"typing-dots\"><div class=\"typing-dot\"></div><div class=\"typing-dot\"></div><div class=\"typing-dot\"></div></div></div>");

    // Input area
    server.sendContent("<div class=\"input-area\">");
    server.sendContent("<div class=\"recording-indicator\" id=\"recordingIndicator\">");
    server.sendContent("<div class=\"pulse\"></div>Recording... Click the mic again to stop</div>");
    server.sendContent("<div class=\"input-container\">");
    server.sendContent("<img id=\"imagePreview\" class=\"image-preview\">");
    server.sendContent("<div class=\"input-row\">");
    server.sendContent("<div class=\"input-controls\">");
    server.sendContent("<button class=\"control-btn\" id=\"imageBtn\" onclick=\"selectImage()\" title=\"Upload image\">📷</button>");
    server.sendContent("<button class=\"control-btn\" id=\"micBtn\" onclick=\"toggleRecording()\" title=\"Voice input\">🎤</button>");
    server.sendContent("<button class=\"control-btn\" id=\"speakerBtn\" onclick=\"toggleAutoSpeak()\" title=\"Auto-speak responses\">🔊</button>");
    server.sendContent("</div>");
    server.sendContent("<textarea class=\"message-input\" id=\"messageInput\" placeholder=\"Message ESP32 AI...\" rows=\"1\" onkeydown=\"handleKeyDown(event)\" oninput=\"autoResize(this)\"></textarea>");
    server.sendContent("<button class=\"send-btn\" id=\"sendBtn\" onclick=\"sendMessage()\" disabled>➤</button>");
    server.sendContent("</div></div></div>");

    // Settings panel
    server.sendContent("<div class=\"settings-panel\" id=\"settingsPanel\">");
    server.sendContent("<div class=\"settings-content\">");
    server.sendContent("<h3>Settings</h3>");
    server.sendContent("<div class=\"form-group\">");
    server.sendContent("<label for=\"apiKeyInput\">Google Gemini API Key</label>");
    server.sendContent("<input type=\"password\" id=\"apiKeyInput\" placeholder=\"Enter your API key\">");
    server.sendContent("<small>Get your key from <a href=\"https://aistudio.google.com/\" target=\"_blank\">Google AI Studio</a></small>");
    server.sendContent("</div>");
    server.sendContent("<div class=\"form-group\">");
    server.sendContent("<label for=\"voiceSelect\">Voice for Text-to-Speech</label>");
    server.sendContent("<select id=\"voiceSelect\"></select>");
    server.sendContent("</div>");
    server.sendContent("<div class=\"form-group\">");
    server.sendContent("<label for=\"speechRate\">Speech Rate</label>");
    server.sendContent("<input type=\"range\" id=\"speechRate\" min=\"0.5\" max=\"2\" step=\"0.1\" value=\"1.0\">");
    server.sendContent("<span id=\"rateValue\">1.0</span>");
    server.sendContent("</div>");
    server.sendContent("<div>");
    server.sendContent("<button class=\"save-btn\" onclick=\"saveSettings()\">Save</button>");
    server.sendContent("<button class=\"close-btn\" onclick=\"closeSettings()\">Close</button>");
    server.sendContent("</div></div></div>");

    server.sendContent("<input type=\"file\" id=\"fileInput\" class=\"hidden-input\" accept=\"image/*\" onchange=\"handleImageSelect()\">");

    // Complete JavaScript implementation
    server.sendContent("<script>");
    sendCompleteJavaScript();
    server.sendContent("</script></body></html>");
    server.sendContent("");
}

void sendCompleteJavaScript() {
    
    // Global variables with full feature support
    server.sendContent("let geminiApiKey = 'Your_Gemini_Api_Key';");
    server.sendContent("let selectedImage = null;");
    server.sendContent("let isRecording = false;");
    server.sendContent("let autoSpeak = false;");
    server.sendContent("let voices = [];");
    server.sendContent("let selectedVoice = null;");
    server.sendContent("let speechRate = 1.0;");
    server.sendContent("let recognition = null;");
    server.sendContent("let continuousRecognition = null;");
    server.sendContent("let isInCall = false;");
    server.sendContent("let isMuted = false;");
    server.sendContent("let callStartTime = null;");
    server.sendContent("let callDurationInterval = null;");
    server.sendContent("let conversationHistory = [];");
    server.sendContent("let isAISpeaking = false;");
    server.sendContent("let isListeningForUser = false;");
    server.sendContent("let currentUtterance = null;");
    server.sendContent("let isInVideoCall = false;");
    server.sendContent("let isCameraOn = false;");
    server.sendContent("let videoStream = null;");
    server.sendContent("let videoAnalysisInterval = null;");
    server.sendContent("let lastAnalysisTime = 0;");
    server.sendContent("let analysisCount = 0;");
    server.sendContent("let isProcessingResponse = false;");
    server.sendContent("let lastTranscript = '';");
    server.sendContent("let lastResponseTime = 0;");
    server.sendContent("let recognitionTimeoutId = null;");
    server.sendContent("let messageCounter = 0;");
    server.sendContent("let currentPlayingId = null;");
    server.sendContent("let microphonePermissionGranted = false;");
    
    // ESP32 system instructions for AI with current data - Updated for general conversation
    server.sendContent("const systemInstructions = `You are a helpful AI assistant. I'm connected to an ESP32 air quality monitoring system with CURRENT DATA: Air Quality: " + mockAirQuality + " (" + String(mockCO2) + " PPM), Fan: " + String(mockFanEnabled ? "ENABLED" : "DISABLED") + " at " + String(mockFanSpeed) + "% (" + String(mockFanManual ? "manual" : "auto") + " mode), Buzzer: Pattern " + String(mockBuzzerPattern) + ", Data Points: " + String(mockDataPoints) + "/1440.\\n\\nYou can discuss ANY topic - technology, science, daily life, hobbies, etc. Be helpful and engaging on all subjects. KEEP RESPONSES SHORT (2-3 sentences max for voice/video calls).\\n\\nAt the END of conversations about topics other than air quality, briefly mention: \\'By the way, I can also help with air quality monitoring questions if needed.\\'\\n\\nSAFETY THRESHOLDS: 500+ PPM: CAUTION. 750+ PPM: WARNING. 1000+ PPM: DANGER.\\n\\nHARDWARE: ESP32 DevKit with sensors and web interface for real-time monitoring.`;");

    // Enhanced initialization with camera enumeration
    server.sendContent("document.addEventListener('DOMContentLoaded', function() {");
    server.sendContent("initializeVoices();");
    server.sendContent("initializeSpeechRecognition();");
    server.sendContent("initializeContinuousSpeechRecognition();");
    server.sendContent("loadSettings();");
    server.sendContent("loadChatHistory();");
    server.sendContent("requestMicrophonePermission();");
    server.sendContent("enumerateCameras();");
    server.sendContent("document.getElementById('callBtn').addEventListener('click', toggleCall);");
    server.sendContent("document.getElementById('videoCallBtn').addEventListener('click', toggleVideoCall);");
    server.sendContent("const messageInput = document.getElementById('messageInput');");
    server.sendContent("messageInput.addEventListener('input', function() {");
    server.sendContent("autoResize(this);");
    server.sendContent("updateSendButton();");
    server.sendContent("});");
    server.sendContent("const speechRateSlider = document.getElementById('speechRate');");
    server.sendContent("speechRateSlider.addEventListener('input', function() {");
    server.sendContent("document.getElementById('rateValue').textContent = this.value;");
    server.sendContent("speechRate = parseFloat(this.value);");
    server.sendContent("});");
    server.sendContent("if ('speechSynthesis' in window) {");
    server.sendContent("speechSynthesis.addEventListener('voiceschanged', initializeVoices);");
    server.sendContent("}");
    server.sendContent("});");

    // Camera enumeration and switching functions
    server.sendContent("async function enumerateCameras() {");
    server.sendContent("try {");
    server.sendContent("if (!navigator.mediaDevices || !navigator.mediaDevices.enumerateDevices) { console.error('enumerateDevices not supported'); return; }");
    server.sendContent("const devices = await navigator.mediaDevices.enumerateDevices();");
    server.sendContent("availableCameras = devices.filter(device => device.kind === 'videoinput');");
    server.sendContent("console.log('Available cameras:', availableCameras.length);");
    server.sendContent("const switchBtn = document.getElementById('switchCameraBtn');");
    server.sendContent("if (availableCameras.length > 1 && switchBtn) {");
    server.sendContent("switchBtn.style.display = 'flex';");
    server.sendContent("} else if (switchBtn) {");
    server.sendContent("switchBtn.style.display = 'none';");
    server.sendContent("}");
    server.sendContent("} catch (error) {");
    server.sendContent("console.error('Error enumerating cameras:', error);");
    server.sendContent("}");
    server.sendContent("}");
    
    server.sendContent("async function switchCamera() {");
    server.sendContent("if (!isInVideoCall || !isCameraOn) {");
    server.sendContent("alert('Please start a video call and turn on the camera first.');");
    server.sendContent("return;");
    server.sendContent("}");
    server.sendContent("if (!navigator.mediaDevices || !navigator.mediaDevices.getUserMedia) { alert('Camera access is not supported in your browser.'); return; }");
    server.sendContent("try {");
    server.sendContent("const switchBtn = document.getElementById('switchCameraBtn');");
    server.sendContent("if (switchBtn) {");
    server.sendContent("switchBtn.disabled = true;");
    server.sendContent("switchBtn.innerHTML = '⏳';");
    server.sendContent("}");
    server.sendContent("if (typeof currentCamera === 'undefined' || !currentCamera) {");
    server.sendContent("currentCamera = 'user';");
    server.sendContent("console.log('Initialized currentCamera for switching');");
    server.sendContent("}");
    server.sendContent("const newCamera = currentCamera === 'user' ? 'environment' : 'user';");
    server.sendContent("console.log('Switching from', currentCamera, 'to', newCamera);");
    server.sendContent("if (videoStream) {");
    server.sendContent("videoStream.getTracks().forEach(track => track.stop());");
    server.sendContent("}");
    server.sendContent("const constraints = {");
    server.sendContent("video: {");
    server.sendContent("facingMode: { exact: newCamera },");
    server.sendContent("width: { ideal: 1280 },");
    server.sendContent("height: { ideal: 720 }");
    server.sendContent("},");
    server.sendContent("audio: true");
    server.sendContent("};");
    server.sendContent("try {");
    server.sendContent("videoStream = await navigator.mediaDevices.getUserMedia(constraints);");
    server.sendContent("} catch (exactError) {");
    server.sendContent("console.log('Exact facingMode failed, trying ideal:', exactError.name);");
    server.sendContent("const fallbackConstraints = {");
    server.sendContent("video: {");
    server.sendContent("facingMode: newCamera,");
    server.sendContent("width: { ideal: 1280 },");
    server.sendContent("height: { ideal: 720 }");
    server.sendContent("},");
    server.sendContent("audio: true");
    server.sendContent("};");
    server.sendContent("videoStream = await navigator.mediaDevices.getUserMedia(fallbackConstraints);");
    server.sendContent("}");
    server.sendContent("const videoElement = document.getElementById('userVideo');");
    server.sendContent("videoElement.srcObject = videoStream;");
    server.sendContent("currentCamera = newCamera;");
    server.sendContent("if (switchBtn) {");
    server.sendContent("switchBtn.disabled = false;");
    server.sendContent("switchBtn.innerHTML = '🔄';");
    server.sendContent("}");
    server.sendContent("const feedbackMsg = currentCamera === 'environment' ? 'Switched to back camera' : 'Switched to front camera';");
    server.sendContent("addToVideoTranscript('ai', '📷 ' + feedbackMsg);");
    server.sendContent("console.log('Camera switched successfully to:', currentCamera);");
    server.sendContent("} catch (error) {");
    server.sendContent("console.error('Error switching camera:', error);");
    server.sendContent("const switchBtn = document.getElementById('switchCameraBtn');");
    server.sendContent("if (switchBtn) {");
    server.sendContent("switchBtn.disabled = false;");
    server.sendContent("switchBtn.innerHTML = '🔄';");
    server.sendContent("}");
    server.sendContent("if (error.name === 'NotFoundError' || error.name === 'DevicesNotFoundError') {");
    server.sendContent("alert('Camera not found. Your device may not have a ' + (newCamera === 'environment' ? 'back' : 'front') + ' camera.');");
    server.sendContent("} else if (error.name === 'NotAllowedError') {");
    server.sendContent("alert('Camera access denied. Please allow camera access and try again.');");
    server.sendContent("} else if (error.name === 'OverconstrainedError') {");
    server.sendContent("alert('The requested camera is not available. Your device may not have a ' + (newCamera === 'environment' ? 'back' : 'front') + ' camera.');");
    server.sendContent("} else {");
    server.sendContent("alert('Failed to switch camera: ' + error.message);");
    server.sendContent("}");
    server.sendContent("}");
    server.sendContent("}");
    server.sendContent("async function requestMicrophonePermission() {");
    server.sendContent("try {");
    server.sendContent("if (navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {");
    server.sendContent("const stream = await navigator.mediaDevices.getUserMedia({ audio: true });");
    server.sendContent("console.log('Microphone permission granted');");
    server.sendContent("microphonePermissionGranted = true;");
    server.sendContent("stream.getTracks().forEach(track => track.stop());");
    server.sendContent("}");
    server.sendContent("} catch (error) {");
    server.sendContent("console.log('Microphone permission not granted yet:', error.name);");
    server.sendContent("microphonePermissionGranted = false;");
    server.sendContent("}");
    server.sendContent("}");

    // Voice initialization
    server.sendContent("function initializeVoices() {");
    server.sendContent("if ('speechSynthesis' in window) {");
    server.sendContent("function loadVoices() {");
    server.sendContent("voices = speechSynthesis.getVoices();");
    server.sendContent("const voiceSelect = document.getElementById('voiceSelect');");
    server.sendContent("voiceSelect.innerHTML = '<option value=\"\">Default Voice</option>';");
    server.sendContent("voices.forEach((voice, index) => {");
    server.sendContent("const option = document.createElement('option');");
    server.sendContent("option.value = index;");
    server.sendContent("option.textContent = voice.name + ' (' + voice.lang + ')';");
    server.sendContent("voiceSelect.appendChild(option);");
    server.sendContent("});");
    server.sendContent("}");
    server.sendContent("loadVoices();");
    server.sendContent("speechSynthesis.onvoiceschanged = loadVoices;");
    server.sendContent("}");
    server.sendContent("}");

    // Speech recognition initialization
    server.sendContent("function initializeSpeechRecognition() {");
    server.sendContent("if ('webkitSpeechRecognition' in window || 'SpeechRecognition' in window) {");
    server.sendContent("const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;");
    server.sendContent("recognition = new SpeechRecognition();");
    server.sendContent("recognition.continuous = false;");
    server.sendContent("recognition.interimResults = false;");
    server.sendContent("recognition.lang = 'en-US';");
    server.sendContent("recognition.onstart = function() {");
    server.sendContent("console.log('Speech recognition started');");
    server.sendContent("startRecording();");
    server.sendContent("};");
    server.sendContent("recognition.onresult = function(event) {");
    server.sendContent("const transcript = event.results[0][0].transcript;");
    server.sendContent("console.log('Transcript received:', transcript);");
    server.sendContent("document.getElementById('messageInput').value = transcript;");
    server.sendContent("autoResize(document.getElementById('messageInput'));");
    server.sendContent("updateSendButton();");
    server.sendContent("stopRecording();");
    server.sendContent("};");
    server.sendContent("recognition.onerror = function(event) {");
    server.sendContent("console.error('Speech recognition error:', event.error);");
    server.sendContent("stopRecording();");
    server.sendContent("if (event.error === 'not-allowed') {");
    server.sendContent("alert('Microphone access denied. Please allow microphone access in your browser settings and try again.');");
    server.sendContent("} else {");
    server.sendContent("console.log('Speech recognition error:', event.error);");
    server.sendContent("}");
    server.sendContent("};");
    server.sendContent("recognition.onend = function() {");
    server.sendContent("stopRecording();");
    server.sendContent("};");
    server.sendContent("} else {");
    server.sendContent("console.log('Speech recognition not supported in this browser.');");
    server.sendContent("}");
    server.sendContent("}");

    // Continuous speech recognition for calls
    server.sendContent("function initializeContinuousSpeechRecognition() {");
    server.sendContent("if ('webkitSpeechRecognition' in window || 'SpeechRecognition' in window) {");
    server.sendContent("const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;");
    server.sendContent("continuousRecognition = new SpeechRecognition();");
    server.sendContent("continuousRecognition.continuous = true;");
    server.sendContent("continuousRecognition.interimResults = false;");
    server.sendContent("continuousRecognition.lang = 'en-US';");
    server.sendContent("continuousRecognition.maxAlternatives = 1;");
    server.sendContent("continuousRecognition.onstart = function() {");
    server.sendContent("console.log('Continuous speech recognition started');");
    server.sendContent("};");
    server.sendContent("continuousRecognition.onresult = function(event) {");
    server.sendContent("if ((!isInCall && !isInVideoCall) || isMuted || isAISpeaking || isProcessingResponse) {");
    server.sendContent("return;");
    server.sendContent("}");
    server.sendContent("clearTimeout(recognitionTimeoutId);");
    server.sendContent("const lastResult = event.results[event.results.length - 1];");
    server.sendContent("if (lastResult.isFinal) {");
    server.sendContent("const transcript = lastResult[0].transcript.trim();");
    server.sendContent("console.log('Final transcript received:', transcript);");
    server.sendContent("if (transcript && transcript.length > 2 && transcript !== lastTranscript) {");
    server.sendContent("const now = Date.now();");
    server.sendContent("if (now - lastResponseTime > 3000) {");
    server.sendContent("lastTranscript = transcript;");
    server.sendContent("lastResponseTime = now;");
    server.sendContent("recognitionTimeoutId = setTimeout(() => {");
    server.sendContent("if (isInVideoCall) {");
    server.sendContent("handleVideoCallUserInput(transcript);");
    server.sendContent("} else if (isInCall) {");
    server.sendContent("handleCallUserInput(transcript);");
    server.sendContent("}");
    server.sendContent("}, 800);");
    server.sendContent("}");
    server.sendContent("}");
    server.sendContent("}");
    server.sendContent("};");
    server.sendContent("continuousRecognition.onerror = function(event) {");
    server.sendContent("console.error('Continuous speech recognition error:', event.error);");
    server.sendContent("if (event.error === 'not-allowed') {");
    server.sendContent("alert('Microphone access denied. Please allow microphone access and try again.');");
    server.sendContent("if (isInCall) endCall();");
    server.sendContent("if (isInVideoCall) endVideoCall();");
    server.sendContent("return;");
    server.sendContent("}");
    server.sendContent("if (event.error === 'no-speech') {");
    server.sendContent("console.log('No speech detected, continuing...');");
    server.sendContent("return;");
    server.sendContent("}");
    server.sendContent("if ((isInCall || isInVideoCall) && !isMuted && !isAISpeaking && !isProcessingResponse) {");
    server.sendContent("setTimeout(() => {");
    server.sendContent("if ((isInCall || isInVideoCall) && !isMuted && !isAISpeaking && !isProcessingResponse) {");
    server.sendContent("console.log('Restarting speech recognition after error');");
    server.sendContent("if (isInVideoCall) {");
    server.sendContent("startVideoListening();");
    server.sendContent("} else {");
    server.sendContent("startListening();");
    server.sendContent("}");
    server.sendContent("}");
    server.sendContent("}, 2000);");
    server.sendContent("}");
    server.sendContent("};");
    server.sendContent("continuousRecognition.onend = function() {");
    server.sendContent("console.log('Continuous speech recognition ended');");
    server.sendContent("if ((isInCall || isInVideoCall) && !isMuted && !isAISpeaking && !isProcessingResponse) {");
    server.sendContent("setTimeout(() => {");
    server.sendContent("if ((isInCall || isInVideoCall) && !isMuted && !isAISpeaking && !isProcessingResponse) {");
    server.sendContent("console.log('Auto-restarting speech recognition');");
    server.sendContent("if (isInVideoCall) {");
    server.sendContent("startVideoListening();");
    server.sendContent("} else {");
    server.sendContent("startListening();");
    server.sendContent("}");
    server.sendContent("}");
    server.sendContent("}, 1500);");
    server.sendContent("}");
    server.sendContent("};");
    server.sendContent("} else {");
    server.sendContent("console.error('Speech recognition not supported in this browser');");
    server.sendContent("}");
    server.sendContent("}");

    // Complete implementation of all core functions
    addAllCoreFunctions();
    
    server.sendContent("console.log('ESP32 AI Assistant with complete features loaded successfully');");
    server.sendContent("window.addEventListener('beforeunload', function() {");
    server.sendContent("if ('speechSynthesis' in window) {");
    server.sendContent("speechSynthesis.cancel();");
    server.sendContent("}");
    server.sendContent("});");
}

void addAllCoreFunctions() {
    // Clear chat function
    server.sendContent("function clearChat() {");
    server.sendContent("if (confirm('Are you sure you want to clear the chat history?')) {");
    server.sendContent("const chatContainer = document.getElementById('chatContainer');");
    server.sendContent("const welcomeMessage = chatContainer.querySelector('.welcome-message');");
    server.sendContent("const systemMessage = chatContainer.querySelector('.bot-message');");
    server.sendContent("chatContainer.innerHTML = '';");
    server.sendContent("if (welcomeMessage) chatContainer.appendChild(welcomeMessage.cloneNode(true));");
    server.sendContent("if (systemMessage) chatContainer.appendChild(systemMessage.cloneNode(true));");
    server.sendContent("localStorage.removeItem('esp32ChatHistory');");
    server.sendContent("messageCounter = 0;");
    server.sendContent("alert('Chat history cleared successfully!');");
    server.sendContent("}");
    server.sendContent("}");

    // Message creation with unique IDs
    server.sendContent("function createMessageElement(sender, text, image, isError = false) {");
    server.sendContent("messageCounter++;");
    server.sendContent("const messageId = 'msg-' + messageCounter;");
    server.sendContent("const messageDiv = document.createElement('div');");
    server.sendContent("messageDiv.className = 'message ' + sender + '-message';");
    server.sendContent("messageDiv.id = messageId;");
    server.sendContent("const avatar = document.createElement('div');");
    server.sendContent("avatar.className = 'message-avatar ' + sender + '-avatar';");
    server.sendContent("avatar.textContent = sender === 'user' ? '👤' : '🤖';");
    server.sendContent("const content = document.createElement('div');");
    server.sendContent("content.className = 'message-content';");
    server.sendContent("if (text) {");
    server.sendContent("const textDiv = document.createElement('div');");
    server.sendContent("textDiv.className = 'message-text';");
    server.sendContent("textDiv.textContent = text;");
    server.sendContent("if (isError) textDiv.style.color = '#dc2626';");
    server.sendContent("content.appendChild(textDiv);");
    server.sendContent("}");
    server.sendContent("if (image) {");
    server.sendContent("const imgElement = document.createElement('img');");
    server.sendContent("imgElement.className = 'message-image';");
    server.sendContent("const reader = new FileReader();");
    server.sendContent("reader.onload = function(e) {");
    server.sendContent("imgElement.src = e.target.result;");
    server.sendContent("};");
    server.sendContent("reader.readAsDataURL(image);");
    server.sendContent("content.appendChild(imgElement);");
    server.sendContent("}");
    server.sendContent("if (sender === 'bot' && text && !isError) {");
    server.sendContent("const actions = document.createElement('div');");
    server.sendContent("actions.className = 'message-actions';");
    server.sendContent("const copyBtn = document.createElement('button');");
    server.sendContent("copyBtn.className = 'action-btn';");
    server.sendContent("copyBtn.textContent = '📋 Copy';");
    server.sendContent("copyBtn.onclick = () => copyToClipboard(text);");
    server.sendContent("const speakBtn = document.createElement('button');");
    server.sendContent("speakBtn.className = 'action-btn speak-btn';");
    server.sendContent("speakBtn.textContent = '🔊 Speak';");
    server.sendContent("speakBtn.id = 'speak-' + messageId;");
    server.sendContent("speakBtn.onclick = () => speakMessage(text, speakBtn.id);");
    server.sendContent("actions.appendChild(copyBtn);");
    server.sendContent("actions.appendChild(speakBtn);");
    server.sendContent("content.appendChild(actions);");
    server.sendContent("}");
    server.sendContent("messageDiv.appendChild(avatar);");
    server.sendContent("messageDiv.appendChild(content);");
    server.sendContent("saveChatHistory();");
    server.sendContent("return messageDiv;");
    server.sendContent("}");

    // Enhanced speech function
    server.sendContent("function speakMessage(text, buttonId) {");
    server.sendContent("const button = document.getElementById(buttonId);");
    server.sendContent("if (!('speechSynthesis' in window)) {");
    server.sendContent("alert('Speech synthesis is not supported in your browser');");
    server.sendContent("return;");
    server.sendContent("}");
    server.sendContent("if (currentPlayingId && currentPlayingId !== buttonId) {");
    server.sendContent("speechSynthesis.cancel();");
    server.sendContent("resetSpeakButton(currentPlayingId);");
    server.sendContent("}");
    server.sendContent("if (button.textContent.includes('Stop')) {");
    server.sendContent("speechSynthesis.cancel();");
    server.sendContent("resetSpeakButton(buttonId);");
    server.sendContent("currentPlayingId = null;");
    server.sendContent("return;");
    server.sendContent("}");
    server.sendContent("currentPlayingId = buttonId;");
    server.sendContent("button.textContent = '⏸️ Stop';");
    server.sendContent("const utterance = new SpeechSynthesisUtterance(text);");
    server.sendContent("utterance.rate = speechRate;");
    server.sendContent("if (selectedVoice) utterance.voice = selectedVoice;");
    server.sendContent("utterance.onend = () => {");
    server.sendContent("resetSpeakButton(buttonId);");
    server.sendContent("currentPlayingId = null;");
    server.sendContent("};");
    server.sendContent("utterance.onerror = () => {");
    server.sendContent("resetSpeakButton(buttonId);");
    server.sendContent("currentPlayingId = null;");
    server.sendContent("};");
    server.sendContent("speechSynthesis.speak(utterance);");
    server.sendContent("}");

    server.sendContent("function resetSpeakButton(buttonId) {");
    server.sendContent("const button = document.getElementById(buttonId);");
    server.sendContent("if (button) {");
    server.sendContent("button.textContent = '🔊 Speak';");
    server.sendContent("}");
    server.sendContent("}");

    // Add all remaining functions with complete implementations
    addRemainingFunctions();
}

void addRemainingFunctions() {
    // Main send message function
    server.sendContent("async function sendMessage() {");
    server.sendContent("const messageInput = document.getElementById('messageInput');");
    server.sendContent("const message = messageInput.value.trim();");
    server.sendContent("if (!message && !selectedImage) return;");
    server.sendContent("if (!geminiApiKey) {");
    server.sendContent("alert('Please set your API key in Settings first.');");
    server.sendContent("return;");
    server.sendContent("}");
    server.sendContent("messageInput.value = '';");
    server.sendContent("autoResize(messageInput);");
    server.sendContent("const imagePreview = document.getElementById('imagePreview');");
    server.sendContent("imagePreview.style.display = 'none';");
    server.sendContent("addUserMessage(message, selectedImage);");
    server.sendContent("const currentImage = selectedImage;");
    server.sendContent("selectedImage = null;");
    server.sendContent("updateSendButton();");
    server.sendContent("showTypingIndicator();");
    server.sendContent("try {");
    server.sendContent("const response = await callGeminiAPI(message, currentImage);");
    server.sendContent("hideTypingIndicator();");
    server.sendContent("if (response && response.candidates && response.candidates[0]) {");
    server.sendContent("const botResponse = response.candidates[0].content.parts[0].text;");
    server.sendContent("addBotMessage(botResponse);");
    server.sendContent("if (autoSpeak) {");
    server.sendContent("speakText(botResponse);");
    server.sendContent("}");
    server.sendContent("} else {");
    server.sendContent("throw new Error('Invalid response format');");
    server.sendContent("}");
    server.sendContent("} catch (error) {");
    server.sendContent("hideTypingIndicator();");
    server.sendContent("let errorMessage = 'Sorry, I encountered an error: ' + error.message;");
    server.sendContent("addBotMessage(errorMessage, true);");
    server.sendContent("}");
    server.sendContent("}");

    // Gemini API call
    server.sendContent("async function callGeminiAPI(text, image) {");
    server.sendContent("const parts = [];");
    server.sendContent("if (text && image) {");
    server.sendContent("parts.push({ text: systemInstructions + '\\n\\nUser message: ' + text + '\\n\\nPlease analyze the uploaded image and respond to the user\\'s request.' });");
    server.sendContent("const base64Data = await fileToBase64(image);");
    server.sendContent("parts.push({ inline_data: { mime_type: image.type, data: base64Data } });");
    server.sendContent("} else if (text) {");
    server.sendContent("parts.push({ text: systemInstructions + '\\n\\nUser: ' + text });");
    server.sendContent("} else if (image) {");
    server.sendContent("parts.push({ text: systemInstructions + '\\n\\nPlease analyze this image and provide feedback.' });");
    server.sendContent("const base64Data = await fileToBase64(image);");
    server.sendContent("parts.push({ inline_data: { mime_type: image.type, data: base64Data } });");
    server.sendContent("}");
    server.sendContent("try {");
    server.sendContent("const response = await fetch('https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=' + geminiApiKey, {");
    server.sendContent("method: 'POST',");
    server.sendContent("headers: { 'Content-Type': 'application/json' },");
    server.sendContent("body: JSON.stringify({");
    server.sendContent("contents: [{ parts: parts }],");
    server.sendContent("generationConfig: { temperature: 0.7, topK: 40, topP: 0.95, maxOutputTokens: 1024 }");
    server.sendContent("})");
    server.sendContent("});");
    server.sendContent("if (!response.ok) {");
    server.sendContent("const errorData = await response.text();");
    server.sendContent("throw new Error('API Error ' + response.status + ': ' + errorData);");
    server.sendContent("}");
    server.sendContent("return await response.json();");
    server.sendContent("} catch (error) {");
    server.sendContent("console.error('Request failed:', error);");
    server.sendContent("throw error;");
    server.sendContent("}");
    server.sendContent("}");

    // Add all utility functions
    server.sendContent("function fileToBase64(file) {");
    server.sendContent("return new Promise((resolve, reject) => {");
    server.sendContent("const reader = new FileReader();");
    server.sendContent("reader.onload = () => {");
    server.sendContent("const base64 = reader.result.split(',')[1];");
    server.sendContent("resolve(base64);");
    server.sendContent("};");
    server.sendContent("reader.onerror = reject;");
    server.sendContent("reader.readAsDataURL(file);");
    server.sendContent("});");
    server.sendContent("}");

    server.sendContent("function addUserMessage(text, image) {");
    server.sendContent("const chatContainer = document.getElementById('chatContainer');");
    server.sendContent("const messageDiv = createMessageElement('user', text, image);");
    server.sendContent("chatContainer.appendChild(messageDiv);");
    server.sendContent("scrollToBottom();");
    server.sendContent("}");

    server.sendContent("function addBotMessage(text, isError = false) {");
    server.sendContent("const chatContainer = document.getElementById('chatContainer');");
    server.sendContent("const messageDiv = createMessageElement('bot', text, null, isError);");
    server.sendContent("chatContainer.appendChild(messageDiv);");
    server.sendContent("scrollToBottom();");
    server.sendContent("}");

    // Add all other essential functions
    addEssentialUtilityFunctions();
}

void addEssentialUtilityFunctions() {
    server.sendContent("function showTypingIndicator() { document.getElementById('typingIndicator').style.display = 'flex'; scrollToBottom(); }");
    server.sendContent("function hideTypingIndicator() { document.getElementById('typingIndicator').style.display = 'none'; }");
    server.sendContent("function scrollToBottom() { const chatContainer = document.getElementById('chatContainer'); chatContainer.scrollTop = chatContainer.scrollHeight; }");
    server.sendContent("function autoResize(textarea) { textarea.style.height = 'auto'; textarea.style.height = Math.min(textarea.scrollHeight, 120) + 'px'; }");
    server.sendContent("function updateSendButton() { const messageInput = document.getElementById('messageInput'); const sendBtn = document.getElementById('sendBtn'); sendBtn.disabled = !messageInput.value.trim() && !selectedImage; }");
    server.sendContent("function handleKeyDown(event) { if (event.key === 'Enter' && !event.shiftKey) { event.preventDefault(); sendMessage(); } }");
    server.sendContent("function selectImage() { document.getElementById('fileInput').click(); }");
    server.sendContent("function handleImageSelect() { const fileInput = document.getElementById('fileInput'); const file = fileInput.files[0]; if (file) { selectedImage = file; const preview = document.getElementById('imagePreview'); const reader = new FileReader(); reader.onload = function(e) { preview.src = e.target.result; preview.style.display = 'block'; updateSendButton(); }; reader.readAsDataURL(file); } }");
    
    // Voice recording functions
    server.sendContent("function toggleRecording() { if (!recognition) { alert('Speech recognition is not supported in your browser.'); return; } if (isRecording) { recognition.stop(); stopRecording(); } else { if (!navigator.mediaDevices || !navigator.mediaDevices.getUserMedia) { alert('Microphone access is not supported in your browser.'); return; } navigator.mediaDevices.getUserMedia({ audio: true }).then(function(stream) { stream.getTracks().forEach(track => track.stop()); recognition.start(); }).catch(function(error) { console.error('Microphone error:', error); if (error.name === 'NotAllowedError') { alert('Microphone access denied.'); } }); } }");
    server.sendContent("function startRecording() { isRecording = true; document.getElementById('micBtn').classList.add('active'); document.getElementById('recordingIndicator').style.display = 'flex'; }");
    server.sendContent("function stopRecording() { isRecording = false; document.getElementById('micBtn').classList.remove('active'); document.getElementById('recordingIndicator').style.display = 'none'; }");
    server.sendContent("function toggleAutoSpeak() { autoSpeak = !autoSpeak; const speakerBtn = document.getElementById('speakerBtn'); if (autoSpeak) { speakerBtn.classList.add('active'); } else { speakerBtn.classList.remove('active'); } }");
    
    // Copy function
    server.sendContent("async function copyToClipboard(text) { try { if (navigator.clipboard && navigator.clipboard.writeText) { await navigator.clipboard.writeText(text); alert('Copied to clipboard!'); } else { const textarea = document.createElement('textarea'); textarea.value = text; textarea.style.position = 'fixed'; textarea.style.left = '-999999px'; textarea.style.top = '-999999px'; document.body.appendChild(textarea); textarea.focus(); textarea.select(); document.execCommand('copy'); textarea.remove(); alert('Copied to clipboard!'); } } catch (err) { console.error('Failed to copy text: ', err); alert('Failed to copy'); } }");
    
    // Speech synthesis
    server.sendContent("function speakText(text) { if (!('speechSynthesis' in window)) { alert('Speech synthesis is not supported in your browser'); return; } speechSynthesis.cancel(); const utterance = new SpeechSynthesisUtterance(text); utterance.rate = speechRate; if (selectedVoice) utterance.voice = selectedVoice; speechSynthesis.speak(utterance); }");
    
    // Settings functions
    server.sendContent("function openSettings() { document.getElementById('settingsPanel').style.display = 'flex'; }");
    server.sendContent("function closeSettings() { document.getElementById('settingsPanel').style.display = 'none'; }");
    server.sendContent("function saveSettings() { const apiKey = document.getElementById('apiKeyInput').value.trim(); if (apiKey) { geminiApiKey = apiKey; localStorage.setItem('geminiApiKey', apiKey); } const voiceIndex = document.getElementById('voiceSelect').value; if (voiceIndex !== '') { selectedVoice = voices[parseInt(voiceIndex)]; localStorage.setItem('selectedVoice', voiceIndex); } localStorage.setItem('speechRate', speechRate); localStorage.setItem('autoSpeak', autoSpeak); closeSettings(); if (apiKey) { alert('Settings saved successfully!'); } }");
    server.sendContent("function loadSettings() { const savedApiKey = localStorage.getItem('geminiApiKey'); if (savedApiKey) { geminiApiKey = savedApiKey; document.getElementById('apiKeyInput').value = savedApiKey; } const savedVoiceIndex = localStorage.getItem('selectedVoice'); if (savedVoiceIndex) { document.getElementById('voiceSelect').value = savedVoiceIndex; selectedVoice = voices[parseInt(savedVoiceIndex)]; } const savedSpeechRate = localStorage.getItem('speechRate'); if (savedSpeechRate) { speechRate = parseFloat(savedSpeechRate); document.getElementById('speechRate').value = speechRate; document.getElementById('rateValue').textContent = speechRate; } const savedAutoSpeak = localStorage.getItem('autoSpeak'); if (savedAutoSpeak === 'true') { autoSpeak = true; document.getElementById('speakerBtn').classList.add('active'); } }");
    
    // Chat history functions
    server.sendContent("function saveChatHistory() { try { const chatContainer = document.getElementById('chatContainer'); const messages = Array.from(chatContainer.children).filter(child => child.classList.contains('message')).map(msg => ({ sender: msg.classList.contains('user-message') ? 'user' : 'bot', text: msg.querySelector('.message-text') ? msg.querySelector('.message-text').textContent : '', timestamp: Date.now() })); localStorage.setItem('esp32ChatHistory', JSON.stringify(messages.slice(-20))); } catch (error) { console.error('Error saving chat history:', error); } }");
    server.sendContent("function loadChatHistory() { try { const savedHistory = localStorage.getItem('esp32ChatHistory'); if (savedHistory) { const messages = JSON.parse(savedHistory); const chatContainer = document.getElementById('chatContainer'); messages.forEach(msg => { if (msg.text.trim()) { const messageDiv = createMessageElement(msg.sender, msg.text); chatContainer.appendChild(messageDiv); } }); scrollToBottom(); } } catch (error) { console.error('Error loading chat history:', error); } }");
    
    // Call functionality
    server.sendContent("function toggleCall() { if (isInCall) { endCall(); } else { startCall(); } }");
    server.sendContent("function toggleVideoCall() { if (isInVideoCall) { endVideoCall(); } else { startVideoCall(); } }");
    server.sendContent("async function startCall() { if (!geminiApiKey) { alert('Please set your API key in Settings first.'); return; } if (!continuousRecognition) { alert('Speech recognition is not supported in your browser. Please use Chrome, Edge, or Safari.'); return; } if (!navigator.mediaDevices || !navigator.mediaDevices.getUserMedia) { alert('Microphone access is not supported in your browser.'); return; } try { console.log('Starting call - requesting microphone access...'); const stream = await navigator.mediaDevices.getUserMedia({ audio: true }); console.log('Microphone access granted for call'); microphonePermissionGranted = true; stream.getTracks().forEach(track => track.stop()); isInCall = true; isMuted = false; conversationHistory = []; callStartTime = Date.now(); isProcessingResponse = false; lastTranscript = ''; lastResponseTime = 0; isAISpeaking = false; isListeningForUser = false; document.getElementById('callInterface').style.display = 'flex'; document.getElementById('callBtn').textContent = '📞 End Call'; document.getElementById('callBtn').classList.add('calling'); document.getElementById('callStatus').textContent = 'Connected'; document.getElementById('muteBtn').classList.remove('muted'); document.getElementById('muteBtn').innerHTML = '🎤'; startCallTimer(); const greeting = 'Hi! I\\'m ready to talk. How can I help you today?'; conversationHistory.push({ role: 'assistant', content: greeting }); addToCallTranscript('ai', greeting); speakTextInCall(greeting, () => { if (isInCall) { console.log('Starting listening after greeting...'); setTimeout(() => startListening(), 1500); } }); } catch (error) { console.error('Microphone access error:', error); if (error.name === 'NotAllowedError') { alert('Microphone access denied. Please allow microphone access in your browser settings and refresh the page to try again.'); } else if (error.name === 'NotFoundError') { alert('No microphone found. Please connect a microphone and try again.'); } else { alert('Microphone error: ' + error.message + '. Please check your microphone settings and try again.'); } } }");
    
    server.sendContent("function endCall() { console.log('Ending voice call...'); isInCall = false; isMuted = false; isAISpeaking = false; isListeningForUser = false; speechSynthesis.cancel(); if (continuousRecognition) { try { continuousRecognition.stop(); } catch (e) {} } if (callDurationInterval) { clearInterval(callDurationInterval); } const finalDuration = document.getElementById('callDuration').textContent || '00:00'; document.getElementById('callInterface').style.display = 'none'; document.getElementById('callBtn').textContent = '📞 Call AI'; document.getElementById('callBtn').classList.remove('calling'); document.getElementById('listeningIndicator').style.display = 'none'; document.getElementById('speakingIndicator').style.display = 'none'; if (conversationHistory.length > 1) { addCallSummaryToChat(finalDuration); } else { addCallEndedToChat(finalDuration); } console.log('Voice call ended successfully'); }");
    
    server.sendContent("function startListening() { console.log('startListening called', { isInCall, isMuted, isAISpeaking, isProcessingResponse, hasContinuous: !!continuousRecognition }); if (!isInCall || isMuted || isAISpeaking || !continuousRecognition || isProcessingResponse) { console.log('Cannot start listening - conditions not met'); return; } try { console.log('Starting call speech recognition...'); isListeningForUser = true; document.getElementById('listeningIndicator').style.display = 'flex'; document.getElementById('speakingIndicator').style.display = 'none'; try { continuousRecognition.stop(); console.log('Stopped previous recognition'); } catch (e) { console.log('No previous recognition to stop'); } setTimeout(() => { if (isInCall && !isMuted && !isAISpeaking && !isProcessingResponse) { try { console.log('Actually starting continuous recognition...'); continuousRecognition.start(); console.log('Continuous recognition started successfully'); } catch (error) { console.error('Error starting recognition in timeout:', error); if (error.name === 'InvalidStateError') { console.log('Recognition already running, continuing...'); } else { alert('Speech recognition failed to start. Please check your microphone and try again.'); } } } else { console.log('Conditions changed, not starting recognition'); } }, 500); } catch (error) { console.error('Error starting call speech recognition:', error); document.getElementById('listeningIndicator').style.display = 'none'; alert('Failed to start speech recognition. Please check your microphone permissions.'); } }");
    
    server.sendContent("function stopListening() { isListeningForUser = false; document.getElementById('listeningIndicator').style.display = 'none'; if (continuousRecognition) { try { continuousRecognition.stop(); } catch (e) {} } }");
    
    server.sendContent("function speakTextInCall(text, onComplete) { if (!isInCall) return; isAISpeaking = true; stopListening(); document.getElementById('speakingIndicator').style.display = 'flex'; document.getElementById('listeningIndicator').style.display = 'none'; speechSynthesis.cancel(); currentUtterance = new SpeechSynthesisUtterance(text); currentUtterance.rate = speechRate; if (selectedVoice) { currentUtterance.voice = selectedVoice; } currentUtterance.onend = () => { isAISpeaking = false; document.getElementById('speakingIndicator').style.display = 'none'; if (onComplete) onComplete(); }; currentUtterance.onerror = () => { isAISpeaking = false; document.getElementById('speakingIndicator').style.display = 'none'; if (onComplete) onComplete(); }; speechSynthesis.speak(currentUtterance); }");
    
    server.sendContent("async function handleCallUserInput(transcript) { if (!isInCall || isAISpeaking || isProcessingResponse) return; const isDuplicate = conversationHistory.length > 0 && conversationHistory[conversationHistory.length - 1].role === 'user' && conversationHistory[conversationHistory.length - 1].content.toLowerCase() === transcript.toLowerCase(); if (isDuplicate) { return; } isProcessingResponse = true; conversationHistory.push({ role: 'user', content: transcript }); addToCallTranscript('user', transcript); stopListening(); try { const response = await callGeminiAPIForCall(transcript); if (response && response.candidates && response.candidates[0]) { const aiResponse = response.candidates[0].content.parts[0].text; conversationHistory.push({ role: 'assistant', content: aiResponse }); addToCallTranscript('ai', aiResponse); speakTextInCall(aiResponse, () => { isProcessingResponse = false; if (isInCall && !isMuted) { setTimeout(() => startListening(), 1000); } }); } else { throw new Error('Invalid response format'); } } catch (error) { console.error('Error in call processing:', error); const errorMessage = 'Sorry, I didn\\'t catch that. Could you please repeat?'; addToCallTranscript('ai', errorMessage); speakTextInCall(errorMessage, () => { isProcessingResponse = false; if (isInCall && !isMuted) { setTimeout(() => startListening(), 1000); } }); } }");
    
    server.sendContent("async function callGeminiAPIForCall(text) { const parts = [{ text: systemInstructions + '\\n\\nUser: ' + text }]; try { const response = await fetch('https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=' + geminiApiKey, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify({ contents: [{ parts: parts }], generationConfig: { temperature: 0.7, topK: 40, topP: 0.95, maxOutputTokens: 512 } }) }); if (!response.ok) { throw new Error('API Error ' + response.status); } return await response.json(); } catch (error) { console.error('Call API failed:', error); throw error; } }");
    
    server.sendContent("function addToCallTranscript(sender, text) { const transcript = document.getElementById('callTranscript'); const entry = document.createElement('div'); entry.className = 'transcript-entry transcript-' + sender; entry.innerHTML = '<strong>' + (sender === 'user' ? 'You' : 'AI') + ':</strong> ' + text; transcript.appendChild(entry); transcript.scrollTop = transcript.scrollHeight; }");
    
    server.sendContent("function startCallTimer() { callDurationInterval = setInterval(() => { if (isInCall && callStartTime) { const duration = Math.floor((Date.now() - callStartTime) / 1000); const minutes = Math.floor(duration / 60); const seconds = duration % 60; document.getElementById('callDuration').textContent = minutes.toString().padStart(2, '0') + ':' + seconds.toString().padStart(2, '0'); } }, 1000); }");
    
    server.sendContent("function toggleMute() { isMuted = !isMuted; const muteBtn = document.getElementById('muteBtn'); if (isMuted) { muteBtn.classList.add('muted'); muteBtn.innerHTML = '🎤🚫'; stopListening(); } else { muteBtn.classList.remove('muted'); muteBtn.innerHTML = '🎤'; if (isInCall && !isAISpeaking) { setTimeout(() => startListening(), 500); } } }");
    
    server.sendContent("function copyCallTranscript() { const transcript = document.getElementById('callTranscript'); let text = 'Call Transcript:\\n\\n'; const entries = transcript.querySelectorAll('.transcript-entry'); entries.forEach(entry => { text += entry.textContent + '\\n'; }); copyToClipboard(text); }");
    
    server.sendContent("function speakCallTranscript() { const transcript = document.getElementById('callTranscript'); let text = 'Reading call transcript. '; const entries = transcript.querySelectorAll('.transcript-entry'); entries.forEach(entry => { text += entry.textContent + '. '; }); speakText(text); }");
    
    server.sendContent("function addCallSummaryToChat(duration) { const chatContainer = document.getElementById('chatContainer'); const exchanges = Math.floor(conversationHistory.length / 2); const summaryText = '📞 Voice Call Summary:\\n\\n' + '⏰ Duration: ' + duration + '\\n' + '💬 Exchanges: ' + exchanges + ' back-and-forth conversations\\n' + '🤖 Topics discussed: ' + (conversationHistory.length > 2 ? 'Various questions and responses' : 'Brief conversation') + '\\n\\n' + 'Call ended successfully. Feel free to start another call or continue chatting!'; const summaryDiv = createMessageElement('bot', summaryText); chatContainer.appendChild(summaryDiv); scrollToBottom(); }");
    
    server.sendContent("function addCallEndedToChat(duration) { const chatContainer = document.getElementById('chatContainer'); const summaryText = '📞 Voice Call Ended\\n\\n' + '⏰ Duration: ' + duration + '\\n' + '💬 Status: Call ended without conversation\\n\\n' + 'Ready for your next call or message!'; const summaryDiv = createMessageElement('bot', summaryText); chatContainer.appendChild(summaryDiv); scrollToBottom(); }");
    
    server.sendContent("function addVideoCallSummaryToChat(duration) { const chatContainer = document.getElementById('chatContainer'); const exchanges = Math.floor(conversationHistory.length / 2); const summaryText = '📹 Video Call Summary:\\n\\n' + '⏰ Duration: ' + duration + '\\n' + '💬 Exchanges: ' + exchanges + ' back-and-forth conversations\\n' + '📸 Video Analysis: ' + analysisCount + ' automatic analysis performed\\n' + '🎥 Camera: ' + (currentCamera === 'environment' ? 'Back camera used' : 'Front camera used') + '\\n' + '🤖 Topics discussed: ' + (conversationHistory.length > 2 ? 'Various questions with visual context' : 'Brief video conversation') + '\\n\\n' + 'Video call ended successfully. Feel free to start another call or continue chatting!'; const summaryDiv = createMessageElement('bot', summaryText); chatContainer.appendChild(summaryDiv); scrollToBottom(); }");
    
    server.sendContent("function addVideoCallEndedToChat(duration) { const chatContainer = document.getElementById('chatContainer'); const summaryText = '📹 Video Call Ended\\n\\n' + '⏰ Duration: ' + duration + '\\n' + '💬 Status: Video call ended without conversation\\n' + '📸 Analysis: ' + analysisCount + ' automatic scans performed\\n' + '🎥 Camera: ' + (currentCamera === 'environment' ? 'Back camera' : 'Front camera') + '\\n\\n' + 'Ready for your next video call or message!'; const summaryDiv = createMessageElement('bot', summaryText); chatContainer.appendChild(summaryDiv); scrollToBottom(); }");

    // Video call functionality - toggleVideoCall is now defined earlier with toggleCall
    server.sendContent("async function startVideoCall() { if (!geminiApiKey) { alert('Please set your API key in Settings first.'); return; } if (!continuousRecognition) { alert('Speech recognition is not supported in your browser. Please use Chrome, Edge, or Safari.'); return; } if (!navigator.mediaDevices || !navigator.mediaDevices.getUserMedia) { alert('Camera and microphone access is not supported in your browser.'); return; } try { console.log('Starting video call...'); if (typeof currentCamera === 'undefined' || !currentCamera) { currentCamera = 'user'; console.log('Initialized currentCamera to default:', currentCamera); } console.log('Using camera:', currentCamera); const constraints = { video: { facingMode: currentCamera, width: { ideal: 1280 }, height: { ideal: 720 } }, audio: true }; console.log('Requesting media with constraints:', constraints); videoStream = await navigator.mediaDevices.getUserMedia(constraints); const videoElement = document.getElementById('userVideo'); videoElement.srcObject = videoStream; isInVideoCall = true; isCameraOn = true; isMuted = false; conversationHistory = []; callStartTime = Date.now(); analysisCount = 0; isProcessingResponse = false; lastTranscript = ''; lastResponseTime = 0; microphonePermissionGranted = true; document.getElementById('videoCallInterface').style.display = 'flex'; document.getElementById('videoCallBtn').textContent = '📹 End Video Call'; document.getElementById('videoCallBtn').classList.add('calling'); document.getElementById('videoCallStatus').textContent = 'Connected'; document.getElementById('videoMuteBtn').classList.remove('muted'); document.getElementById('videoMuteBtn').innerHTML = '🎤'; document.getElementById('videoCameraBtn').classList.remove('off'); document.getElementById('videoCameraBtn').innerHTML = '📹'; console.log('Video call started successfully'); await enumerateCameras(); startVideoCallTimer(); videoAnalysisInterval = setInterval(() => { if (isInVideoCall && isCameraOn && !isAISpeaking && !isProcessingResponse) { analyzeVideoAutomatically(); } }, 30000); const greeting = 'Hi! I can see and hear you now. How can I help you today?'; conversationHistory.push({ role: 'assistant', content: greeting }); addToVideoTranscript('ai', greeting); speakTextInVideoCall(greeting, () => { if (isInVideoCall) { setTimeout(() => startVideoListening(), 1000); } }); } catch (error) { console.error('Error starting video call:', error); if (error.name === 'NotAllowedError') { alert('Camera and microphone access are required for video calls. Please allow access in your browser settings and try again.'); } else if (error.name === 'NotFoundError') { alert('Camera or microphone not found. Please connect your devices and try again.'); } else if (error.name === 'OverconstrainedError') { console.log('Camera constraints not supported, trying basic constraints...'); try { const basicConstraints = { video: true, audio: true }; videoStream = await navigator.mediaDevices.getUserMedia(basicConstraints); const videoElement = document.getElementById('userVideo'); videoElement.srcObject = videoStream; currentCamera = 'user'; isInVideoCall = true; isCameraOn = true; document.getElementById('videoCallInterface').style.display = 'flex'; document.getElementById('videoCallBtn').textContent = '📹 End Video Call'; document.getElementById('videoCallBtn').classList.add('calling'); alert('Started video call with basic camera settings.'); } catch (basicError) { alert('Failed to start video call: ' + basicError.message); } } else { alert('Failed to start video call: ' + error.message); } } }");
    
    server.sendContent("function endVideoCall() { console.log('Ending video call...'); isInVideoCall = false; isCameraOn = false; isMuted = false; isAISpeaking = false; isListeningForUser = false; speechSynthesis.cancel(); if (continuousRecognition) { try { continuousRecognition.stop(); } catch (e) {} } if (videoStream) { videoStream.getTracks().forEach(track => track.stop()); videoStream = null; } if (videoAnalysisInterval) { clearInterval(videoAnalysisInterval); } if (callDurationInterval) { clearInterval(callDurationInterval); } const finalDuration = document.getElementById('videoCallDuration').textContent || '00:00'; document.getElementById('videoCallInterface').style.display = 'none'; document.getElementById('videoCallBtn').textContent = '📹 Video Call'; document.getElementById('videoCallBtn').classList.remove('calling'); document.getElementById('listeningIndicator').style.display = 'none'; document.getElementById('speakingIndicator').style.display = 'none'; document.getElementById('videoAnalysisIndicator').style.display = 'none'; const switchBtn = document.getElementById('switchCameraBtn'); if (switchBtn) { switchBtn.disabled = false; switchBtn.innerHTML = '🔄'; } if (conversationHistory.length > 1) { addVideoCallSummaryToChat(finalDuration); } else { addVideoCallEndedToChat(finalDuration); } console.log('Video call ended successfully'); }");
    
    server.sendContent("function startVideoListening() { if (!isInVideoCall || isMuted || isAISpeaking || !continuousRecognition || isProcessingResponse) { return; } try { isListeningForUser = true; document.getElementById('listeningIndicator').style.display = 'flex'; document.getElementById('speakingIndicator').style.display = 'none'; try { continuousRecognition.stop(); } catch (e) {} setTimeout(() => { if (isInVideoCall && !isMuted && !isAISpeaking && !isProcessingResponse) { try { continuousRecognition.start(); } catch (error) { console.error('Error starting video recognition:', error); } } }, 300); } catch (error) { console.error('Error starting video call speech recognition:', error); } }");
    
    server.sendContent("function stopVideoListening() { isListeningForUser = false; document.getElementById('listeningIndicator').style.display = 'none'; if (continuousRecognition) { try { continuousRecognition.stop(); } catch (e) {} } }");
    
    server.sendContent("function speakTextInVideoCall(text, onComplete) { if (!isInVideoCall) return; isAISpeaking = true; stopVideoListening(); document.getElementById('speakingIndicator').style.display = 'flex'; document.getElementById('listeningIndicator').style.display = 'none'; speechSynthesis.cancel(); currentUtterance = new SpeechSynthesisUtterance(text); currentUtterance.rate = speechRate; if (selectedVoice) { currentUtterance.voice = selectedVoice; } currentUtterance.onend = () => { isAISpeaking = false; document.getElementById('speakingIndicator').style.display = 'none'; if (onComplete) onComplete(); }; currentUtterance.onerror = () => { isAISpeaking = false; document.getElementById('speakingIndicator').style.display = 'none'; if (onComplete) onComplete(); }; speechSynthesis.speak(currentUtterance); }");
    
    server.sendContent("async function handleVideoCallUserInput(transcript) { if (!isInVideoCall || isAISpeaking || isProcessingResponse) return; const isDuplicate = conversationHistory.length > 0 && conversationHistory[conversationHistory.length - 1].role === 'user' && conversationHistory[conversationHistory.length - 1].content.toLowerCase() === transcript.toLowerCase(); if (isDuplicate) { return; } isProcessingResponse = true; conversationHistory.push({ role: 'user', content: transcript }); addToVideoTranscript('user', transcript); stopVideoListening(); try { const response = await callGeminiAPIForCall(transcript); if (response && response.candidates && response.candidates[0]) { const aiResponse = response.candidates[0].content.parts[0].text; conversationHistory.push({ role: 'assistant', content: aiResponse }); addToVideoTranscript('ai', aiResponse); speakTextInVideoCall(aiResponse, () => { isProcessingResponse = false; if (isInVideoCall && !isMuted) { setTimeout(() => startVideoListening(), 1000); } }); } else { throw new Error('Invalid response format'); } } catch (error) { console.error('Error in video call processing:', error); const errorMessage = 'Sorry, I didn\\'t catch that. Could you please repeat?'; addToVideoTranscript('ai', errorMessage); speakTextInVideoCall(errorMessage, () => { isProcessingResponse = false; if (isInVideoCall && !isMuted) { setTimeout(() => startVideoListening(), 1000); } }); } }");
    
    server.sendContent("function addToVideoTranscript(sender, text) { const transcript = document.getElementById('videoTranscript'); const entry = document.createElement('div'); entry.className = 'transcript-entry transcript-' + sender; entry.innerHTML = '<strong>' + (sender === 'user' ? 'You' : 'AI') + ':</strong> ' + text; transcript.appendChild(entry); transcript.scrollTop = transcript.scrollHeight; }");
    
    server.sendContent("function startVideoCallTimer() { callDurationInterval = setInterval(() => { if (isInVideoCall && callStartTime) { const duration = Math.floor((Date.now() - callStartTime) / 1000); const minutes = Math.floor(duration / 60); const seconds = duration % 60; document.getElementById('videoCallDuration').textContent = minutes.toString().padStart(2, '0') + ':' + seconds.toString().padStart(2, '0'); } }, 1000); }");
    
    server.sendContent("function toggleVideoMute() { isMuted = !isMuted; const muteBtn = document.getElementById('videoMuteBtn'); if (isMuted) { muteBtn.classList.add('muted'); muteBtn.innerHTML = '🎤🚫'; stopVideoListening(); } else { muteBtn.classList.remove('muted'); muteBtn.innerHTML = '🎤'; if (isInVideoCall && !isAISpeaking) { setTimeout(() => startVideoListening(), 500); } } }");
    
    server.sendContent("function toggleCamera() { isCameraOn = !isCameraOn; const cameraBtn = document.getElementById('videoCameraBtn'); const videoElement = document.getElementById('userVideo'); if (isCameraOn) { cameraBtn.classList.remove('off'); cameraBtn.innerHTML = '📹'; if (videoStream) { videoElement.srcObject = videoStream; } } else { cameraBtn.classList.add('off'); cameraBtn.innerHTML = '📹🚫'; videoElement.srcObject = null; } }");
    
    server.sendContent("function captureAndAnalyze() { if (!isInVideoCall || !isCameraOn) { alert('Video call and camera must be active for analysis.'); return; } const video = document.getElementById('userVideo'); const canvas = document.getElementById('videoCaptureCanvas'); const ctx = canvas.getContext('2d'); canvas.width = video.videoWidth; canvas.height = video.videoHeight; ctx.drawImage(video, 0, 0); document.getElementById('videoAnalysisIndicator').style.display = 'flex'; canvas.toBlob(async (blob) => { try { const response = await callGeminiAPI('Please analyze what you see in this image and provide feedback on what I\\'m doing.', blob); if (response && response.candidates && response.candidates[0]) { const analysisResult = response.candidates[0].content.parts[0].text; addToVideoTranscript('ai', '📸 Analysis: ' + analysisResult); speakTextInVideoCall('I can see ' + analysisResult, () => { if (isInVideoCall && !isMuted) { setTimeout(() => startVideoListening(), 1000); } }); } } catch (error) { console.error('Video analysis error:', error); addToVideoTranscript('ai', 'Sorry, I couldn\\'t analyze the image.'); } finally { document.getElementById('videoAnalysisIndicator').style.display = 'none'; } }, 'image/jpeg', 0.8); }");
    
    server.sendContent("function analyzeVideoAutomatically() { if (!isInVideoCall || !isCameraOn || isAISpeaking || isProcessingResponse) return; analysisCount++; if (analysisCount % 2 === 0) { const video = document.getElementById('userVideo'); const canvas = document.getElementById('videoCaptureCanvas'); const ctx = canvas.getContext('2d'); canvas.width = video.videoWidth; canvas.height = video.videoHeight; ctx.drawImage(video, 0, 0); canvas.toBlob(async (blob) => { try { const response = await callGeminiAPI('Briefly describe what you see in this image. Keep it under 20 words.', blob); if (response && response.candidates && response.candidates[0]) { const analysisResult = response.candidates[0].content.parts[0].text; console.log('Auto-analysis:', analysisResult); } } catch (error) { console.error('Auto video analysis error:', error); } }, 'image/jpeg', 0.6); } }");
    
    server.sendContent("function copyVideoTranscript() { const transcript = document.getElementById('videoTranscript'); let text = 'Video Call Transcript:\\n\\n'; const entries = transcript.querySelectorAll('.transcript-entry'); entries.forEach(entry => { text += entry.textContent + '\\n'; }); copyToClipboard(text); }");
    
    server.sendContent("function speakVideoTranscript() { const transcript = document.getElementById('videoTranscript'); let text = 'Reading video call transcript. '; const entries = transcript.querySelectorAll('.transcript-entry'); entries.forEach(entry => { text += entry.textContent + '. '; }); speakText(text); }");
    
    server.sendContent("function addVideoCallSummaryToChat() { const chatContainer = document.getElementById('chatContainer'); const summaryDiv = createMessageElement('bot', '📹 Video Call Summary: ' + conversationHistory.length + ' exchanges. Duration: ' + document.getElementById('videoCallDuration').textContent + '. Analysis count: ' + analysisCount); chatContainer.appendChild(summaryDiv); scrollToBottom(); }");
    
    // Console log for successful loading
    server.sendContent("console.log('ESP32 AI Assistant with complete features loaded successfully');");
    
    // Window cleanup on page unload
    server.sendContent("window.addEventListener('beforeunload', function() {");
    server.sendContent("if ('speechSynthesis' in window) {");
    server.sendContent("speechSynthesis.cancel();");
    server.sendContent("}");
    server.sendContent("if (videoStream) {");
    server.sendContent("videoStream.getTracks().forEach(track => track.stop());");
    server.sendContent("}");
    server.sendContent("if (continuousRecognition) {");
    server.sendContent("try { continuousRecognition.stop(); } catch (e) {}");
    server.sendContent("}");
    server.sendContent("});");
}

void handleNotFound() {
    String html = "<!DOCTYPE html>";
    html += "<html><head>";
    html += "<meta charset=\"UTF-8\">";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    html += "<title>404 - ESP32 AI Assistant</title>";
    html += "<style>";
    html += "* { margin: 0; padding: 0; box-sizing: border-box; }";
    html += "body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); min-height: 100vh; display: flex; align-items: center; justify-content: center; padding: clamp(16px, 4vw, 32px); }";
    html += ".container { max-width: clamp(280px, 85vw, 500px); background: rgba(255, 255, 255, 0.98); backdrop-filter: blur(15px); padding: clamp(24px, 6vw, 40px); border-radius: clamp(15px, 3vw, 25px); text-align: center; box-shadow: 0 20px 40px rgba(0,0,0,0.1); border: 1px solid rgba(255,255,255,0.3); }";
    html += "h1 { color: #e74c3c; margin-bottom: clamp(16px, 4vw, 24px); font-size: clamp(24px, 5vw, 36px); font-weight: 700; }";
    html += "p { color: #4a5568; margin-bottom: clamp(20px, 5vw, 32px); font-size: clamp(14px, 3vw, 18px); line-height: 1.5; }";
    html += ".btn { background: linear-gradient(45deg, #4f46e5, #7c3aed); color: white; padding: clamp(12px, 3vw, 16px) clamp(20px, 5vw, 32px); text-decoration: none; border-radius: clamp(20px, 5vw, 40px); font-size: clamp(14px, 3vw, 18px); font-weight: 600; display: inline-block; margin-top: clamp(8px, 2vw, 16px); transition: all 0.3s ease; }";
    html += ".btn:hover { background: linear-gradient(45deg, #3730a3, #6d28d9); transform: translateY(-2px); box-shadow: 0 8px 20px rgba(79, 70, 229, 0.4); }";
    html += ".emoji { font-size: clamp(48px, 10vw, 72px); margin-bottom: clamp(16px, 4vw, 24px); }";
    html += "</style></head><body>";
    html += "<div class=\"container\">";
    html += "<div class=\"emoji\">🤖❓</div>";
    html += "<h1>404 - Page Not Found</h1>";
    html += "<p>The page you're looking for doesn't exist on this ESP32 AI Assistant server.</p>";
    html += "<a href=\"/\" class=\"btn\">🏠 Return to Home</a>";
    html += "</div></body></html>";
    
    server.send(404, "text/html", html);
}