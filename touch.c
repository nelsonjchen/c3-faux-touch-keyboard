// Libraries
#include "src/config.h" // user configurations
#include "src/delay.h"  // delay functions
#include "src/gpio.h"   // GPIO functions
#include "src/neo.h"    // NeoPixel functions
#include "src/system.h" // system functions
#include "usb_multitouch.h"

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) { USB_interrupt(); }

// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {
  __idata uint8_t i; // temp variable

  NEO_init(); // init NeoPixels

  // Boot Flash if key 1 is held
  if (!PIN_read(PIN_KEY1)) { // key 1 pressed?
    NEO_latch();             // make sure pixels are ready
    for (i = 9; i; i--)
      NEO_sendByte(127); // light up all pixels
    BOOT_now();          // enter bootloader
  }

  // Setup
  CLK_config(); // configure system clock
  MT_init();
  DLY_ms(10);       // wait for clock to settle
  PIN_low(PIN_LED); // light up LED - blocking activated

  __xdata unsigned int touchCount = 0;
  __xdata int lampLight = 0;
  __xdata int keysChanged = 0;
  // Track key states. Only send updates if the key state has changed.
  __xdata int key1Pressed = 0;
  __xdata int key2Pressed = 0;
  __xdata int key3Pressed = 0;
  // 0 for clockwise, 1 for counter-clockwise
  __xdata int knobDirection = 0;
  __xdata int keyDirty = 0;

  NEO_clearAll(); // clear NeoPixels

  // Loop
  while (1) {
    keyDirty = 0;
    touchCount = 0;

    PIN_toggle(PIN_LED); // toggle LED and function state

    DLY_ms(10); // debounce

    // Check if PIN_KEY1 is pressed
    if (!PIN_read(PIN_KEY1)) { // key 1 pressed?
      if (!key1Pressed) {
        key1Pressed = 1;
        keyDirty = 1;
        touchCount += 1;
      }
    } else {
      if (key1Pressed) {
        key1Pressed = 0;
        keyDirty = 1;
      }
    }
    // Check if PIN_KEY2 is pressed
    if (!PIN_read(PIN_KEY2)) { // key 2 pressed?
      if (!key2Pressed) {
        key2Pressed = 1;
        keyDirty = 1;
        touchCount += 1;
      }
    } else {
      if (key2Pressed) {
        key2Pressed = 0;
        keyDirty = 1;
      }
    }
    // Check if PIN_KEY3 or PIN_ENC_SW is pressed
    if (!PIN_read(PIN_KEY3) || !PIN_read(PIN_ENC_SW)) {
      // key 3 / encoder switch pressed?
      if (!key3Pressed) {
        key3Pressed = 1;
        keyDirty = 1;
        touchCount += 1;
      }
    } else {
      if (key3Pressed) {
        key3Pressed = 0;
        keyDirty = 1;
      }
    }

    // Check if PIN_ENC_A, PIN_ENC_B is pressed or not and update knobDirection
    if (!PIN_read(PIN_ENC_A)) {
      if (PIN_read(PIN_ENC_B)) {
        lampLight = 1; // clockwise?
      } else {
        lampLight = 0; // counter-clockwise?
      }
      DLY_ms(10); // debounce
      while (!PIN_read(PIN_ENC_A))
        ; // wait until next detent
      keyDirty = 1;
    }

    if (keyDirty) {
      if (key1Pressed) {
        NEO_writeColor(0, 25, 19, 0);
        MT_touchDown(touchCount, 1, 110, 108);
      } else {
        if (lampLight) {
          NEO_writeColor(0, 5, 1, 0);
        } else {
          NEO_clearPixel(0);
        }
        MT_touchUp(touchCount, 1);
      }
      if (key2Pressed) {
        NEO_writeColor(1, 25, 19, 0);
        MT_touchDown(touchCount, 2, 540, 864);
      } else {
        if (lampLight) {
          NEO_writeColor(1, 5, 1, 0);
        } else {
          NEO_clearPixel(1);
        }
        MT_touchUp(touchCount, 2);
      }
      if (key3Pressed) {
        NEO_writeColor(2, 25, 19, 0);
        MT_touchDown(touchCount, 3, 907, 1983);
      } else {
        if (lampLight) {
          NEO_writeColor(2, 5, 1, 0);
        } else {
          NEO_clearPixel(2);
        }
        MT_touchUp(touchCount, 3);
      }
    }
    NEO_update(); // update NeoPixels
  }
}
