idf_component_register(
    SRCS
        "main.c"
        "ble/my_ble.c"
        "ble/services/neopixe_grid/neopixel_grid_service.c"

    INCLUDE_DIRS
        "."
        "ble"
        "ble/services/neopixe_grid/"
    )
