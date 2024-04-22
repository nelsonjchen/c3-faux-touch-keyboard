# 🦾 comma three Touchkey keyboard

*Long arms for those of us with short arms from birth or those who can't afford arm extension surgery!*

![touchkey keyboard demo](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/d9617916-2442-4287-b430-709dad173da8)

These are instructions and firmware for a relatively cheap off-the-shelf macro keyboard off AliExpress/Amazon (that has many copies/clones) to control a comma three running openpilot from an accessible and comfortable driver's position.

No more this and reaching out when you want to bookmark a segment or toggle experimental mode:

![touch](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/d6085e3b-109d-4347-a9d0-cbc847b3c234)

The macro keyboard we will be using look like this and come in this configuration:

![Picture of keyboard](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/bf44187f-1143-46d3-bb61-b068b7270087)

The default configuration software and firmware on these kinds of keyboards is notoriously bad, sketchy in origin, and may not be trustworthy. Most importantly, it won't work for our use case where we need to send touchscreen input. So, don't bother downloading and don't install the configuration software. We will be throwing it all out.

Instead, we flash the keyboard's microprocessor to pretend to be a USB touchscreen digitizer, and the buttons to send touch events to the comma three. The new firmware touch areas are currently hardcoded to the bottom left corner for bookmark, the center for hide/show menu, and the top right corner for experimental mode toggling. The knob is used to control the LEDs to be a "lamp" light for night driving use and pressing down on it is an alternative button for the top right corner button pressing.

**A limitation of the blind touch approach is that I don't think this might work for the comma prime navigation UI. I don't have comma prime to develop against and that issue is being tracked in this issue: https://github.com/nelsonjchen/c3-touchkey-keyboard/issues/2 .**

These keyboards are built around the [`CH552G`][ch552info] microcontroller. By shorting two pins together on initial power, the keyboard can be put into bootloader mode, and the new touchscreen-emulation firmware can then be flashed over USB.

Restoring the original vendor firmware is not possible without  the original vendor firmware which I haven't been able to find yet. That said, somewhat similar functional firmware to the original functionality without the sketchy vendor software can be found here if you want to "reverse" the process and restore the keyboard to something like its original functionality:

https://github.com/biemster/3keys_1knob

## Bill of Materials

Cost: Expect the cost to be about $3-20 for the keyboard, $2-10 for the male USB-C to female USB-A adapter, and an optional $6-10 for nicities like 90 degree USB-C angle adapters for a cleaner look. You may also need a USB-C extension cable. The rest of the materials you probably have lying around. The cost can be $14 to $40 depending on how long you want to wait for the materials to arrive from AliExpress, if you're in a hurry and want to buy from Amazon, or how clean you want the install to look.

### Keyboard

![3Keys-Mechanical-Keyboard-For-Photoshop-USB-Macro-Custom-Keyboard-RGB-Gaming-Custom-Programming-Knob-Mini-Keyboard jpg_](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/9c643f4a-c5e8-464b-b5f0-c03f875083f7)

A specific type of mass-produced macro keyboard with a [`CH552G`][ch552info] microcontroller. The one this project supports and what I used was this:

* https://www.aliexpress.us/item/3256806441586710.html

  * Note that sometimes these keyboards are on sale for $5 from vendors.
  * https://www.aliexpress.us/item/3256806441586710.html
  * <img width="619" alt="image" src="https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/266f13cb-fbde-4881-9231-7d1539b2891a">

* https://amzn.to/3Q7Mw5c

Go for AliExpress if you want to save money and don't mind waiting. Go for Amazon if you want it faster and have Prime.

As there are many vendors of this keyboard, there is no steady name other than a similar look, so keep an eye for these traits when looking for an equivalent keyboard:

* Looks like the keyboard in those links I have above.
* Shows up when you search for "3 keys 1 knob keyboard"
* 3 keys in a row
* 1 knob, metal-looking usually
* Acryllic layered construction with rounded corners
* Exposed screws heads on bottom and top
* Multi-color LEDs
* USB-C is offset a bit torwards the knob side of the keyboard and not in the center.
* Comes with a male USB-A to male USB-C cable
* No wireless.
* Has a black or white variant. Color doesn't matter, choose your preference.

These will usually guarantee you get a keyboard with the `CH552G` microcontroller present in the manner we need.

### Male USB-C to Female USB-A cable

Unfortunately, the keyboard is not perfect. It is missing two resistors in it that allow it to be powered by a USB-C port in a USB-C to USB-C setup. However, we need to power it from the comma three's USB-C port. While it is theoretically possible to solder in the right resistors, it is easier to just use a cable to convert the comma three USB-C port to a USB-A port. The longer, the better and here are some examples:

* https://amzn.to/4aFOj9I

* https://www.aliexpress.us/item/3256806084714064.html

### Right Angle Adapters

These are optional, but they help reduce cable strain on the cable at the comma three's USB-C port and clean up the cables in the area with the keyboard attached to your car.

* https://amzn.to/3U3WtSu - This is a pack of 5 adapters with 3 of them being useful to get the angles right to reduce strain and clean up the cables.
* https://www.aliexpress.us/item/3256805061903701.html
  * Purchase "Color": 1, 4, 5

### Male USB-C to Female USB-C Extension Cable

This is optional. Without it, the setup barely fits in my Corolla. If you got the 5 pack of adapters from Amazon above, there's a female to female adapter you can use to extend the cable with a male USB-C to male USB-C cable alternatively if you'll like.

Search on Amazon or AliExpress for "USB-C extension cable".

### Mounting Tape

You can attach the keyboard to your car however you like. I used large 3M Command Picture Hanging Strips to attach the keyboard in front of my gear shifter. They are strong enough to hold the keyboard in place and can be fully removed without damaging the car. The strips are also velcro-like so you can remove the keyboard to change it or reprogram it away from the car without disturbing the tape too.

https://amzn.to/49Nm87A

Of course, you can use whatever else you like for mounting.

AliExpress has command strip-like products as well, but I haven't tried them yet:

https://www.aliexpress.us/w/wholesale-3m-command-picture-hanging-strips.html

### Shorting Tools

You'll need to short two pins on the `CH552G` microcontroller to put it into bootloader mode. You can do this with a paperclip or a metal conductor, but it is easier to do with test hooks.
After you flash it with this project's firmware, you won't need these tools anymore as you can boot the keyboard into bootloader mode by holding the key furthest from the knob down on powerup so these tools are a first-time only thing. 

#### Cheap

* A paperclip or metal conductor to short the pins on some chip on the off-the-shelf keyboard for the initial flashing.
* Steady hands or tape or whatever to mask off pins that aren't to be shorted together.
* Or YOLO it and short the pins with a paperclip or metal conductor with no tape. Good luck!

#### Throw a bit of money at AliExpress

You can use these hooks to precisely clip onto the pins to and then connect the two hooks of the pins to short them together. This is useful if you have shaky hands or need to do this multiple times.

https://www.aliexpress.us/item/3256805244460946.html - Get the 2pcs male option.

## Instructions

### (Windows) Preparing your Windows computer to flash

You will need to use Zadig to make the device when it is in bootloader mode available to flashing software.

1. Download Zadig from https://zadig.akeo.ie/
2. Run Zadig
3. Under devices, select `Create New Device`.
   1. ![zadig_create_new_device](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/5fad813d-7202-4c03-9d69-1e5a01985c0e)
4. Fill in three fields. The first field is just a description and you can fill in anything. The next two fields are very important. Fill them in with 4348 and 55e0 respectively. Press "Install Driver" and give it a few minutes to install.
   1. ![fill it in this way](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/c0280b31-646e-43bc-a01b-6269a9c0be70)
  
### (Ubuntu Linux) Preparing Ubuntu Linux to allow the device to flash via a Chromium-based browser

You will need to create a udev rule to allow your user account to access the device when it is in bootloader mode.

1. Open a terminal and enter the following commands to create the udev rule:

```bash
sudo tee /etc/udev/rules.d/50-ch552-flash.rules <<EOF
# CH552G Bootloader
SUBSYSTEMS=="usb", ATTRS{idVendor}=="4348", ATTRS{idProduct}=="55e0", GROUP="plugdev", MODE="0666"
EOF
```

2. Reload the udev rules:

```bash
sudo udevadm control --reload-rules
```

3. Ensure your user account is part of the `plugdev` group:

```bash
sudo usermod -a -G plugdev $USER
```

4. Log out and log back in for the group change to take effect.

### Getting the keyboard into bootloader mode

1. Disassemble the keyboard. There are 4 screws on the back of the keyboard.
2. Unscrew them and take off the bottom. There will be an acrylic cut out. You will see the `CH552G` microcontroller.
3. Take out the acrylic cut out so you have a bit more space
4. Short these two pins on the `CH552G` microcontroller. Technical info: These pull USB D+ up to 3.3V from the chip's 3.3V supply.
   * <img width="451" alt="diagram" src="https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/acf0296f-f89b-44d5-97a0-b87a16d54020">
   * ![real world](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/80d1c5b8-61d9-4d01-8cbe-9e7f5c4405f6)
5. While these two pins are shorted together, plug the keyboard into your computer.
6. Remove the shorting tool after the keyboard is plugged in.
7. Check if the keyboard shows up in Device Manager as a `WinChipHead` or `CH552` or whatever device you've named it as in Zadig. On Linux, use `lsusb` to check for a `WinChipHead` device. On macOS, open the `System Information` app and check the USB section.

### Flashing the firmware

After the keyboard is in bootloader mode, you can flash the firmware.

1. Download the `touch.hex` firmware to be flashed from the [GitHub Releases page](https://github.com/nelsonjchen/c3-touchkey-keyboard/releases).
2. Visit https://www.stephenkingston.net/CH55x-WebProgrammer/ on a Chromium based browser
3. Press Connect
4. Select the device with "`WinChipHead`" in the name from the dropdown.
5. Drop the `.hex` file into the web page and it'll flash.

### Keyboard Reassembly

Put it back together, screw it down, and you're done!

### Testing your work

Connect the keyboard to the comma three and test the buttons and knob. Start the car, with the engine not running. The bottom left corner should bookmark, the center should hide/show the side menu, and the top right corner should toggle experimental mode (if available). The knob should control the LEDs and pressing down on the knob should act as an alternative button for the top right corner.

### Install into car

Pretend it's like a dashcam install, which you should have done with the comma three. Use the mounting tape to attach the keyboard to a convenient location. I put mine in front of the gear shifter. Connect the cables. Use the right angle adapters to clean up the cable routing, reduce strain on the comma three's USB-C port and minimize any weird blocking of the cameras or interior.

I ran my cable down the passenger side A pillar under the trim.

#### My Install Photos

![c3](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/4b39ad35-261c-450b-8351-33ba2037e278)

![down the a pillar](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/cc9bc08f-d1fb-4949-8ea1-9398a7b691b3)

![console](https://github.com/nelsonjchen/c3-touchkey-keyboard/assets/5363/f66b56cb-b862-4018-b9cc-11246ea958d5)


## Updating the firmware with the new firmware

If you ever need to update the firmware with the new firmware, the old firmware can be put into bootloader mode by holding the key furthest away from the knob while plugging it into the computer. All the LEDs should light up in full white when this is done. The new firmware can then be flashed without shorting the pins using the web flasher.

## Development

See the Makefile and try to get `make flash` going. You'll need sdcc, Python with pyusb, and build tools.

`sudo libinput debug-events` is your friend. You may need to `apt update -y` and `apt install -y libinput-tools` to get it.

## Inspirations and References

This firmware is based on the work of the following projects:

* https://github.com/biemster/3keys_1knob/ - Showed me the possibility of flashing these keyboards and some implementation reference.
* https://github.com/wagiminator/MCU-Templates - the basis for `3keys_1knob` and a good reference for clean CH55X code.

## License

CC-BY-SA 3.0 as it is mostly based on https://github.com/wagiminator/MCU-Templates/blob/main/CH552/LICENSE . See LICENSE.md for more details.

[ch552info]: https://hackaday.com/2019/02/17/how-to-program-a-really-cheap-microcontroller/
