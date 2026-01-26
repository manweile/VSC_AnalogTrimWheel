# Fritzing
Yeah, I know some dev's look down on Fritzing, and I don't blame them. The program does indeed have drawbacks.   
But it's biggest pro is the intuitive breadboard view, and the ease of use compared to ANY cad program.

## JTAG and ISP
Atmel wants to gouge a pretty penny for connectors, which I refuse to pay.  

Luckily, Adafruit has a [SWD breakout](https://www.adafruit.com/product/2743) that you can adapt for JTAG use.  
All that you need to do is pay attention to the pin mapping specified in Atmel-ICE documentation.  

Adafruit also has an [ISP breadboard adapter](https://www.adafruit.com/product/1465), perfect for ISP.  

Both breakouts are for use with Atmel-ICE with flat jtag/isp cable.  
You can attach both the 10 pin header and 6 pin header.  

## Micro
The micro does have a dedicated ISP header, you can use it or the regular edge pins.  
For JTAG, use the regular edge pins. 

[Micro JTAG ISP](https://github.com/manweile/VSC_AnalogTrimWheel/blob/master/Documentation/Fritzing/micro_program_debug_bb.pdf)  

If you put anything in the regular edge pins next to the ISP header, you can't use the Atmel-ICE flat cable ISP connector.  
It's got a keyway that protrudes, and will prevent you from getting proper electrical connection.  
Hence the ISP breadboard adapter.  

## Pro Micro
The promicro does not have a dedicated ISP header, use the regular edge pins.  
For JTAG, use the regular edge pins.  

[Promicro JTAG ISP](https://github.com/manweile/VSC_AnalogTrimWheel/blob/master/Documentation/Fritzing/promicro_program_debug_bb.pdf)

### SWD for JTAG and ISP
My Atmel-ICE flat cable ISP developed a broken wire somewhere, which rendered the ISP connection unusable.  
Fortunately, after reviewing the Atmel-ICE documentation, I realized a SWD header can supply signal for both JTAG and ISP.  

[Promicro SWD Debug/Program](https://github.com/manweile/VSC_AnalogTrimWheel/blob/master/Documentation/Fritzing/promicro_swd_to_jtag_and_isp_mapping_bb.pdf)  

