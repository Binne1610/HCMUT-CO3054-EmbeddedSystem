#include <cstdio>
#include <inttypes.h>
#include <string>
#include <sdkconfig.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

using namespace std;

class ESP32Info 
{
public:
    void printHelloWorld() 
    {
        printf("Hello world!\n");
    }

    void printChipInfo() const
    {
        esp_chip_info_t chip_info;
        esp_chip_info(&chip_info);
        
        uint32_t flash_size;
        if (esp_flash_get_size(nullptr, &flash_size) != ESP_OK) 
        {
            printf("Get flash size failed\n");
            return;
        }

        unsigned major_rev = chip_info.revision / 100;
        unsigned minor_rev = chip_info.revision % 100;

        printf("This is %s chip with %d CPU core(s), %s%s%s%s\n",
               CONFIG_IDF_TARGET,
               chip_info.cores,
               (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
               (chip_info.features & CHIP_FEATURE_BT) ? "BT/" : "",
               (chip_info.features & CHIP_FEATURE_BLE) ? "BLE/" : "",
               (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

        printf("Silicon revision v%d.%d\n", major_rev, minor_rev);
        printf("Flash size: %" PRIu32 " MB (%s)\n",
               flash_size / (uint32_t)(1024 * 1024),
               (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    }

    void printHeapInfo() const 
    {
        printf("Minimum free heap size: %" PRIu32 " bytes\n",
               esp_get_minimum_free_heap_size());
    }

    void CountdownAndRestart(int seconds) const
    {
        for (int i = seconds; i >= 0; i--)
        {
            printf("Restarting in %d seconds...\n", i);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        printf("Restarting now.\n");
        fflush(stdout);
        esp_restart();
    }
};

extern "C" void app_main(void)
    {
    ESP32Info printer;

    printer.printHelloWorld();
    printer.printChipInfo();
    printer.printHeapInfo();
    printer.CountdownAndRestart(10);
}
