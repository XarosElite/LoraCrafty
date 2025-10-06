#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "string.h"

#define UART_PORT UART_NUM_1
#define TXD_PIN GPIO_NUM_5  // D6 (TX to LoRa RX)
#define RXD_PIN GPIO_NUM_4  // D7 (RX from LoRa TX)
#define BUF_SIZE 128

static const char *TAG = "LORA_HELLO";

void init_uart() {
    const uart_config_t uart_config = {
        .baud_rate = 115200,  // Default baud for RYLR896
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_driver_install(UART_PORT, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_PORT, &uart_config);
    uart_set_pin(UART_PORT, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void lora_send_cmd(const char *cmd) {
    char full_cmd[256];
    snprintf(full_cmd, sizeof(full_cmd), "%s\r\n", cmd);
    uart_write_bytes(UART_PORT, full_cmd, strlen(full_cmd));
}



void app_main() {
    init_uart();

    const char* at_cmd = "AT?\r\n";
    uart_write_bytes(UART_PORT, at_cmd, strlen(at_cmd));
    ESP_LOGI(TAG, "Sent: %s", (char*)at_cmd);

    uint8_t rx_buffer[BUF_SIZE];
    int len = uart_read_bytes(UART_PORT, rx_buffer, BUF_SIZE - 1, pdMS_TO_TICKS(1000));
    if (len > 0) {
        rx_buffer[len] = 0;  // Null-terminate
        ESP_LOGI(TAG, "Received: %s", (char*)rx_buffer);

        if (strstr((char*)rx_buffer, "OK")) {
            ESP_LOGI(TAG, "✅ LoRa is connected!");
        } else {
            ESP_LOGW(TAG, "⚠️ Unexpected response from LoRa");
        }
    } else {
        ESP_LOGE(TAG, "❌ No response from LoRa module.");
    }

    uint8_t data[BUF_SIZE];

    // Set address (optional)
    lora_send_cmd("AT+ADDRESS=1");
    vTaskDelay(pdMS_TO_TICKS(500));

    lora_send_cmd("AT+SEND=2,5,Hello");

    while (1) {
        int len = uart_read_bytes(UART_PORT, data, BUF_SIZE - 1, pdMS_TO_TICKS(1000));
        if (len > 0) {
            data[len] = 0;  // Null-terminate
            ESP_LOGI(TAG, "Received: %s", data);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }



   
}

