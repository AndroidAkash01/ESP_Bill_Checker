#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "wifi_config.h"
#include <ArduinoJson.h>
#include <time.h>



float getElectricityPrice() {

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("No WiFi");
        return -1.0;
    }

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    const char* url = "https://nordapi.ee/api/v1/electricity/current/SE3";

    http.begin(client, url);

    int httpCode = http.GET();

    if (httpCode <= 0) {
        Serial.print("HTTP Error: ");
        Serial.println(httpCode);
        http.end();
        return -1.0;
    }

    String payload = http.getString();
    http.end();
    Serial.println(payload);

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
        Serial.print("JSON parse failed: ");
        Serial.println(error.c_str());
        return -1.0;
    }

    bool success = doc["success"] | false;
    if (!success) {
        Serial.println("API returned success = false");
        return -1.0;
    }

    if (!doc["price_local_kwh"].is<float>() && !doc["price_local_kwh"].is<double>()) {
        Serial.println("Missing price_local_kwh in API response");
        return -1.0;
    }

    float price = doc["price_local_kwh"].as<float>();

    const char* zone = doc["zone"] | "unknown";
    const char* startTime = doc["hour_start"] | "";
    const char* endTime = doc["hour_end"] | "";

    Serial.print("Zone: ");
    Serial.println(zone);

    Serial.print("Window: ");
    Serial.print(startTime);
    Serial.print(" -> ");
    Serial.println(endTime);

    Serial.print("⚡ Current electricity price: ");
    Serial.print(price, 5);
    Serial.println(" SEK/kWh");

    return price;
}



bool connectToWiFi() {
    Serial.print("Connecting to WiFi: ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int attempts = 0;

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        attempts++;

        if (attempts > 30) {
            Serial.println("\n❌ Failed to connect");
            Serial.print("Status code: ");
            Serial.println(WiFi.status()); // 👈 IMPORTANT
            return false;
        }
    }

    Serial.println("\n✅ Connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    return true;

}

bool checkConnection() {
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi OK");
        return true;
    } else {
        Serial.println("WiFi LOST");
        return false;
    }
}

void testServer() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("No WiFi, skipping request");
        return;
    }

    HTTPClient http;
    http.begin(TEST_HOST);

    int httpCode = http.GET();

    if (httpCode > 0) {
        Serial.print("Server responded with code: ");
        Serial.println(httpCode);
    } else {
        Serial.print("Request failed: ");
        Serial.println(http.errorToString(httpCode));
    }

    http.end();
}