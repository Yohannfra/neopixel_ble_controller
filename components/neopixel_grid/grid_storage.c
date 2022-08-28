#include "grid_storage.h"

#include "esp_log.h"
#include "nvs_flash.h"

#define STORAGE_NAMESPACE "grid_storage"

static const char *TAG = "GRID_STORAGE";

bool grid_storage_has_pixels(void)
{
    nvs_handle_t handle;
    esp_err_t ret;

    ret = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "error nvs_open");
        return false;
    }

    size_t read_size = 0;
    ret = nvs_get_blob(handle, "grid", NULL, &read_size);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read grid");
        nvs_close(handle);
        return false;
    }

    nvs_close(handle);

    return read_size != 0;
}

bool grid_storage_has_brightness(void)
{
    nvs_handle_t handle;
    esp_err_t ret;
    bool found;

    ret = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "error nvs_open");
        return false;
    }

    uint8_t out = 0;
    ret = nvs_get_u8(handle, "brightness", &out);

    if (ret != ESP_OK && ret != ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGE(TAG, "Failed to read brightness");
        nvs_close(handle);
        return false;
    } else if (ret == ESP_ERR_NVS_NOT_FOUND) {
        found = false;
    } else {
        found = true;
    }

    nvs_close(handle);

    return found;
}

esp_err_t grid_storage_load_pixels(rgb_color_t grid[NP_GRID_SIZE][NP_GRID_SIZE])
{
    esp_err_t ret;
    nvs_handle_t handle;

    ret = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "error nvs_open");
        return ret;
    }

    size_t size_to_read = sizeof(rgb_color_t[NP_GRID_SIZE][NP_GRID_SIZE]);
    ret = nvs_get_blob(handle, "grid", grid, &size_to_read);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read grid");
        nvs_close(handle);
        return ret;
    }

    nvs_close(handle);

    ESP_LOGI(TAG, "Load pixels:");
    np_grid_print_pixels(grid);

    return ESP_OK;
}

esp_err_t grid_storage_save_pixels(rgb_color_t grid[NP_GRID_SIZE][NP_GRID_SIZE])
{
    esp_err_t ret;
    nvs_handle_t handle;

    ESP_LOGI(TAG, "Saving pixels:");
    np_grid_print_pixels(grid);

    ret = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "error nvs_open");
        return ret;
    }

    ret = nvs_set_blob(handle, "grid", (uint8_t *)grid, sizeof(rgb_color_t[NP_GRID_SIZE][NP_GRID_SIZE]));
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to save grid");
        nvs_close(handle);
        return ret;
    }

    ret = nvs_commit(handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "error nvs_commit");
        nvs_close(handle);
        return ret;
    }

    nvs_close(handle);

    return ESP_OK;
}

esp_err_t grid_storage_load_brightness(uint8_t *brightness)
{
    esp_err_t ret;
    nvs_handle_t handle;

    ret = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "error nvs_open");
        return ret;
    }

    ret = nvs_get_u8(handle, "brightness", brightness);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read brightness");
        nvs_close(handle);
        return ret;
    }

    nvs_close(handle);

    return ESP_OK;
}

esp_err_t grid_storage_save_brightness(uint8_t brightness)
{
    esp_err_t ret;
    nvs_handle_t handle;

    ret = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "error nvs_open");
        return ret;
    }

    ret = nvs_set_u8(handle, "brightness", brightness);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to save brightness");
        nvs_close(handle);
        return ret;
    }

    ret = nvs_commit(handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "error nvs_commit");
        nvs_close(handle);
        return ret;
    }

    nvs_close(handle);

    return ESP_OK;
}
