# OLED_I2C_STM32
A repo where I try to implement a driver for the ssd1306 Oled Screen using SPI.

**References** : 

[SSD1306 Datasheet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)

[Controllers Tech Tuto](https://controllerstech.com/oled-display-using-i2c-stm32/)

[Micro Peta Tuto](https://www.youtube.com/@NizarMohideen/videos)

## SSD1306 Must know Concepts : 

### Pins :
SSD1306 have some control pins that we must know prior to establishing connection between our MCU and the screen in order to get the I2C Frame Right ! 

#### D/C bit :

Stands for Data or command Pin, When this Bit is et to **HIGH**, data in  [0..7] will be treated as data, when it is LOW incoming data will be treated as command.

#### R/W bit :

Stands for read/write command, When this Bit is et to **HIGH**, data in  [0..7] will be treated as data, when it is LOW incoming data will be treated as command.

### I2C Frames for command and Data : 

After the transmission of the slave address, either the control byte or the data byte may be sent across
the SDA. A control byte mainly consists of Co and D/C# bits following by six “0” ‘s.
a. If the Co bit is set as logic “0”, the transmission of the following information will contain
data bytes only.
b. The D/C# bit determines the next data byte is acted as a command or a data. If the D/C# bit is
set to logic “0”, it defines the following data byte as a command. If the D/C# bit is set to
logic “1”, it defines the following data byte as a data which will be stored at the GDDRAM.
The GDDRAM column address pointer will be increased by one automatically after each 


#### Adressing Mode : 

Oled have **three** ways of representing printed data and those are : **Page Adressing**, **Horizontal** and **Verical** Adressing.
As Far as I have seen many are using the default way which is the Page Adressing.

This Figure in SSD1306's Datasheet explains very well how page adressing works.

![image](https://github.com/oussemajelassi/OLED_I2C_STM32/assets/100140668/3723ed95-38bc-44d6-a421-11dd16c81287)

It basically says that the screen is divided horizontally in 8 pages, each page have 8 rows.
Vertically speaking there are 128 columns all accross the screen.


#### Fonts :

In order to write Charachters we have to make a big buffer having binary representation for each pixel for every charachter.
There are many ready to use and I think there is an automated way to do so using Python #TODO.

So to Write a charachter we will take its binary representation and iterate over its bits. Every time will will shift it by one bit and look if that bit is **1** or **0**, only then we go lower and write pixel after Pixel.
Testing an MSB for a 16 bits variable is done using **& 0x8000**. 

#### Pixel Light-UP : 

Each Byte of the static OLED Buffer is representing the status of 8 pixels vertically (**one column in one page**) .
Each Bit stands for a pixel status.
We should Locate the **exact Bit** of the wanted Pixel and Force It into HIGH
Suppose I wanted to light up pixel ( 30 , 50 )
the **corresponding byte** is located at 30 + ( 50 / 8 ) * Height.  **8** Here Stands for **number of pages**.
the **corresonding bit** in that Variable is 1 >> (y % 8) . **8** here stands for **number of pixels** in a single Byte.

## Next : OLED White Board using HID MOUSE as a USB Device and my STM32 as a HOST.

I will build up on this by making a white board project on the screen, ~~Most probably on a seperate Repo~~, Will keep this repo up to date if anything changes.

My Application is quite straight forward, combining this OLED simple control with data from my mouse I will draw on My Oled, For now I think there is a problem with Y axis so I will procede with only X axis.
The problem may be related to my gamer mouse high DPI and I am not sure to be honest.
Below will be a small description about my application architecture which will implement __real time__ techniques.

![Diagramme sans nom](https://github.com/oussemajelassi/OLED_SimpleControl_STM32/assets/100140668/66c9e9d7-c4de-4ad2-899f-15b1ade9191b)


