// my_accessory.c
#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <stdio.h>

// Fonction d'identification (appelée quand tu cliques sur "Identifier" dans Maison)
void accessory_identify(homekit_value_t _value) {
    printf("Accessory identify\n");
}

// Caractéristique de température (celle qu'on mettra à jour depuis l'ESP8266)
homekit_characteristic_t cha_current_temperature = HOMEKIT_CHARACTERISTIC_(
    CURRENT_TEMPERATURE,
    0.0
);

// Nom de l’accessoire (visible dans Maison)
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "Capteur DHT11");

// Définition de l’accessoire HomeKit
homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(
        .id = 1,
        .category = homekit_accessory_category_sensor,
        .services = (homekit_service_t*[]) {
            // Service info
            HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics = (homekit_characteristic_t*[]) {
                HOMEKIT_CHARACTERISTIC(NAME, "Capteur Température"),
                HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Antoine"),
                HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0001"),
                HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266-DHT11"),
                HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
                HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
                NULL
            }),
            // Service capteur de température
            HOMEKIT_SERVICE(TEMPERATURE_SENSOR, .primary = true, .characteristics = (homekit_characteristic_t*[]) {
                &cha_current_temperature,
                NULL
            }),
            NULL
        }),
    NULL
};

// Configuration du serveur HomeKit
homekit_server_config_t config = {
    .accessories = accessories,
    // Code HomeKit à entrer dans l'app Maison :
    .password = "111-11-111",
};