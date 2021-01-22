# ATmega-16-BOOTLOADER

#### bootloader designed and developed for ATmega-16 to upload and flash new app code into the flash memory using Python script to communicate with the bootloader.
#### Note: Used Atmega-16 frequence is 1 MHZ, so i the cpu frq changed , just change what is depended like USART Baudrate value.
#### This project is divided into three part:

## I- Application Code
#### I just wrote a simple UART application code that just transmit two string messages over USART channel.
![1](https://user-images.githubusercontent.com/66730765/105389186-3acaa500-5c20-11eb-9110-2cb2aead450d.PNG)
#### That's to make sure we flashed the app code successfully into flash memory and the app code is running now.

### USART Configuration:
Baudrate = 4800 ,parity = None ,Stop Bit = One

### HEX File of APP CODE:
#### 1- We need to extract the data Hex Bytes from the APP CODE Hex file generated.
#### 2- The Generated APP CODE Hex file is located inside the Debug folder.
![2](https://user-images.githubusercontent.com/66730765/105389913-1de2a180-5c21-11eb-9e67-dc6b62e83959.PNG)
#### 3- The Hex file Openned in Notepad++:
![3](https://user-images.githubusercontent.com/66730765/105390530-d01a6900-5c21-11eb-9639-eaee9fed3f2d.PNG)
#### 4- Using C Parsing code Code "HEX-To-Array" the extract the Data Bytes.
##### Note: The C code github link: https://github.com/AhmedYousriSobhi/Hex-To-array-txt
#### 5-Take a copy of the hex file and past it inside the same folder as HexToArray C code.
![4](https://user-images.githubusercontent.com/66730765/105391151-7e261300-5c22-11eb-8cc7-8ee8db397352.PNG)
#### 6- Using CMD, Run the line:   hextoarray.exe UART_APPLICATION.hex
![5](https://user-images.githubusercontent.com/66730765/105391152-7f574000-5c22-11eb-97a9-a473c2b624cc.PNG)
#### 7- The Output File is named : OutputArray.txt, and looks like:
![7](https://user-images.githubusercontent.com/66730765/105391691-0c9a9480-5c23-11eb-8a04-d221ee01afa5.PNG)
##### The C parsing code is designed so it takes the HEX file and output the txt file in array hex bytes format, Code size in bytes and number of pages in flash memory. 

## II- Bootloader Code
![8](https://user-images.githubusercontent.com/66730765/105463206-62f5ea80-5c98-11eb-917e-2a82609d416d.PNG)
![9](https://user-images.githubusercontent.com/66730765/105463210-638e8100-5c98-11eb-82fe-266756800d8d.PNG)

## III- Python Script
#### This Script is used 
#####                  1- To talk to the Bootloader.
#####                  2- To read Hex Bytes from the OutputArray.txt file - from APP Code Stage - and Transmit those bytes through USART to Boodloader.
### LET'S EXPLAIN THE SCRIPT
#### 1- first we import the modules:
![10](https://user-images.githubusercontent.com/66730765/105463213-64271780-5c98-11eb-9849-af1733e98944.PNG)
##### Modules: "serial" is used to create a serial com port object, and configure its name, baudrate, parity, stop bit ,... etc 
##### Modules: "serial.tools.list_ports" is used to get all connected com ports on your os device PC/LAPTOP.
![11](https://user-images.githubusercontent.com/66730765/105465714-f381fa00-5c9b-11eb-97f6-462e3a0f504d.PNG)
##### the code lines in the BLUE-BOX is to get all connected com ports and print them, so that when we connect TTL-USB to our PC/LAPTOP, we get the com number.
##### Run Time: 
![12](https://user-images.githubusercontent.com/66730765/105466210-963a7880-5c9c-11eb-88ef-58d202f13f63.PNG)
##### In my case, the TTL-USB is COM4
![12](https://user-images.githubusercontent.com/66730765/105466316-b833fb00-5c9c-11eb-8613-75c924bc25d9.PNG)
##### In the GREEN-BOX: we get the com number in the while loop and check for spelling "COM" word-key in the input.
##### So the user should input: COM4 then press enter.
##### Next, asking for the Baudrate. The baudrate i use for ATmega-16 is 4800
![13](https://user-images.githubusercontent.com/66730765/105467150-f251cc80-5c9d-11eb-85b4-fa0c9fec7d0c.PNG)
##### To make no error if we try to open an already openned port, so first thing to do is to close the selected com port using : ser.close()
