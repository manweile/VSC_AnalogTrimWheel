# Programming Environment
## About
This project was as much for learning how to break free of Microchip Studio as building a trim wheel controller.

# Tools Used
- Atmel-ICE
- VS Code & Extensions
- Arduino IDE
- avrdude
- avr toolchain (avr-gdb, avr-gcc)
- Arduino-CLI
- AVRDUDESS (optional)
- WSL2
- AVaRICE

## Atmel-ICE
I know there are other hardware programmer/debuggers available, but the Atmel-ICE is for AVR/SAM mcu's.  
The Arduino Pro Micro and Micro both have JTAG and ISP pins broken out.  
So do the Mega2560 and Uno - but you can't easily use them for a HID application.  
I am presuming you've already installed drivers for you Atmel-ICE per MicroChips install instructions (https://www.microchip.com/en-us/development-tool/atatmel-ice).  
Follow the JTAG_ICE setup and use from WSL.txt file.  

## ArduinoIDE
Let's face it, the Arduino IDE is the sandbox. It's where you start, but you sure as hell out grow it quickly.  
It does have it's uses though - quick way to get the avr tools (avr-gcc, avr-gdb, avrdude), third party libraries, board management, etc.  
Arduino IDE is a staring point - installing it gets you a Windows avr toolchain and board packages.  
You're going to need it installed anyways if you want to do arduino coding with Microchip Studio.
https://www.arduino.cc/en/software/

## AVR Toolchain
### Arduino AVR Toolchain
I prefer the arduino avr toolchain. Why? Because it's maintained, compiled for Windows, works with my arduino boards, it's reasonably documented, it's easy to update.  
You can update the IDE itself, which might update your tool chain. Personally, I like the 7.3.0-atmel3.6.1-arduino5 toolchain that came with installing Arduino IDE 2.2 version.  
You can manually update the toolchain by going to https://github.com/arduino/toolchain-avr, grabbing the zip file for the version you want, and extract to correct location.  
- On Windows: C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\tools  
- On Linux (Ubuntu): /HOME/USERNAME/.arduino15/packages/arduino/tools/

Just remember if you any environment variables looking at those locations, you'll need to edit them!  

### Manual AVR toolchain
Many variations here. https://www.tonymitchell.ca/tags/avr/ is a good source of info & guidance.  
You will highly probably need to do some Linux on Windows setup - be it WSL or Cygwin, MYSYS2, etc.  
Again, don't forget about those environment variables!  

## AVRDUDE
Avrdude (AVR Downloader Uploader) https://avrdudes.github.io/avrdude/ is a program for downloading and uploading the on-chip memories of Atmel’s AVR microcontrollers.  
It comes with the avr toolchain (all flavours and source I have seen so far). It's what Microchip Studio and Arduino IDE use under the hood to get code onto your mcu.  
Avrdude is a command line application, and easily used with VS Code tasks.  

## AVRDUDESS
AVRDUDESS https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/ is a gui wrapper for avrdude.  
Quite useful when you have something kinda one off that you don't have a VS Code task configured (restoring boot loaders for one!), and want a graphic interface for avrdude.  

## Arduino-CLI
Arduino CLI is an all-in-one command line solution that provides Boards/Library Managers, sketch builder, board detection, uploader, and many other tools.  
It's the hidden motor that runs in Arduino IDE. Christ knows why Arduino did that, forcing you to a manually install if you want to leverage it into VS Code.  
The documentation is adequate (https://docs.arduino.cc/arduino-cli/), but sure would like to find a well formatted pdf, or better yet, a hard cover manual.  
The beauty of arduino-cli is you can do so much with it from VS Code tasks!  
What's more, Arduino replaced make with arduino-cli compile functionality, it's actually easier to compile with.  

### arduino-cli.yaml
The yaml configuration file is probably the most important step in the arduino-cli install process.  
It's also something that could use better documentation! https://docs.arduino.cc/arduino-cli/configuration/  
I found the important sections of the yaml file were:
- board manager
  - additional urls
        This where every board you want to work with needs to be.  
        The listing is also exactly what you put into the Arduino IDE preferences Additional boards manager URLS. Literally copy from and paste into yaml file.
- directories
  - builtin
    - libraries
        The path to your builtin Arduino Libraries. C:\Users\USERNAME\AppData\Local\Arduino15\libraries
  - data
        the path to your Arduino directory used to store Boards/Library Manager index files and Boards Manager platform installations. C:\Users\USERNAME\AppData\Local\Arduino15
  - downloads
        directory used to stage downloaded archives during Boards/Library Manager installations. C:\Users\USERNAME\AppData\Local\Arduino15\staging
  - user
        the equivalent of the Arduino IDE's "sketchbook" directory. You can copy from Arduino IDE preferences and past it into yaml file.

## VSCODE
Why? Because it's hella easier to use than Microchip Studio, it's better than Arduino IDE, it's very well supported, and it's free.  
VS Code is Windows and/or Ubuntu (either free-standing or via WSL), far more extensions available (and almost all are free), and I have used it for 10 years now.  
Far and away the devil I know and comprehend. Sure the documentation could be better, but hey, isn't all software like that?

### Extensions
#### Required
- C/C++: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools
Need this for Intellisense and debugging.

#### Optional
- WSL: https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl

#### Failures
- PlatformIO https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide
    Couldn't get it to work for my AVR mcu's or with Atmel-ICE.  
    From the PlatformIO documentation, it really looks like really optimized for SAM/ARM mcu Arduino's, but not AVR mcu's. 

- Arduino Community Edition https://marketplace.visualstudio.com/items?itemName=vscode-arduino.vscode-arduino-community
    Gave me nothing but grief. Actually bricked my micro and pro micro boards.  
    Appears to be really optimized for SAM/ARM mcu Arduino's, but not AVR mcu's. 

### System Environment Variables
You can create environment variables here that your c_cpp_properties.json can use.
TODO eg

#### PATH
arduino-cli
avrdude

### tasks.json
TODO

### launch.json
TODO

### c_cpp_properties.json
This where you get you Intellisense from!  
Specifically, if you have 3rd party libraries, you need to put their paths here.  

## WSL
A WSL2 (Windows Subsystem for Linux) install was the winning solution.  
The primary reason was the libhidapi library - getting via Cygwin, MYSYS, or GetGNUWin32 proved to be impossible.  
Plenty of good documentation from Microsoft: https://learn.microsoft.com/en-us/windows/wsl/install

### AVaRICE on WSL2
The winner (no shit sherlock, literally made for AVR mcu's and Atmel-ICE!), downside is still had to jump through some hoops to run on Windows, as it really Linux based.  
Namely, had to run AVaRICE on WSL Ubuntu, and do some fancy dancing with usbipd-win to get communication with the Atmel-Ice.  
This setup is somewhat kludgey, namely, I have to revert the usbipd configuration to restore normal Windows operation with Atmel-Ice, arduino-cli & avrdude.  
Needs further investigation to see if I can streamline VS code launch and tasks operations.
Follow the WSL Avarice installation.txt file.  

# Other Tools
## IDES
### Microchip Studio
Frankly, unless you really need to go deep into the bare metal, registers and assembly code, you don't need it, and it's only for Microchip mcu's anyways.  
Microchip is no longer updating it, and they are pushing you hard to switch to MPLAB. No thank you.  
Visual Micro is a paid extension for Microchip Studio, and does make Microchip Studio somewhat more bearable (at a cost of steeper learning curve).  
I will grant the device programming dialog GUI is easier to use with Atmel-Ice than avrdude cli and about equal with avrdudess GUI though. 

#### Visual Micro
Visual Micro (https://www.visualmicro.com/) is paid extension for MicroChip Studio/Visual Studio.  
While it does help MicroChip Studio, it has it's own learning curve and foibles.

### Visual Studio
VS Code's big brother might be an option worth looking into. The portability/availability of extensions will probably be the deciding factor.  
I don't know if VSCode extensions are Visual Studio compatible. Sure would be nice if they are.  
BTW, Microchip Studio is a port of Visual Studio. Not sure how Microchip pulled that off.  

### Eclipse
No, just no. Been there, done that with java, real PITA to configure. Don't even want to try for avr mcu's.  

## Interfacing Software
To hardware debug with Atmel-Ice, you need interfacing software between Atmel-ICE, avr-gdb, and your mcu.  

### pyOCD
Was a non-starter, I simply could not get it to work. A pity, because I really liked the os-agnosticism inherent to a python app.  
Uninstalled, but going to keep an eye on it in case it gets usable.  

### OpenOCD
Was far more promising, but still only a partial success.  
Supposedly, Microchip Studio uses OpenOCD "under the hood", but I couldn't get native OpenOCD to work with my Arduino Micro & Pro Micro (atmega32u4).  
Documentation is conflicting on OpenOCD working with AVR mcu's, it really appears to be slanted to SAM/ARM mcu's, which I don't have any of (yet).  
Keeping it around for the potential to work with ESP32 mcu's, which I do have. 