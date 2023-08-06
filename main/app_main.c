/* MQTT (over TCP) Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "driver/gpio.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"

#include "mqtt.h"
#include "wifi.h"
#include "camera.h"

static const char* TAG = "Main";

#include "mqtt_client.h"

void app_main(void)
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %"PRIu32" bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("mqtt_client", ESP_LOG_VERBOSE);
    esp_log_level_set("MQTT_EXAMPLE", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_BASE", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("outbox", ESP_LOG_VERBOSE);

    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) 
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Init wifi connection
    ESP_LOGI(TAG, "Wifi init");
    wifi_init_sta();

    // Init MQTT connection
    ESP_LOGI(TAG, "MQTT Init");
    mqtt_init();
    // Start MQTT 
    ESP_LOGI(TAG, "MQTT Start");
    mqtt_start();

    // Init camera
    ESP_LOGI(TAG, "Camera Init");
    camera_init();

    // Send image
    // camera_fb_t* fb = esp_camera_fb_get();
    //ESP_ERROR_CHECK(camera_capture_frame(fb));
    
    uint8_t* jpg_buf = NULL;
    size_t jpg_buf_len = 0;

    const uint8_t quality = 80;
    
    //ESP_LOGI(TAG, "Size -> h: %d w: %d ", fb->height, fb->width);
    // if (frame2jpg(fb, quality, &jpg_buf, &jpg_buf_len) == false)
    // {1
    //     ESP_LOGE(TAG, "Error when converting camera frame to jpg");
    //     return;
    // }

    //vTaskDelay(3000 / portTICK_PERIOD_MS);
    // int mqtt_ret = esp_mqtt_client_enqueue(client_handle, "/data", (const char*)fb->buf, fb->len, 1, 0, 0);
    // ESP_LOGI(TAG, "Send data ==> %d", mqtt_ret);

    // esp_camera_fb_return(fb);
    // free(fb);
}
