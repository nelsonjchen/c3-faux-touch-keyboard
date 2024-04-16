// ===================================================================================
// Project:   CAPS bLOCK for CH551, CH552 and CH554
// Version:   v1.1
// Year:      2023
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Tired of accidentally hitting the CAPS-LOCK key? It doesn't have to be.
// CAPS bLOCK identifies itself as a USB HID keyboard and constantly monitors the
// state of CAPS LOCK. It immediately deactivates it if it has been activated.
//
// References:
// -----------
// - Blinkinlabs: https://github.com/Blinkinlabs/ch554_sdcc
// - Deqing Sun: https://github.com/DeqingSun/ch55xduino
// - Ralph Doncaster: https://github.com/nerdralph/ch554_sdcc
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// Compilation Instructions:
// -------------------------
// - Chip:  CH551, CH552 or CH554
// - Clock: 16 MHz internal
// - Adjust the firmware parameters in src/config.h if necessary.
// - Make sure SDCC toolchain and Python3 with PyUSB is installed.
// - Press BOOT button on the board and keep it pressed while connecting it via USB
//   with your PC.
// - Run 'make flash' immediatly afterwards.
// - To compile the firmware using the Arduino IDE, follow the instructions in the
//   .ino file.
//
// Operating Instructions:
// -----------------------
// - Connect the board via USB to your PC. It should be detected as a HID keyboard.
// - Activate/deactivate the blocking function by pressing the ACT button. The
//   built-in LED lights up when the function is activated.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

// Libraries
#include "src/config.h"                   // user configurations
#include "src/system.h"                   // system functions
#include "src/gpio.h"                     // GPIO functions
#include "src/delay.h"                    // delay functions
#include "usb_hid.h"


// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {
  // Boot Flash if key 1 is held
  if(!PIN_read(PIN_KEY1)) {                 // key 1 pressed?
    BOOT_now();                             // enter bootloader
  }

  // Setup
  CLK_config();                           // configure system clock
  HID_init();
  DLY_ms(10);                             // wait for clock to settle
  PIN_low(PIN_LED);                       // light up LED - blocking activated
  __xdata unsigned char touchDownReport1[] = {
    0x01, // Contact Count
    0x01, // Contact Identifier
    0x03, // Tip Switch and In Range
    0x7F, // Pressure
    0x88, 0x13, // x / 10000, 5000
    0x88, 0x13, // y / 10000, 5000
  };

  __xdata unsigned char touchUpReport1[] = {
    0x00, // Contact Count
    0x01, // Contact Identifier
    0x00, // Not in Range
    0x00, // No pressure
    0x00, 0x00, // Disregarded
    0x00, 0x00, // Disregarded
  };
  __xdata unsigned char touchDownReport2[] = {
    0x01, // Contact Count
    0x02, // Contact Identifier
    0x03, // Tip Switch and In Range
    0x7F, // Pressure
    0x88, 0x13, // x / 10000, 5000
    0x88, 0x13, // y / 10000, 5000
  };

  __xdata unsigned char touchUpReport2[] = {
    0x00, // Contact Count
    0x02, // Contact Identifier
    0x00, // Not in Range
    0x00, // No pressure
    0x00, 0x00, // Disregarded
    0x00, 0x00, // Disregarded
  };
  __xdata unsigned char touchDownReport3[] = {
    0x01, // Contact Count
    0x03, // Contact Identifier
    0x03, // Tip Switch and In Range
    0x7F, // Pressure
    0x88, 0x13, // x / 10000, 5000
    0x88, 0x13, // y / 10000, 5000
  };

  __xdata unsigned char touchUpReport3[] = {
    0x00, // Contact Count
    0x03, // Contact Identifier
    0x00, // Not in Range
    0x00, // No pressure
    0x00, 0x00, // Disregarded
    0x00, 0x00, // Disregarded
  };

  __xdata unsigned int touchCount = 0;
  __xdata int keysChanged = 0;
  // Track key states. Only send updates if the key state has changed.
  __xdata int key1Pressed = 0;
  __xdata int key2Pressed = 0;
  __xdata int key3Pressed = 0;
  __xdata int keyDirty = 0;

  // Loop
  while(1) {
      keyDirty = 0;
      touchCount = 0;

      PIN_toggle(PIN_LED);                // toggle LED and function state

      DLY_ms(200);                         // debounce
      // Touch down report

      // Check if PIN_KEY1 is pressed
      if(!PIN_read(PIN_KEY1)) {             // key 1 pressed?
        if(!key1Pressed) {
          key1Pressed = 1;
          keyDirty = 1;
          touchCount += 1;
        }
      } else {
        if(key1Pressed) {
          key1Pressed = 0;
          keyDirty = 1;
        }
      }
      // Check if PIN_KEY2 is pressed
      if(!PIN_read(PIN_KEY2)) {             // key 2 pressed?
        if(!key2Pressed) {
          key2Pressed = 1;
          keyDirty = 1;
          touchCount += 1;
        }
      } else {
        if(key2Pressed) {
          key2Pressed = 0;
          keyDirty = 1;
        }
      }
      // Check if PIN_KEY3 is pressed
      if(!PIN_read(PIN_KEY3)) {             // key 3 pressed?
        if(!key3Pressed) {
          key3Pressed = 1;
          keyDirty = 1;
          touchCount += 1;
        }
      } else {
        if(key3Pressed) {
          key3Pressed = 0;
          keyDirty = 1;
        }
      }

      // Change the first byte of each report to the number of fingers
      touchDownReport1[0] = touchCount;
      touchUpReport1[0] = touchCount;
      touchDownReport2[0] = touchCount;
      touchUpReport2[0] = touchCount;
      touchDownReport3[0] = touchCount;
      touchUpReport3[0] = touchCount;

      if(keyDirty) {
        if(key1Pressed) {
          HID_sendReport(touchDownReport1, sizeof(touchDownReport1));
        } else {
          HID_sendReport(touchUpReport1, sizeof(touchUpReport1));
        }
        if(key2Pressed) {
          HID_sendReport(touchDownReport2, sizeof(touchDownReport2));
        } else {
          HID_sendReport(touchUpReport2, sizeof(touchUpReport2));
        }
        if(key3Pressed) {
          HID_sendReport(touchDownReport3, sizeof(touchDownReport3));
        } else {
          HID_sendReport(touchUpReport3, sizeof(touchUpReport3));
        }
      }
  }
}
