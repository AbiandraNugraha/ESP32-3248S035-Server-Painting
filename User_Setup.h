#define USER_SETUP_LOADED 1
#define ST7796_DRIVER
#define TFT_WIDTH  320
#define TFT_HEIGHT 480

// Pin Definitions for ESP32-3248S035C
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST  -1
#define TFT_BL   27

#define TFT_BACKLIGHT_ON HIGH

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SPI_FREQUENCY  40000000 // Stable speed for ST7796
#define SPI_READ_FREQUENCY 20000000
