#ifndef _MQTT_H__
#define _MQTT_H__

#include "esp_err.h"
#include "mqtt_client.h"

//#define CONFIG_BROKER_URL "mqtt://sebi:admin@192.168.1.4:1883"

static esp_mqtt_client_handle_t client_handle;

// Init MQTT 
void mqtt_init(void);

// Start MQTT
void mqtt_start(void);

#endif // _MQTT_H__