# ATmega-16-BOOTLOADER

bootloader designed and developed for ATmega-16 to upload and flash new app code into the flash memory using Python script to communicate with the bootloader.
Note: Used Atmega-16 frequence is 1 MHZ, so i the cpu frq changed , just change what is depended like USART Baudrate value.
This project is divided into three part:
## Application Code
I just wrote a simple UART application code that just transmit two string messages over USART channel.
![1](https://user-images.githubusercontent.com/66730765/105389186-3acaa500-5c20-11eb-9110-2cb2aead450d.PNG)
### USART Configuration:
Baudrate = 4800 ,parity = None ,Stop Bit = One

## Bootloader Code
## Python Script
