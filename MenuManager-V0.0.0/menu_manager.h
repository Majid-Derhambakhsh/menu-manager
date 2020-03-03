/*
------------------------------------------------------------------------------
~ File   : menu_manager.h
~ Author : Majid Derhambakhsh
~ Version: V0.0.0
~ Created: 03/03/2020 02:18:00 AM
~ Brief  :
~ Support:
           E-Mail : Majid.Derhambakhsh@gmail.com (subject : Embedded Library Support)
           
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    Menu Manager library for manage the menu & items with support click event.

~ Attention  :    

~ Changes    :    
------------------------------------------------------------------------------
*/

#ifndef __MENU_MANAGER_H_
#define __MENU_MANAGER_H_

/*----------------------------------------------------------*/

#ifdef __cplusplus

extern "C"
{

#endif /* __cplusplus */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <stdint.h>

#include "menu_manager_conf.h"

#ifndef __CHARACTER_LCD_H_

#include "CHARACTER_LCD/character_lcd.h"

#endif /* __CHARACTER_LCD_H_ */

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
#define _CH_LCD_LINES 2

#define _LCD_PUTS(x)     Lcd_PutString(x)
#define _LCD_PUTCH(x)    Lcd_PutChar(x)
#define _LCD_CLEAR()     Lcd_Clear()
#define _LCD_GOTOXY(x,y) Lcd_GotoXY(x,y)

/* ---------------------------- Public ---------------------------- */
#ifndef _TRUE
	#define _TRUE 1
#endif

#ifndef _FALSE
	#define _FALSE
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
	
	char (*ItemsName)[];
	
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

void Menu_SelectNextItem(Page_TypeDef *_page);

void Menu_SelectNextItem_CurrentPage(void);

void Menu_SelectPreviousItem_CurrentPage(void);

void Menu_OpenSelectedPage(void);

void Menu_BackToPreviousPage(void);

void Menu_RunClickEvent(void);

void NullClickEvent(void);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifdef __cplusplus

}

#endif /* __cplusplus */

#endif /* __MENU_MANAGER_H_ */
