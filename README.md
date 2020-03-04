# menu-manager
Menu Manager library for manage the menu &amp; items with support click event.

### Version : 0.0.0

- #### Type : Embedded Software.

- #### Support : AVR/ARM STM32 series with character_lcd library.

- #### Program Language : C/C++

- #### Properties :

### Initialization and de-initialization functions:
- Menu_PageInit()

### Menu operation functions:
- Menu_FindPage()
- Menu_ShowPage()
- Menu_ShowCurrentPage()
- Menu_SelectNextItem()
- Menu_SelectNextItem_CurrentPage()
- Menu_SelectPreviousItem_CurrentPage()
- Menu_OpenSelectedPage()
- Menu_BackToPreviousPage()
- Menu_RunClickEvent()

### Menu control macros:
- __MENU_EnableBackToPreviousPage
- __MENU_EnableGoToNewPage
- __MENU_EnableSelectNextItem
- __MENU_EnableSelectPreviousItem

- __MENU_DisableBackToPreviousPage
- __MENU_DisableGoToNewPage
- __MENU_DisableSelectNextItem
- __MENU_DisableSelectPreviousItem

## How to use this driver

### The Menu Manager library can be used as follows:
1.1  Set Menu (number of pages - current selected character and required libraries) in the menu_manager_conf.h header, for example:  

       /* ~~~~~~ Pages configuration ~~~~~~ */
       #define _NUMBER_OF_PAGES 3
       
       #define _CURRENT_SELECTED_CHAR '>'
     
       /* ~~~~~~ Required Libraries ~~~~~~~ */ 
       #include "CHARACTER_LCD/character_lcd.h"
       
2.1  Initialize:  
-  Declare Page_TypeDef menu structures, for example:  

       Page_TypeDef mainMenu;
       Page_TypeDef mainMenu_Display;
       Page_TypeDef mainMenu_Sound;
       
-  Declare a PageList_TypeDef page list and set it, for example:

       PageList_TypeDef pageList[_NUMBER_OF_PAGES] = {&mainMenu, &mainMenu_Display, &mainMenu_Sound};

-  Declare (PageItemName_TypeDef - PageItemID_TypeDef & ClickEvent_TypeDef) page informations and set it, for example:

       PageItemName_TypeDef mainMenuItemsName[number of items][max length of items names] = {"Display","Sounds","About"};
       PageItemID_TypeDef   mainMenuItemsID[number of items] = {ID,ID,ID}; 
       ClickEvent_TypeDef   mainMenuItemsClickEvent[number of items] = {Click event,Click event,Click event};
       
          /* ..... Main menu - Display menu ..... */
          PageItemName_TypeDef dispPageItemsName[number of items][max length of items names] = {"Backlight"};
          PageItemID_TypeDef   dispPageItemsID[number of items] = {ID};
          ClickEvent_TypeDef   dispPageItemsClickEvent[number of items] = {ScreenBackLightEnDis_ClickEvent};
          
          /* ..... Main menu - Sound menu ..... */
          ...
          ...
          ...
          
       Tip 1: Each ID is for a page (Page_TypeDef)
       Tip 2: If the ID is the same as the parent ID, it will not enter the new page
       Tip 3: If you do not need to execute your commands in the items click, set the event value to NullClickEvent

-  Declare click event functions, for example:

       void ScreenBackLightEnDis_ClickEvent(void)
       {
          My commands for run in Backlight clicks
       }
       
-  Config & Initialize pages, for example:

       mainMenu.ID = ID of this page;
       mainMenu.ItemsID = mainMenuItemsID;
       mainMenu.ItemsName = mainMenuItemsName;
       mainMenu.ClickEvent = mainMenuItemsClickEvent;
       mainMenu.ItemsQuantity = Number of items;
       mainMenu.ItemsNameLength = Max length of items names;
       mainMenu.ParentID = Parent ID of this page;
       mainMenu.SelectedItem = 0;
       mainMenu.DefaultItem = 0;
       
       mainMenu_Display.ID = ID of this page;
       mainMenu_Display.ItemsID = dispPageItemsID;
       mainMenu_Display.ItemsName = dispPageItemsName;
       mainMenu_Display.ClickEvent = dispPageItemsClickEvent;
       mainMenu_Display.ItemsQuantity = Number of items;
       mainMenu_Display.ItemsNameLength = Max length of items names;
       mainMenu_Display.ParentID = Parent ID of this page (in this example: ID of mainMenu);
       mainMenu_Display.SelectedItem = 0;
       mainMenu_Display.DefaultItem = 0;
       
       mainMenu_Sound ...
       ...
       ...
       
       Menu_PageInit(pageList, &mainMenu);  mainMenu is root page of this example

2.1  Using menu operation functions, for example:  

       void MyBackKey(void)
       {
          Menu_BackToPreviousPage();
       }
       
       void MyUpKey(void)
       {
          Menu_SelectPreviousItem_CurrentPage();
          Menu_ShowCurrentPage(); /* Or using Menu_ShowPage(&page_name) */
       }
       
       void MyEnterKey(void)
       {
          Menu_RunClickEvent();
          Menu_OpenSelectedPage();
          /*  */
       }
       
       void MyDownKey(void)
       {
          Menu_SelectNextItem_CurrentPage(); /* Or using Menu_SelectNextItem(&page_name) */
          Menu_ShowCurrentPage(); /* Or using Menu_ShowPage(&page_name) */
       }
       

#### Developer: Majid Derhambakhsh
