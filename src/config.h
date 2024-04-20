// ===================================================================================
// User Configurations for CH55xE Development Stick
// ===================================================================================

#pragma once

// Pin definitions
#define PIN_NEO             P34         // pin connected to NeoPixel
#define PIN_LED             P32         // pin connected to LED
#define PIN_KEY1            P11         // pin connected to key 1
#define PIN_KEY2            P17         // pin connected to key 2
#define PIN_KEY3            P16         // pin connected to key 3
#define PIN_ENC_SW          P33         // pin connected to knob switch
#define PIN_ENC_A           P31         // pin connected to knob outA
#define PIN_ENC_B           P30         // pin connected to knob outB
#define NEO_COUNT           3           // number of NeoPixels

// NeoPixel configuration
#define NEO_GRB                       // type of pixel: NEO_GRB or NEO_RGB

// USB device descriptor
#define USB_VENDOR_ID       0x6666    // VID: Prototype
#define USB_PRODUCT_ID      0x6666    // PID: Prototype
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)

// USB configuration descriptor
#define USB_MAX_POWER_mA    50        // max power in mA

// USB descriptor strings
#define MANUFACTURER_STR    'm','i','n','d','f','l','a','k','e','s','.','c','o','m'
#define PRODUCT_STR         'c','3','-','t','o','u','c','h','k','e','y','-','k','e','y','b','o','a','r','d'
#define SERIAL_STR          '0','0','7'
#define INTERFACE_STR       'H','I','D','-','T','o','u','c','h','s','c','r','e','e','n'