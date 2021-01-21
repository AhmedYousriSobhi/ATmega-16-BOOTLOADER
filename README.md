# ATmega-16-BOOTLOADER

#### bootloader designed and developed for ATmega-16 to upload and flash new app code into the flash memory using Python script to communicate with the bootloader.
#### Note: Used Atmega-16 frequence is 1 MHZ, so i the cpu frq changed , just change what is depended like USART Baudrate value.
#### This project is divided into three part:

## Application Code
#### I just wrote a simple UART application code that just transmit two string messages over USART channel.
![1](https://user-images.githubusercontent.com/66730765/105389186-3acaa500-5c20-11eb-9110-2cb2aead450d.PNG)
#### That's to make sure we flashed the app code successfully into flash memory and the app code is running now.

### USART Configuration:
Baudrate = 4800 ,parity = None ,Stop Bit = One

### HEX File of APP CODE:
#### 1- We need to extracte the data Hex Bytes from the APP CODE Hex file generated.
#### 2- The Generated APP CODE Hex file is located inside the Debug folder.
![2](https://user-images.githubusercontent.com/66730765/105389913-1de2a180-5c21-11eb-9e67-dc6b62e83959.PNG)

## Bootloader Code

## Python Script
