#include <Arduino.h>
#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void accessory_identify(homekit_value_t _value) {
  Serial.println("Accessory identify");
}

// ---------- HomeKit Characteristics ----------
homekit_characteristic_t cha_current_temperature = HOMEKIT_CHARACTERISTIC_( CURRENT_TEMPERATURE, 0 );
homekit_characteristic_t cha_current_humidity    = HOMEKIT_CHARACTERISTIC_( CURRENT_RELATIVE_HUMIDITY, 0 );

// ---------- Accessory ----------
homekit_accessory_t *accessories[] = {
  HOMEKIT_ACCESSORY(
    .id=1,
    .category=homekit_accessory_category_sensor,
    .services=(homekit_service_t*[]) {
      HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]){
        HOMEKIT_CHARACTERISTIC(NAME, "Capteur DHT11"),
        HOMEKIT_CHARACTERISTIC(MANUFACTURER, "DIY"),
        HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "001"),
        HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266-DHT11"),
        HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
        HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
        NULL
      }),
      
      // ---- Température ----
      HOMEKIT_SERVICE(TEMPERATURE_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]){
        &cha_current_temperature,
        HOMEKIT_CHARACTERISTIC(NAME, "Température"),
        NULL
      }),

      // ---- Humidité ----
      HOMEKIT_SERVICE(HUMIDITY_SENSOR, .characteristics=(homekit_characteristic_t*[]){
        &cha_current_humidity,
        HOMEKIT_CHARACTERISTIC(NAME, "Humidité"),
        NULL
      }),

      NULL
    }
  ),
  NULL
};

// ---------- Server config ----------
homekit_server_config_t config = {
  .accessories = accessories,
  .password = "111-11-111",   // Code HomeKit pour ajouter l’accessoire
};