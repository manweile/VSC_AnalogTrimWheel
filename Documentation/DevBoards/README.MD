# Custom USB Device

The promicro does NOT have it's own entry in the arduino boards.txt file.  
This means when you hook up an Arduino Pro Micro, what you will see in Devices & Printers is Arduino Leonardo.  

## IMPORTANT

Creating a promicro entry in boards.txt has ramifications!
Boards.txt defines the characteristics and parameters of different Arduino boards and microcontrollers.  
It tells the Arduino IDE and Arduino-CLI  how to:

- compile
- link
- upload code

This WILL impact any VS Code c_cpp_properties.json, tasks.json or launch.json functionality for Arduino-CLI.  
Specifically any inputs looking for fully qualified board name arduino:avr:promicro or build directory arduino.avr.promicro  

A Pro Micro is just a renamed Leonardo!  
You only want to change the .name, .pid.3, .build.pid, .build.usb_product, and .build.usb_product values.  
You can optionally add promicro.build.usb_manufacturer.  

## Setting custom USB device name

1. Modify Arduino Board Configuration
   1. Ensure Arduino IDE is closed
   2. Locate the boards.txt file  
      Usually in C:\users\USERNAME\AppData\Local\Arduino15\packages\arduino\hardware\1.8.x,
      where USERNAME is your user name and 1.8.x is the version of Arduino AVR Boards installed by Arduino IDE.  
      You can get the version by checking Boards Manager in Arduino IDE.  
   3. Create a custom board entry  
      Copy the existing leonardo (and not leonardoeth) definition lines to end of board.txt file.  
      In the new custom board entry, edit all "leonardo" entries to "promicro"  
   4. Change promicro.name=Arduino Leonardo to promicro.name=Arduino Pro Micro
   5. Change promicro.pid.1=0x8036 to promicro.pid.1=0x8035
   6. Change promicro.build.pid=0x8036 to leonardo.build.pid=0x8035  
      You want a unique pid.  
      It's a good idea to search through out boards.txt to make sure 0x8035 is not in use.  
      If it is, do a regex search for the last digit or last two digits.  
   7. Change promicro.build.usb_product="Arduino Leonardo" to promicro.build.usb_product="Arduino Pro Micro"
   8. Optional - add promicro.build.usb_manufacturer="Arduino" underneath promicro.build.usb_product="Arduino Pro Micro"
   9. Save the boards.txt file
   10. Ensure your pro micro is plugged into USB on computer
   11. Open Arduino IDE
   12. Find & select the new custom board name Tools > Board Manager > Arduino AVR Boards
   13. Upload a sketch (preferably the analog trim wheel sketch!)
   14. Close Arduino IDE

## Resulting Arduino Pro Micro Entry in Boards.txt

promicro.name=Arduino Pro Micro  

promicro.vid.0=0x2341  
promicro.pid.0=0x0036  
promicro.vid.1=0x2341  
promicro.pid.1=0x8035  
promicro.vid.2=0x2A03  
promicro.pid.2=0x0036  
promicro.vid.3=0x2A03  
promicro.pid.3=0x8035  

promicro.upload.tool=avrdude  
promicro.upload.protocol=avr109  
promicro.upload.maximum_size=28672  
promicro.upload.maximum_data_size=2560  
promicro.upload.speed=57600  
promicro.upload.disable_flushing=true  
promicro.upload.use_1200bps_touch=true  
promicro.upload.wait_for_upload_port=true  

promicro.bootloader.tool=avrdude  
promicro.bootloader.low_fuses=0xff  
promicro.bootloader.high_fuses=0xd8  
promicro.bootloader.extended_fuses=0xcb  
promicro.bootloader.file=caterina/Caterina-Leonardo.hex  
promicro.bootloader.unlock_bits=0x3F  
promicro.bootloader.lock_bits=0x2F  

promicro.build.mcu=atmega32u4  
promicro.build.f_cpu=16000000L  
promicro.build.vid=0x2341  
promicro.build.pid=0x8035  
promicro.build.usb_product="Arduino Pro Micro"  
promicro.build.usb_manufacturer="Arduino"  
promicro.build.board=AVR_LEONARDO  
promicro.build.core=arduino  
promicro.build.variant=leonardo
promicro.build.extra_flags={build.usb_flags}
