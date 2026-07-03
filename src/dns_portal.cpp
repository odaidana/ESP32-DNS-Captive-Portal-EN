#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>

// Network credentials for the Local Access Point
const char* AP_SSID = "ESP32_Local_Network";
const char* AP_PASS = "123456789";

// Standard DNS port configuration
const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer webServer(80);

// Simple production response page for redirected clients
const char* HTML_CONTENT = 
"<!DOCTYPE html><html><head><title>ESP32 Portal</title></head>"
"<body style='background:#0f172a; color:#f8fafc; font-family:sans-serif; text-align:center; padding:50px;'>"
"<h1>Welcome to ESP32 Local Dashboard</h1>"
"<p>Your DNS request was successfully resolved by the microcontroller stack.</p>"
"</body></html>";

void handle_captive_portal() {
    webServer.send(200, "text/html", HTML_CONTENT);
}

void setup() {
    Serial.begin(115200);
    
    // 1. Initializing the independent Wi-Fi Access Point
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);
    
    IPAddress apIP = WiFi.softAPIP();
    Serial.print("[WiFi] Access Point Ready. IP Address: ");
    Serial.println(apIP);

    // 2. Booting the DNS Server to intercept all incoming requests (*)
    dnsServer.start(DNS_PORT, "*", apIP);
    Serial.println("[DNS] Server active on Port 53. Intercepting queries.");

    // 3. Setting up HTTP routing rules
    webServer.onNotFound(handle_captive_portal);
    webServer.begin();
    Serial.println("[HTTP] Web Server online.");
}

void loop() {
    // Process pending DNS and HTTP networking operations
    dnsServer.processNextRequest();
    webServer.handleClient();
    delay(1);
}
