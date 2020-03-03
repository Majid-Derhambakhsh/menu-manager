/*
------------------------------------------------------------------------------
~ File   : menu_manager.c
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

#include "menu_manager.h"

/* ............. Global variables ............ */
static Page_TypeDef *g_current_page;
static Page_TypeDef **g_page_list;

/* .................. Struct ................. */
MenuControl_TypeDef MenuControl;

/* ................ Functions ................ */
void Menu_PageInit(Page_TypeDef **_page_list, Page_TypeDef *_root_page)
{
	
	g_page_list    = _page_list;
	g_current_page = _root_page;
	
	/* ~~~~~~~~~~ Initialize ~~~~~~~~~~ */
	if (_root_page->SelectedItem < _root_page->DefaultItem)
	{
		_root_page->SelectedItem = _root_page->DefaultItem;
	}
	
	/* ~~~~~~~~~~ Enable control functions ~~~~~~~~~~ */
	__MENU_EnableSelectNextItem;
	__MENU_EnableSelectPreviousItem;
	__MENU_EnableGoToNewPage;
	__MENU_EnableBackToPreviousPage;
	
}
/*
	Guide   :
			Function description	This function is used to initialize pages.
			
			Parameters
									_page_list : Pointer to page list.
									_root_page : Pointer to first page for run.
			Return Values
									-
			
	Example :
			Page_TypeDef mainPage;
			Page_TypeDef mainPage_pagex;
			
			PageItemName_TypeDef mainPageItemsName[2][6] = {"Item1", "Item2"};
			PageItemID_TypeDef   mainPageItemsID[2] = {5,2};
			ClickEvent_TypeDef   mainPageItemsClickEvent[2] = {NullClickEvent, NullClickEvent};
			
			PageItemName_TypeDef mainPage_pagexItemsName[3][8] = {"Item1_1", "Item1_2", "Item1_3"};
			PageItemID_TypeDef   mainPage_pagexItemsID[3] = {5,6,5};
			ClickEvent_TypeDef   mainPage_pagexItemsClickEvent[3] = {NullClickEvent, NullClickEvent, NullClickEvent};
			
			PageList_TypeDef pageList[_NUMBER_OF_PAGES] = {&mainPage, &mainPage_pagex};
			
			Menu_PageInit(pageList, &mainPage);
			
*/

Page_TypeDef *Menu_FindPage(uint8_t _page_id)
{
	
	uint8_t page_quantity = 0;
	
	Page_TypeDef **_page_list = g_page_list;
	
	/* ~~~~~~~~~~ Find page by ID ~~~~~~~~~~ */
	while ((page_quantity < _NUMBER_OF_PAGES) && ((**_page_list).ID != _page_id))
	{
		
		page_quantity++;
		*_page_list++;
		
	}
	
	/* ~~~~~~~~~~~~~~~~~~~~ */
	return *_page_list;
	
}
/*
	Guide   :
			Function description	This function is used to find pages.
			
			Parameters
									_page_id : Page ID for find.
			Return Values
									Page with identical ID
			
	Example :
			Page_TypeDef *mypage;
			
			mypage = Menu_FindPage(12);
			
*/

void Menu_ShowPage(Page_TypeDef *_page)
{
	
	uint8_t lcd_line   = 0;
	uint8_t items_show = _page->SelectedItem;
	
	/* ~~~~~~~~~~ Show on LCD ~~~~~~~~~~ */
	_LCD_CLEAR();
	_LCD_GOTOXY(0,0);
	_LCD_PUTCH(_CURRENT_SELECTED_CHAR);
	
	/* ~~~~~~~~~~ Show on LCD ~~~~~~~~~~ */
	for (; lcd_line < _CH_LCD_LINES; lcd_line++)
	{
		
		if (items_show < g_current_page->ItemsQuantity)
		{
			
			_LCD_GOTOXY(1,lcd_line);
			_LCD_PUTS(*_page->ItemsName + (items_show * _page->ItemsNameLength));
			
			/* ~~~~~~~~~~~~~~~~~~~~ */
			items_show++;
			
		}
		
	}
	
}
/*
	Guide   :
			Function description	This function is used to show pages.
			
			Parameters
									_page : Pointer to page for show.
			Return Values
									-
			
	Example :
			Page_TypeDef mypage;
			
			Menu_ShowPage(&mypage);
			
*/

void Menu_ShowCurrentPage(void)
{
	
	uint8_t lcd_line   = 0;
	uint8_t items_show = g_current_page->SelectedItem;
	
	/* ~~~~~~~~~~ Show on LCD ~~~~~~~~~~ */
	_LCD_CLEAR();
	_LCD_GOTOXY(0,0);
	_LCD_PUTCH(_CURRENT_SELECTED_CHAR);
	
	/* ~~~~~~~~~~ Show on LCD ~~~~~~~~~~ */
	for (; lcd_line < _CH_LCD_LINES; lcd_line++)
	{
		
		if (items_show < g_current_page->ItemsQuantity)
		{
			
			_LCD_GOTOXY(1,lcd_line);
			_LCD_PUTS(*g_current_page->ItemsName + (items_show * g_current_page->ItemsNameLength));
			
			/* ~~~~~~~~~~~~~~~~~~~~ */
			items_show++;
			
		}
		
	}
	
}
/*
	Guide   :
			Function description	This function is used to show current page.
			
			Parameters
									-
			Return Values
									-
			
	Example :
			
			Menu_ShowCurrentPage();
			
*/

void Menu_SelectNextItem(Page_TypeDef *_page)
{
	
	if (MenuControl.SelectNextItemEnable == _TRUE)
	{
		
		_page->SelectedItem++;
		
		/* ~~~~~~~~~~ Reset index ~~~~~~~~~~ */
		if(_page->SelectedItem == _page->ItemsQuantity)
		{
			_page->SelectedItem = _page->DefaultItem;
		}
		
	}
	
}
/*
	Guide   :
			Function description	This function is used to select next item of pages.
			
			Parameters
									_page : Pointer to page for select item.
			Return Values
									-
			
	Example :
			Page_TypeDef mypage;
			
			Menu_SelectNextItem(&mypage);
			
*/

void Menu_SelectNextItem_CurrentPage(void)
{
	
	if (MenuControl.SelectNextItemEnable == _TRUE)
	{
		
		g_current_page->SelectedItem++;
		
		/* ~~~~~~~~~~ Reset index ~~~~~~~~~~ */
		if(g_current_page->SelectedItem == g_current_page->ItemsQuantity)
		{
			g_current_page->SelectedItem = g_current_page->DefaultItem;
		}
		
	}
	
}
/*
	Guide   :
			Function description	This function is used to select next item of current page.
			
			Parameters
									-
			Return Values
									-
			
	Example :
			
			Menu_SelectNextItem_CurrentPage();
			
*/

void Menu_SelectPreviousItem_CurrentPage(void)
{
	
	if (MenuControl.SelectPreviousItemEnable == _TRUE)
	{
		
		if(g_current_page->SelectedItem != g_current_page->DefaultItem)
		{
			g_current_page->SelectedItem--;
		}
		
	}
	
}
/*
	Guide   :
			Function description	This function is used to select previous item of current page.
			
			Parameters
									-
			Return Values
									-
			
	Example :
			
			Menu_SelectPreviousItem_CurrentPage();
			
*/

void Menu_OpenSelectedPage(void)
{
	
	uint8_t *page_item = g_current_page->ItemsID;
	
	/* ~~~~~~~~~~~~~~~~~~~~ */
	if (MenuControl.GoToNewPageEnable == _TRUE)
	{
		
		page_item += g_current_page->SelectedItem;
		
		/* ~~~~~~~~~~ Check sub ID ~~~~~~~~~~ */
		if (*page_item != g_current_page->ID)
		{
			
			g_current_page = Menu_FindPage(*page_item);
			
			/* ~~~~~~~~~~~~~~~~~~~~ */
			Menu_ShowCurrentPage();
			
		}
		
	}
	
}
/*
	Guide   :
			Function description	This function is used to open and show new page of selected.
			
			Parameters
									-
			Return Values
									-
			
	Example :
			
			Menu_OpenSelectedPage();
			
*/

void Menu_BackToPreviousPage(void)
{
	
	if (MenuControl.BackToPreviousPageEnable == _TRUE)
	{
		
		/* ~~~~~~~~~~ Check parent ID ~~~~~~~~~~ */
		if (g_current_page->ParentID != g_current_page->ID)
		{
			g_current_page->SelectedItem = g_current_page->DefaultItem;
			
			/* ~~~~~~~~~~ Find page ~~~~~~~~~~ */
			g_current_page = Menu_FindPage(g_current_page->ParentID);
			
			/* ~~~~~~~~~~~~~~~~~~~~ */
			Menu_ShowCurrentPage();
			
		}
		
	}
	
}
/*
	Guide   :
			Function description	This function is used to backward parent page of current page.
			
			Parameters
									-
			Return Values
									-
			
	Example :
			
			Menu_BackToPreviousPage();
			
*/

void Menu_RunClickEvent(void)
{
	
	ClickEvent_TypeDef *clkevent = g_current_page->ClickEvent;
	ClickEvent_TypeDef clkeventrun;
	
	/* ~~~~~~~~~~ Initialize ClickEvent ~~~~~~~~~~ */
	clkevent += g_current_page->SelectedItem;
	clkeventrun = *clkevent;
	
	/* ~~~~~~~~~~~~~~~~~~~~ */
	clkeventrun();
	
}
/*
	Guide   :
			Function description	This function is used to running 'ClickEvent functions of item and pages'.
			
			Parameters
									-
			Return Values
									-
			
	Example :
			
			Menu_RunClickEvent();
			
*/

void NullClickEvent(void){}

