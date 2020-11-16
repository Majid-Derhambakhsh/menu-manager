/*
------------------------------------------------------------------------------
~ File   : menu_manager_conf.h
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

#ifndef __MENU_MANAGER_CONF_H_
#define __MENU_MANAGER_CONF_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~ Options ~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~~~~~~~~~~ Add required libraries ~~~~~~~~~~~~ */
//#include "x.h"

/* ~~~~~~~~~~~~ Add required namespace ~~~~~~~~~~~~ */
//using namespace x;

/* ~~~~~~~~~~~~~~~ Add Your OBJ/VAR ~~~~~~~~~~~~~~~ */
//extern x y;

/* ~~~~~~~~~~~~ Display configurations ~~~~~~~~~~~~ */
//#define _USE_LCD_DISPLAY
//#define _USE_7SEGMENT_DISPLAY

#define _NMB_OF_DISPLAY_LINES  1
#define _NMB_OF_DISPLAY_COLUMN 1

//#define _7SEGMENT_DISPLAY xDisplay

/* ~~~~~~~ Add your custom display methods ~~~~~~~~ */
//#define _MENU_PUTS(x)     Lcd_PutString(x)
//#define _MENU_PUTCH(x)    Lcd_PutChar(x)
//#define _MENU_CLEAR()     Lcd_Clear()
//#define _MENU_GOTOXY(x,y) Lcd_GotoXY(x,y)

/* ~~~~~~~~~~~ Library configurations ~~~~~~~~~~~~~ */
//#define _MENU_CLREARING_DISABLE
//#define _MENU_CURSOR_DISABLE
//#define _DISABLE_MENU_WARNINGS

#define _MENU_CURSOR_CHAR '>'

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif
