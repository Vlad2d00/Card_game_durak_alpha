#if !defined(__PRINT_ELEMENTS_H) 
#define __PRINT_ELEMENTS_H 

#include "header.h"

void PrintAchievementTable(HANDLE h, COORD point, Ttheme* ptheme);
void PrintImgBookRuleButton(HANDLE h, COORD point);
void PrintTableSimulation(HANDLE h, Tblock block, Ttheme* ptheme);
void PrintImgHeaderMainMenu(HANDLE h, COORD point);
void SetCatMatr(char a[8][WIDTH]);
void PrintMatrPoint(HANDLE h, char(*a)[WIDTH], size_t m, size_t n, COORD point);
void PrintPointerMainMenu(HANDLE h, COORD point);
void PrintSymbolIconSun(HANDLE h, COORD point);
void PrintSymbolIconRain(HANDLE h, COORD point);
void PrintSymbolIconSnow(HANDLE h, COORD point);
void PrintOutlineBlock(HANDLE h, Tblock block);
void PrintTableControlKeys(HANDLE h, COORD point, Ttheme* ptheme);
void PrintImgCardNotColor(HANDLE h, COORD point, Tcard card);
void PrintImgCard(HANDLE h, COORD point, Tcard card, Ttheme* ptheme);
void PrintImgCardColor(HANDLE h, COORD point, Tcard card,
	char* cbg, char* ctext, Ttheme* ptheme);
void PrintShirtCard(HANDLE h, COORD point, Ttheme* ptheme);
void PrintRegionImgCardColor(HANDLE h, COORD point, Tcard card,
	size_t k, size_t n, Ttheme* ptheme);
void PrintSpecialCard(HANDLE h, COORD point);
void PrintRectangle(HANDLE h, Tblock block, char* color, Ttheme* ptheme);
void PrintLargeBook(HANDLE h, COORD point);
void PrintSymbolIconLeft(HANDLE h, COORD point);
void PrintSymbolIconBulb(HANDLE h, COORD point);
void PrintSymbolIconVoice(HANDLE h, COORD point);
void PrintSymbolIconRight(HANDLE h, COORD point);


#endif 