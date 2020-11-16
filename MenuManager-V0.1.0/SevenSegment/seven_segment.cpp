/*
------------------------------------------------------------------------------
~ File   : seven_segment.cpp
~ Author : Majid Derhambakhsh
~ Version: V0.0.0
~ Created: 05/10/2020 07:25:00 PM
~ Brief  :
~ Support: 
           E-Mail : Majid.do16@gmail.com (subject : Embedded Library Support)
		   
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    

~ Attention  :    

~ Changes    :
------------------------------------------------------------------------------
*/

#include "seven_segment.h"

/* Standard CA 7Segment Pin

		S1 A  F  S2 S3 B
		E  D  DP C  G  S4

*/

namespace Display
{

	const uint8_t segment_characters[_SEGMENT_NMB_OF_ASCII_CHARACTERS] =
	{

		/* ASCII Table:

		   Number             is start from 48 ~ 57 Decimal
		   Alphabet uppercase is start from 65 ~ 90 Decimal
		   Alphabet lowercase is start from 97 ~ 122 Decimal

		*/

		/* Special Character:
		   space !     "     #     $     %     &     '     (     )
		   *     +     ,     -     .     /

		*/
		0x00, 0x86, 0x22, 0x00, 0x00, 0x00, 0x00, 0x02, 0x39, 0x41,
		0x00, 0x00, 0x00, 0x40, 0x80, 0x40,

		/* Number:
		   0     1     2     3     4     5     6     7     8     9

		*/
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,

		/* Special Character:
		   :     ;     <     =     >     ?     @
		   
		*/
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/* Alphabet uppercase:
		   A     B     C     D     E     F     G     H     I
		   J     K     L     M     N     O     P     Q     R
		   S     T     U     V     W     X     Y     Z

		*/
		0x77, 0x7F, 0x39, 0x1F, 0x79, 0x71, 0x3D, 0x76, 0x30,
		0x1E, 0x7A, 0x38, 0x55, 0x76, 0x3F, 0x73, 0x3B, 0x7B,
		0x6D, 0x31, 0x3E, 0x2E, 0x6A, 0x49, 0x6E, 0x5B,

		/* Special Character:
		   [     \     ]     ^     _     `
		   
		*/
		0x39, 0x00, 0x0F, 0x21, 0x08, 0x00,

		/* Alphabet lowercase:
		   a     b     c     d     e     f     g     h     i
		   j     k     l     m     n     o     p     q     r
		   s     t     u     v     w     x     y     z

		*/
		0x4C, 0x7C, 0x58, 0x5E, 0x1A, 0x71, 0x59, 0x74, 0x10,
		0x0E, 0x69, 0x30, 0x15, 0x54, 0x5C, 0x73, 0x67, 0x50,
		0x48, 0x78, 0x1C, 0x0C, 0x2A, 0x48, 0x6E, 0x48,

		/* Special Character:
		   {     |     }     ~
		   
		*/
		0x39, 0x30, 0x0F, 0x40
		
	};

	enum PinNumberIndex
	{

		PinAIndex = 0,
		PinBIndex = 1,
		PinCIndex = 2,
		PinDIndex = 3,
		PinEIndex = 4,
		PinFIndex = 5,
		PinGIndex = 6,
		PinDPIndex = 7

	};

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	/* ~~~~~~~~~~~~~~~~ Constractor ~~~~~~~~~~~~~~~~ */
	SSegment::SSegment(uint8_t _nmb_of_segments, uint8_t _refresh_rate, uint8_t _buffer_length): NmbOfSegments(_nmb_of_segments), RefreshRate(_refresh_rate), RefreshTime(_SECOND_MS / (_nmb_of_segments * _refresh_rate)), BufferLength(_buffer_length)
	{
		/* ..... Create buffer ..... */
		Buffer = new char[BufferLength];

	}
	SSegment::SSegment(SSegmentCfg_TypeDef _cfg, uint8_t _nmb_of_segments, uint8_t _refresh_rate, uint8_t _buffer_length): NmbOfSegments(_nmb_of_segments), RefreshRate(_refresh_rate), RefreshTime(_SECOND_MS / (_nmb_of_segments * _refresh_rate)), BufferLength(_buffer_length)
	{
		/* ..... Create buffer ..... */
		Buffer = new char[BufferLength];

		/* ..... Set configurations ..... */
		ShiftValue = 0; 
		SegmentCounter = 0;
		Configurations = _cfg;

		if (_cfg.Type == CommonAnode)
		{
			DataPinSetState = _GPIO_PIN_RESET;
			DataPinResetState = _GPIO_PIN_SET;
		}
		else
		{
			DataPinSetState = _GPIO_PIN_SET;
			DataPinResetState = _GPIO_PIN_RESET;
		}

		ControlPinSetState = DataPinResetState;
		ControlPinResetState = DataPinSetState;

		/* ..... Control pin sets ..... */
		ControlPins = 0;

		for (size_t pin_counter = 0; pin_counter < NmbOfSegments; pin_counter++)
		{
			ControlPins = (ControlPins << 1);
			ControlPins += 1;
		}

		/* ..... Clean segments ..... */
		SSegment::Clear();

	}
	
	/* ~~~~~~~~~~~~~~~~ Global ~~~~~~~~~~~~~~~~ */
	void SSegment::Init(SSegmentCfg_TypeDef _cfg)
	{
		
		/* ..... Set configurations ..... */
		ShiftValue = 0; 
		SegmentCounter = 0;
		Configurations = _cfg;

		if (_cfg.Type == CommonAnode)
		{
			DataPinSetState = _GPIO_PIN_RESET;
			DataPinResetState = _GPIO_PIN_SET;
		}
		else
		{
			DataPinSetState = _GPIO_PIN_SET;
			DataPinResetState = _GPIO_PIN_RESET;
		}

		ControlPinSetState = DataPinResetState;
		ControlPinResetState = DataPinSetState;

		/* ..... Control pin sets ..... */
		ControlPins = 0;

		for (size_t pin_counter = 0; pin_counter < NmbOfSegments; pin_counter++)
		{
			ControlPins = (ControlPins << 1);
			ControlPins += 1;
		}

		/* ..... Clean segments ..... */
		SSegment::Clear();

	}

	void SSegment::PinConfig(SSegmentPinCfg_TypeDef _cfg)
	{

		PinNumberList = new uint8_t[_SEGMENT_NMB_OF_DATA_PINS];

		PinNumberList[PinAIndex] = _cfg.PINA;
		PinNumberList[PinBIndex] = _cfg.PINB;
		PinNumberList[PinCIndex] = _cfg.PINC;
		PinNumberList[PinDIndex] = _cfg.PIND;
		PinNumberList[PinEIndex] = _cfg.PINE;
		PinNumberList[PinFIndex] = _cfg.PINF;
		PinNumberList[PinGIndex] = _cfg.PING;
		PinNumberList[PinDPIndex] = _cfg.PINDP;

		for (size_t pin_counter = 0; pin_counter < _SEGMENT_NMB_OF_DATA_PINS; pin_counter++)
		{

			DataPins |= (1 << PinNumberList[pin_counter]);

		}

	}

	/* ..... Sync functions ..... */
	void SSegment::Sync()
	{

		/* ..... Enable segment x ..... */
		_GPIO_WritePin(Configurations.ControlGPIO, (ControlPins << Configurations.ControlPinA), ControlPinResetState);
		_GPIO_WritePin(Configurations.ControlGPIO, (1 << (Configurations.ControlPinA + SegmentCounter)), ControlPinSetState);

		/* ..... Write data on segment ..... */
		ShiftStatus = SegmentCounter + ShiftValue;

		if ((ShiftStatus < 0) || (ShiftStatus >= BufferLength))
		{
			BufferChar = ',';
		}
		else
		{
			BufferChar = Buffer[ShiftStatus];
		}

		/* ..... Write data ..... */
		#ifdef _ENABLE_CUSTOM_PIN

		Configurations.DataPinA = 0;

		for (size_t pin_counter = 0; pin_counter < _SEGMENT_NMB_OF_DATA_PINS; pin_counter++)
		{
			
			Configurations.DataPinA |= (_GiveBitState(segment_characters[(BufferChar - _SEGMENT_CHARACTER_INDEX_DIFFERENCE)], pin_counter) << PinNumberList[pin_counter]);

		}

		_GPIO_WritePin(Configurations.DataGPIO, DataPins, DataPinResetState);
		_GPIO_WritePin(Configurations.DataGPIO, Configurations.DataPinA, DataPinSetState);

		#else

		_GPIO_WritePin(Configurations.DataGPIO, (0xFF << Configurations.DataPinA), DataPinResetState);
		_GPIO_WritePin(Configurations.DataGPIO, (segment_characters[(BufferChar - _SEGMENT_CHARACTER_INDEX_DIFFERENCE)] << Configurations.DataPinA), DataPinSetState);

		#endif /* _ENABLE_CUSTOM_PIN */

		/* ..... Disable segment x ..... */
		SegmentCounter++;

		/* Check index */
		if (SegmentCounter == NmbOfSegments)
		{
			SegmentCounter = 0;
		}

	}
	void SSegment::SyncLoop()
	{

		/* ..... Enable segment x ..... */
		_GPIO_WritePin(Configurations.ControlGPIO, (ControlPins << Configurations.ControlPinA), ControlPinResetState);
		_GPIO_WritePin(Configurations.ControlGPIO, (1 << (Configurations.ControlPinA + SegmentCounter)), ControlPinSetState);

		/* ..... Write data on segment ..... */
		ShiftStatus = SegmentCounter + ShiftValue;

		if ((ShiftStatus < 0) || (ShiftStatus >= BufferLength))
		{
			BufferChar = ',';
		}
		else
		{
			BufferChar = Buffer[ShiftStatus];
		}

		/* ..... Write data ..... */
		#ifdef _ENABLE_CUSTOM_PIN

		Configurations.DataPinA = 0;

		for (size_t pin_counter = 0; pin_counter < _SEGMENT_NMB_OF_DATA_PINS; pin_counter++)
		{

			Configurations.DataPinA |= (_GiveBitState(segment_characters[(BufferChar - _SEGMENT_CHARACTER_INDEX_DIFFERENCE)], pin_counter) << PinNumberList[pin_counter]);

		}

		_GPIO_WritePin(Configurations.DataGPIO, DataPins, DataPinResetState);
		_GPIO_WritePin(Configurations.DataGPIO, Configurations.DataPinA, DataPinSetState);

		#else

		_GPIO_WritePin(Configurations.DataGPIO, (0xFF << Configurations.DataPinA), DataPinResetState);
		_GPIO_WritePin(Configurations.DataGPIO, (segment_characters[(BufferChar - _SEGMENT_CHARACTER_INDEX_DIFFERENCE)] << Configurations.DataPinA), DataPinSetState);

		#endif /* _ENABLE_CUSTOM_PIN */

		/* ..... Disable segment x ..... */
		SegmentCounter++;

		/* Check index */
		if (SegmentCounter == NmbOfSegments)
		{
			SegmentCounter = 0;
		}

		/* ..... Refresh delay ..... */
		_DELAY_MS(RefreshTime);

	}

	/* ..... Control functions ..... */
	void SSegment::DisplayOff(void)
	{
	}
	void SSegment::DisplayOn(void)
	{
	}

	void SSegment::Shift(int8_t _value)
	{
		ShiftValue -= _value;
	}

	/* ..... Dataset functions ..... */
	void SSegment::Clear(void)
	{
		for (size_t array_counter = 0; array_counter < BufferLength; array_counter++)
		{
			Buffer[array_counter] = ';';
		}
	}

	void SSegment::Show(const char *_text)
	{

		const char* address = _text;

		uint8_t str_length = 0;

		/* Count data */
		while (*address != '\0')
		{
			str_length++;
			address++;
		}

		/* Clean Buffer */
		SSegment::Clear();

		/* Copy new data */
		strncpy(Buffer, _text, str_length);

	}
	void SSegment::ShowASync(char *_text)
	{

		for (SegmentCounter = 0; SegmentCounter < NmbOfSegments; SegmentCounter++)
		{

			/* ..... Enable segment x ..... */
			_GPIO_WritePin(Configurations.ControlGPIO, (ControlPins << Configurations.ControlPinA), ControlPinResetState);
			_GPIO_WritePin(Configurations.ControlGPIO, (1 << (Configurations.ControlPinA + SegmentCounter)), ControlPinSetState);

			/* ..... Write data on segment ..... */
			ShiftStatus = SegmentCounter + ShiftValue;

			if ((ShiftStatus < 0) || (ShiftStatus >= BufferLength))
			{
				BufferChar = ',';
			}
			else
			{
				BufferChar = *_text;
			}

			/* ..... Write data ..... */
			#ifdef _ENABLE_CUSTOM_PIN

			Configurations.DataPinA = 0;

			for (size_t pin_counter = 0; pin_counter < _SEGMENT_NMB_OF_DATA_PINS; pin_counter++)
			{

				Configurations.DataPinA |= (_GiveBitState(segment_characters[(BufferChar - _SEGMENT_CHARACTER_INDEX_DIFFERENCE)], pin_counter) << PinNumberList[pin_counter]);

			}

			_GPIO_WritePin(Configurations.DataGPIO, DataPins, DataPinResetState);
			_GPIO_WritePin(Configurations.DataGPIO, Configurations.DataPinA, DataPinSetState);

			#else

			_GPIO_WritePin(Configurations.DataGPIO, (0xFF << Configurations.DataPinA), DataPinResetState);
			_GPIO_WritePin(Configurations.DataGPIO, (segment_characters[(BufferChar - _SEGMENT_CHARACTER_INDEX_DIFFERENCE)] << Configurations.DataPinA), DataPinSetState);

			#endif /* _ENABLE_CUSTOM_PIN */
			
			_text++;

			/* ..... Refresh delay ..... */
			_DELAY_MS(RefreshTime);

		}

	}
	void SSegment::ShowASync(string _text)
	{

		for (SegmentCounter = 0; SegmentCounter < NmbOfSegments; SegmentCounter++)
		{

			/* ..... Enable segment x ..... */
			_GPIO_WritePin(Configurations.ControlGPIO, (ControlPins << Configurations.ControlPinA), ControlPinResetState);
			_GPIO_WritePin(Configurations.ControlGPIO, (1 << (Configurations.ControlPinA + SegmentCounter)), ControlPinSetState);

			/* ..... Write data on segment ..... */
			ShiftStatus = SegmentCounter + ShiftValue;

			if ((ShiftStatus < 0) || (ShiftStatus >= BufferLength))
			{
				BufferChar = ',';
			}
			else
			{
				BufferChar = _text[ShiftStatus];
			}

			/* ..... Write data ..... */
			#ifdef _ENABLE_CUSTOM_PIN

			Configurations.DataPinA = 0;

			for (size_t pin_counter = 0; pin_counter < _SEGMENT_NMB_OF_DATA_PINS; pin_counter++)
			{

				Configurations.DataPinA |= (_GiveBitState(segment_characters[(BufferChar - _SEGMENT_CHARACTER_INDEX_DIFFERENCE)], pin_counter) << PinNumberList[pin_counter]);

			}

			_GPIO_WritePin(Configurations.DataGPIO, DataPins, DataPinResetState);
			_GPIO_WritePin(Configurations.DataGPIO, Configurations.DataPinA, DataPinSetState);

			#else

			_GPIO_WritePin(Configurations.DataGPIO, (0xFF << Configurations.DataPinA), DataPinResetState);
			_GPIO_WritePin(Configurations.DataGPIO, (segment_characters[(BufferChar - _SEGMENT_CHARACTER_INDEX_DIFFERENCE)] << Configurations.DataPinA), DataPinSetState);

			#endif /* _ENABLE_CUSTOM_PIN */

			/* ..... Refresh delay ..... */
			_DELAY_MS(RefreshTime);

		}

	}

}
