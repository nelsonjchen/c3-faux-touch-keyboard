# CH552 Touch Play

Experiment in making a CH552 report itself as a USB HID device that is recognized as a touchscreen.

https://github.com/wagiminator/MCU-Templates/issues/3

Plan:

1. Get it working for my use case as as a keyboard for the comma.ai devices.
2. See how it can be extracted out
3. Contribute up and finish https://github.com/wagiminator/MCU-Templates/issues/3
4. Figure if there's a way to make a composite device that can be a keyboard, mouse, and a touchscreen. And programmable through a web page.

State: Hello World! (I'm touching you!)

This repo is a hello world for the CH552. It's a USB HID device that reports itself as a touchscreen. It's a simple example that sends a touch event to the host in a loop.

Tester: https://naqtn.github.io/WBBMTT/