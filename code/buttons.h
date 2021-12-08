#if !defined(__BUTTONS_H) 
#define __BUTTONS_H 

#include "header.h"

// работа с указателем консольного окна и курсором мыши
POINT GetSellSize(HWND h);
POINT GetMousePos(HWND h, POINT sellSz);
void SetConsoleCursorCoord(HANDLE h, size_t x, size_t y);
void SetConsoleCursorPoint(HANDLE h, COORD* point,
	size_t x, size_t y);
void MoveConsoleCursorPoint(HANDLE h, COORD* point,
	int dx, int dy);

// большие надписи из символов
char GetLowCh(char ch);
size_t GetSizeLargeWord(char* s);
size_t GetSizeButtonStandart(char* s);
size_t GetSizeButtonMark(char* s);
size_t GetSizeButtonInputNumber(char* s);
void PrintWordLarge(HANDLE h, COORD point, char* s, size_t w);

// вывод изображений кнопок
void PrintImgButton(HANDLE h, COORD point, char* s, size_t w);
void PrintImgPressedButton(HANDLE h, COORD point, char* s, size_t w, Ttheme* ptheme);

// вывод функциональных кнопок
size_t CursoreInBlock(Tblock block);
size_t PrintButtonStandart(HANDLE h, Tblock* pblock, char* s, size_t w, Ttheme* ptheme);
size_t PrintButtonBookRule(HANDLE h, Tblock* pblock, Ttheme* ptheme);
size_t PrintButtonAchievementTable(HANDLE h, Tblock* pblock, Ttheme* ptheme);
size_t PrintButtonCat(HANDLE h, Tblock* pblock, Ttheme* ptheme);

// вывод однострочных кнопкок (высотой в один символ)
size_t PrintWordCursorHover(HANDLE h, Tblock* pblock, char* s, Ttheme* ptheme);
size_t PrintButtonSmall(HANDLE h, Tblock* pblock, char* s, size_t w, Ttheme* ptheme);
size_t PrintButtonMark(HANDLE h, Tblock* pblock, char* s, size_t* pvalue, Ttheme* ptheme);
size_t PrintButtonMarkImg(HANDLE h, Tblock* pblock, void f(HANDLE, COORD),
	size_t* pvalue, Ttheme* ptheme);
size_t PrintElCursorHover(HANDLE h, Tblock* pblock, void f(HANDLE, COORD), Ttheme* ptheme);
PrintCat(HANDLE h, COORD point);
void PrintStrCursorHover(HANDLE h, Tblock* pblock, char* s,
	char* cbg, char* ctext, char* ctarget, Ttheme* ptheme);
char* GetStrWords(char* s_in, size_t maxlen, char* s_out, Ttheme* ptheme);
void PrintStrInBlock(HANDLE h, Tblock block, char* s,
	char* cbg, char* ctext, Ttheme* ptheme);

// формы ввода
size_t InputNumber(HANDLE h, COORD point, size_t w, size_t min,
	size_t max, size_t* pvalue, Ttheme* ptheme);
size_t InputName(HANDLE h, COORD point, size_t w, char* name,
	size_t min, size_t max, char* name_default, Ttheme* ptheme);
size_t PrintButtonInputNumber(HANDLE h, Tblock* pblock, char* s, size_t w,
	size_t* pvalue, size_t min, size_t max, Ttheme* ptheme);

// выпадающий список
int PrintArrButtonSmall(HANDLE h, COORD point, char(*options)[300],
	size_t n, size_t w, Ttheme* ptheme);
void PrintDropDownList(HANDLE h, Tblock* pblock, char* s,
	char(*options)[2][300], size_t n, size_t* pvalue, Ttheme* ptheme);

#endif 