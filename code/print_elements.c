#if !defined(__PRINT_ELEMENTS_H) 
#define __PRINT_ELEMENTS_H 

#include "header.h"

/*вывод в окне с дескриптором h таблицы достижений в точке point*/
void PrintAchievementTable(HANDLE h, COORD point, Ttheme* ptheme) {
	COORD point_base = point;
	MoveConsoleCursorPoint(h, &point, 4, -1);
	printf("_");
	MoveConsoleCursorPoint(h, &point, 30, 0);
	printf("_");
	MoveConsoleCursorPoint(h, &point, -34, 1);
	printf(" __|_|_______________  __________|_|_");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                    \\//             \\");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                                     |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                                     |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                                     |");
	MoveConsoleCursorPoint(h, &point, 1, -3);
	PrintWordLarge(h, point, "новости", 35);
	MoveConsoleCursorPoint(h, &point, 19, 0);
	printf("\\//");
	MoveConsoleCursorPoint(h, &point, -20, 4);
	printf("\\_____________________________________|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("/                                     |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|__,__________________________________|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|  \\                              \\   |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|___\\ _____________________________/__|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|    \\/                          /_   |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|_____________________________________|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                                     |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|_\\______________________/\\___________|");
	MoveConsoleCursorPoint(h, &point, 3, 1);
	printf("| /");
	MoveConsoleCursorPoint(h, &point, 31, 0);
	printf("\\ |");
	for (size_t i = 0; i < 3; i++) {
		MoveConsoleCursorPoint(h, &point, -31, 1);
		printf("| |");
		MoveConsoleCursorPoint(h, &point, 31, 0);
		printf("| |");
	}
	MoveConsoleCursorPoint(h, &point, -31, 1);
	printf("|_|");
	MoveConsoleCursorPoint(h, &point, 31, 0);
	printf("|_|");

	COORD point0;
	char s[100], s_space[50];
	point0.X = point_base.X + 1;
	point0.Y = point_base.Y + 4;

	sprintf(s, "игрока %s", ptheme->userName);
	GetStrSingleChar(s_space, ' ', (37 - strlen(s)) / 2);
	SetConsoleCursorPosition(h, point0);
	printf("%s%s", s_space, s);

	point0.Y = point_base.Y + 6;
	if (ptheme->raiting < 1400)
		sprintf(s, "Рейтинг: %u (новичок)", ptheme->raiting);
	else if (ptheme->raiting < 2100)
		sprintf(s, "Рейтинг: %u (опытный)", ptheme->raiting);
	else if (ptheme->raiting < 3000)
		sprintf(s, "Рейтинг: %u (подмастерье)", ptheme->raiting);
	else if (ptheme->raiting < 3850)
		sprintf(s, "Рейтинг: %u (мастер)", ptheme->raiting);
	else if (ptheme->raiting < 4300)
		sprintf(s, "Рейтинг: %u (прфессионал)", ptheme->raiting);
	else
		sprintf("Рейтинг: %u (бог)", ptheme->raiting);
	GetStrSingleChar(s_space, ' ', (37 - strlen(s)) / 2);
	SetConsoleCursorPosition(h, point0);
	printf("%s%s", s_space, s);

	point0.X = point_base.X + 12;
	point0.Y = point_base.Y + 8;
	SetConsoleCursorPosition(h, point0);
	printf("Кол-во побед: %u", ptheme->countWins);

	point0.X = point_base.X + 10;
	point0.Y = point_base.Y + 10;
	SetConsoleCursorPosition(h, point0);
	printf("Кол-во поражений: %u", ptheme->countLose);

	point0.X = point_base.X + 1;
	point0.Y = point_base.Y + 12;
	if (ptheme->minutsInGame < 60)
		sprintf(s, "В игре: %u минут", ptheme->minutsInGame);
	else if (ptheme->minutsInGame < 1440)
		sprintf(s, "В игре: %u час %u минут", ptheme->minutsInGame / 60,
			ptheme->minutsInGame % 60);
	else
		sprintf(s, "В игре: %u дней %u час %u минут", ptheme->minutsInGame / 1440,
			ptheme->minutsInGame / 60 % 24, ptheme->minutsInGame % 60);
	GetStrSingleChar(s_space, ' ', (37 - strlen(s)) / 2);
	SetConsoleCursorPosition(h, point0);
	printf("%s%s", s_space, s);
}

/*вывод в окне с дескриптором h изображения книги правил
правила в точке point*/
void PrintImgBookRuleButton(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf(" _________ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("/\\ справка\\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("\\ \\________\\");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" \\/________/");
}

/*вывод в окне с дескриптором h таблицы с кнопками
выбора ИИ для игроков в блоке block*/
void PrintTableSimulation(HANDLE h, Tblock block, Ttheme* ptheme) {
	COORD point = block.pos;
	SetConsoleCursorPosition(h, point);
	SetColor(h, "bgmsg", "textmsg", ptheme);
	printf(".---------------------------------------------------------------.");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("| ? | № ИГРОКА |       УРОВЕНЬ ИГРЫ      |         ИМЯ          |");
	for (size_t i = 0; i < 6; i++) {
		MoveConsoleCursorPoint(h, &point, 0, 1);
		printf("|---|----------|-------------------------|----------------------|");
		MoveConsoleCursorPoint(h, &point, 0, 1);
		printf("|                                                               |");
	}
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("'---------------------------------------------------------------'");
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*вывод в окне с дескриптором h заголовка
"card game durak" в позицию point*/
void PrintImgHeaderMainMenu(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("   ___              _                                   ___                 _    \n");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  / __\\__ _ _ __ __| |   __ _  __ _ _ __ ___   ___     /   \\_   _ _ __ __ _| | __\n");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" / /  / _` | '__/ _` |  / _` |/ _` | '_ ` _ \\ / _ \\   / /\\ / | | | '__/ _` | |/ /\n");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("/ /__| (_| | | | (_| | | (_| | (_| | | | | | |  __/  / /_//| |_| | | | (_| |   < \n");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("\\____/\\__,_|_|  \\__,_|  \\__, |\\__,_|_| |_| |_|\\___| /___,'  \\__,_|_|  \\__,_|_|\\_\\\n");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("                        |___/                                                    \n");
}

/*запись в матрицу a размера 8 x 15 изображения кота*/
void SetCatMatr(char a[8][WIDTH]) {
	char s_cat[] = "\
        />__/> \
       | _  _\\ \
      (`= _x =)\
     /       / \
 __/ `      )  \
/  _    | | |  \
| (_ \\___`_)_) \
 \\__>          \
\0";
	size_t k = 0;
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 15; j++) {
			a[i][j] = s_cat[k++];
		}
	}
}

/*вывод в окне с дескриптором h матрицы a размера 
m x n в с начлаом в точке point*/
void PrintMatrPoint(HANDLE h, char (*a)[WIDTH], size_t m, size_t n, COORD point) {
	int j, k;
	size_t baseX = point.X;
	for (size_t i = 0; i < m; i++) {
		j = 0;
		while (j < n && a[i][j] == ' ') {
			j++;
		}
		k = n - 1;
		while (k >= 0 && a[i][k] == ' ') {
			k--;
		}

		point.X = baseX + j;
		SetConsoleCursorPosition(h, point);
		while (j <= k) {
			printf("%c", a[i][j++]);
		}
		point.Y++;
	}
}

/*вывод в окне с дескриптором h изображения
указателя главного меню в позицию point*/
void PrintPointerMainMenu(HANDLE h, COORD point) {
	MoveConsoleCursorPoint(h, &point, -7, 1); // 1 строка начало
	printf("       ");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 2 строка начало
	printf("  /\\   ");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 3 строка начало
	printf(" /  \\  ");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 4 строка начало
	printf("(_  _) ");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 5 строка начало
	printf(" /__\\  ");
}

/*вывод в окне с дескриптором h иконки сонлца из символов
размера 6 x 13 в точке point*/
void PrintSymbolIconSun(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("      |      ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" \\ \\ ___/  / ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("_  /     \\ _ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" _|       | _");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   \\ ___ /   ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  /   |   \\  ");
}

/*вывод в окне с дескриптором h иконки дождя из символов
размера 6 x 13 в точке point*/
void PrintSymbolIconRain(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("\\  \\  \\    \\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     \\   \\  \\");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("\\  \\    \\    ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  \\  \\  \\  \\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  \\  \\  \\  \\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" _x %%_ __x%% x");
}

/*вывод в окне с дескриптором h иконки снегопада из символов
размера 6 x 13 в точке point*/
void PrintSymbolIconSnow(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf(" *    *   *  ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  *   *  *  *");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   * *    *  ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" *   *  *  * ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  **   *  *  ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  *    *     ");
}

/*вывод в окне с дескриптором h символьной обводки вокруг блока block*/
void PrintOutlineBlock(HANDLE h, Tblock block) {
	char outline[WIDTH];
	COORD point = block.pos;
	point.X--;
	point.Y--;
	GetStrSingleChar(outline, '-', block.lenX);
	SetConsoleCursorPosition(h, point);
	printf(".%s.", outline);

	for (size_t i = 0; i < block.lenY; i++) {
		MoveConsoleCursorPoint(h, &point, 0, 1);
		printf("|");
	}
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("'%s'", outline);

	MoveConsoleCursorPoint(h, &point, block.lenX + 1, 0);
	for (size_t i = 0; i < block.lenY; i++) {
		MoveConsoleCursorPoint(h, &point, 0, -1);
		printf("|");
	}
}

/*вывод в окне с дескриптором h таблицы управляющих клавиш
игры в точке point с цветовой темой структуры по адресу ptheme*/
void PrintTableControlKeys(HANDLE h, COORD point, Ttheme* ptheme) {
	SetColor(h, "bgbase", "textbase", ptheme);
	SetConsoleCursorPosition(h, point);
	printf(" _______  ___________________________________________");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|       \\/                              /\\_          |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                УПРАВЛЯЮЩИЕ КЛАВИШИ:   \\_\\      ____/");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Space]\\textbase-bgbase: - подтвердить выбор.                        |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Esc]\\textbase-bgbase: - отменить выбор карты / выйти в меню.        |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[\"стрелки\"]\\textbase-bgbase: - перемещение между кнопками и картами. |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Shift]\\textbase-bgbase: - пас / подтверждение конца хода.           |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Enter]\\textbase-bgbase: - подтвердить ввод текста / числа.          |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Tab]\\textbase-bgbase: - открыть поле ввода чата / отменить ввод.    |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Backspace]\\textbase-bgbase: - удалить последний символ поле ввода.  |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Ctrl]\\textbase-bgbase: + \\bgbase-textbase:[\"колесо мыши\"]\\textbase-bgbase: - изменить масштабы окна.  |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|________________________________/ \\\\________________|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("------| |------------------------------------| |------");
	MoveConsoleCursorPoint(h, &point, 6, 1);
	printf("| |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|_|");
	MoveConsoleCursorPoint(h, &point, 39, -1);
	printf("| |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|_|");
}

/*вывод в окне с дескриптором h в точку
point изображение карты card*/
void PrintImgCardNotColor(HANDLE h, COORD point, Tcard card) {
	SetConsoleCursorPosition(h, point); // 1-я строка
	printf(" _________ ");

	MoveConsoleCursorPoint(h, &point, 0, 1); // 2-я строка
	if (card.n <= 10)
		printf("|%2u       |", card.n);
	else
		printf("| %c       |", GetCharDigintyCard(card.n));

	MoveConsoleCursorPoint(h, &point, 0, 1); // 3-я строка
	switch (card.m) {
	case 'ч': printf("|  _  _   |"); break;
	case 'п': printf("|   /\\    |"); break;
	case 'к': printf("|    _    |"); break;
	case 'б': printf("|   / \\   |"); break;
	}
	MoveConsoleCursorPoint(h, &point, 0, 1); // 4-я строка
	switch (card.m) {
	case 'ч': printf("| ( \\/ )  |"); break;
	case 'п': printf("|  /  \\   |"); break;
	case 'к': printf("|  _| |_  |"); break;
	case 'б': printf("|  /   \\  |"); break;
	}

	MoveConsoleCursorPoint(h, &point, 0, 1); // 5-я строка
	switch (card.m) {
	case 'ч': printf("|  \\  /   |"); break;
	case 'п': printf("| (_  _)  |"); break;
	case 'к': printf("| (_   _) |"); break;
	case 'б': printf("|  \\   /  |"); break;
	}

	MoveConsoleCursorPoint(h, &point, 0, 1); // 6-я строка
	switch (card.m) {
	case 'ч': printf("|   \\/    |"); break;
	case 'п': printf("|  /__\\   |"); break;
	case 'к': printf("|   /_\\   |"); break;
	case 'б': printf("|   \\ /   |"); break;
	}

	MoveConsoleCursorPoint(h, &point, 0, 1); // 7-я строка
	if (card.n <= 10)
		printf("|      %2u |", card.n);
	else
		printf("|       %c |", GetCharDigintyCard(card.n));

	MoveConsoleCursorPoint(h, &point, 0, 1); // 8-я строка
	printf("|_________|");
}

/*вывод в окне с дескриптором h в точку
point изображение карты card с цветовой темой
структуры по адресу ptheme*/
void PrintImgCard(HANDLE h, COORD point, Tcard card, Ttheme* ptheme) {
	SetColorBySuit(h, card.m, ptheme);
	PrintImgCardNotColor(h, point, card);
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*вывод в окне с дескриптором h в точку
point изображение карты card с цветом фона cbg
и цветом символов ctext с цветовой темой структуры
по адресу ptheme*/
void PrintImgCardColor(HANDLE h, COORD point, Tcard card,
	char* cbg, char* ctext, Ttheme* ptheme) {
	SetColor(h, cbg, ctext, ptheme);
	PrintImgCardNotColor(h, point, card);
	SetColor(h, "bgbase", ctext, ptheme);
	SetConsoleCursorPosition(h, point);
	printf(" _________ ");
	SetConsoleCursorPosition(h, point);
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*вывод в окне с дескриптором h в точку
point рубашки карты с цветовой темой структуры
по адресу ptheme*/
void PrintShirtCard(HANDLE h, COORD point, Ttheme* ptheme) {
	SetConsoleCursorPosition(h, point); // 1-я строка
	SetColor(h, "bgbase", "texttarget", ptheme);
	printf(" _________ ");
	for (size_t i = 0, f = 0; i < 6; i++, f++) {
		MoveConsoleCursorPoint(h, &point, 0, 1); // (2 + i)-я строка
		if (f % 2)
			printf("|\\/\\/\\/\\/\\| ");
		else
			printf("|/\\/\\/\\/\\/| ");
	}
	MoveConsoleCursorPoint(h, &point, 0, 1); // 8-я строка
	printf("|_________|");

	SetColor(h, "bgbase", "textbase", ptheme);
}

/*вывод в окне с дескриптором h в точку point области 
изображения карты card, начиная с k-го символа до n символов*/
void PrintRegionImgCardColor(HANDLE h, COORD point, Tcard card, 
	size_t k, size_t n, Ttheme* ptheme) {
	char* p_line;
	size_t k2 = k + n; // индекс конечного символа дял вывода карты
	SetColorBySuit(h, card.m, ptheme);

	SetConsoleCursorPosition(h, point); // 1-я строка
	char line[12] = " _________ ";
	p_line = &line[k];
	line[k2] = '\0';
	printf("%s", p_line);

	for (size_t i = 1; i < 8; i++) {
		MoveConsoleCursorPoint(h, &point, 0, 1);
		switch (i) {
			case 1:
				if (card.n <= 10)
					sprintf(line, "|%2u       |", card.n);
				else
					sprintf(line, "| %c       |", GetCharDigintyCard(card.n));
				break;
			case 2:
				switch (card.m) {
					case 'ч': sprintf(line, "|  _  _   |"); break;
					case 'п': sprintf(line, "|   /\\    |"); break;
					case 'к': sprintf(line, "|    _    |"); break;
					case 'б': sprintf(line, "|   / \\   |"); break;
				}
				break;
			case 3:
				switch (card.m) {
					case 'ч': sprintf(line, "| ( \\/ )  |"); break;
					case 'п': sprintf(line, "|  /  \\   |"); break;
					case 'к': sprintf(line, "|  _| |_  |"); break;
					case 'б': sprintf(line, "|  /   \\  |"); break;
				}
				break;
			case 4:
				switch (card.m) {
					case 'ч': sprintf(line, "|  \\  /   |"); break;
					case 'п': sprintf(line, "| (_  _)  |"); break;
					case 'к': sprintf(line, "| (_   _) |"); break;
					case 'б': sprintf(line, "|  \\   /  |"); break;
				}
				break;
			case 5:
				switch (card.m) {
					case 'ч': sprintf(line, "|   \\/    |"); break;
					case 'п': sprintf(line, "|  /__\\   |"); break;
					case 'к': sprintf(line, "|   /_\\   |"); break;
					case 'б': sprintf(line, "|   \\ /   |"); break;
				}
				break;
			case 6:
				if (card.n <= 10)
					sprintf(line, "|      %2u |", card.n);
				else
					sprintf(line, "|       %c |", GetCharDigintyCard(card.n));
				break;
			case 7:
				sprintf(line, "|_________|");
				break;
		}
		p_line = &line[k];
		line[k2] = '\0';
		printf("%s", p_line);
	}
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*вывод в окне с дескриптором h в точку point специальной карты*/
void PrintSpecialCard(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point); // 1-я строка
	printf(" _________ ");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 2-я строка
	printf("|\\       /|");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 3-я строка
	printf("| \\#### / |");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 4-я строка
	printf("| ##  ##  |");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 5-я строка
	printf("| ##      |");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 6-я строка
	printf("| ##  ##  |");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 7-я строка
	printf("| /#### \\ |");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 8-я строка
	printf("|_________|");
}

/*вывод в окне с дескриптором h в блоке block прямоугольника 
цвета color с цветовой темой структуры по адресу ptheme*/
void PrintRectangle(HANDLE h, Tblock block, char* color, Ttheme* ptheme) {
	SetConsoleCursorPosition(h, block.pos);
	SetColor(h, color, color, ptheme);
	for (size_t i = 0; i < block.lenY; i++) {
		for (size_t j = 0; j < block.lenX; j++) {
			printf(" ");
		}
		MoveConsoleCursorPoint(h, &block.pos, 0, 1);
	}
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*вывод в окне с дескриптором h в точке point книги размера 40 x 141*/
void PrintLargeBook(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("            =------------:::::::::::::::------------------*===*-             -:===========+++*****++++++==============++++**:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("          -%%=                                                   -%%+    *%%=*                                                  %%#*");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("         -=%%=                                                      -%%%%-                                                      +@%%@%%*");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("        -%%*%%+                                                       :*                                                       *#%%%%:%%@##:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("       ##@%%=*                                                       -+                                                       -#%%=*%%=%%#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("      %%##%%%%=:                                                       -+                                                        @%%%%+%%+=#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     -###%%%%%%                                                        -+                                                        %%%%=%%++%%##");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     *##@%%==                                                        -+                                                        ==%%%%*=%%@#");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     +##%%%%%%%%                                                        -=                                                        +#=%%:%%%%%%#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     %%##=%%%%=                                                         =                                                        :@%%=*%%==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     @##=%%=+                                                         =                                                         #%%+=%%+=#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     ###+@=*                                                         +                                                         =%%=%%=+%%#@");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    -###=%%=:                                                         =                                                         %%%%=%%*=%%@#-");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    *##%%%%%%=-                                                         =                                                         +%%%%%%:%%%%=#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    =##%%%%%%%%                                                          =                                                         *@%%++%%==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    %%##=%%%%=                                                          =                                                         -@%%+=%%*=#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    ###+@%%=                                                          =                                                          @%%=%%=*%%##");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    ##@*@==                                                          =                                                          ==%%%%*=%%@#");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   :##%%*@++                                                          =                                                          =%%==*%%%%=#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   *##%%=#+*                                                          =                                                          +%%%%++%%==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   =#@%%=%%=-                                                          =                                                          :%%%%+%%%%+=#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   %%#@=%%%%%%                                                           =                                                           %%%%=%%=+%%#@");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   ##@*%%%%%%                                                           =                                                           =%%%%%%+=%%@#");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   ##@:%%=%%                                                           =                                                           %%%%%%=*%%%%%%#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  :##%%:#==                                                           =                                                           +%%%%+=%%==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  +#@%%*#++                                                           =                                                           *%%%%*%%%%+=#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  =#@%%+#+*                                                           =                                                           -%%%%=%%=+%%#@");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  %%#%%+=#=-                                                           =                                                            %%%%%%%%*=@@#-");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  ##%%*%%%%%%-                                                           =                                                            =%%%%=*%%%%=#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  ##%%:%%%%%%                                                            =                                                            ==%%*=%%==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" -##@:@==                                                            =                                                            +=%%*%%%%+=#=");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" *#%%%%:#+=                                                            +                                                            :=%%=%%=+%%#@");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" =#%%%%:#*=                                                            =                                                            -=%%%%%%+=%%@#");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" @#%%+*#**                                                            +                                                             %%%%%%=+%%@%%#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" ##%%*+#=:                                                            +                                                             =%%%%*=@==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" ##@:=@=-                                                            =                                                             ==%%*%%%%+%%#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(":#@%%:%%%%%%==%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@###########@@%%%%=++*:-                     =                  ---:::::********++++++++++++++======#######@@%%=%%=+%%#@");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("*#%%%%:@####################################################@##########################################################################@#@#");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("=#@@%%####################################################################################################################################:");
}

/*вывод в окне с дескриптором h иконки стрелки влево 
размера 3 x 8 в точке point*/
void PrintSymbolIconLeft(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf(" /|____ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("(  ____|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" \\|     ");
}

/*вывод в окне с дескриптором h иконки лампочки
размера 6 x 9 в точке point*/
void PrintSymbolIconBulb(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("  _____  ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" /     \\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("| Shift |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" \\_ П _/ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   |_|   ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   \"\"\"   ");
}

/*вывод в окне с дескриптором h иконки микрофона
размера 5 x 8 в точке point*/
void PrintSymbolIconVoice(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("   __   ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" _/  |-_");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|_Tab|-_");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  \\__|- ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("        ");
}

/*вывод в окне с дескриптором h иконки стрелки вправо 
размера 3 x 8 в точке point*/
void PrintSymbolIconRight(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf(" ____|\\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|____  )");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     |/ ");
}

#endif 