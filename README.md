# OLED_I2C_STM32
A repo where I try to implement a driver for the ssd1306 Oled Screen using SPI.

## SSD1306 Must know Concepts : 

### Pins :
SSD1306 have some control pins that we must know prior to establishing connection between our MCU and the screen in order to get the I2C Frame Right ! 

#### D/C bit :

Stands for Data or command Pin, When this Bit is et to **HIGH**, data in  [0..7] will be treated as data, when it is LOW incoming data will be treated as command.

#### R/W bit :

Stands for read/write command, When this Bit is et to **HIGH**, data in  [0..7] will be treated as data, when it is LOW incoming data will be treated as command.
