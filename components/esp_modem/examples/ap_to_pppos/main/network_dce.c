/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

/*
 * softAP to PPPoS Example (network_dce)
*/

#include <string.h>
#include "esp_netif.h"
#include "esp_modem_api.h"
#include "esp_log.h"

static const char *TAG = "network_dce";

static esp_modem_dce_t *dce = NULL;


esp_err_t modem_init_network(esp_netif_t *netif)
{
    // setup the DCE
    esp_modem_dte_config_t dte_config = ESP_MODEM_DTE_DEFAULT_CONFIG();
    esp_modem_dce_config_t dce_config = ESP_MODEM_DCE_DEFAULT_CONFIG(CONFIG_EXAMPLE_MODEM_PPP_APN);
    dte_config.uart_config.cts_io_num = -1;
    dte_config.uart_config.rts_io_num = -1;
    dte_config.uart_config.rx_io_num = 18;
    dte_config.uart_config.tx_io_num = 17;

    dce = esp_modem_new_dev(ESP_MODEM_DCE_SIM7070, &dte_config, &dce_config, netif);
    if (!dce) {
        return ESP_FAIL;
    }

#ifdef CONFIG_EXAMPLE_NEED_SIM_PIN
    // configure the PIN
    bool pin_ok = false;
    if (esp_modem_read_pin(dce, &pin_ok) == ESP_OK && pin_ok == false) {
        if (esp_modem_set_pin(dce, CONFIG_EXAMPLE_SIM_PIN) == ESP_OK) {
            vTaskDelay(pdMS_TO_TICKS(1000));
        } else {
            abort();
        }
    }
#endif // CONFIG_EXAMPLE_NEED_SIM_PIN

    char resp[100];
    esp_modem_at(dce, "AT\r", resp, 1000);
    ESP_LOGI(TAG, "AT is %s", resp);


    return ESP_OK;
}

void modem_deinit_network(void)
{
    if (dce) {
        esp_modem_destroy(dce);
        dce = NULL;
    }
}

bool modem_start_network()
{
    char resp[100];
    int act = 0;
    esp_modem_read_pin(dce, (bool*)&act);
    ESP_LOGI(TAG, "Pin %i", act);
    esp_modem_get_module_name(dce, resp);
    ESP_LOGI(TAG,"Module name %s", resp);
    esp_modem_get_operator_name(dce, resp, &act);
    ESP_LOGI(TAG,"Operator name %s act %i", resp, act);
    esp_modem_get_network_attachment_state(dce, &act);
    ESP_LOGI(TAG,"Network status %i", act);
    esp_modem_set_network_attachment_state(dce, 1);
    esp_modem_set_radio_state(dce, 1);

    vTaskDelay(pdMS_TO_TICKS(15000));

    esp_modem_get_operator_name(dce, resp, &act);
    ESP_LOGI(TAG,"Operator name %s act %i", resp, act);
    esp_modem_get_network_attachment_state(dce, &act);
    ESP_LOGI(TAG,"Network status %i", act);


//     esp_modem_at(dce, "AT+CFUN=0", resp, 1000);
//     esp_modem_at(dce, "AT+CGDCONT=1,\"IP\",\"internet\"", resp, 1000);
//     esp_modem_at(dce, "AT+CFUN=1", resp, 1000);
//     esp_modem_at(dce, "AT+CGATT?", resp, 1000);
//    // esp_modem_at(dce, "AT+CGNAPN", resp, 1000);
//    // esp_modem_at(dce, "AT+CNCFG=0,1,\"internet\"", resp, 1000);
//    // esp_modem_at(dce, "AT+CNACT=0,1", resp, 1000);
//     esp_modem_at(dce, "AT+CREG?", resp, 1000);
//     esp_modem_at(dce, "AT+CGATT?", resp, 1000);
//     esp_modem_at(dce, "AT+CGACT?", resp, 1000);
    return esp_modem_set_mode(dce, ESP_MODEM_MODE_DATA) == ESP_OK;
}

bool modem_stop_network()
{
    return esp_modem_set_mode(dce, ESP_MODEM_MODE_COMMAND);
}

bool modem_check_sync()
{
    return esp_modem_sync(dce) == ESP_OK;
}

void modem_reset()
{
    esp_modem_reset(dce);
}

bool modem_check_signal()
{
    int rssi, ber;
    if (esp_modem_get_signal_quality(dce, &rssi, &ber) == ESP_OK) {
        return rssi != 99 && rssi > 5;
    }
    return false;
}
