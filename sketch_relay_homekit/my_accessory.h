#pragma once

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

#ifdef __cplusplus
extern "C" {
#endif

extern homekit_server_config_t config;
extern homekit_characteristic_t cha_switch_on;

#ifdef __cplusplus
}
#endif