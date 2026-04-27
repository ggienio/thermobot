#include <WiFi.h>
#include "camera.h"
#include "esp_camera.h"
#include "app_httpd.h"

void Camera::init() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = pin_y2;
    config.pin_d1 = pin_y3;
    config.pin_d2 = pin_y4;
    config.pin_d3 = pin_y5;
    config.pin_d4 = pin_y6;
    config.pin_d5 = pin_y7;
    config.pin_d6 = pin_y8;
    config.pin_d7 = pin_y9;
    config.pin_xclk = pin_xclk;
    config.pin_pclk = pin_pclk;
    config.pin_vsync = pin_vsync;
    config.pin_href = pin_href;
    config.pin_sccb_sda = pin_siod;
    config.pin_sccb_scl = pin_sioc;
    config.pin_pwdn = pin_pwdn;
    config.pin_reset = pin_reset;
    config.xclk_freq_hz = 8000000;
    config.frame_size = FRAMESIZE_HVGA;
    config.pixel_format = PIXFORMAT_JPEG;    // for streaming
    //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
    //                                            for larger pre-allocated frame buffer.
    if (config.pixel_format == PIXFORMAT_JPEG) {
        if (psramFound()) {
            config.jpeg_quality = 10;
            config.fb_count = 2;
            config.grab_mode = CAMERA_GRAB_LATEST;
        } else {
            Serial.println("PSRAM not found");
            // Limit the frame size when PSRAM is not available
            config.frame_size = FRAMESIZE_SVGA;
            config.fb_location = CAMERA_FB_IN_DRAM;
        }
    } else {
        // Best option for face detection/recognition
        config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
        config.fb_count = 2;
#endif
    }

#if defined(CAMERA_MODEL_ESP_EYE)
    pinMode(13, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);
#endif

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }

    sensor_t *s = esp_camera_sensor_get();
    // initial sensors are flipped vertically and colors are a bit saturated
    if (s->id.PID == OV3660_PID) {
        s->set_vflip(s, 1);          // flip it back
        s->set_brightness(s, 1);     // up the brightness just a bit
        s->set_saturation(s, -2);    // lower the saturation
    }
    // drop down frame size for higher initial frame rate
    // if (config.pixel_format == PIXFORMAT_JPEG) {
    //     s->set_framesize(s, FRAMESIZE_QVGA);
    // }

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
    s->set_vflip(s, 1);
    s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
    s->set_vflip(s, 1);
#endif

// Setup LED Flash if LED pin is defined in camera_pins.h
#if defined(LED_GPIO_NUM)
    setupLedFlash();
#endif
}

void Camera::start_camera_server() {
    startCameraServer();
}
