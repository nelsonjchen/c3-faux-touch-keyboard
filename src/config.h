// ===================================================================================
// User Configurations for CH55xE Development Stick
// ===================================================================================

#pragma once

// Pin definitions
#define PIN_NEO             P34         // pin connected to NeoPixel
#define PIN_LED             P32       // pin connected to LED
#define PIN_TOUCH           P16       // pin connected to touch key
#define PIN_ACTKEY          P17       // pin connected to ACT-button
#define LED_BUILTIN         P15       // builtin LED
#define PIN_KEY1            P11         // pin connected to key 1
#define PIN_KEY2            P17         // pin connected to key 2
#define PIN_KEY3            P16         // pin connected to key 3

// NeoPixel configuration
#define NEO_GRB                       // type of pixel: NEO_GRB or NEO_RGB

// Touchkey configuration
#define TOUCH_TH_LOW        2000      // key pressed threshold
#define TOUCH_TH_HIGH       2400      // key released threshold

// USB device descriptor
#define USB_VENDOR_ID       0x6666    // VID: Prototype
#define USB_PRODUCT_ID      0x6666    // PID: Prototype
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)

// USB configuration descriptor
#define USB_MAX_POWER_mA    50        // max power in mA

// USB descriptor strings
#define MANUFACTURER_STR    'm','i','n','d','f','l','a','k','e','s'
#define PRODUCT_STR         't','o','u','c','h','k','e','y'
#define SERIAL_STR          'l','m','a','o'
#define INTERFACE_STR       'H','I','D','-','T','o','u','c','h','s','c','r','e','e','n'