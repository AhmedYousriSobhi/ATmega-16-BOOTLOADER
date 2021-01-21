# ATmega-16-BOOTLOADER

bootloader designed and developed for ATmega-16 to upload and flash new app code into the flash memory using Python script to communicate with the bootloader.
Note: Used Atmega-16 frequence is 1 MHZ, so i the cpu frq changed , just change what is depended like USART Baudrate value.
This project is divided into three part:
## Application Code
I just wrote a simple UART application code that just transmit two string messages over USART channel.
#### 
int main(void)
{
    USART_Init(12); // setting baudrate to 4800
    while (1) 
    {
		USART_Transmit_Msg((uint8_t *)"HELLO FROM APPLICATION\n");
		USART_Transmit_Msg((uint8_t *)"YOU HAVE DONE YOUR FIRST BOOTLOADER CODE\n");
    }
}
### USART Configuration:
Baudrate = 4800 ,parity = None ,Stop Bit = One

## Bootloader Code
## Python Script
