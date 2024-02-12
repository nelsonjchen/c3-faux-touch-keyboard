// ===================================================================================
// Project:   Example for CH551, CH552, CH554
// Version:   v1.0
// Year:      2022
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Blink example.
//
// References:
// -----------
// - Blinkinlabs: https://github.com/Blinkinlabs/ch554_sdcc
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// Compilation Instructions:
// -------------------------
// - Make sure SDCC toolchain and Python3 with PyUSB is installed. In addition, Linux
//   requires access rights to the USB bootloader.
// - Press the BOOT button on the MCU board and keep it pressed while connecting it
//   via USB to your PC.
// - Run 'make flash' immediatly afterwards.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================
#include "config.h"                         // user configurations
#include "system.h"                               // system functions
#include "delay.h"                                // delay functions
#include "gpio.h"                                 // GPIO functions


// ===================================================================================
// Main Function
// ===================================================================================

void main() {
  CLK_config();                                   // configure system clock
  PIN_output(PIN_LED);                            // set LED pin as output

  if(!PIN_read(PIN_KEY1)) {                 // key 1 pressed?
    BOOT_now();                             // enter bootloader
  }

  while (1) {
    PIN_toggle(PIN_LED);                          // toggle LED
    DLY_ms(100);                                  // wait a bit
  }
}
