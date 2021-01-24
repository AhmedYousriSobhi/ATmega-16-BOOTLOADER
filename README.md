# ATmega-16-BOOTLOADER

#### bootloader designed and developed for ATmega-16 to upload and flash new app code into the flash memory using Python script to communicate with the bootloader.
#### Notes: <br/>
 - Used Atmega-16 frequence is 1 MHZ, so if you want to change the cpu frq - like add crystal-, just change what is depended like USART Baudrate value.<br/>
 - The used program for AVR is Atmel studio, you can use whatever you like as long as it compiles your project and generate the hex file code.<br/>
 - Hex file uploading to AVR through AVRDUDESS.<br/>
#### I will try to explain as much as i can, so you could design yout own code, and learn something.<br/>
#### This project is divided into three part:

# I- Application Code Section
<details>
<summary>expand/compress</summary>

#### I just wrote a simple UART application code that just transmit two string messages over USART channel.<br/>
That's to make sure we flashed the app code successfully into flash memory and the app code is running now and printing these messages.
### Hello from App: --: CODE.    
    int main(void)
    {
      USART_Init(12); // setting baudrate to 4800
      while (1) 
      {
		  USART_Transmit_Msg((uint8_t *)"HELLO FROM APPLICATION\n");
		  USART_Transmit_Msg((uint8_t *)"YOU HAVE DONE YOUR FIRST BOOTLOADER CODE\n");
      }
    }
#### I assummed that you know to use USART peripheral in AVR. Even if you are not, you can simply use the functions definition that are written inside the datasheet. you can find USART_Init(), USART_Transmit() and USART_Recieve() funciton, that's what you will need for this project. 
#### In addition to a simply USART_Tranmsit_mesg function to transmit a string, like the code below, the function is just taking a uint8_t pointer that carry the char of the string message and increment that pointer until '\n' char, or you could simply use '\0' as every string is ended with '\0'. Then transmit one by one to USART_transmit() function.
	void USART_Transmit_Msg(uint8_t *word )
	{
		uint8_t index = 0;
		while(word[index] != '\n')
		{
			USART_Transmit(word[index++]);
		}
		USART_Transmit('\n');	
	}

## I.1-  USART Configuration:<br/>
Baudrate = 4800 ,parity = None ,Stop Bit = One

## I.2-  HEX File of APP CODE:	
I.2.1- We need to extract the data Hex Bytes from the APP CODE Hex file generated when we make build for the project.<br/>
I.2.2- The Generated APP CODE Hex file is located inside the Debug folder, like the image below.

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

#### I.2.4- Using C Parsing code "HEX-To-Array" to extract the Data Bytes.<br/>
##### Note: 
 - The [C code github link](https://github.com/AhmedYousriSobhi/Hex-To-array-txt)  <br/>
 - First you need to understand [Intel Hex Format](https://en.wikipedia.org/wiki/Intel_HEX)
 - This code is simple just open the hex file: 
   - Reads every line byte by byte.
   - Check the number of data bytes in this line and reads these data.
   - Store these data in the output txt file which i named OutputArray.txt and fill the reset of bytes by 0xFF until the code size is equivlent to const integer * PAGE_SIZE in ATmega-16. The Page size in AVR is 128 bytes = 64 word.
   - The OutputArray.txt file contains the Data bytes of the Application code, Code size, and number of pages needed for this code in the flash memory.
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
### One Last step here is to take a copy of OutputArray.txt file as we'll need this file in the coming Python Stage.
### So right now let's jump to the Bootloader Section and contiune this journey.

</details>

# II- Bootloader Code Section
<details>
<summary>expand/compress</summary>
	
![8](https://user-images.githubusercontent.com/66730765/105463206-62f5ea80-5c98-11eb-917e-2a82609d416d.PNG)
![9](https://user-images.githubusercontent.com/66730765/105463210-638e8100-5c98-11eb-82fe-266756800d8d.PNG)

</details>

# III- Python Script Section
<details>
<summary>expand/compress</summary>
	
### The Idea here, Insted of using a Terminal - whatever was the terminal: Atmel studio terminal, Arduino IDE,..etc - to communicate with the bootloader through COM PORT (USART), we will write a python script for a program that a user can use even if he/she does not know the bootloader commands to talk to it directly.
### So we'll try to make this program as friendly as possible for the user.
### Another thing we may need is to send the new hex Application Code to bootloader through USART, so typing byte by byte for through Serial Terminal will not be humanly at all. That's why it would be best to make a program takes out hex code and send those data bytes in timeless process.
### Other solution but not efficient is that we take the array hex bytes we got from OutputArray.txt file and place it in the Bootloader code before uploading and Flashing the bootloader into out AVR. But this way means every time we want to upload new app code to bootloader, we have to flash the code of the bootloader. This is worthless and meaningless as what is the bootloader benefits now.
	
## III.1 This Script is used to :
 - 1- Talk to the Bootloader.<br/>
 - 2- Read Hex Bytes from the OutputArray.txt file - from APP Code Section - and Transmit those bytes through USART to Boodloader.

### Now LET'S EXPLAIN THIS SCRIPT in details:	
## III.2  First The imported modules:<br/>	
#### Three Modules were imported, the third one was created and designed as we will need it in a next step, so i'll explain it later when we will need it. 
	import serial
	import serial.tools.list_ports
	from TXT_FILE_HANDLER import *
 - Modules: "serial" is used to create a serial COM PORT object, and configure COM PORT name, baudrate, parity, stop bit ,... etc <br/>
 - Modules: "serial.tools.list_ports" is used to get all connected com ports on your os device PC/LAPTOP.
### So let's see how to create an object for COM PORT.	
## ◦ III.3  PORT CONFIGURATION	
##### ‣ Port Configuration: --: Implementation.	
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
#### Let's take it easy and split these code lines into pieces blocks of code.
 - In this block, used to get all connected com ports and print them, so that when we connect TTL-USB to our PC/LAPTOP, we know the com number.
 - Instead of checking through windows manger for COM PORT connected (in case you are using Windows).
####
	ports = serial.tools.list_ports.comports()
    	print("PY_DEBUG: LIST OF CONNECTED COM PORTS :")
    	for port, desc, hwid in sorted(ports):
            	print("{}: {} [{}]".format(port, desc, hwid))
#### Let's see the run time of these codes:		
##### ‣ Port Configuration: --: Run Time. 
![12](https://user-images.githubusercontent.com/66730765/105466210-963a7880-5c9c-11eb-88ef-58d202f13f63.PNG)
##### ‣ In my case, the TTL-USB is COM4<br/>
![12](https://user-images.githubusercontent.com/66730765/105466316-b833fb00-5c9c-11eb-8613-75c924bc25d9.PNG)
 - From these Code block below we want the user to input the COM PORT number.
 - Using while loop to check for spelling "COM" word-key in the input. So the user should input: COM4 then press enter.<br/>
####
	keyword_com = 'COM'
    	while True:
        	ser.port = input("PY_DEBUG: ENTER COM NUMBER : ")
        	if keyword_com in ser.port :
            	break;
‣ Next, asking for the Baudrate. The baudrate i use for ATmega-16 is 4800 with intenal 1 MHZ CPU frq.
![25](https://user-images.githubusercontent.com/66730765/105495480-e6c5cc00-5cc4-11eb-81f9-d580ac4c11e2.png)
##### ‣ In case, we try to open an already openned port, so to make no error, The first thing to do is to close the selected com port using : ser.close()<br/>
## ◦ III.4- Display MAIN MENUE Get Command from User:<br/>
#### <img align="right" src="https://user-images.githubusercontent.com/66730765/105471067-03510c80-5ca3-11eb-914c-b78b8763dac6.PNG">
##### 
    #Get Command From User.
    cmd = '0'
    while(1):
        print(50*'-','\n\t\tM A I N  M E N U E\n')
        cmd= input("\nPY_DEBUG: COMMAND LIST:\
                    \n\tOPEN_PORT : TO OPEN COM PORT SELECTED.\
                    \n\tCLOSE_PORT : TO CLOSE COM PORT.\
                    \n\tCONFIG_COM : TO CHANGE COM PORT.\
                    \n\nYOUR COMMAND IS : ")
        if cmd == "OPEN_PORT" :
            	ser.open()
            	print("PY_DEBUG: COM PORT IS OPENED? ", ser.is_open)
            	comBoard()
        elif cmd == "CLOSE_PORT":
            	ser.close()
            	print("PY_DEBUG: COM PORT IS CLOSED? ", not ser.is_open)
        elif cmd == "CONFIG_COM":
            	print("PY_DEBUG: ENTERING CONFIGURATION COM BOARD.")
            	comConfig()
        else:
            	print("PY_DEBUG: UNDEFINED COMMAND.")


##### ‣ The input command is checked in if-elif statements, so according to the input CMD, it's calling specific function.<br/>

### ◦ let's first explain CONFIG_COM command:
#### <img align="right" src="https://user-images.githubusercontent.com/66730765/105472524-b9692600-5ca4-11eb-9d1a-eb8c9410a326.PNG">
## ∙ Command : CONFIG_COM<br/>

 - From its name, it 's used to configure the com port like changing com port number and changing baudrate. 
 - You can add more features like changing parity mode, stop bits number and another properites of USART Protocol.

##### 
	#*******COM PORT FUNCTIONS********#        
	def comConfig():
    	print(50*'-',"\n\t",ser.port, "C O N F I G  B O A R D\n")
    	while True:
        	cmd= input("\nPY_DEBUG: COMMAND LIST:\
                    	\n\tCHANGE_COM : TO CHANGE COM PORT.\
                    	\n\tCHANGE_BAUD : TO CHANGE BAUDRATE.\
                    	\n\tRETURN : TO RETURN TO MAIN MENUE.\
                    	\n\nYOUR COMMAND IS : ")
        	if cmd == "CHANGE_COM":
            		ser.port = input("PY_DEBUG: ENTER COM NUMBER : ")
        	elif cmd == "CHANGE_BAUD":
            		ser.baudrate = int(input("PY_DEBUG: ENTER BAUDRATE : "))
        	elif cmd == "RETURN":
            		break;
        	else:
            		print("PY_DEBUG: UNDEFINED COMMAND!!")

### ◦ Command : CHANGE_COM <br/>
 - To change the com port, as an input from the user.
####
	elif cmd == "CHANGE_COM":
		ser.port = input("PY_DEBUG: ENTER COM NUMBER : ")
### ◦ Command : CHANGE_BAUD <br/>
 - To change the Baudrate of the com port, as an input from the user.
####
	elif cmd == "CHANGE_BAUD":
		ser.baudrate = int(input("PY_DEBUG: ENTER BAUDRATE : "))
### ◦ Command : RETURN <br/> 
 - Just breaks the while loop and get out of the comConfig function and returns to MAIN-MENUE
####
	elif cmd == "RETURN":
        		break;

### ◦ The Second command to explain is Open_port.
## ∙ Command : OPEN_PORT 
#### <img align="right" src="https://user-images.githubusercontent.com/66730765/105474483-eddde180-5ca6-11eb-9cdc-ebb55183c204.PNG">
##### ‣ What it realy do is that :
 - Firstly, open the selected com port.<br/>
 - Secondly, print the status of the com port: open/close using ser.is_open that return True if com port is opened successfully.<br/>
 - Thirdly, Call the function comBoard(), That jumps to comBoard Menue.
####
	if cmd == "OPEN_PORT" :
        	ser.open()
        	print("PY_DEBUG: COM PORT IS OPENED? ", ser.is_open)
        	comBoard()
#### <img align="right" src="https://user-images.githubusercontent.com/66730765/105475653-4661ae80-5ca8-11eb-971c-a1b27ec4f5bd.PNG">
####
##### ‣ if you notice, the first then to do when jumping to com Board, is to reset the AVR MCU, as explained in BOOTLOADER SECTION above, that the bootloader sends some starting messages, and ofcourse these messages are sent directly as the AVR is powered and we missed these messages while starting python script. That's why we need to reset the MCU after opening the COM port.
##### ‣ Let's Press the push button that connected to AVR RESET pin:

#### <img align="right" src="https://user-images.githubusercontent.com/66730765/105475966-b8d28e80-5ca8-11eb-8079-5cb59e034458.PNG">
##### ‣ As you can see, there are two debug-texter here: <br/>
∙ PY_DEBUG : is from Python script.<br/>
∙ BLD_DEBUG : is from ATmega-16 BOOTLOADER.

##### ‣ Now our Bootloader is waiting for new command to receiver from USART.<br/>
##### ‣ NOTE: The  b'  character before the BLD_DEBUG message means that the printed message was recieved in bytes in python.<br/> 
##### ‣ Now we jumped to Com port Serial Board, where our python debuger shows us some command to use.
##### ‣ In our Python script, we have some predefined commands, just choose what to do. And if the user wants to write his own command manually, there is a command also for that.<br/>
#### Let's first see its code implementation.
### COM BOARD implementation:
	def comBoard():
    		print(50*'-',"\n\t",ser.port, "S E R I A L  B O A R D\n")
    		print("PY_DEBUG: RESET THE MCU")
    		read_string()
   		while True:        
        	    	cmdB = input("\nPY_DEBUG: COMMAND LIST:\
                     		\n\tBLD_LIST : TO SEE BLD LIST COMMAND.\
                     		\n\tBLD_FLASH : TO FLASH APP CODE FROM BLD COMMAND.\
                     		\n\tBLD_UPLOAD : TO UPLOAD NEW APP CODE BYTES TO BLD.\
                     		\n\tCMD : TO SEND MANUAL COMMAND.\
                     		\n\tRETURN : TO RETURN TO MAIN MENUE.\
                     		\n\nYOUR COMMAND IS: ")
        		if cmdB == "BLD_LIST":
            		BLD_CMD_LIST()
        		elif cmdB == "BLD_FLASH":
            		BLD_CMD_FLASH()
        		elif cmdB == "BLD_UPLOAD":
            		BLD_CMD_UPLOAD()
        		elif cmd == "CMD":
            		co = input("ENTER COMMAND MANUALLY: ")
            		ser.write(bytearray.fromhex(co))
            		read_string()    
        		elif cmdB == "RETURN":
            			break
        		else:
            			print("PY_DEBUG: UNDEFINED COMMAND.")
## ◦ III.5 Predefined command : BOOTLOADER FUNCTIONS
#### <img align="right" src="https://user-images.githubusercontent.com/66730765/105628713-36cc9c00-5e47-11eb-883b-f626c82cc230.png">
### ◦ Command : BLD_LIST  
 - Calls BLD_CMD_LIST() Function that send char 'A' to Bootloader 
 - Receive the response which is the Bootloader command list we defined in Bootloader code.
#### 
	def BLD_CMD_LIST():
    		print("PY_DEBUG: BLD COMMANDS LIST CMD IS SENT")
    		ser.write('A'.encode('ascii'))
    		read_string()


###### The response -In the Box- is a list of commands defined in Bootloader.

### ◦ Command : CMD 
#### <img align="right" src="https://user-images.githubusercontent.com/66730765/105628785-a9d61280-5e47-11eb-9a29-d490167a39a1.png"> 
 - Used to write the hex byte manually to transmit it Bootloader through USART.
####
	elif cmd == "CMD":
            co = input("ENTER COMMAND MANUALLY: ")
            ser.write(bytearray.fromhex(co))
            read_string()

### ◦ Command : RETURN
 - Just breaks the while loop and return the MAIN MENUE.
####
	elif cmdB == "RETURN":
            break
### ◦ Command : BLD_UPLOAD
##### <img align="right" src="https://user-images.githubusercontent.com/66730765/105629035-5fee2c00-5e49-11eb-9cfb-4816a3b73578.png">
#### 
- Calls BLD_CMD_UPLOAD() Function, that's used to:<br/>
  - 1- Send 'U' byte to Bootloader so that the Bootloader gets ready to receive new HEX Bytes for APP CODE.
  - 2- Our Python script starts reading the .txt file we created above in the Application Code Section, so we have to copy the outputArray.txt file and paste it in the Python script folder.
  - 3- Parse the .txt file and collect the hex bytes in a list.
  - Note: From here we'll need to explain the thrird module we used in the code >> from TXT_FILE_HANDLER import *
  - 4- Then, Transmit App code list through USART to the Bootloader in the AVR.
####
	def BLD_CMD_UPLOAD():
    		print("PY_DEBUG: BLD UPLOAD NEW COMMAND IS SENT")
    		ser.write('U'.encode('ascii'))
    		read_string()
    		i = 0
    		app_code = TXT_FILE_READ()
    		BytesInPage = 128
    		CODE_SIZE = len(app_code)
    		NumOfPage = CODE_SIZE // BytesInPage
    		print("PY_DEBUG: CODE SIZE = ",CODE_SIZE," , Num of Page = ", NumOfPage)
    		ser.write(str(NumOfPage).encode('ascii'))
    		while i<CODE_SIZE:
        		ser.write(app_code[i])
        		print(i)
        		i=i+1
    		read_string()
#### So when we input the .txt file name, python script will read it and send bytes to AVR automatically. 
#### Before explaining what this thrid module we imported is used for, Python code is waiting for the user to enter the .txt file name, which is OutputArray.txt , so let's ENTER IT!!.

####
 - Our Python debugger sends char 'U' to Bootloader, and waits for its response.
 - Bootloader replys back with the cmd it has received, sending message that it received an upload command and sends its ack char 'A'.
 - Now Python debugger waits for the user to enter the .txt file name.
 - After entering OutputArray.txt, it jumped to the TXT_FILE_READ() function which return the list contains APP Code.
 - Calculate the CODE SIZE and NUMBER OF PAGES, then printing these information.
 - First it send the number of pages of the upcoming APP CODE to Bootloader.
 - Then Starting sending the APP CODE List Byte by Byte, and print the index number of byte it sent - This is just for debugging, so you can comment this line - .
 - After Finishing sending all the bytes, it waits for Bootloader to send back acknowlege that it received successfully.
### Note:
 - You would ask why we calculate the code size and number of pages again?
   - That's because i simply in the parsing process done by python script, want to make easy in parsing and simply read the data bytes only.
 - You would ask again, why we don't let python parse the .hex file instead of .txt file?
   - The answer for that as i said upove in Application code section is that: if the user wants to upload its bootloader code with an array of APP Code embedded inside it, but i said it would does not have any meaning for the bootloader conept, as now you will simply just upload a code in different flash memory address and write another code in the flash memory and run it.
 - This "Squeezed text (92 lines)" is just because there is a print for the list as i was testing the code and want to know how the list looks like, you can simply comment this print line inside the "TXT_FILE_HANDLER.py". 
   
#### <img align="left" width="450" height="300" src="https://user-images.githubusercontent.com/66730765/105630533-85cbfe80-5e52-11eb-8ae5-6dc5d9b07470.png">

#### <img align="right" width="460" height="300" src="https://user-images.githubusercontent.com/66730765/105630650-0a1e8180-5e53-11eb-982c-6120bdbb7c91.png"><br><br>

### ◦ Command : BLD_FLASH
#### <img align="right" src="https://user-images.githubusercontent.com/66730765/105632434-bbc1b080-5e5b-11eb-878b-d91f05219079.png">
####
 - Now the last thing to do is to command the Bootloader to flash this APP CODE it's just received.
 - Bootloader sends message that it start flashing the new APP CODE into flash memory.
 - From our code we programmed the bootloader code to jump to address 0 asm"jmp0" to run the Application Code.
 - So now we see the messages we made in the Application code "HELLO FROM APPLICATION", This means our uploading and flashing have WORKED !!!!.
 - From this stage our Pyhton Script becomes a Serial Monitor to read if any thing i sending from the application code in our ATmega-16.
#### 
    def BLD_CMD_FLASH():
    	print("PY_DEBUG: BLD FLASH APP CODE CMD IS SENT")
    	ser.write('F'.encode('ascii'))
    	read_string()
    	print("PY_DEBUG: BOOTLOADER IS OUT OF COMMUNICATION")
    	read_string()

## ◦ III.6 Predefined command : USART FUNCTIONS
### To finish up this section, we have not take a look about the USART function we defined in the python script as we were using them in our other function.
 - waitForDataRecieve :
 	- Used for waiting for any bytes coming to our com port.
	- It's just a loop that wait untile something is received.
	- Input : none.
	- Output : none.
	- So it does not reads the coming bytes.
###
	def waitForDataRecieve():
    		print("PY_DEBUG: WAITING TO RECIEVE DATA")
    		while ser.in_waiting == 0:
       		pass
 - read_byte :
 	- Used to read a bytes after waiting for any upcoming bytes.
###
	def read_byte():
    		waitForDataRecieve()
    		print(ser.read())
- read_string :
	- Used to read a string, which means reading bytes until it found a null character '\0'
###
	def read_string():
    		waitForDataRecieve()
    		while ser.in_waiting !=0:
        		print(ser.read_until())
### Until now i hope you don't find these funciton difficult, so let's jump to our last thing to explain here, the text file handler module we created.
## ◦ III.7 Predefined Module : Txt file Handler "TXT_FILE_HANDLER.py"
 - 1- Reads the file name from the user. the file name must have a ".txt" keyword in it to make sure the user entered the correct file format.
 - 2- Opens our .txt file.
 - 3- Creating an empty list to store the upcoming bytes which we are going to read.
 - 4- Looping while reading a byte each time and check for the zero number in hex "0x--".
 - 5- If the reading bytes is 0 then skip the 'x' and reads the rest two numbers and store then in the list.
 - 6- Repeat this process untile we dound ';' or '}' .
 - 7- Converting the numbers we read into hex format using function: bytearray.fromhex(list[index]).
 - 8- Printing the new array for testing, so you can comment this line.
 - 9- returning the list to the caller variable.
 
 ####
    def TXT_FILE_READ():
    	while True:
        	file_name = input("PY_DEBUG: ENTER TXT FILE NAME LIKE 'text.txt' : ")
        	if ".txt" in file_name:
            	break
    	text = open(file_name)
    	# Creating void array:
    	app_code_list=[]
    	index = 1
    	counter = 0
    	while True:
        	temp = text.read(index)
        	if( temp.isnumeric()): #to collect hex
            	text.read(index)
            	temp=text.read(index)
            	temp+=text.read(index)
            	app_code_list.append(temp)
        	elif (temp == ';'):
            	break
    	#print(app_code)
    	for i in range(0,len(app_code_list)):
        	app_code_list[i] = (bytearray.fromhex(app_code_list[i]))
    
    	print(app_code_list)   
    	#print(type(app_code_list[0]))
    	#CODE_SIZE = len(app_code_list)
    	#print("CODE SIZE = ",CODE_SIZE," , Num of Page = ", NumOfPage)
    	print("PY_DEBUG: CLOSING FILE.")
    	#print(text.close())
    	return app_code_list


 
</details>
