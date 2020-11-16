/*
------------------------------------------------------------------------------
~ File   : menu_manager.h
~ Author : Majid Derhambakhsh
~ Version: V0.1.0
~ Created: 11/15/2020 09:00:00 AM
~ Brief  :
~ Support:
           E-Mail : Majid.Derhambakhsh@gmail.com (subject : Embedded Library Support)
           
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    Menu Manager library for manage the menu & items with support click event.

~ Attention  :    

~ Changes    :    Add new configurations in menu_manager_conf.h
                  Add 'Menu_GetCurrentPageID' function
                  Add 'Menu_ResetCurrentPage' function
                  Add 'Menu_ShowCurrentPage' in 'Menu_SelectNextItem_CurrentPage'
                  Add 'Menu_ShowCurrentPage' in 'Menu_SelectPreviousItem_CurrentPage'
                  
                  Remove '_NUMBER_OF_PAGES' and automatic calculate in 'Menu_PageInit' function
                  
                  Improve 'Menu_ShowPage' function speed and usage memory
                  Improve 'Menu_ShowCurrentPage' function speed and usage memory
                  
------------------------------------------------------------------------------
*/

#ifndef __MENU_MANAGER_H_
#define __MENU_MANAGER_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <stdint.h>

#include "menu_manager_conf.h"

#ifdef _USE_LCD_DISPLAY
	
	#ifndef __CHARACTER_LCD_H_
	
		#include "CHARACTER_LCD/character_lcd.h"
	
	#endif /* __CHARACTER_LCD_H_ */
	
#endif /* _USE_LCD_DISPLAY */

#ifdef _USE_7SEGMENT_DISPLAY
	
	#ifndef __SEVEN_SEGMENT_H_
	
		#include "SevenSegment/seven_segment.h"
	
	#endif /* __SEVEN_SEGMENT_H_ */
	
	using namespace Display;
	
#endif /* _USE_7SEGMENT_DISPLAY */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ----------------------------- Menu ----------------------------- */
#define __MENU_EnableBackToPreviousPage (MenuControl.BackToPreviousPageEnable = 1)
#define __MENU_EnableGoToNewPage        (MenuControl.GoToNewPageEnable = 1)
#define __MENU_EnableSelectNextItem     (MenuControl.SelectNextItemEnable = 1)
#define __MENU_EnableSelectPreviousItem (MenuControl.SelectPreviousItemEnable = 1)

#define __MENU_DisableBackToPreviousPage (MenuControl.BackToPreviousPageEnable = 0)
#define __MENU_DisableGoToNewPage        (MenuControl.GoToNewPageEnable = 0)
#define __MENU_DisableSelectNextItem     (MenuControl.SelectNextItemEnable = 0)
#define __MENU_DisableSelectPreviousItem (MenuControl.SelectPreviousItemEnable = 0)

/* -------------------------- LCD Config -------------------------- */
#ifndef _NMB_OF_DISPLAY_LINES
	
	#define _NMB_OF_DISPLAY_LINES 1
	
	#ifndef _DISABLE_MENU_WARNINGS
		#warning [MENU WARN01] --> "_NMB_OF_DISPLAY_LINES is auto set to 1"
	#endif
	
#endif

#ifndef _NMB_OF_DISPLAY_COLUMN
	
	#define _NMB_OF_DISPLAY_COLUMN 1
	
	#ifndef _DISABLE_MENU_WARNINGS
		#warning [MENU WARN01] --> "_NMB_OF_DISPLAY_COLUMN is auto set to 1"
	#endif
	
#endif

#if (_NMB_OF_DISPLAY_LINES == 0)
	
	#define _NMB_OF_DISPLAY_LINES 1
	
	#ifndef _DISABLE_MENU_WARNINGS
		#warning [MENU WARN01] --> "_NMB_OF_DISPLAY_LINES is auto set to 1"
	#endif
	
#endif

#if (_NMB_OF_DISPLAY_COLUMN == 0)
	
	#define _NMB_OF_DISPLAY_COLUMN 1
	
	#ifndef _DISABLE_MENU_WARNINGS
		#warning [MENU WARN01] --> "_NMB_OF_DISPLAY_COLUMN is auto set to 1"
	#endif
	
#endif

#ifndef _MENU_PUTS
	
	#ifdef _USE_LCD_DISPLAY
		
		#define _MENU_PUTS(x)     Lcd_PutString(x) 
		
	#elif defined(_USE_7SEGMENT_DISPLAY)
		
		#define _MENU_PUTS(x)     _7SEGMENT_DISPLAY.Show(x)
		
	#endif
	
#endif

#ifndef _MENU_PUTCH
	
	#ifdef _USE_LCD_DISPLAY
		
		#define _MENU_PUTCH(x)     Lcd_PutChar(x)
		
	#endif
	
#endif

#ifndef _MENU_CLEAR

	#ifdef _USE_LCD_DISPLAY

		#define _MENU_CLEAR()     Lcd_Clear()

	#elif defined(_USE_7SEGMENT_DISPLAY)

		#define _MENU_CLEAR()     _7SEGMENT_DISPLAY.Clear()

	#endif

#endif

#ifndef _MENU_GOTOXY

	#ifdef _USE_LCD_DISPLAY

		#define _MENU_GOTOXY(x,y)     Lcd_GotoXY(x,y)

	#endif

#endif

/* ---------------------------- Public ---------------------------- */
#ifndef _TRUE
	#define _TRUE 1
#endif

#ifndef _FALSE
	#define _FALSE 0
#endif

/* ---------------------- Define by compiler ---------------------- */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef char           PageItemName_TypeDef;
typedef uint8_t        PageItemID_TypeDef;

typedef void(*ClickEvent_TypeDef)(void);

typedef struct /* Page control structure */
{
	
	uint8_t BackToPreviousPageEnable : 1;
	uint8_t GoToNewPageEnable        : 1;
	uint8_t SelectNextItemEnable     : 1;
	uint8_t SelectPreviousItemEnable : 1;
	
}MenuControl_TypeDef;

typedef struct /* Page structure */
{
	
	#ifdef __cplusplus
	
		char (*ItemsName)[_NMB_OF_DISPLAY_COLUMN + 1];
	
	#else
	
		char (*ItemsName)[];
	
	#endif /* __cplusplus */
	
	
	uint8_t *ItemsID;
	
	uint8_t ID;
	uint8_t ParentID;
	uint8_t ItemsNameLength;
	uint8_t ItemsQuantity;
	uint8_t DefaultItem;
	uint8_t SelectedItem;
	
	ClickEvent_TypeDef *ClickEvent;
	
}Page_TypeDef;

typedef Page_TypeDef*  PageList_TypeDef;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
extern MenuControl_TypeDef MenuControl;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void Menu_PageInit(Page_TypeDef **_page_list, Page_TypeDef *_root_page);

void Menu_ShowPage(Page_TypeDef *_page);

void Menu_ShowCurrentPage(void);

uint8_t Menu_GetCurrentPageID(void);

void Menu_ResetCurrentPage(void);

void Menu_SelectNextItem(Page_TypeDef *_page);

void Menu_SelectNextItem_CurrentPage(void);

void Menu_SelectPreviousItem_CurrentPage(void);

void Menu_OpenSelectedPage(void);

void Menu_BackToPreviousPage(void);

void Menu_RunClickEvent(void);

void NullClickEvent(void);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#endif /* __MENU_MANAGER_H_ */
