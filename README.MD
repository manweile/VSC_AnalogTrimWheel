# Analog Trim Wheel
A microcontroller for MSFS Flight Simulator trim tab control  
Based on https://makers-point.com/3d-prints/trim-wheel-pro/

## About
This project was as much for learning how to break free of Microchip Studio as building a trim wheel controller.

## Open Source Tools
- VS Code
- Microchip Studio
- Arduino IDE
- Visual Studio
- Eclipse
- OpenOCD
- pyOCD
- AVaRICE
- avr toolchain
- arduino-cli

## Purchased Tools
- Atmel-ICE
- Visual Micro

### IDES
#### VS Code
Why? Because it's hella easier to use than Microchip Studio, it's better than Arduino IDE, it's very well supported, and it's free.  
VS Code is Windows and/or Ubuntu (either free-standing or via WSL), far more extensions available (and almost all are free), and I have used it for 10 years now.  
Far and away the devil I know and comprehend. Sure the documentation could be better, but hey, isn't all software like that?

#### Arduino IDE
Let's face it, the Arduino IDE is the sandbox. It's where you start, but you sure as hell out grow it quickly.  
It does have it's uses though - quick way to get the avr tools (avr-gcc, avr-gd, avrdude), third party libraries, board management, etc.  
Arduino IDE is a staring point - installing it gets you a Windows avr toolchain and board packages.  
You're going to need it installed anyways if you want to do arduino coding with Microchip Studio.

#### Microchip Studio
Frankly, unless you really need to go deep into the bare metal, registers and assembly code, you don't need it, and it's only for Microchip mcu's anyways.  
Microchip is no longer updating it, and they are pushing you hard to switch to MPLAB. No thank you.  
Visual Micro is a paid extension for Microchip Studio, and does make Microchip Studio somewhat more bearable (at a cost of steeper learning curve).  
I will grant the device programming dialog GUI is easier to use with Atmel-Ice than avrdude cli and about equal with avrdudess GUI though.  

#### Visual Studio
VS Code's big brother might be an option worth looking into. The portability/availability of extensions will probably be the deciding factor.  
BTW, Microchip Studio is a port of Visual Studio. Not sure how Microchip pulled that off.  

#### Eclipse
No, just no. Been there, done that with java, real PITA to configure. Don't even want to try for avr mcu's.  

### Interfacing Software
To hardware debug with Atmel-Ice, you need interfacing software between Atmel-ICE, avr-gdb, and your mcu.  

#### pyOCD
Was a non-starter, I simply could not get it to work. A pity, because I really liked the os-agnosticism inherent to a python app.  
Uninstalled, but going to keep an eye on it in case it gets usable.  

#### OpenOCD
Was far more promising, but still only a partial success.  
Supposedly, Microchip Studio uses OpenOCD "under the hood", but I couldn't get native OpenOCD to work with my Arduino Micro & Pro Micro (atmega32u4).  
Documentation is conflicting on OpenOCD working with AVR mcu's, it really appears to be slanted to SAM/ARM mcu's, which I don't have any of (yet).  
Keeping it around for the potential to work with ESP32 mcu's, which I do have.

#### AVaRICE
The winner (no shit sherlock, literally made for AVR mcu's and Atmel-ICE!), downside is still had to jump through some hoops to run on Windows, as it really Linux based.  
Namely, had to run AVaRICE on WSL Ubuntu, and do some fancy dancing with usbipd-win to get communication with the Atmel-Ice.  
This setup is somewhat kludgey, namely, I have to revert the usbipd configuration to restore normal Windows operation with Atmel-Ice, arduino-cli & avrdude.  
Needs further investigation to see if I can streamline VS code launch and tasks operations.  

### AVR Toolchain
#### Arduino AVR Toolchain
I prefer the arduino avr toolchain. Why? Because it's maintained, compiled for Windows, works with my arduino boards, it's reasonably documented, it's easy to update.  
You can update the IDE itself, which might update your tool chain. Personally, I like the 7.3.0-atmel3.6.1-arduino5 toolchain that came with installing Arduino IDE 2.2 version.  
You can manually update the toolchain by going to https://github.com/arduino/toolchain-avr, grabbing the zip file for the version you want, and extract to correct location.  
- On Windows: C:\Users\<USER>\AppData\Local\Arduino15\packages\arduino\tools  
- On Linux (Ubuntu): /HOME/<user>/.arduino15/packages/arduino/tools/

Just remember if you any environment variables looking at those locations, you'll need to edit them!  

#### Manual AVR toolchain
Many variations here. https://www.tonymitchell.ca/tags/avr/ is a good source of info & guidance.  
You will highly probably need to do some Linux on Windows setup - be it WSL or Cygwin, MYSYS2, etc.  
Again, don't forget about those environment variables!  

#### AVRDUDE
Avrdude (AVR Downloader Uploader) https://avrdudes.github.io/avrdude/ is a program for downloading and uploading the on-chip memories of Atmel’s AVR microcontrollers.  
It comes with the avr toolchain (all flavours and source I have seen so far). It's what Microchip Studio and Arduino IDE use under the hood to get code onto your mcu.  
Avrdude is a command line application, and easily used with VS Code tasks.  

#### AVRDUDESS
AVRDUDESS https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/ is a gui wrapper for avrdude.  
Quite useful when you have something kinda one off that you don't have a VS Code task configured (restoring boot loaders for one!), and want a graphic interface for avrdude.  

#### Arduino-cli
Arduino CLI is an all-in-one command line solution that provides Boards/Library Managers, sketch builder, board detection, uploader, and many other tools.  
It's the hidden motor that runs in Arduino IDE. Christ knows why Arduino did that, forcing you to a manually install if you want to leverage it into VS Code.  
The documentation is adequate (https://docs.arduino.cc/arduino-cli/), but sure would like to find a well formatted pdf, or better yet, a hard cover manual.  
The beauty of arduino-cli is you can do so much with it from VS Code tasks!  
What's more, Arduino replaced make with arduino-cli compile functionality, it's actually easier to compile with.  

### Hardware Programmer
#### Atmel-ICE
TODO

## BOM
TODO


