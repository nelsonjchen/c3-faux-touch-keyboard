# 🦾 comma three Touchkey keyboard

*Long arms for those of us with short arms from birth or those who can't afford arm extension surgery!*

![touchkey keyboard demo](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/d9617916-2442-4287-b430-709dad173da8)

These are instructions and firmware for a relatively cheap off-the-shelf macro keyboard off AliExpress/Amazon (that has many copies/clones) to control a comma three running openpilot from an accessible and comfortable driver's position.

No more this and reaching out when you want to bookmark a segment or toggle experimental mode:

https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/d7d32187-ce30-4456-afb6-641c660ce235

The macro keyboard we will be using look like this and come in this configuration:

![Picture of keyboard](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/bf44187f-1143-46d3-bb61-b068b7270087)

The default configuration software and firmware on these kinds of keyboards is notoriously bad, sketchy in origin, and may not be trustworthy. More importantly, it won't work for our use case where we need to send touchscreen input. So, don't bother downloading and don't install the configuration software. We will be throwing it all out.

Instead, we flash the keyboard's microprocessor to pretend to be a USB touchscreen digitizer, and the buttons to send touch events to the comma three. The new firmware touch areas are currently hardcoded to the bottom left corner for bookmark, the center for hide/show menu, and the top right corner for experimental mode toggling. The knob is used to control the LEDs to be a "lamp" light for night driving use and pressing down on it is an alternative button for the top right corner button pressing.

These keyboards are built arount the `CH552G` microcontroller. By shorting two pins together on initial power, the keyboard can be put into bootloader mode, and the new touchscreen-emulation firmware can then be flashed over USB.

Restoring the original firmware is not possible without a the original firmware which I haven't been able to find yet. That said, somewhat similar functional firmware to the original functionality without the sketchy vendor software can be found here if you want to "reverse" the process and restore the keyboard to something like its original functionality:

https://github.com/biemster/3keys_1knob


## Bill of Materials

Cost: Expect the cost to be about $3-20 for the keyboard, $2-10 for the male USB-C to female USB-A adapter, and an optional $6-10 for nicities like 90 degree USB-C angle adapters for a cleaner look. The rest of the materials you probably have lying around. The cost can be $14 to $40 depending on how long you want to wait for the materials to arrive from AliExpress, if you're in a hurry and want to buy from Amazon, and how clean you want the install to look.

### Keyboard

A specific type of mass-produced macro keyboard with a `CH552G` microcontroller. The one this project supports and what I used was this:

* https://www.aliexpress.us/item/3256806441586710.html

* https://amzn.to/3Q7Mw5c

Go for AliExpress if you want to save money and don't mind waiting. Go for Amazon if you want it faster and have Prime.

As there are many vendors of this keyboard, there is no steady name other than a similar look, so keep an eye for these trait when looking for an equivalent keyboard:

* Looks like the keyboard in those links I have above.
* Shows up when you search for "3 keys 1 knob keyboard"
* 3 keys in a row
* 1 knob, metal-looking usually
* Acryllic layer exterior with rounded corners
* Exposed screws heads on bottom and top
* Multi-color LEDs
* USB-C is offset a bit torwards the knob side of the keyboard and not in the center.
* Comes with a male USB-A to male USB-C cable

These will usually guarantee you get a keyboard with the `CH552G` microcontroller present in the manner we need.

### Male USB-C to Female USB-A cable

Unfortunately, the keyboard is not perfect. It is missing two resistors in it that allow it to be powered by a USB-C port in a USB-C to USB-C setup. However, we need to power it from the comma three's USB-C port. While it is theoretically possible to solder in the right resistors, it is easier to just use a cable to convert the comma three USB-C port to a USB-A port. The longer, the better and here are some examples:

* https://amzn.to/4aFOj9I

* https://www.aliexpress.us/item/3256806084714064.html

### Right Angle Adapters

These are optional, but they help reduce cable strain on the cable at the comma three's USB-C port and clean up the cables a area with the keyboard attached to your car.

* https://amzn.to/3U3WtSu - This is a pack of 5 adapters with 3 of them being useful to get the angles right to reduce strain and clean up the cables.
* https://www.aliexpress.us/item/3256805061903701.html
  * Purchase "Color": 1, 4, 5

### Mounting Tape

You can attach the keyboard to your car however you like. I used large 3M Command Picture Hanging Strips to attach the keyboard in front of my gear shifter. They are strong enough to hold the keyboard in place and can be fully removed without damaging the car. The strips are also velcro-like so you can remove the keyboard to change it or reprogram it away from the car without disturbing the tape too.

https://amzn.to/49Nm87A

Of course, you can use whatever else you like for mounting.

AliExpress has command strip-like products as well, but I haven't tried them yet:

https://www.aliexpress.us/w/wholesale-3m-command-picture-hanging-strips.html

### Shorting Tools

You'll need to short two pins on the `CH552G` microcontroller to put it into bootloader mode. You can do this with a paperclip or a metal conductor, but it is easier to do with these hooks.

#### Cheap

* A paperclip or metal conductor to short the pins on some chip on the off-the-shelf keyboard for the initial flashing.
* Steady hands or tape or whatever to mask off pins that aren't to be shorted together.
* Or YOLO it and short the pins with a paperclip or metal conductor with no tape. Good luck!

#### Throw a bit of money at AliExpress

You can use these hooks to precisely clip onto the pins to and then connect the two hooks of the pins to short them together. This is useful if you have shaky hands or need to do this multiple times.

https://www.aliexpress.us/item/3256805244460946.html - Get the 2pcs male option.

## Instructions

### Preparing your Windows computer to flash

You will need to use Zadig to make the device when it is in bootloader mode available to flashing software.

1. Download Zadig from https://zadig.akeo.ie/
2. Run Zadig

WIP

### Getting the keyboard into bootloader mode

1. Disassemble the keyboard. There are 4 screws on the back of the keyboard.
2. Unscrew them and take off the bottom. There will be an acrylic cut out.
3. Take out the acrylic cut out and you will see the `CH552G` microcontroller.
4. Short these two pins on the `CH552G` microcontroller. WIP add pins
5. While the two pins are shorted, plug the keyboard into your computer.

WIP

## Flashing the firmware

1. Download the firmware to be flashed from the releases page.
2. Visit https://www.stephenkingston.net/CH55x-WebProgrammer/
3. Press Connect
4. Drop the hex file into the web page.
5. Flash!

## Reassembly

Put it back together and you're done!

## Install into car

WIP

## Updating the firmware with the new firmware

If you ever need to update the firmware with the new firmware, the new firmware can be put into bootloader mode by holding the key furthest away from the knob while plugging it into the computer. The new firmware can then be flashed without shorting the pins.


## Inspirations and References

This firmware is based on the work of the following projects:


* https://github.com/biemster/3keys_1knob/ - Showed me the possibility of flashing these keyboards and some implementation reference.
* https://github.com/wagiminator/MCU-Templates - the basis for `3keys_1knob` and a good reference for clean CH55X code.

## License

CC-BY-SA 3.0 as it is mostly based on https://github.com/wagiminator/MCU-Templates/blob/main/CH552/LICENSE . See LICENSE.md for more details.