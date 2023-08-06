#ifndef _CAMERA_H__
#define _CAMERA_H__

// Camera pins
#include "camera_pins.h"

#include "esp_camera.h"
#include "img_converters.h"
#include "esp_err.h"



// Initialize camera
esp_err_t camera_init();

// Get Camera image pointer
esp_err_t camera_capture_frame(camera_fb_t* fb);

#endif // _CAMERA_H__