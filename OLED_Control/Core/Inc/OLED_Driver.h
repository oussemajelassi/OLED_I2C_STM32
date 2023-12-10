/*
 * OLED_Driver.h
 *
 *  Created on: Dec 8, 2023
 *      Author: ousjl
 */

#ifndef INC_OLED_DRIVER_H_
#define INC_OLED_DRIVER_H_

/** Privale Includes **/

#include "stdint.h"
#include "main.h"

/** Private Macros **/
#define OLED_Size   1024
#define OLED_HEIGHT 64
#define OLED_WIDTH  128
#define OLED_POINT_HEIGHT 16
#define OLED_POINT_WIDTH  26
#define OLED_I2C_SLAVE_ADRESS (0x3C << 1)
/** Private extern Varibles **/

extern I2C_HandleTypeDef hi2c1;

class OLED

{
public :
	static uint16_t Point_BitMap [ 26 ] ;
private :

	uint16_t CurrentCursor_X ;
	uint16_t CurrentCursor_Y ;
	uint8_t ScreenBuffer [ OLED_Size ] ;

public:
	void Init () ;
	void Clear() ;
	HAL_StatusTypeDef SendCommand ( uint8_t  cmd ) ;
	HAL_StatusTypeDef SendData 	  ( uint8_t* data ) ;
	void WritePixel  (uint32_t x , uint32_t y ) ;
	void DrawPoint	   ( void ) ;
	void RefreshScreen ( void ) ;
	void SetCursor ( uint16_t x , uint16_t y ) ;

};


#endif /* INC_OLED_DRIVER_H_ */
