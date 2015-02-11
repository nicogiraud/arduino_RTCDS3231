#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
 #include <TinyWireM.h>
#else
 #include <Wire.h>
#endif


class RTCDS3231
{
	public:

		RTCDS3231();

		uint8_t year;
		uint8_t month;
		uint8_t date;
		uint8_t day;
		uint8_t hour;
		uint8_t minute;
		uint8_t second;

		void init(uint8_t _i2c_addr);

		void read(void);
		void write(void);

	protected:
		uint8_t DEC2BCD(uint8_t value);
		uint8_t BCD2DEC(uint8_t value);
		uint8_t i2c_addr;

};
