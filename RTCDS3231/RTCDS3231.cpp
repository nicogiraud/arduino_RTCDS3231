
#ifdef __AVR_ATtiny85__
 #include <TinyWireM.h>
#else
 #include <Wire.h>
#endif

#include "RTCDS3231.h"


// constructor
// -----------
RTCDS3231::RTCDS3231()
{
	year = 0x00;
	month = 0x00;
	date = 0x00;
	day = 0x00;
	hour = 0x00;
	minute = 0x00;
	second = 0x00;
}


// init, set i2c address
// ---------------------
void RTCDS3231::init(uint8_t _i2c_addr)
{
	i2c_addr = _i2c_addr;
	
	// starts i2c
	Wire.begin();
}


// read from device
// ----------------
void RTCDS3231::read(void)
{
	Wire.beginTransmission(i2c_addr);
  Wire.write(0);
	Wire.endTransmission();

  Wire.requestFrom((int)i2c_addr, 7);
 	
	if(Wire.available())
	{ 
		second = BCD2DEC(Wire.read() & 0x7f);
		minute = BCD2DEC(Wire.read());
		hour = BCD2DEC(Wire.read() & 0x3f);
		day = BCD2DEC(Wire.read());
		date = BCD2DEC(Wire.read());
		month = BCD2DEC(Wire.read());
		year = BCD2DEC(Wire.read());
	}
}


// write to device
// ---------------
void RTCDS3231::write(void)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write(0);
  Wire.write(DEC2BCD(second));
  Wire.write(DEC2BCD(minute));
  Wire.write(DEC2BCD(hour));
  Wire.write(DEC2BCD(day));
  Wire.write(DEC2BCD(date));
  Wire.write(DEC2BCD(month));
  Wire.write(DEC2BCD(year));
  Wire.endTransmission();
}


// converts from Decimal to BCD
// ----------------------------
uint8_t RTCDS3231::DEC2BCD(uint8_t value)
{
	return( (value/10*16) + (value%10) );
}


// converts from BCD to Decimal
// ----------------------------
uint8_t RTCDS3231::BCD2DEC(uint8_t value)
{
	return( (value/16*10) + (value%16) );
}
