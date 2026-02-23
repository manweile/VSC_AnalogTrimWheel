# Programming Environment
## About
This project was as much for learning how to break free of Microchip Studio as building a trim wheel controller.

# Tools Used
- Atmel-ICE
- Arduino IDE
- avr toolchain (avr-gdb, avr-gcc, avrdude)
- Arduino-CLI
- AVRDUDESS (optional, but recommended)
- VS Code & Extensions
- AVaRICE
- MYSYS2
- WSL2

## Atmel-ICE
I know there are other hardware programmer/debuggers available, but the Atmel-ICE is for AVR/SAM mcu's.  

The Arduino Pro Micro and Micro both have JTAG and ISP pins broken out.  
So do the Mega2560 and Uno - but you can't easily use them for a HID application.  
I am presuming you've already installed drivers for you Atmel-ICE per Microchip's [install instructions](https://www.microchip.com/en-us/development-tool/atatmel-ice).  

## ArduinoIDE
Let's face it, the [Arduino IDE](https://www.arduino.cc/en/software/) is the sandbox.  
It's where you start, but you sure as hell out grow it quickly.  
It does have it's uses though - quick way to get the avr tools (avr-gcc, avr-gdb, avrdude), third party libraries, board management, etc.  
You're going to need it installed anyways if you want to do arduino coding with Microchip Studio.

## AVR Toolchain
### Arduino AVR Toolchain
I prefer the arduino avr toolchain. Why?  
Because it's maintained, compiled for Windows, works with my arduino boards, it's reasonably documented, it's easy to update.  
You can update the Arduino IDE itself, which might update your tool chain. This is the easiest way to update.  

Personally, I like the 7.3.0-atmel3.6.1-arduino5 toolchain that came with installing Arduino IDE 2.2 version.  

You can [manually update the toolchain](https://github.com/arduino/toolchain-avr/tags), just download the zip file for the version you want.  
You WILL have to compile for your preferred OS, and that's an exercise I will leave to you.  
Look at the Readme.md file in your download for details.  

Of course you will also have to install the new compile in the correct location for your OS.  

- On Windows: C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\tools
- On Linux (Ubuntu): /HOME/USERNAME/.arduino15/packages/arduino/tools/

Just remember if you any environment variables looking at toolchain path locations, you'll need to edit them!  

### Manual AVR toolchain
Many variations here, [AVR Toolchain on Windows](https://www.tonymitchell.ca/posts/setup-avr-toolchain-on-windows/) is a good source of info & guidance.  

The major advantage of manually installing the toolchain is the pathing.  
You get to choose directory names, which means shorter and not highly specific.  

C:\AVR\avr8-gnu-toolchain\bin  
vs  
C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5\bin  

Downside is you might need to do some Linux on Windows setup - be it WSL2, Cygwin, MYSYS2, MINGW, etc.  
Again, don't forget about those environment variables!  

### AVRDUDE
[Avrdude (AVR Downloader Uploader)](https://avrdudes.github.io/avrdude/) is a program for downloading and uploading the on-chip memories of Atmel’s AVR microcontrollers.  
It's what Microchip Studio and Arduino IDE (and Arduino-CLI) use under the hood to get code onto your mcu.    
Avrdude is a command line application, and easily used with VS Code tasks.   

It comes with the Arduino AVR toolchain, which is a good reason to install the Arduino IDE.  
Otherwise you have to select a version from [Avrdudes](https://github.com/avrdudes/avrdude/releases) and manually install.  

## Arduino-CLI
Arduino-CLI is an all-in-one command line solution that's the hidden motor in Arduino IDE.  
Arduino-CLI provides Boards/Library Managers, sketch builder, board detection, uploader, and many other tools.  
However, an Arduino IDE installation does NOT give you command line access. Not sure why Arduino did that.  
This forces you to a manually install if you want to leverage it into VS Code.  
The [documentation](https://docs.arduino.cc/arduino-cli/) is adequate, but sure would like to find a well formatted pdf. 

The beauty of arduino-cli is you can do so much with it from VS Code tasks!  
What's more, Arduino replaced make with arduino-cli compile functionality, it's actually easier to compile with.  

### arduino-cli.yaml
The yaml configuration file is probably the most important step in the arduino-cli install process.  
It's also something that could use better [documentation!](https://docs.arduino.cc/arduino-cli/configuration/)  

I found the important sections of the yaml file were:  
- board manager
  - additional urls
        This where every board you want to work with needs to be.  
        The listing is also exactly what you put into the Arduino IDE preferences Additional boards manager URLS.  
        Literally copy from and paste into yaml file.
- directories
  - builtin
    - libraries
        The path to your builtin Arduino Libraries.  
        C:\Users\USERNAME\AppData\Local\Arduino15\libraries
  - data  
        the path to your Arduino directory used to store Boards/Library Manager index files and Boards Manager platform installations.  
        C:\Users\USERNAME\AppData\Local\Arduino15
  - downloads  
        directory used to stage downloaded archives during Boards/Library Manager installations.  
        C:\Users\USERNAME\AppData\Local\Arduino15\staging
  - user  
        the equivalent of the Arduino IDE's "sketchbook" directory.  
        You can copy from Arduino IDE preferences and past it into yaml file.

## AVRDUDESS
[AVRDUDESS](https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/) is a gui wrapper for avrdude.  

Optional, but recommended, it is quite useful when you have something kinda one off thing that you don't have a VS Code task configured for.  
- restoring boot loaders
- setting fuses  
- general mcu problem solving (ie unbricking!)

For fuses, you just have to be aware that in AVRDUDESS, a 1 for fuse actually means unset, and a 0 means set!  
In this aspect Microchip Studio's device programming dialog is actually more intuitive ... if you don't mind the baggage that comes with.  

AVRDUDESS is Windows centric, but you can get it onto Ubuntu - refer to the [AVRDUDESS readme](https://github.com/avrdudes/avrdude/blob/main/README.md). 

## VSCODE
Why?  
- Because it's hella easier to use than Microchip Studio
- It's better than Arduino IDE
- It's multi-OS 
  - Windows 
  - Ubuntu (either free-standing or via WSL2)
- I have 10 years of experience with it
- Fantastic amount of extensions
- And it's free!  

Far and away the devil I know and comprehend.  
Sure the documentation could be better, but hey, isn't all software like that?

### Extensions
- [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)  
      Required, need this for Intellisense and debugging.
- [Command Variable](https://marketplace.visualstudio.com/items?itemName=rioj7.command-variable)  
      Optional, but highly recommended for command and/or variable substitution in tasks and launch json files.  
      Allows you you really leverage external functionality.  
- [WSL](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)  
      Optional if you want to build Linux applications that run on WSL without the hassle of dual booting or a full virtual machine.  
      Required to use Ubuntu AVaRICE with Atmel-ICE, but comes with usb connectivity issue to the Atmel-ICE. More on that later.  

#### Failures
- [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)  
    Couldn't get it to work for my AVR mcu's or with Atmel-ICE.  
    From the PlatformIO documentation, it really looks like really optimized for SAM/ARM mcu Arduino's, but not AVR mcu's.  
    Also looks like might be the go to for ESP32 mcu's which I do have.  

- [Arduino Community Edition](https://marketplace.visualstudio.com/items?itemName=vscode-arduino.vscode-arduino-community)  
    Gave me nothing but grief.  
    Actually bricked my micro and pro micro boards.  
    Appears to be really optimized for SAM/ARM mcu Arduino's, but not AVR mcu's. 

### System Environment
#### Variables
You can create and use custom environment variables that your c_cpp_properties.json, tasks.json and launch.json can use.  

Note if you update a path pointed to by a custom environment variable, you have to update the variable!  

You need to name the custom variable ARDUINO_  
Be aware that the Arduino-CLI can use custom variables too.  
Eg. ARDUINO_DIRECTORIES_USER, which is D:\MyArduino\Projects on my computer.  
Make sure you are not conflicting, refer to https://docs.arduino.cc/arduino-cli/configuration/#configuration-keys to check!

- ARDUINO_HARDWARE_BOOTLOADERS:  
    C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.2\bootloaders
- ARDUINO_HARDWARE_CORES:  
    C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.2\cores
- ARDUINO_HARDWARE_LIBRARIES:  
    C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.2\libraries
- ARDUINO_HARDWARE_VARIANTS:  
    C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.2\variants
- ARDUINO_LIBRARIES: 
    D:\MyArduino\Projects\Libraries
- ARDUINO_TOOLS:  
    C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\tools
- ARDUINO_TOOLS_AVRGCC_BIN:  
  C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5\bin

Now I can use these system variables in the c_cpp_properties.json, tasks.json or launch.json and NOT have to put in a long ass OS specific path.  
You still have to maintain the path no matter what, but now it's only in 1 place.  

#### PATH
To use applications like arduino-cli, avr-gdb, avrdude, etc., in VSCode tasks.json and launch.json files, you must have them in your path.  
User or Environment really doesn't matter, so long as they are available.

### c_cpp_properties.json
This where you get you Intellisense from!  
Specifically, if you have 3rd party libraries, you need to put their paths here.  
Refer to:
- [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)  
- [C++ extension settings reference](https://code.visualstudio.com/docs/cpp/customize-cpp-settings)

### tasks.json
Tasks.json is where you get to leverage command line scripts and external tools.  
Refer to [Integrate External Tools via Tasks](https://code.visualstudio.com/docs/debugtest/tasks) for documentation.

### launch.json
Launch.json is where the debugging magic happens.  
Refer to [Launch Configurations](https://code.visualstudio.com/docs/debugtest/debugging-configuration) for documentation.  
I also found google AI searches helpful (so long as you watch out for "hallucinations").  

## AVaRICE
AVaRICE was the winner (no shit sherlock, literally made for AVR mcu's and Atmel-ICE!) over [OpenOCD](https://openocd.org/) and [pyOCD](https://pyocd.io/).  
I never tried [Bloom](https://bloom.oscillate.io/) - found out about it after I got AVaRICe working, and it's Linux only.  

The major issue with AVaRICE was operating system flavour.  
With Ubuntu, the usual sudo apt update && sudo apt upgrade -y followed by sudo apt install avarice works fine.  
The problem after that was Atmel-ICE is very much a Windows tool - interfacing across WSL2 to use the Atmel-ICE is kludgy.  
More on that in [AVaRICE on WSL2](#avarice-on-wsl2).

With Windows ... oh dear.  
The primary grief was the libhidapi library - getting it via Cygwin, MYSYS, or GetGNUWin32 proved to be impossible.  

AVaRICE github has documentation saying you can use Cygwin to compile.  
When you read closer, it's a much older version of Cygwin (cygwin 1.3.22-1). 

GetGNUWin32 just didn't work. Ended up uninstalling it.  

MYSYS actually worked!  

## MYSYS2
[MYSYS2](https://www.msys2.org/) brings powerful, Linux-style development tools and package management to Windows users.  
MYSYS2 simplifies the process of creating native applications.  
Installation is straightforward, use is very easy.  

### AVaRICE on MYSYS2
AVaRICE on MYSYS2 worked when I dug into the github workflow logs.  
Beautiful template on how to compile and use AVaRICE.  
Upshot is libhidapi is replaced, but you have to compile 3 different libraries before you compile AVaRICE.  

You will have to run AVaRICE in a MYSYS2 MYSYS shell, but it works quite well, command line and in tasks/launch json files.  
The payoff is you can stay entirely in Windows - no arcane interfacing with Atmel-ICE required!  

Refer to [MYSYS2 Avarice compilation.txt](https://github.com/manweile/VSC_AnalogTrimWheel/blob/master/Documentation/Programming%20Environment/MYSY2%20Avarice%20compilation.txt)

## WSL2 
Plenty of good documentation from Microsoft: https://learn.microsoft.com/en-us/windows/wsl/install.  
Installation is straightforward, configuration can take little time, but is worth it.  
WSL2 offers a full Linux environment directly on Windows using a light weight virtual machine.  

### AVaRICE on WSL2
AVaRICE on WSL2 Ubuntu works, downside is still had to jump through some hoops to run on Windows.   
- The installation of AVaRICE is quite painless
  - but have to do some fancy dancing with usbipd-win to get communication with the Atmel-ICE.    

This setup is somewhat kludgey
- have to revert the usbipd configuration to restore normal Windows operation with Atmel-ICE, arduino-cli & avrdude.  

Needs further investigation to see if I can do the usbipd configuring in VS code launch and tasks operations.  

Follow the [WSL Avarice installation.txt](https://github.com/manweile/VSC_AnalogTrimWheel/blob/master/Documentation/Programming%20Environment/WSL%20Avarice%20installation.txt) file.  
Follow the [JTAG_ICE setup and use from WSL.txt](https://github.com/manweile/VSC_AnalogTrimWheel/blob/master/Documentation/Programming%20Environment/JTAG_ICE%20setup%20and%20use%20from%20WSL.txt) file to run AVaRICE on WSL2.  

Bottom line, it works, and it is a Ubuntu solution if that's your bent.  

# Other Tools
## IDES
### Microchip Studio
Microchip is no longer updating it, and promoting switching to MPLAB. No thank you.  
It's only for Microchip mcu's anyways, and really is overkill for almost all development tasks.  
What it is good for is going deep into the bare metal, registers, ports, and assembly code.  
I will grant the device programming dialog GUI is easier to use with Atmel-ICE than avrdude, and about equal with AVRDUDESS GUI.

#### Visual Micro
[Visual Micro](https://www.visualmicro.com/) is a paid extension for MicroChip Studio/Visual Studio.  
While it does help MicroChip Studio, it has it's own learning curve and foibles.  
And you can't have an simultaneous install of the extension in both Microchip Studio and Visual Studio.  
It's one or the other, and furthermore, you can only swap once per month!

### Visual Studio
VS Code's big brother might be an option worth looking into.  
VSCode extensions are not Visual Studio compatible. Sure would be nice if they were.  
Personally, I'm not fond of the default layout of VS 2026 - I actually prefer older versions like 2017/2019.  
BTW, Microchip Studio is a port of Visual Studio. Not sure how Microchip pulled that off.  

### Eclipse
No, just no. Been there, done that with Java. 
I find Eclipse a real PITA to configure. Don't even want to try for avr mcu's.  

## Interfacing Software
To hardware debug with Atmel-ICE, you need interfacing software between Atmel-ICE, avr-gdb, and your mcu.  

### pyOCD
[pyOCD](https://pyocd.io/) was a non-starter, I simply could not get it to work.  
A pity, because I really liked the os-agnosticism inherent to a python app.    
Uninstalled, but going to keep an eye on it in case it gets usable.  

### OpenOCD
[OpenOCD](https://openocd.org/) was far more promising, but still only a partial success.  
Supposedly, Microchip Studio uses OpenOCD "under the hood".  
I couldn't get native OpenOCD to work with my Arduino Micro & Pro Micro (atmega32u4).  

Documentation is conflicting on OpenOCD working with AVR mcu's.  
It really appears to be slanted to SAM/ARM mcu's, which I don't have any of (yet).  
Keeping it around for the potential to work with ESP32 mcu's, which I do have.  

### Bloom
I never tried [Bloom](https://bloom.oscillate.io/), found it after I had AVaRICE working.  At first glance, it looks good.  
I like the Insight GUI, which is something that could rival Microchip Studio for serious bare metal work.  
The caveat with Bloom is that it is Linux only, and I already have that with AVaRICE.  
Going to keep an eye on it though for a Windows port.