#include <sdkconfig.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_system.h>
#include <driver/gpio.h>

#include <iostream>
#include <string.h>

using namespace std;

void printStudentID (void *parameter ) {
    for(;;) {
        printf("2213322 - 2210364 - 2211064\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void printESP32 (void *parameter) {
    gpio_config_t gpioConfig;
    gpioConfig.pin_bit_mask = (1 << 0);
    gpioConfig.mode = GPIO_MODE_INPUT;
    gpioConfig.pull_up_en = GPIO_PULLUP_ENABLE;
    gpioConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpioConfig.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpioConfig);

    int last_state = 1;
    for(;;) {
        int level = gpio_get_level(GPIO_NUM_0);
        if (level == 0 && last_state == 1) {
            printf("ESP32\n");
        }
        last_state = level;
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

extern "C" void app_main(void)
{
    xTaskCreate(printStudentID, "Print Student ID", 2048, NULL, 1, NULL);
    xTaskCreate(printESP32, "Print ESP32", 2048, NULL, 1, NULL);
}
