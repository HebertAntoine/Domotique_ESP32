#include <Arduino.h>
#include <ESP8266WiFi.h>

// WiFiManager pour portail de config Wi-Fi
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <arduino_homekit_server.h>
#include <DHT.h>

// ------------ DHT11 ------------
#define DHTPIN D3        // D3 = GPIO0 sur NodeMCU
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ------------ HomeKit (définis dans my_accessory.c) ------------
extern "C" {
  #include "homekit/homekit.h"
  #include "homekit/characteristics.h"

  extern homekit_server_config_t config;
  extern homekit_characteristic_t cha_current_temperature;
  extern homekit_characteristic_t cha_current_humidity;
}

// ------------ Variables ------------
unsigned long next_measure_ms = 0;

// ------------ Portail Wi-Fi (pop-up) ------------
void wifi_setup_with_portal() {
  WiFi.mode(WIFI_STA);

  WiFiManager wm;
  bool res = wm.autoConnect("DHT11_Setup");

  if (!res) {
    Serial.println("Echec configuration WiFi, reboot...");
    delay(3000);
    ESP.restart();
  } else {
    Serial.println("WiFi connecté !");
    Serial.print("SSID : ");
    Serial.println(WiFi.SSID());
    Serial.print("IP   : ");
    Serial.println(WiFi.localIP());
  }
}

// ------------ Setup ------------
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("==== DHT11 + HomeKit (ESP8266) ====");

  dht.begin();

  // 1) Portail Wi-Fi
  wifi_setup_with_portal();

  // 2) HomeKit
  arduino_homekit_setup(&config);
}

// ------------ Lecture capteur + notif HomeKit ------------
void update_sensor() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Erreur lecture DHT11");
    return;
  }

  Serial.print("Température = ");
  Serial.print(t);
  Serial.println(" °C");

  Serial.print("Humidité = ");
  Serial.print(h);
  Serial.println(" %");

  // --- HomeKit ---
  cha_current_temperature.value.float_value = t;
  homekit_characteristic_notify(&cha_current_temperature, cha_current_temperature.value);

  cha_current_humidity.value.float_value = h;
  homekit_characteristic_notify(&cha_current_humidity, cha_current_humidity.value);
}

// ------------ Loop ------------
void loop() {
  arduino_homekit_loop();

  unsigned long now = millis();
  if (now > next_measure_ms) {
    next_measure_ms = now + 5000;   // toutes les 5 secondes
    update_sensor();
  }

  delay(10);
}