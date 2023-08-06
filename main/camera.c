#include "camera.h"

#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_log.h"

const static char* TAG = "Camera";

const static camera_config_t camera_config = {
    .pin_pwdn  = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sccb_sda = CAM_PIN_SIOD,
    .pin_sccb_scl = CAM_PIN_SIOC,

    .pin_d7 = CAM_PIN_D7,
    .pin_d6 = CAM_PIN_D6,
    .pin_d5 = CAM_PIN_D5,
    .pin_d4 = CAM_PIN_D4,
    .pin_d3 = CAM_PIN_D3,
    .pin_d2 = CAM_PIN_D2,
    .pin_d1 = CAM_PIN_D1,
    .pin_d0 = CAM_PIN_D0,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,

    .xclk_freq_hz = 20000000,//EXPERIMENTAL: Set to 16MHz on ESP32-S2 or ESP32-S3 to enable EDMA mode
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG,//YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_UXGA,//QQVGA-UXGA, For ESP32, do not use sizes above QVGA when not JPEG. The performance of the ESP32-S series has improved a lot, but JPEG mode always gives better frame rates.

    .jpeg_quality = 12, //0-63, for OV series camera sensors, lower number means higher quality
    .fb_count = 1, //When jpeg mode is used, if fb_count more than one, the driver will work in continuous mode.
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY,//CAMERA_GRAB_LATEST. Sets when buffers should be filled
};

esp_err_t camera_capture_frame(camera_fb_t* fb)
{
    //camera_fb_t* tmp_fb = esp_camera_fb_get();
    fb = esp_camera_fb_get();
    if (fb == NULL) 
    {
        ESP_LOGE(TAG, "Camera Capture Failed");
        return ESP_FAIL;
    }

    // //replace this with your own function
    // process_image(fb->width, fb->height, fb->format, fb->buf, fb->len);
    //ESP_LOGI(TAG, "Size -> h: %d w: %d len: %d", tmp_fb->height, tmp_fb->width, tmp_fb->len);
    // fb = (camera_fb_t*)malloc(sizeof(camera_fb_t));
    // if (fb == NULL) 
    // {
    //     ESP_LOGE(TAG, "Allocate camera frame space error");
    //     return ESP_FAIL;
    // }
    // fb->buf = (uint8_t*)malloc(fb->len * sizeof(uint8_t));
    // if (fb->buf == NULL) 
    // {
    //     ESP_LOGE(TAG, "Allocate camera frame space error");
    //     return ESP_FAIL;
    // }

    // Copy temp_image pointer data to image
    // memcpy(fb, tmp_fb, sizeof(camera_fb_t));
    // memcpy(fb->buf, tmp_fb->buf, fb->len * sizeof(uint8_t));

    // Return the frame buffer back to the driver for reuse
    // esp_camera_fb_return(tmp_fb);

    return ESP_OK;
}




esp_err_t camera_init()
{
    // Power up the camera if PWDN pin is defined
    if(CAM_PIN_PWDN != -1)
    {
        gpio_set_direction(CAM_PIN_PWDN, GPIO_MODE_OUTPUT);
        gpio_set_level(CAM_PIN_PWDN, 0);
    }

    // Initialize the camera
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK) 
    {
        ESP_LOGE(TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}