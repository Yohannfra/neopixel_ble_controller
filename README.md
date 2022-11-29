# neopixel_ble_controller

This firmware controls an ESP32 with a 5x5 Neopixel (ws2812) grid.

This device is made to be used as a testing BLE peripheral for the [bluerepl](https://github.com/Yohannfra/bluerepl) project.

A picture of the ESP32 and the full device :\
<img src=".github/full.JPG" width="400"/>


## Requirements
- [Install ESP-IDF v4.4](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html)

## Get started

Build
```
$ make
```
Flash
```
make flash
```

## Ble services and characteristics

There is one service with three characteristics, one for sending commands one for reading the grid colors and a third one to send notifications when the button is pressed.

---

### Service UUID:
UUID: **8e72bbe5-f777-5284-7849-b4a0b2ac70d2**

---

### Characteristic for sending commands:
UUID: **0000beb6-0000-1000-8000-00805f9b34fb**\
Properties: **WRITE** / **WRITE WITHOUT RESPONSE**

#### Commands

- **0x01** => clear the grid

- **0x02**[x][y][r][g][b] => set a pixel color

    example: 
    ```c
    uint8_t payload[] = {0x02, 0x02, 0x02, 0xff, 0x00, 0x50};
    // send payload

    // Will set the color of the pixel at x=2 and y=2 to color 0xff0050
    ```

- **0x03**[r][g][b] => set the color of all the pixels (same color for all pixels)

    example:
    ```c
    uint8_t payload[] = {0x03, 0xff, 0x00, 0x00};
    // send payload

    // Will set the color of all the pixels to color 0xff0000
    ```

- **0x04**{[r][g][b], ... * 25} => set the color of all the pixels one by one

    example:
    ```c
    uint8_t payload[] = {0x04, 0xff, 0x00, 0xff, 0x00, 0xff, 0x50 /*...*/};
    // send payload

    // Will set the first pixel to 0xff00ff the second to 0x00ff50 and so on ...
    ```

- **0x05**[brightness] => set the brightness of all the pixels

    The brightness must go from 1 to 20.

    example
    ```c
    uint8_t payload[] = {0x05, 0x01};
    // send payload

    // Will set the brightness to 1 (the lowest brightness)
    ```

- **0x06** => turn on the leds

- **0x07** => turn off the leds

---

### Characteristic for reading pixels color:
UUID: **0000cad8-0000-1000-8000-00805f9b34fb**\
Properties: **READ**

The colors will be arranged like this

```c
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;

rgb_color_t the_array_you_receive[25];
```

---

### Characteristic for button notifications:
UUID: **0000dac4-0000-1000-8000-00805f9b34fb**\
Properties: **READ** / **NOTIFY**

When the button is pressed it will increment a counter and notify it's value.
