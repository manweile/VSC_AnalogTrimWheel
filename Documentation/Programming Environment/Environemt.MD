# Programming Environment
## About
This project was as much for learning how to break free of Microchip Studio as building a trim wheel controller.

# Tools
- WSL2
- AVaRICE
- Atmel-ICE
- VS Code & Extensions
- Arduino IDE
- Arduino-CLI
- avrdude
- avr toolchain (optional)
- AVRDUDESS (optional)
- OpenOCD (optional)


## WSL
A WSL2 (Windows Subsystem for Linux) install was the winning solution.
The primary reason was the libhidapi library - getting via Cygwin, MYSYS, or GetGNUWin32 proved to be impossible.

### AVaRICE on WSL2
Follow the WSL Avarice installation.txt file.

## OpenOCD
While OpenOCD is supposed to function with ATmega32u4 mcu's, I couldn't get it to work.
I have left it in because it is supposed to work quite well with MicroChip SAM mcu's - I just don't have any.

## Atmel-ICE
I know there are other hardware programmer/debuggers available, but the Atmel-ICE is for AVR/SAM mcu's.

The Arduino Pro Micro and Micro both have JTAG and ISP pins broken out.
So do the Mega2560 and Uno - but you can't easily use them for a HID application.

I am presuming you've already installed drivers for you Atmel-ICE per MicroChips install instructions.
If not, you'll have to search for them.

Follow the JTAG_ICE setup and use from WSL.txt file.

## ArduinoIDE
TODO

## Arduino-CLI
TODO
add yaml file to project

## VSCODE
TODO

### Extensions
TODO
WSL
C/CPP

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

