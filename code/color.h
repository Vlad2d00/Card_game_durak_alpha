#pragma once

// базовые цвета консоли
#define BASE_COLOR_BG BLACK // базовый цвет фона текста в консоли
#define BASE_COLOR_TEXT WHITE // базовый цвет текста в консоли

// изменение цвета текста в консоли
#define TEXT_COLOR(n) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n)
//  изменение цвета фона и текста в консоли
#define COLOR(h, bg, text) SetConsoleTextAttribute(h, (bg << 4) | text)

// список цветов
#define BLACK 0 // черный
#define BLUE 1 // сииний
#define GREEN 2 // зеленый
#define CYAN 3 // голубой
#define RED 4 // красный
#define MAGENTA 5 // пурпурный
#define BROWN 6 // коричневый
#define LIGHTGRAY 7 // светло-серый
#define DARKGRAY 8 // темно-серый
#define LIGHTBLUE 9 // светло-синий
#define LIGHTGREEN 10 // светло-зеленый
#define LIGHTCYAN 11 // светло-голубой
#define LIGHTRED 12 // светло-красный
#define LIGHTMAGENTA 13 // светло-пурпурный
#define YELLOW 14 // желтый
#define WHITE 15 // белый
