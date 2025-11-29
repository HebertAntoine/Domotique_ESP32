#include <stdio.h>
#include "homekit/homekit.h"
#include "homekit/characteristics.h"

// --------- Caractéristiques globales (utilisées dans le .ino) ---------

homekit_characteristic_t cha_current_temperature =
    HOMEKIT_CHARACTERISTIC_(CURRENT_TEMPERATURE, 0.0);

homekit_characteristic_t cha_current_humidity =
    HOMEKIT_CHARACTERISTIC_(CURRENT_RELATIVE_HUMIDITY, 0.0);

// --------- Fonction Identify (quand tu appuies sur "Identifier" dans Maison) ---------

void accessory_identify(homekit_value_t _value) {
    printf("Accessory identify\n");
}

// --------- Définition de l’accessoire HomeKit ---------

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(
        .id = 1,
        .category = homekit_accessory_category_sensor,
        .services = (homekit_service_t*[]){
            // Service Info Accessoire
            HOMEKIT_SERVICE(
                ACCESSORY_INFORMATION,
                .characteristics = (homekit_characteristic_t*[]){
                    HOMEKIT_CHARACTERISTIC(NAME, "Capteur DHT11"),
                    HOMEKIT_CHARACTERISTIC(MANUFACTURER, "DIY"),
                    HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "001"),
                    HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266-DHT11"),
                    HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
                    HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
                    NULL
                }
            ),

            // Service Température (service principal)
            HOMEKIT_SERVICE(
                TEMPERATURE_SENSOR,
                .primary = true,
                .characteristics = (homekit_characteristic_t*[]){
                    &cha_current_temperature,
                    NULL
                }
            ),

            // Service Humidité
            HOMEKIT_SERVICE(
                HUMIDITY_SENSOR,
                .characteristics = (homekit_characteristic_t*[]){
                    &cha_current_humidity,
                    NULL
                }
            ),

            NULL
        }
    ),
    NULL
};

// --------- Configuration HomeKit (code de jumelage) ---------

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "111-11-111",   // code que tu rentreras dans l’app Maison
};