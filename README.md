# ATmega-16-BOOTLOADER

#### bootloader designed and developed for ATmega-16 to upload and flash new app code into the flash memory using Python script to communicate with the bootloader.
#### Note: Used Atmega-16 frequence is 1 MHZ, so i the cpu frq changed , just change what is depended like USART Baudrate value.
#### This project is divided into three part:

# I- Application Code
#### I just wrote a simple UART application code that just transmit two string messages over USART channel.
![1](https://user-images.githubusercontent.com/66730765/105389186-3acaa500-5c20-11eb-9110-2cb2aead450d.PNG)
#### That's to make sure we flashed the app code successfully into flash memory and the app code is running now.

## I.1 USART Configuration:
Baudrate = 4800 ,parity = None ,Stop Bit = One

## I.2 HEX File of APP CODE:
I.2.1- We need to extract the data Hex Bytes from the APP CODE Hex file generated.
I.2.2- The Generated APP CODE Hex file is located inside the Debug folder.
![2](https://user-images.githubusercontent.com/66730765/105389913-1de2a180-5c21-11eb-9e67-dc6b62e83959.PNG)
#### I.2.3- The Hex file Openned in Notepad++:
![3](https://user-images.githubusercontent.com/66730765/105390530-d01a6900-5c21-11eb-9639-eaee9fed3f2d.PNG)
#### I.2.4- Using C Parsing code Code "HEX-To-Array" the extract the Data Bytes.
##### Note: The C code github link: https://github.com/AhmedYousriSobhi/Hex-To-array-txt
#### I.2.5-Take a copy of the hex file and past it inside the same folder as HexToArray C code.
![4](https://user-images.githubusercontent.com/66730765/105391151-7e261300-5c22-11eb-8cc7-8ee8db397352.PNG)
#### I.2.6- Using CMD, Run the line:   hextoarray.exe UART_APPLICATION.hex
![5](https://user-images.githubusercontent.com/66730765/105391152-7f574000-5c22-11eb-97a9-a473c2b624cc.PNG)
#### I.2.7- The Output File is named : OutputArray.txt, and looks like:
![7](https://user-images.githubusercontent.com/66730765/105391691-0c9a9480-5c23-11eb-8a04-d221ee01afa5.PNG)
##### The C parsing code is designed so it takes the HEX file and output the txt file in array hex bytes format, Code size in bytes and number of pages in flash memory. 

# II- Bootloader Code
![8](https://user-images.githubusercontent.com/66730765/105463206-62f5ea80-5c98-11eb-917e-2a82609d416d.PNG)
![9](https://user-images.githubusercontent.com/66730765/105463210-638e8100-5c98-11eb-82fe-266756800d8d.PNG)

# III- Python Script
## • III.1 This Script is used to
#####                  ‣ 1- Talk to the Bootloader.
#####                  ‣ 2- Read Hex Bytes from the OutputArray.txt file - from APP Code Stage - and Transmit those bytes through USART to Boodloader.
## • III.2 LET'S EXPLAIN THE SCRIPT
#### ◦ III.2.1  First The imported modules:
##### ‣ Three Modules we imported, the third one was created and designed as we will need it in a next step, so i'll explain it later when we will need it.
![10](https://user-images.githubusercontent.com/66730765/105463213-64271780-5c98-11eb-9849-af1733e98944.PNG)
##### ‣ Modules: "serial" is used to create a serial com port object, and configure its name, baudrate, parity, stop bit ,... etc 
##### ‣ Modules: "serial.tools.list_ports" is used to get all connected com ports on your os device PC/LAPTOP.
![11](https://user-images.githubusercontent.com/66730765/105465714-f381fa00-5c9b-11eb-97f6-462e3a0f504d.PNG)
##### ‣ The code lines in the BLUE-BOX is to get all connected com ports and print them, so that when we connect TTL-USB to our PC/LAPTOP, we get the com number.
##### ‣ Run Time: 
![12](https://user-images.githubusercontent.com/66730765/105466210-963a7880-5c9c-11eb-88ef-58d202f13f63.PNG)
##### ‣ In my case, the TTL-USB is COM4
![12](https://user-images.githubusercontent.com/66730765/105466316-b833fb00-5c9c-11eb-8613-75c924bc25d9.PNG)
##### ‣ In the GREEN-BOX: we get the com number in the while loop and check for spelling "COM" word-key in the input. So the user should input: COM4 then press enter.
##### ‣ Next, asking for the Baudrate. The baudrate i use for ATmega-16 is 4800
![13](https://user-images.githubusercontent.com/66730765/105467150-f251cc80-5c9d-11eb-85b4-fa0c9fec7d0c.PNG)
##### ‣ To make no error if we try to open an already openned port, so first thing to do is to close the selected com port using : ser.close()
#### ◦ III.2.2- Display MAIN MENUE Get Command from User:
##### ‣ CODE: 
![15](https://user-images.githubusercontent.com/66730765/105471060-02b87600-5ca3-11eb-9a1e-a9d0bd850c5e.PNG)
##### ‣ Run Time:
![14](https://user-images.githubusercontent.com/66730765/105471067-03510c80-5ca3-11eb-914c-b78b8763dac6.PNG)
##### ‣ The input command is checked in if-elif statements, so according to the input CMD, it's calling specific function.
##### ‣ let's first explain CONFIG_COM command:
#### ◦ Command : CONFIG_COM
##### ‣ Code:
![16](https://user-images.githubusercontent.com/66730765/105472343-7f981f80-5ca4-11eb-99b9-fc8bc75023d0.PNG) 
##### ‣ Run time:
![17](https://user-images.githubusercontent.com/66730765/105472524-b9692600-5ca4-11eb-9d1a-eb8c9410a326.PNG)
#### ◦ Command : RETURN 
##### ‣ Just breaks the while loop and get out of the comConfig function and returns to MAIN-MENUE
![18](https://user-images.githubusercontent.com/66730765/105473066-588e1d80-5ca5-11eb-9f5b-3ed6904e059a.PNG)
#### ◦ Command : OPEN_PORT 
#####          ‣ Firstly, open the selected com port.
#####          ‣ Secondly, print the status of the com port: open/close using ser.is_open that return True if com port is opened successfully.
#####          ‣ Thirdly, Call the function comBoard(), That jumps to comBoard Menue.
![19](https://user-images.githubusercontent.com/66730765/105474483-eddde180-5ca6-11eb-9cdc-ebb55183c204.PNG)
##### ‣ if you notice, the first then to do when jumping to com Board, is to reset the AVR MCU, as explained in BOOTLOADER SECTION above, that the bootloader sends some starting messages, and ofcourse these messages are sent directly as the AVR is powered and we missed these messages while starting python script. That's why we need to reset the MCU after opening the COM port.
![20](https://user-images.githubusercontent.com/66730765/105475653-4661ae80-5ca8-11eb-971c-a1b27ec4f5bd.PNG)
##### ‣ As you can see, there are two debug-texter here: 
######              ∙ PY_DEBUG : is from Python script.
######              ∙ BLD_DEBUG : is from ATmega-16 BOOTLOADER.
![20](https://user-images.githubusercontent.com/66730765/105475966-b8d28e80-5ca8-11eb-8079-5cb59e034458.PNG)
##### ‣ Now our Bootloader is waiting for new command to receiver from USART.
##### ‣ The " b' " character before the BLD_DEBUG message means that the printed message was recieved in bytes in python. 
##### ‣ In Python we have some predefined commands, just choose what to do, and if the user wants to write his own command manually, there is a command also for that.
#### ◦ III.2.3 Python Predefined command :
##### ‣ BLD_LIST : call BLD_CMD_LIST() Function that send char 'A' to Bootloader and receive the response which is the Bootloader command list we defined in Bootloader code.
![21](https://user-images.githubusercontent.com/66730765/105487130-49fd3180-5cb8-11eb-8731-5347098d07f9.PNG)
##### ‣ BLD_LIST : Run Time.
![22](https://user-images.githubusercontent.com/66730765/105487504-e6273880-5cb8-11eb-9a97-387df0eaa628.PNG)
###### The response is a list of commands defined in Bootloader.

