idf_component_register(
    SRCS
        "main.c"
        "ble/my_ble.c"
        "ble/services/dis/my_dis.c"
        "ble/services/neopixe_grid/neopixel_grid_service.c"
        "ble/utils.c"
        "ble/gatt_svr.c"

    INCLUDE_DIRS
        "."
        "ble"
        "ble/services/neopixe_grid/"
        "ble/services/dis/"
    )
