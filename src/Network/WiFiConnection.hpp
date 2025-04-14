#pragma once

#include <WiFi.h>
#include <AH/Arduino-Wrapper.h>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for managing WiFi connections
 */
class WiFiConnection {
  public:
    /**
     * @brief Constructor for WiFiConnection
     * 
     * @param ssid WiFi network name
     * @param pwd WiFi password
     */
    WiFiConnection(const char *ssid = nullptr, const char *pwd = nullptr)
        : _ssid(ssid), _pwd(pwd), _connected(false) {}

    /**
     * @brief Initialize the WiFi connection
     */
    virtual void begin() {
        if (_ssid == nullptr || _pwd == nullptr) {
            Serial.println("Error: WiFi credentials not set");
            return;
        }

        Serial.println("Connecting to WiFi network: " + String(_ssid));

        // delete old config
        WiFi.disconnect(true);
        
        //Initiate connection
        WiFi.begin(_ssid, _pwd);
        
        Serial.println("Waiting for WIFI connection...");
        
        // Wait for connection with timeout
        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED) {
            if (millis() - startTime > 20000) { // 20 second timeout
                Serial.println("WiFi connection timeout");
                return;
            }
            delay(500);
            Serial.print(".");
        }
        
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        
        _connected = true;
    }

    /**
     * @brief Set WiFi credentials
     * 
     * @param ssid WiFi network name
     * @param pwd WiFi password
     */
    void setWiFiCredentials(const char *ssid, const char *pwd) {
        _ssid = ssid;
        _pwd = pwd;
    }

    /**
     * @brief Update function to check WiFi connection status
     */
    virtual void update() {
        if (!_connected) {
            if (WiFi.status() == WL_CONNECTED) {
                _connected = true;
                Serial.println("WiFi reconnected");
            }
            return;
        }
        
        if (WiFi.status() != WL_CONNECTED) {
            _connected = false;
            Serial.println("WiFi connection lost");
            return;
        }
    }

    /**
     * @brief Check if WiFi is connected
     * 
     * @return true if connected, false otherwise
     */
    bool isConnected() const {
        return _connected;
    }

  protected:
    const char* _ssid;
    const char* _pwd;
    bool _connected;
};

END_CS_NAMESPACE
