#if !defined(__COLOR_CONSOLE_H) 
#define __COLOR_CONSOLE_H 

// вывод строк в цвете заданных тегов
void SetColor(HANDLE h, char* cbg, char* ctext,
	Ttheme* ptheme);
void PrintColor(HANDLE h, char* s, Ttheme* ptheme);
void SetConsoleColor(char* cbg, char* ctext, Ttheme* ptheme);
size_t StrLengthWithoutColor(char* s, Ttheme* ptheme);
char* GetStrColorCode(char* s, char* cbg, char* ctext);
void PrintColorCenter(HANDLE h, char* s, char* cbg, char* ctext,
	size_t size, Ttheme* ptheme);
void PrintColorWidth(HANDLE h, char* s, char* cbg, char* ctext,
	size_t size, Ttheme* ptheme);

// работа с цветовыми тегами в строках
void CopyColorCodeStr(char* color, char* s);
void GetColorFromStr(char* s, char* cbg, char* ctext);
void CopyColorCodeStrEnd(char* tag, char* s);
void AddColorBg(char* s, char* cbg);
void PrintColorTagWidth(HANDLE h, char* s, char* cbg, char* ctext, size_t size, Ttheme* ptheme);

// цвет мастей карт
void SetColorBySuit(HANDLE h, char m, Ttheme* ptheme);
void GetColorSuit(char* color_suit, char m, Ttheme* ptheme);

#endif 