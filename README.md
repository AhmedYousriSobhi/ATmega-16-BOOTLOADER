# ATmega-16-BOOTLOADER

#### bootloader designed and developed for ATmega-16 to upload and flash new app code into the flash memory using Python script to communicate with the bootloader.
#### Note: Used Atmega-16 frequence is 1 MHZ, so i the cpu frq changed , just change what is depended like USART Baudrate value.
#### This project is divided into three part:

# I- Application Code
#### I just wrote a simple UART application code that just transmit two string messages over USART channel.
    int main(void)
    {
      USART_Init(12); // setting baudrate to 4800
      while (1) 
      {
		  USART_Transmit_Msg((uint8_t *)"HELLO FROM APPLICATION\n");
		  USART_Transmit_Msg((uint8_t *)"YOU HAVE DONE YOUR FIRST BOOTLOADER CODE\n");
      }
    }
That's to make sure we flashed the app code successfully into flash memory and the app code is running now.

## I.1-  USART Configuration:<br/>
Baudrate = 4800 ,parity = None ,Stop Bit = One

## I.2-  HEX File of APP CODE:
I.2.1- We need to extract the data Hex Bytes from the APP CODE Hex file generated.<br/>
I.2.2- The Generated APP CODE Hex file is located inside the Debug folder.

![2](https://user-images.githubusercontent.com/66730765/105389913-1de2a180-5c21-11eb-9e67-dc6b62e83959.PNG)<br/>

#### I.2.3- The Hex file Openned in Notepad++: 
####  <img align="right" src="https://user-images.githubusercontent.com/66730765/105493251-cf391400-5cc1-11eb-9d4f-701f7083ce6b.png">	
	:100000000C942A000C943F000C943F000C943F0089
	:100010000C943F000C943F000C943F000C943F0064
	:100020000C943F000C943F000C943F000C943F0054
	:100030000C943F000C943F000C943F000C943F0044
	:100040000C943F000C943F000C943F000C943F0034
	:100050000C943F0011241FBECFE5D4E0DEBFCDBF1E
	:1000600010E0A0E6B0E0EEEDF0E002C005900D92E9
	:10007000A23AB107D9F70E9460000C946D000C946D
	:10008000000090BD89B988E18AB986E880BD0895ED
	:100090005D9BFECF8CB908950F931F93CF938C0176
	:1000A000C0E0F801EC0FF11D80818A3021F0CF5FB4
	:1000B0000E944800F6CFCF911F910F910C944800F9
	:1000C0008CE090E00E94410080E690E00E944C00AD
	:0E00D00088E790E00E944C00F7CFF894FFCF35
	:1000DE0048454C4C4F2046524F4D204150504C49B4
	:1000EE00434154494F4E0A00594F552048415645F9
	:1000FE0020444F4E4520594F555220464952535495
	:10010E0020424F4F544C4F4144455220434F44459B
	:02011E000A00D5
	:00000001FF

#### I.2.4- Using C Parsing code Code "HEX-To-Array" the extract the Data Bytes.<br/>
##### Note: The C code github link: https://github.com/AhmedYousriSobhi/Hex-To-array-txt <br/>
#### I.2.5-Take a copy of the hex file and past it inside the same folder as HexToArray C code.
![4](https://user-images.githubusercontent.com/66730765/105391151-7e261300-5c22-11eb-8cc7-8ee8db397352.PNG)<br/>
#### I.2.6- Using CMD, Run the line:   hextoarray.exe UART_APPLICATION.hex
![5](https://user-images.githubusercontent.com/66730765/105391152-7f574000-5c22-11eb-97a9-a473c2b624cc.PNG)<br/>
#### I.2.7- The Output File is named : OutputArray.txt, and looks like:
	{
 	0x0C, 0x94, 0x2A, 0x00, 0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00,
 	0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00,
 	0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00,
 	0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00,
 	0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00, 0x0C, 0x94, 0x3F, 0x00,
 	0x0C, 0x94, 0x3F, 0x00, 0x11, 0x24, 0x1F, 0xBE, 0xCF, 0xE5, 0xD4, 0xE0, 0xDE, 0xBF, 0xCD, 0xBF,
 	0x10, 0xE0, 0xA0, 0xE6, 0xB0, 0xE0, 0xEE, 0xED, 0xF0, 0xE0, 0x02, 0xC0, 0x05, 0x90, 0x0D, 0x92,
 	0xA2, 0x3A, 0xB1, 0x07, 0xD9, 0xF7, 0x0E, 0x94, 0x60, 0x00, 0x0C, 0x94, 0x6D, 0x00, 0x0C, 0x94,
 	0x00, 0x00, 0x90, 0xBD, 0x89, 0xB9, 0x88, 0xE1, 0x8A, 0xB9, 0x86, 0xE8, 0x80, 0xBD, 0x08, 0x95,
 	0x5D, 0x9B, 0xFE, 0xCF, 0x8C, 0xB9, 0x08, 0x95, 0x0F, 0x93, 0x1F, 0x93, 0xCF, 0x93, 0x8C, 0x01,
 	0xC0, 0xE0, 0xF8, 0x01, 0xEC, 0x0F, 0xF1, 0x1D, 0x80, 0x81, 0x8A, 0x30, 0x21, 0xF0, 0xCF, 0x5F,
 	0x0E, 0x94, 0x48, 0x00, 0xF6, 0xCF, 0xCF, 0x91, 0x1F, 0x91, 0x0F, 0x91, 0x0C, 0x94, 0x48, 0x00,
 	0x8C, 0xE0, 0x90, 0xE0, 0x0E, 0x94, 0x41, 0x00, 0x80, 0xE6, 0x90, 0xE0, 0x0E, 0x94, 0x4C, 0x00,
 	0x88, 0xE7, 0x90, 0xE0, 0x0E, 0x94, 0x4C, 0x00, 0xF7, 0xCF, 0xF8, 0x94, 0xFF, 0xCF,
 	0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x20, 0x46, 0x52, 0x4F, 0x4D, 0x20, 0x41, 0x50, 0x50, 0x4C, 0x49,
 	0x43, 0x41, 0x54, 0x49, 0x4F, 0x4E, 0x0A, 0x00, 0x59, 0x4F, 0x55, 0x20, 0x48, 0x41, 0x56, 0x45,
 	0x20, 0x44, 0x4F, 0x4E, 0x45, 0x20, 0x59, 0x4F, 0x55, 0x52, 0x20, 0x46, 0x49, 0x52, 0x53, 0x54,
 	0x20, 0x42, 0x4F, 0x4F, 0x54, 0x4C, 0x4F, 0x41, 0x44, 0x45, 0x52, 0x20, 0x43, 0x4F, 0x44, 0x45,
 	0x0A, 0x00,
 	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
 	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
 	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
 	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
 	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
 	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	};
	#define CODE_SIZE 384
	#define NO_OF_PAGES 3

##### The C parsing code is designed so it takes the HEX file and output the txt file in array hex bytes format, Code size in bytes and number of pages in flash memory. 

# II- Bootloader Code
![8](https://user-images.githubusercontent.com/66730765/105463206-62f5ea80-5c98-11eb-917e-2a82609d416d.PNG)
![9](https://user-images.githubusercontent.com/66730765/105463210-638e8100-5c98-11eb-82fe-266756800d8d.PNG)

# III- Python Script
## • III.1 This Script is used to
##### ‣ 1- Talk to the Bootloader.<br/>
‣ 2- Read Hex Bytes from the OutputArray.txt file - from APP Code Stage - and Transmit those bytes through USART to Boodloader.
### • III.2 LET'S EXPLAIN THE SCRIPT
## ◦ III.2.1  First The imported modules:<br/>
##### ‣ Three Modules we imported, the third one was created and designed as we will need it in a next step, so i'll explain it later when we will need it. 
	import serial
	import serial.tools.list_ports
	from TXT_FILE_HANDLER import *
##### ‣ Modules: "serial" is used to create a serial com port object, and configure its name, baudrate, parity, stop bit ,... etc <br/>
‣ Modules: "serial.tools.list_ports" is used to get all connected com ports on your os device PC/LAPTOP.
## ◦ III.2.2  PORT CONFIGURATION
	#*********PORT CONFIGURATION**************#
	# if this the main py file to run ,
	# so if another program run , it will not run the code inside this if.          
	if __name__ == '__main__':
    	ser = serial.Serial()
    	ports = serial.tools.list_ports.comports()
    	print("PY_DEBUG: LIST OF CONNECTED COM PORTS :")
    	for port, desc, hwid in sorted(ports):
            	print("{}: {} [{}]".format(port, desc, hwid))
    	keyword_com = 'COM'
    	while True:
        	ser.port = input("PY_DEBUG: ENTER COM NUMBER : ")
        	if keyword_com in ser.port :
            	break;
    	ser.baudrate = int(input("PY_DEBUG: ENTER BAUDRATE : "))
    	ser.close()
    	print("PY_DEBUG : SERIAL PORT :\n", ser)
##### ‣ The code lines in the BLUE-BOX is to get all connected com ports and print them, so that when we connect TTL-USB to our PC/LAPTOP, we get the com number.<br/>
##### ‣ Run Time: 
![12](https://user-images.githubusercontent.com/66730765/105466210-963a7880-5c9c-11eb-88ef-58d202f13f63.PNG)
##### ‣ In my case, the TTL-USB is COM4<br/>
![12](https://user-images.githubusercontent.com/66730765/105466316-b833fb00-5c9c-11eb-8613-75c924bc25d9.PNG)
##### ‣ In the GREEN-BOX: we get the com number in the while loop and check for spelling "COM" word-key in the input. So the user should input: COM4 then press enter.<br/>
‣ Next, asking for the Baudrate. The baudrate i use for ATmega-16 is 4800
![13](https://user-images.githubusercontent.com/66730765/105467150-f251cc80-5c9d-11eb-85b4-fa0c9fec7d0c.PNG)
##### ‣ To make no error if we try to open an already openned port, so first thing to do is to close the selected com port using : ser.close()<br/>
## ◦ III.2.2- Display MAIN MENUE Get Command from User:<br/>
##### ‣ CODE: 
![15](https://user-images.githubusercontent.com/66730765/105471060-02b87600-5ca3-11eb-9a1e-a9d0bd850c5e.PNG)
##### ‣ Run Time:
![14](https://user-images.githubusercontent.com/66730765/105471067-03510c80-5ca3-11eb-914c-b78b8763dac6.PNG)
##### ‣ The input command is checked in if-elif statements, so according to the input CMD, it's calling specific function.<br/>
‣ let's first explain CONFIG_COM command:<br/>
### ◦ Command : CONFIG_COM<br/>
##### ‣ Code:
![16](https://user-images.githubusercontent.com/66730765/105472343-7f981f80-5ca4-11eb-99b9-fc8bc75023d0.PNG) 
##### ‣ Run time:
![17](https://user-images.githubusercontent.com/66730765/105472524-b9692600-5ca4-11eb-9d1a-eb8c9410a326.PNG)
### ◦ Command : RETURN <br/> 
##### ‣ Just breaks the while loop and get out of the comConfig function and returns to MAIN-MENUE
![18](https://user-images.githubusercontent.com/66730765/105473066-588e1d80-5ca5-11eb-9f5b-3ed6904e059a.PNG)
### ◦ Command : OPEN_PORT <br/> 
#####          ‣ Firstly, open the selected com port.<br/>
#####          ‣ Secondly, print the status of the com port: open/close using ser.is_open that return True if com port is opened successfully.<br/>
#####          ‣ Thirdly, Call the function comBoard(), That jumps to comBoard Menue.
![19](https://user-images.githubusercontent.com/66730765/105474483-eddde180-5ca6-11eb-9cdc-ebb55183c204.PNG)<br/>
##### ‣ if you notice, the first then to do when jumping to com Board, is to reset the AVR MCU, as explained in BOOTLOADER SECTION above, that the bootloader sends some starting messages, and ofcourse these messages are sent directly as the AVR is powered and we missed these messages while starting python script. That's why we need to reset the MCU after opening the COM port.
![20](https://user-images.githubusercontent.com/66730765/105475653-4661ae80-5ca8-11eb-971c-a1b27ec4f5bd.PNG)<br/>
##### ‣ As you can see, there are two debug-texter here: <br/>
######              ∙ PY_DEBUG : is from Python script.<br/>
######              ∙ BLD_DEBUG : is from ATmega-16 BOOTLOADER.
![20](https://user-images.githubusercontent.com/66730765/105475966-b8d28e80-5ca8-11eb-8079-5cb59e034458.PNG)<br/>
##### ‣ Now our Bootloader is waiting for new command to receiver from USART.<br/>
##### ‣ The " b' " character before the BLD_DEBUG message means that the printed message was recieved in bytes in python.<br/> 
##### ‣ In Python we have some predefined commands, just choose what to do, and if the user wants to write his own command manually, there is a command also for that.<br/>
## ◦ III.2.3 Python Predefined command :
##### ‣ BLD_LIST : call BLD_CMD_LIST() Function that send char 'A' to Bootloader and receive the response which is the Bootloader command list we defined in Bootloader code.
![21](https://user-images.githubusercontent.com/66730765/105487130-49fd3180-5cb8-11eb-8731-5347098d07f9.PNG)<br/>
##### ‣ BLD_LIST : Run Time.
![22](https://user-images.githubusercontent.com/66730765/105487504-e6273880-5cb8-11eb-9a97-387df0eaa628.PNG)
###### The response is a list of commands defined in Bootloader.

