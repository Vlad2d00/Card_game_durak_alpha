#include <windows.h>
#include <stdio.h>
#include "color.h"
#include "header.h"

// ошибок нет
const int noError = 0;
// неправильное значение цвета
const int wrongColorValue = 1;

int colorError = 0;

/*возвращает код цвета color или код базового 
цвета цветовой темы струтктуры по адресу ptheme, 
если код цвета ему соотвтствует*/
static char GetCodeColor(char* color, Ttheme* ptheme) {
	if (color[0] == 'l' && color[1] == 'i' && color[2] == 'g' 
		&& color[3] == 'h' && color[4] == 't') {
		color += 5;
		if (!strcmp(color, "gray")) // 7
			return LIGHTGRAY;
		else if (!strcmp(color, "blue")) // 9
			return LIGHTBLUE;
		else if (!strcmp(color, "green")) // 10
			return LIGHTGREEN;
		else if (!strcmp(color, "cyan")) // 11
			return LIGHTCYAN;
		else if (!strcmp(color, "red")) // 12
			return LIGHTRED;
		else if (!strcmp(color, "magenta")) // 13
			return LIGHTMAGENTA;

	} else if (color[0] == 'b' && color[1] == 'g') {
		color += 2;
		if (!strcmp(color, "base"))
			return GetCodeColor(ptheme->colorBgBase, ptheme);
		else if (!strcmp(color, "msg"))
			return GetCodeColor(ptheme->colorBgMsg, ptheme);
		else if (!strcmp(color, "target"))
			return GetCodeColor(ptheme->colorBgTarget, ptheme);

	} else if (color[0] == 't' && color[1] == 'e' 
		&& color[2] == 'x' && color[3] == 't') {
		color += 4;
		if (!strcmp(color, "base"))
			return GetCodeColor(ptheme->colorTextBase, ptheme);
		else if (!strcmp(color, "msg"))
			return GetCodeColor(ptheme->colorTextMsg, ptheme);
		else if (!strcmp(color, "target"))
			return GetCodeColor(ptheme->colorTextTarget, ptheme);

	} else if (color[0] == 's' && color[1] == 'u'
		&& color[2] == 'i' && color[3] == 't') {
		color += 4;
		if (!strcmp(color, "1"))
			return GetCodeColor(ptheme->colorSuit1, ptheme);
		else if (!strcmp(color, "2"))
			return GetCodeColor(ptheme->colorSuit2, ptheme);

	} else {
		if (!strcmp(color, "black")) // 0
			return BLACK;
		else if (!strcmp(color, "blue")) // 1
			return BLUE;
		else if (!strcmp(color, "green")) // 2
			return GREEN;
		else if (!strcmp(color, "cyan")) // 3
			return CYAN;
		else if (!strcmp(color, "red")) // 4
			return RED;
		else if (!strcmp(color, "magenta")) // 5
			return MAGENTA;
		else if (!strcmp(color, "brown")) // 6
			return BROWN;
		else if (!strcmp(color, "darkgray")) // 8
			return DARKGRAY;
		else if (!strcmp(color, "yellow")) // 14
			return YELLOW;
		else if (!strcmp(color, "white")) // 15
			return WHITE;
		else
			colorError = wrongColorValue;
	}
}

/*установление цвета последующего фона текста в 
консоли с дескриптором h на bg и цвета текста на 
text цветовой темы струтктуры по адресу ptheme*/
void SetColor(HANDLE h, char* cbg, char* ctext, 
	Ttheme* ptheme) {
	char code_color_bg, code_color_text;
	code_color_bg = GetCodeColor(cbg, ptheme);
	if (!colorError) {
		code_color_text = GetCodeColor(ctext, ptheme);
		if (!colorError) {
			COLOR(h, code_color_bg, code_color_text);
		} else {
			colorError = noError;
		}
	} else {
		colorError = noError;
	}
}

/*вывод в консоль по адресу h строки s, выводя все ее
символы после подстроки "\\<цвет текста>-<фон текста>"
или "\\<цвет текста>" в соответствующем цвете, пока
не встретится другой такой код с другим цветом, или
пока не достигнут конец строки, уставливая после этого
цвет вывода последующего текста с цветовой темой 
струтктуры по адресу ptheme*/
void PrintColor(HANDLE h, char* s, Ttheme* ptheme) {
	char color[SIZE];
	char* pcolor;
	char code_color_bg, code_color_text;
	colorError = noError;

	while (*s) {
		if (*s == '\\') {
			if (*(s + 1) && *(s + 1) == '\\') {
				putchar(*s);
				s++;
			}
			else {
				pcolor = color;
				s++;
				while (*s && *s != ':' && *s != '-' && *s > ' ' && *s != '\\') {
					*pcolor++ = *s++;
				}
				*pcolor++ = '\0';

				code_color_text = GetCodeColor(color, ptheme);
				if (!colorError) {
					if (*s == ':') {
						code_color_bg = GetCodeColor(ptheme->colorBgBase, ptheme);
					} else if (*s == '-') {
						pcolor = color;
						s++;
						while (*s && *s != ':') {
							*pcolor++ = *s++;
						}
						*pcolor++ = '\0';
						code_color_bg = GetCodeColor(color, ptheme);
					}
					if (!colorError && *s == ':') {
						COLOR(h, code_color_bg, code_color_text);
						if (!*s)
							return;
					} else {
						colorError = noError;
						printf("\\%s", color);
						if (!*s)
							return;
						s--;
					}
				} else {
					colorError = noError;
					printf("\\%s", color);
					if (!*s)
						return;
					s--;
				}
			}
		} else {
			putchar(*s);
		}
		s++;
	}
	SetColor(h, ptheme->colorBgBase, ptheme->colorTextBase, ptheme);
}

/*установление основного цвета фона консоли на cbg 
и основоного цвета текста на ctext с цветовой темой 
струтктуры по адресу ptheme*/
void SetConsoleColor(char* cbg, char* ctext, Ttheme* ptheme) {
	char s[9] = "color ";
	char code_color = GetCodeColor(cbg, ptheme);

	if (code_color >= BLACK && code_color <= WHITE) {
		if (code_color >= 10)
			code_color += 'A' - 10;
		else
			code_color += '0';
		s[6] = code_color;

		code_color = GetCodeColor(ctext, ptheme);
		if (code_color >= BLACK && code_color <= WHITE) {
			if (code_color >= 10)
				code_color += 'A' - 10;
			else
				code_color += '0';
			s[7] = code_color;
			s[8] = '\0';
		} else
			colorError = wrongColorValue;
	} else
		colorError = wrongColorValue;

	system(s);
}

/*возвращает длину строки s без учета кодов 
цвета с цветовой темой струтктуры по адресу ptheme*/
size_t StrLengthWithoutColor(char* s, Ttheme* ptheme) {
	char color[WIDTH];
	char* pcolor;
	size_t i = 0, j;
	char* ps = s;
	colorError = noError;

	while (*s) {
		if (*s == '\\') {
			if (*(s + 1) && *(s + 1) == '\\') {
				i++;
				s++;
			}
			else {
				s++;
				j = 1;
				pcolor = color;

				while (*s && *s != ':' && *s != '-') {
					*pcolor++ = *s++;
					j++;
				}
				*pcolor++ = '\0';
				j++;
				GetCodeColor(color, ptheme);
				if (!colorError) {
					if (*s && *s != ':') {
						pcolor = color;
						s++;
						while (*s && *s != ':') {
							*pcolor++ = *s++;
							j++;
						}
						j++;
						*pcolor++ = '\0';
						GetCodeColor(color, ptheme);
					}
					if (colorError) {
						colorError = noError;
						i += j;
						s--;
					}
				} else {
					colorError = noError;
					i += j;
					s--;
				}
			}
		} else
			i++;
		s++;
	}
	return i;
}

/*запись в строку s текста кода цвета фона 
cbg и текста ctext, возвращая указатель на 
конец строки*/
char* GetStrColorCode(char* s, char* cbg, char* ctext) {
	*s++ = '\\';
	*s = '\0';
	s = strcat(s, cbg);
	*s++ = '-';
	*s = '\0';
	s = strcat(s, ctext);
	*s++ = ':';
	*s = '\0';
	return s;
}

/*вывод в консоли в дескриптором h строки s с
цветом фона cbg и цветом текста ctext, центрируя
ее в блоке длины size, уставливая после этого
цвет вывода последующего текста в соответствии с 
цветовой темой струтктуры по адресу ptheme*/
void PrintColorCenter(HANDLE h, char* s, char* cbg, char* ctext, 
	size_t size, Ttheme* ptheme) {
	size_t len = StrLengthWithoutColor(s, ptheme);
	char stmp[SIZE];
	char* pstmp = stmp;
	size_t d; // отступы с краев
	d = len > size ? 0 : (size - len) / 2;

	pstmp = GetStrColorCode(pstmp, cbg, cbg);
	for (size_t i = 0; i < d; i++) {
		*pstmp++ = ' ';
	}
	pstmp = GetStrColorCode(pstmp, ctext, cbg);
	pstmp = strcat(pstmp, s);
	pstmp = GetStrColorCode(pstmp, cbg, cbg);
	for (size_t i = 0; i < d; i++) {
		*pstmp++ = ' ';
	}
	if (len + 2 * d < size)
		*pstmp++ = ' ';

	*pstmp++ = '\n';
	*pstmp = '\0';
	PrintColor(h, stmp, ptheme);
}

/*вывод в консоли в дескриптором h строки s с цветом фона 
cbg и цветом текста ctext, прижимая ее к левому краю 
блока длины size, уставливая после этого цвет вывода 
последующего текста в соответствии с цветовой темой 
струтктуры по адресу ptheme*/
void PrintColorWidth(HANDLE h, char* s, char* cbg, char* ctext,
	size_t size, Ttheme* ptheme) {
	size_t len = StrLengthWithoutColor(s, ptheme);
	char stmp[SIZE];
	char* pstmp = stmp;
	size_t d; // отступ с правого края
	d = len > size ? 0 : size - len;

	pstmp = GetStrColorCode(pstmp, ctext, cbg);
	pstmp = strcat(pstmp, s);
	pstmp = GetStrColorCode(pstmp, cbg, cbg);
	for (size_t i = 0; i < d; i++) {
		*pstmp++ = ' ';
	}
	*pstmp++ = '\n';
	*pstmp = '\0';
	PrintColor(h, stmp, ptheme);
}

/*запись в строку tag всех символов из строки s, которые 
лежат в первом интервале от '\\' до ':' включительно, иначе, 
если такой подстроки нет, записывает пустую строку, возвращая 
указатель на последний считанный символ*/
char* CopyColorCodeStr(char* tag, char* s) {
	// пропуск ненужных символов
	while (*s && *s == '\\' && *(s + 1) && *(s + 1) == '\\')
		s += 2;
	while (*s && *s != '\\') {
		s++;
		while (*s && *s == '\\' && *(s + 1) && *(s + 1) == '\\')
			s += 2;
	}
	flagCopyColorCodeStr:
	if (*s == '\\') {
		// получение слова
		while (*s && *s != ':' && *s > ' ') {
			*tag++ = *s++;
		}
		if (*s == ':')
			*tag++ = ':';
	}
	*tag = '\0';
	return s;
}

/*запись из строки тега цвета s в строку cbg текста кода 
цвета фона и в строку ctext текста кода цвета*/
void GetColorFromStr(char* s, char* cbg, char* ctext) {
	while (*s && *s != '\\')
		s++;
	if (*s == '\\') {
		if (*(s + 1) && *(s + 1) == '\\') {
			putchar(*s);
			s++;
		}
		else {
			s++;
			char* ps = s;
			// поиск подстроки кода цвета текста
			while (*s && *s != '-' && *s != ':' && *s > ' ')
				s++;
			if (*s && *s > ' ') {
				size_t d = s - ps;
				strncpy(ctext, ps, d);
				ctext[d] = '\0';
				if (*s == '-') {
					s++;
					char* ps = s;
					// поиск подстроки кода цвета фона
					while (*s && *s != ':' && *s > ' ')
						s++;
					if (*s && *s > ' ') {
						d = s - ps;
						strncpy(cbg, ps, d);
						cbg[d] = '\0';
					}
				}
			}
		}
	}
	return s;
}

/*запись в строку tag всех символов из строки s,
которые лежат в последнем интервале от '\' до ':' включительно, 
иначе, если такой подстроки нет, записывает пустую строку*/
void CopyColorCodeStrEnd(char* tag, char* s) {
	*tag = '\0';
	char tmp_tag[50];
	s = CopyColorCodeStr(tmp_tag, s);
	while (*tmp_tag != '\0') {
		strcpy(tag, tmp_tag);
		s = CopyColorCodeStr(tmp_tag, s);
	}
}

/*запись в строку s, ко всем командам установления
цвета текста, код цвета фона текста cbg*/
void AddColorBg(char* s, char* cbg) {
	size_t i = 0;
	while (s[i]) {
		if (s[i] == '\\') {
			while (s[i] && s[i] != ':' && s[i] != '-')
				i++;
			if (s[i] == ':') {
				size_t len_cbg = strlen(cbg);
				size_t len_s = strlen(s);
				size_t len_new_s = len_s + len_cbg + 1;
				s[len_new_s] = '\0';

				size_t j1 = len_s - 1, j2 = len_new_s - 1;
				while (j1 > i) {
					s[j2--] = s[j1--];
				}
				s[i++] = '-';
				char* pcbg = cbg;
				while (*pcbg) {
					s[i++] = *pcbg++;
				}
				s[i] = ':';
			}
		}
		if (s[i])
			i++;
	}
}

/*вывод в консоли в дескриптором h строки s с цветом фона
cbg и цветом текста ctext, выводя теги темно-серым цветом,
а последующий после них текс в цвете, соответствующим
этим тегам, прижимая ее к левому краю блока длины size,
уставливая после этого цвет вывода последующего текста в
соответствии с цветовой темой струтктуры по адресу ptheme*/
void PrintColorTagWidth(HANDLE h, char* s, char* cbg, char* ctext, size_t size, Ttheme* ptheme) {
	size_t len = strlen(s);
	size_t d; // отступ с правого края
	d = len > size ? 0 : size - len;

	char tag[50];
	*tag = '\0';
	char stmp[SIZE];
	*stmp = '\0';
	char* p1stmp = stmp + strlen(stmp);
	char* p2stmp = p1stmp;
	char* p0stmp = p1stmp;
	while (*s) {
		*p1stmp++ = *s++;
	}
	*p1stmp = '\0';
	p1stmp = stmp; // символ после изначального тега цвета

	SetColor(h, cbg, ctext, ptheme);
	while (*p2stmp) {
		if (*p2stmp == '\\') {
			// вывод символов до тега
			char ch = *p2stmp; // временое сохранение символа
			*p2stmp = '\0';
			printf("%s", p1stmp);
			*p2stmp = ch;

			// вывод темно-серым цветом тега
			p2stmp = CopyColorCodeStr(tag, p2stmp);
			SetColor(h, cbg, "darkgray", ptheme);
			printf("%s", tag);
			if (*p2stmp == ':')
				p2stmp++;
			else
				SetColor(h, cbg, ctext, ptheme);

			// вывод последующего текста с цветом тега
			char new_cbg[50], new_ctext[50];
			*new_cbg = '\0';
			*new_ctext = '\0';
			GetColorFromStr(tag, new_cbg, new_ctext);
			if (*new_cbg == '\0')
				strcpy(new_cbg, cbg);
			SetColor(h, new_cbg, new_ctext, ptheme);
			p1stmp = p2stmp;
		} else
			p2stmp++;
	}
	*p2stmp = '\0';
	if (*p2stmp != '\0')
		SetColor(h, cbg, "darkgray", ptheme);
	printf("%s", p1stmp);

	for (size_t i = 0; i < d; i++) {
		*p0stmp++ = ' ';
	}
	*p0stmp = '\0';
	SetColor(h, cbg, ctext, ptheme);
	PrintColor(h, stmp, ptheme);
}

/*устанавливает цвет текста консоли с дескриптором h
на цвет, соответствующий теме ptheme*/
void SetColorBySuit(HANDLE h, char m, Ttheme* ptheme) {
	if (m == 'ч' || m == 'б')
		SetColor(h, ptheme->colorBgBase, ptheme->colorSuit1, ptheme);
	else
		SetColor(h, ptheme->colorBgBase, ptheme->colorSuit2, ptheme);
}

/*записывает в строку color_suit цвет масти 
карты m, соответствующий теме ptheme*/
void GetColorSuit(char* color_suit, char m, Ttheme* ptheme) {
	if (m == 'ч' || m == 'б')
		strcpy(color_suit, ptheme->colorSuit1);
	else
		strcpy(color_suit, ptheme->colorSuit2);
}
