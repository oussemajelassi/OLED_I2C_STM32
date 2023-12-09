# OLED_I2C_STM32
A repo where I try to implement a driver for the ssd1306 Oled Screen using SPI.

## SSD1306 Must know Concepts : 

### Pins :
SSD1306 have some control pins that we must know prior to establishing connection between our MCU and the screen in order to get the I2C Frame Right ! 

#### D/C bit :

Stands for Data or command Pin, When this Bit is et to **HIGH**, data in  [0..7] will be treated as data, when it is LOW incoming data will be treated as command.

#### R/W bit :

Stands for read/write command, When this Bit is et to **HIGH**, data in  [0..7] will be treated as data, when it is LOW incoming data will be treated as command.

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

