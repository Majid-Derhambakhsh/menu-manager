/*
------------------------------------------------------------------------------
~ File   : seven_segment.h
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

#ifndef __SEVEN_SEGMENT_H_
#define __SEVEN_SEGMENT_H_

/*----------------------------------------------------------*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <stdint.h>
#include <string>
#include <string.h>

#include "seven_segment_conf.h"

using namespace std;

/* ------------------------------------------------------------------ */

#ifdef __CODEVISIONAVR__  /* Check compiler */

#pragma warn_unref_func- /* Disable 'unused function' warning */

#include "GPIO_UNIT/gpio_unit.h" /* Import gpio lib */

#include <delay.h>       /* Import delay library */

/* ------------------------------------------------------------------ */

#elif defined(__GNUC__) && !defined(USE_HAL_DRIVER)  /* Check compiler */

#pragma GCC diagnostic ignored "-Wunused-function" /* Disable 'unused function' warning */

#include "GPIO_UNIT/gpio_unit.h" /* Import gpio lib */

#include <util/delay.h>  /* Import delay library */

/* ------------------------------------------------------------------ */

#elif defined(USE_HAL_DRIVER)  /* Check driver */

	/* --------------- Check Mainstream series --------------- */

	#ifdef STM32F0
		#include "stm32f0xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F1)
		#include "stm32f1xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F2)
		#include "stm32f2xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F3)
		#include "stm32f3xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F4)
		#include "stm32f4xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F7)
		#include "stm32f7xx_hal.h"       /* Import HAL library */
	#elif defined(STM32G0)
		#include "stm32g0xx_hal.h"       /* Import HAL library */
	#elif defined(STM32G4)
		#include "stm32g4xx_hal.h"       /* Import HAL library */

	/* ------------ Check High Performance series ------------ */

	#elif defined(STM32H7)
		#include "stm32h7xx_hal.h"       /* Import HAL library */

	/* ------------ Check Ultra low power series ------------- */

	#elif defined(STM32L0)
		#include "stm32l0xx_hal.h"       /* Import HAL library */
	#elif defined(STM32L1)
		#include "stm32l1xx_hal.h"       /* Import HAL library */
	#elif defined(STM32L5)
		#include "stm32l5xx_hal.h"       /* Import HAL library */
	#elif defined(STM32L4)
		#include "stm32l4xx_hal.h"       /* Import HAL library */
	#elif defined(STM32H7)
		#include "stm32h7xx_hal.h"       /* Import HAL library */
	#else
	#endif /* STM32F1 */

	/* ------------------------------------------------------- */

	#if defined ( __ICCARM__ ) /* ICCARM Compiler */

	#pragma diag_suppress=Pe177   /* Disable 'unused function' warning */

	#elif defined   (  __GNUC__  ) /* GNU Compiler */

	#pragma diag_suppress 177     /* Disable 'unused function' warning */

	#endif /* __ICCARM__ */

/* ------------------------------------------------------------------ */

#else                     /* Compiler not found */

#error Chip or Library not supported  /* Send error */

#endif /* __CODEVISIONAVR__ */

/* ------------------------------------------------------------------ */

namespace Display
{

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	/* ---------------------------- Public ---------------------------- */
	#define _GiveBitState(val, bitx)  (((val) >> (bitx)) & 1)

	/* ..... Default value set ..... */
	#define _SEGMENT_DEFAULT_BUFFER_LENGTH   5
	#define _SEGMENT_DEFAULT_REFRESH_RATE    50
	#define _SEGMENT_DEFAULT_NMB_OF_SEGMENTS 2

	/* ............................. */
	#define _SEGMENT_NMB_OF_DATA_PINS           8
	#define _SEGMENT_CHARACTER_INDEX_DIFFERENCE 32
	#define _SEGMENT_NMB_OF_ASCII_CHARACTERS    95
	#define _SECOND_MS                          1000UL

	/* ---------------------- By compiler ---------------------- */

	#ifdef __CODEVISIONAVR__  /* Check compiler */

	#define _GPIO_WritePin(gpio , pn, ps)       GPIO_WritePin((&gpio), (pn),(ps)) /* Change function */

	#ifndef _DELAY_MS
	#define _DELAY_MS(t)                        delay_ms((t)) /* Change function */
	#endif /* _DELAY_MS */

	typedef register_t GPIO_TypeDef;
	typedef uint8_t    GPIO_PinState;

	/* ------------------------------------------------------------------ */

	#elif defined(__GNUC__) && !defined(USE_HAL_DRIVER)  /* Check compiler */

	#define _GPIO_WritePin(gpio , pn, ps)       GPIO_WritePin((&gpio), (pn),(ps)) /* Change function */

	#ifndef _DELAY_MS
	#define _DELAY_MS(t)                        _delay_ms((t)) /* Change function */
	#endif /* _DELAY_MS */

	typedef register_t GPIO_TypeDef;
	typedef uint8_t    GPIO_PinState;

	/* ------------------------------------------------------------------ */

	#elif defined(USE_HAL_DRIVER)  /* Check driver */

	#define _GPIO_PIN_RESET                     GPIO_PIN_RESET /* Select GPIO reset instruction */
	#define _GPIO_PIN_SET                       GPIO_PIN_SET /* Select GPIO set instruction */

	#define _GPIO_WritePin(gpio , pn, ps)       HAL_GPIO_WritePin((gpio), (pn),(ps)) /* Change function */

	#ifndef _DELAY_MS
	#define _DELAY_MS(t)                        HAL_Delay((t)) /* Change function */
	#endif /* _DELAY_MS */

	/* ------------------------------------------------------------------ */

	#else 
	#endif /* __CODEVISIONAVR__ */
	/* ----------------------------------------------------------------------- */

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	typedef enum
	{

		CommonCathode = 0,
		CommonAnode   = 1

	}SSegmentType_TypeDef;

	typedef struct
	{

		GPIO_TypeDef *DataGPIO;
		GPIO_TypeDef *ControlGPIO;

		uint16_t ControlPinA;

		uint32_t DataPinA;

		SSegmentType_TypeDef Type;

	}SSegmentCfg_TypeDef;

	typedef struct
	{

		uint8_t PINA;
		uint8_t PINB;
		uint8_t PINC;
		uint8_t PIND;
		uint8_t PINE;
		uint8_t PINF;
		uint8_t PING;
		uint8_t PINDP;

	}SSegmentPinCfg_TypeDef;

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	extern const uint8_t segment_characters[];

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Class ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	class SSegment
	{

		public:

			/* ~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~ */
			/* ..... Constructor ..... */
			SSegment(uint8_t _nmb_of_segments, uint8_t _refresh_rate, uint8_t _buffer_length);
			SSegment(SSegmentCfg_TypeDef _cfg, uint8_t _nmb_of_segments, uint8_t _refresh_rate, uint8_t _buffer_length);

			/* .......................... */
			void Init(SSegmentCfg_TypeDef _cfg);
			void PinConfig(SSegmentPinCfg_TypeDef _cfg);

			/* ..... Sync functions ..... */
			void Sync(void);
			void SyncLoop(void);

			/* ..... Control functions ..... */
			void DisplayOff(void);
			void DisplayOn(void);

			void Shift(int8_t _value);

			/* ..... Dataset functions ..... */
			void Clear(void);

			void Show(const char *_text);
			void ShowASync(char *_text);
			void ShowASync(string _text);

		protected:
		private:

			/* ~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~ */
			char* Buffer;
			char BufferChar;

			int8_t ShiftValue;
			int8_t ShiftStatus;

			volatile int8_t SegmentCounter;

			const uint8_t BufferLength;
			const uint8_t NmbOfSegments;
			const uint8_t RefreshRate;
			const uint8_t RefreshTime;

			uint16_t ControlPins;

			#ifdef _ENABLE_CUSTOM_PIN

			uint8_t* PinNumberList;

			uint32_t DataPins;

			#endif /* _ENABLE_CUSTOM_PIN */

			GPIO_PinState ControlPinSetState;
			GPIO_PinState DataPinSetState;
			GPIO_PinState ControlPinResetState;
			GPIO_PinState DataPinResetState;

			/* ~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~ */
			SSegmentCfg_TypeDef Configurations;

	};

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#endif /* __SEVEN_SEGMENT */
