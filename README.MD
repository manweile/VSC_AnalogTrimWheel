# Analog Trim Wheel

A microcontroller for MSFS Flight Simulator trim tab control  

## About

I had been using my Thrustmaster TWCS dial axis as the trim wheel controller in Microsoft Flight Simulator.  
However, it is way to small of diameter - the sensitivity makes it nearly impossible to use.  
Trying to adjust the sensitivity response just wasn't working either.  

So I went searching for a microcontroller project and found [Trim Wheel Pro](https://makers-point.com/3d-prints/trim-wheel-pro/).  
The large diameter wheel and 360 degree non-contact angle sensor attached to it were exactly the solution I needed.  
The Arduino Pro Micro met my needs for the USB HID device. Since I am a retired developer, programming the Arduino was no issue.  
However, I did not own a 3d printer at the time. My son-in-law owns several, he borrowed me one, and I ended up buying a newer model of it.  

This project was also as much for learning how to break free of Microchip Studio as building a trim wheel controller.  
Refer to the [Environment README](https://github.com/manweile/VSC_AnalogTrimWheel/blob/master/Documentation/Programming%20Environment/README.MD) file for details.  

Bottom line, this project gave me a proper trim wheel control for MSFS and will make future AVR mcu development far easier.  

## Bill of Materials

|Item|Count|Link|Part Number|
|-|-|-|-|
|Rotary Hall Angle Sensor|1|[Rotary Hall Angle Sensor](https://www.aliexpress.com/item/4000143910873.html)|P3022-V1-CW360|
|Arduino Pro Micro|1|[Arduino Pro Micro](https://www.amazon.ca/ATmega32U4-Replace-ATmega328-Leonardo-Interface/dp/B0FLLNVNFL)|Arduino Pro Micro 5V|
|M3 Bolts & Nuts|1|[Glarks](https://www.amazon.ca/dp/B01J7NM9JA?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)|Glarks 230 Pc M3 Bolts and Nuts|
|White Lithium Grease|1|[White Lithium Grease](https://www.amazon.ca/dp/B004X70LZA?ref=ppx_yo2ov_dt_b_fed_asin_title)|Lucas White Lithium Grease|
|Creality Hi Combo|1|[Creality Hi Combo](https://www.reprapwarehouse.com/)|Creality Hi Combo|
|SWD Breakout Board|1|[Adafruit SWD Cable Breakout Board](https://www.adafruit.com/product/2743)|2743|
|AVR ISP Adapter|1|[Adafruit AVR 6 Pin ISP Adapter](https://www.adafruit.com/product/1465)|1465|
|Female Headers|10|[Sparkfun Female Headers](https://www.sparkfun.com/products/115)|PRT-00115|
|Mini Pushbutton Switch|1|[Sparkfun Mini Pushbutton](https://www.sparkfun.com/products/97?_gl=1*36uoho*_ga*MTc1Mjg5MTM4NC4xNzAxMTA1MDY1*_ga_T369JS7J9N*MTcwNTE4NTg2My4xMS4wLjE3MDUxODU4NjMuNjAuMC4w&_ga=2.58816493.1571879566.1705185864-1752891384.1701105065)|COM-0097|
|Atmel-ICE Debugger|1|[Digikey Atmel-ICE Basic](https://www.digikey.ca/en/products/detail/microchip-technology/ATATMEL-ICE-BASIC/4753381?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Product_Low%20ROAS%20Categories&utm_term=&productid=4753381&utm_content=&utm_id=go_cmp-20291741422_adg-_ad-__dev-c_ext-_prd-4753381_sig-EAIaIQobChMIvM6727jdgwMV7zutBh3bswzIEAQYASABEgI7UPD_BwE&gad_source=1&gclid=EAIaIQobChMIvM6727jdgwMV7zutBh3bswzIEAQYASABEgI7UPD_BwE)|ATATMEL-ICE-BASIC-ND|

## Todo's

1. remove usb serial port so device appears solely as HID-compliant game controller/USB input device
   1. this will require using Atmel-Ice for uploading
2. rename to trim wheel pro
   1. this will require changing boards.txt entries
