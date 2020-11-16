![Banner](Menu-Manager.png)

# menu-manager
Menu Manager library for manage the menu &amp; items with support click event.

### [V0.0.0 Guide](https://github.com/Majid-Derhambakhsh/menu-manager/blob/master/README-V0.0.0.md)
### Version : 0.1.0

- #### Type : Embedded Software.

- #### Support : AVR/ARM STM32 series with character_lcd library.

- #### Program Language : C/C++

- #### Properties :

### Initialization and de-initialization functions:
```c++
void Menu_PageInit(Page_TypeDef **_page_list, Page_TypeDef *_root_page);
``` 

### Menu operation functions:
```c++
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
``` 

### Macros:
```c++
#define _USE_LCD_DISPLAY
#define _USE_7SEGMENT_DISPLAY

#define _NMB_OF_DISPLAY_LINES
#define _NMB_OF_DISPLAY_COLUMN

#define _7SEGMENT_DISPLAY

#define _MENU_PUTS(x)
#define _MENU_PUTCH(x)
#define _MENU_CLEAR()
#define _MENU_GOTOXY(x,y)

#define _MENU_CLREARING_DISABLE
#define _MENU_CURSOR_DISABLE
#define _MENU_WARNINGS_DISABLE

#define _MENU_CURSOR_CHAR
``` 

### Menu control macros:
```c++
#define __MENU_EnableBackToPreviousPage
#define __MENU_EnableGoToNewPage
#define __MENU_EnableSelectNextItem
#define __MENU_EnableSelectPreviousItem

#define __MENU_DisableBackToPreviousPage
#define __MENU_DisableGoToNewPage
#define __MENU_DisableSelectNextItem
#define __MENU_DisableSelectPreviousItem
``` 

## How to use this driver

### The Menu Manager library can be used as follows:
1.1  Menu configuration in the menu_manager_conf.h header, for example:  
   * Options for 16*2 Alphanumeric LCD ([use Character-Lcd library](https://github.com/Majid-Derhambakhsh/Character-Lcd)):  
   
      ```c++
      /* ~~~~~~~~~~~~~~~~~~~~~~~~~ Options ~~~~~~~~~~~~~~~~~~~~~~~~~ */

      /* ~~~~~~~~~~~~ Add required libraries ~~~~~~~~~~~~ */
      #include "CHARACTER_LCD/character_lcd.h"

      /* ~~~~~~~~~~~~ Add required namespace ~~~~~~~~~~~~ */
      //using namespace x;

      /* ~~~~~~~~~~~~~~~ Add Your OBJ/VAR ~~~~~~~~~~~~~~~ */
      //extern x y;

      /* ~~~~~~~~~~~~ Display configurations ~~~~~~~~~~~~ */
      #define _USE_LCD_DISPLAY
      //#define _USE_7SEGMENT_DISPLAY

      #define _NMB_OF_DISPLAY_LINES  2
      #define _NMB_OF_DISPLAY_COLUMN 16

      //#define _7SEGMENT_DISPLAY xDisplay

      /* ~~~~~~~ Add your custom display methods ~~~~~~~~ */
      //#define _MENU_PUTS(x)     Lcd_PutString(x)
      //#define _MENU_PUTCH(x)    Lcd_PutChar(x)
      //#define _MENU_CLEAR()     Lcd_Clear()
      //#define _MENU_GOTOXY(x,y) Lcd_GotoXY(x,y)

      /* ~~~~~~~~~~~ Library configurations ~~~~~~~~~~~~~ */
      //#define _MENU_CLREARING_DISABLE
      //#define _MENU_CURSOR_DISABLE
      //#define _MENU_WARNINGS_DISABLE

      #define _MENU_CURSOR_CHAR '>'      
      ```
      
   * Options for 7Segment with 4 column ([use 7Segment-Library](https://github.com/Majid-Derhambakhsh/7Segment-Library)):  
   
      ```c++
      /* ~~~~~~~~~~~~~~~~~~~~~~~~~ Options ~~~~~~~~~~~~~~~~~~~~~~~~~ */

      /* ~~~~~~~~~~~~ Add required libraries ~~~~~~~~~~~~ */
      #include "SevenSegment/seven_segment.h"

      /* ~~~~~~~~~~~~ Add required namespace ~~~~~~~~~~~~ */
      using namespace Display;

      /* ~~~~~~~~~~~~~~~ Add Your OBJ/VAR ~~~~~~~~~~~~~~~ */
      extern SSegment MainDisplay;

      /* ~~~~~~~~~~~~ Display configurations ~~~~~~~~~~~~ */
      //#define _USE_LCD_DISPLAY
      #define _USE_7SEGMENT_DISPLAY

      #define _NMB_OF_DISPLAY_LINES  1
      #define _NMB_OF_DISPLAY_COLUMN 4

      #define _7SEGMENT_DISPLAY MainDisplay

      /* ~~~~~~~ Add your custom display methods ~~~~~~~~ */
      //#define _MENU_PUTS(x)     Lcd_PutString(x)
      //#define _MENU_PUTCH(x)    Lcd_PutChar(x)
      //#define _MENU_CLEAR()     Lcd_Clear()
      //#define _MENU_GOTOXY(x,y) Lcd_GotoXY(x,y)

      /* ~~~~~~~~~~~ Library configurations ~~~~~~~~~~~~~ */
      #define _MENU_CLREARING_DISABLE
      //#define _MENU_CURSOR_DISABLE
      //#define _MENU_WARNINGS_DISABLE

      #define _MENU_CURSOR_CHAR '-'      
      ```  
      
2.1  Initialize:  
-  Declare Page_TypeDef menu structures, for example:  
      ```c++
       Page_TypeDef mainMenu;
       Page_TypeDef mainMenu_Display;
       Page_TypeDef mainMenu_Sound;
      ``` 
       
-  Declare a PageList_TypeDef page list and set it, for example:
      ```c++
       PageList_TypeDef pageList[number of pages] = {&mainMenu, &mainMenu_Display, &mainMenu_Sound};
      ``` 

-  Declare (PageItemName_TypeDef - PageItemID_TypeDef & ClickEvent_TypeDef) page informations and set it, for example:
      ```c++
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
      ``` 
      * Tips   
       Tip 1: Each ID is for a page (Page_TypeDef)   
       Tip 2: If the ID is the same as the parent ID, it will not enter the new page   
       Tip 3: If you do not need to execute your commands in the items click, set the event value to NullClickEvent   

-  Declare click event functions, for example:
      ```c++
       void ScreenBackLightEnDis_ClickEvent(void)
       {
          // My commands for run in Backlight clicks
       }
      ``` 
      
-  Config & Initialize pages, for example:
      ```c++
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
      ``` 
      
3.1  Using menu operation functions, for example:  
```c++
   void MyBackKey(void)
   {
      Menu_BackToPreviousPage();
   }
       
   void MyUpKey(void)
   {
      Menu_SelectPreviousItem_CurrentPage();
   }
       
   void MyEnterKey(void)
   {
      Menu_RunClickEvent();
      Menu_OpenSelectedPage();
   }
       
   void MyDownKey(void)
   {
      Menu_SelectNextItem_CurrentPage(); /* Or using Menu_SelectNextItem(&page_name) */
   }
       
```

#### Developer: Majid Derhambakhsh
