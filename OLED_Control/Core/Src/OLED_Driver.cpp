/*
 * OLED_Driver.cpp
 *
 *  Created on: Dec 8, 2023
 *      Author: ousjl
 */

#include "OLED_Driver.h"
#include <string.h>

/* Static Members Init */

uint16_t OLED::Point_BitMap [26] = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x03E0,0x03E0,0x03E0,0x03E0,0x0000,0x0000,0x0000,0x0000,0x0000};


HAL_StatusTypeDef OLED::SendCommand( uint8_t cmd)
{
	if ( HAL_I2C_Mem_Write(&hi2c1, OLED_I2C_SLAVE_ADRESS, 0x00, 1 , &cmd, 1, 10) == HAL_OK  ) { HAL_Delay(5) ; return ( HAL_OK ) ; }
	else { return ( HAL_ERROR ) ; }
}

void OLED::Init()
{
    HAL_Delay(100);

    // Init OLED
    this->SendCommand(0xAE); //display off

    this->SendCommand(0x20); //Set Memory Addressing Mode
    this->SendCommand(0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;  10b,Page Addressing Mode (RESET); 11b,Invalid
    this->SendCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
    this->SendCommand(0xC8); //Set COM Output Scan Direction
    this->SendCommand(0x00); //---set low column address
    this->SendCommand(0x10); //---set high column address

    this->SendCommand(0x40); //--set start line address - CHECK

    this->SendCommand(0x81);
    this->SendCommand(0xFF); // Contrast

    this->SendCommand(0xA1); //--set segment re-map 0 to 127 - CHECK
    this->SendCommand(0xA6); //--set normal color
    this->SendCommand(0xA8); //--set multiplex ratio(1 to 64) - CHECK
    this->SendCommand(0x3F); //
    this->SendCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    this->SendCommand(0xD3); //-set display offset - CHECK
    this->SendCommand(0x00); //-not offset
    this->SendCommand(0xD5); //--set display clock divide ratio/oscillator frequency
    this->SendCommand(0xF0); //--set divide ratio
    this->SendCommand(0xD9); //--set pre-charge period
    this->SendCommand(0x22); //
    this->SendCommand(0xDA); //--set com pins hardware configuration - CHECK
    this->SendCommand(0x12);
    this->SendCommand(0xDB); //--set vcomh
    this->SendCommand(0x20); //0x20,0.77xVcc

    this->SendCommand(0x8D); //--set DC-DC enable
    this->SendCommand(0x14); //
    this->SendCommand(0xAF); //--turn on SSD1306 panel

    // Clear screen
    this->Clear() ;

    // Flush buffer to screen
    this->RefreshScreen();
}

/*
 * Brief : this method will be used in refresh screen, and so we Will iterate over pages so every time we are sending OLED_WIDTH equivalent of data.
 */
HAL_StatusTypeDef OLED::SendData( uint8_t* data)
{
	if ( HAL_I2C_Mem_Write(&hi2c1, OLED_I2C_SLAVE_ADRESS , 0x40 ,  1 , data , OLED_WIDTH , HAL_MAX_DELAY) == HAL_OK ) { HAL_Delay(5) ; return (HAL_OK)  ; }
	else { return ( HAL_ERROR ) ; }
}

/*
 * Brief : Each Byte of the static OLED Buffer is representing the status of 8 pixels vertically (**one column in one page**) .
 * Each Bit stands for a pixel status.
 * We should Locate the exact Bit of the wanted Pixel and Force It into HIGH
 * Suppose I wanted to light up pixel ( 30 , 50 )
 * the corresponding byte is located at 30 + ( 50 / 8 ) * Height.  8 Here Stands for number of pages.
 * the corresonding bit in that Variable is 1 >> (y % 8) . 8 here stands for number of pixels in a single Byte.
 */

void OLED::WritePixel(uint32_t x , uint32_t y )
{
	this->ScreenBuffer [ x + (y/8) * OLED_HEIGHT ] |= ( 1 << (y % 8 ) ) ;
}

void OLED::DrawPoint ()
{
	uint32_t PointPixels = 0 ;
	bool pixelHigh   = 0 ;
	if   ( ( ( this->CurrentCursor_X + OLED_POINT_WIDTH  ) > OLED_WIDTH ) \
		|| ( ( this->CurrentCursor_Y + OLED_POINT_HEIGHT ) > OLED_HEIGHT ) )
	{
		return ;
	}
	for ( uint32_t column = 0 ; column < OLED_POINT_WIDTH ; column ++ )
	{
		PointPixels = this->Point_BitMap[column] ;
		for ( uint32_t bit = 0 ; bit < OLED_POINT_HEIGHT ; bit ++ )
		{
			pixelHigh = ( ( PointPixels << bit ) & 0x8000U );
			if  ( pixelHigh )
			{
				this->WritePixel(this->CurrentCursor_X + bit , this->CurrentCursor_Y + column ) ;
			}
		}
	}
	this->RefreshScreen() ;
}

void OLED::SetCursor(uint16_t x , uint16_t y )
{
	this->CurrentCursor_X = x ;
	this->CurrentCursor_Y = y ;
}
void OLED::Clear()
{
	memset(this->ScreenBuffer , 0x00 , OLED_Size ) ;
	this->RefreshScreen() ;
}

/*
 * Brief : We are iterating over pages.
 */
void OLED::RefreshScreen()

{
	for(uint8_t i = 0; i < OLED_HEIGHT / 8 ; i++) {
	        this->SendCommand(0xB0 + i); // Set the current RAM page address.
	        this->SendCommand(0x00 );
	        this->SendCommand(0x10 );
	        this->SendData(&this->ScreenBuffer[OLED_WIDTH * i]);
	    }
}
