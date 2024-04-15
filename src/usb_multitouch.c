#include "usb_multitouch.h"

uint8_t MT_control(void) {
  switch(USB_SetupReq) {
    case HID_GET_REPORT:
        EP0_buffer[0] = 10; // 10 fingers max
        return 1;

    default:
      return 0xff;                       // failed
  }
}