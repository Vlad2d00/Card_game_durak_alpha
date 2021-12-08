#include "header.h"

/* возвращает из окна hwnd размера
WIDTH x HEIGHT символов размер символа в пикселях*/
POINT GetSellSize(HWND h) {
	RECT rct;
	GetClientRect(h, &rct);
	POINT sellSz;
	sellSz.x = (rct.right - rct.left) / WIDTH;
	sellSz.y = (rct.bottom - rct.top) / HEIGHT;
	return sellSz;
}

/*возвращает из окна hwnd позицию курсора мыши
при размер символа в пикселях sellSz*/
POINT GetMousePos(HWND h, POINT sellSz) {
	static POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(h, &pt);
	pt.x = sellSz.x ? pt.x / sellSz.x : 0;
	pt.y = sellSz.y ? pt.y / sellSz.y : 0;
	return pt;
}

/*разместить в окне с дескриптором h позицию
указателя в точке (x, y)*/
void SetConsoleCursorCoord(HANDLE h, size_t x, size_t y) {
	COORD point;
	point.X = x;
	point.Y = y;
	SetConsoleCursorPosition(h, point);
}

/*разместить в окне с дескриптором h позицию
указателя в точке (x, y), записывая в точку по
адресу point позицию указателя*/
void SetConsoleCursorPoint(HANDLE h, COORD* point,
	size_t x, size_t y) {
	point->X = x;
	point->Y = y;
	SetConsoleCursorPosition(h, *point);
}

/*переместить в окне с дескриптором h позицию
указателя point и окне по горизонтальной
и вертикальной на значения dx и dy */
void MoveConsoleCursorPoint(HANDLE h, COORD* point,
	int dx, int dy) {
	point->X += dx;
	point->Y += dy;
	SetConsoleCursorPosition(h, *point);
}

/*возвращает символ ch в нижнем регистре, если он
относится к символам латинского или русского алфавита*/
char GetLowCh(char ch) {
	const int dist_ru = 'я' - 'Я';
	const int dist_en = 'z' - 'Z';
	if (ch >= 'A' && ch <= 'Z')
		ch += dist_en;
	else if (ch >= 'А' && ch <= 'Я')
		ch += dist_ru;
}

/*возвращает длину большого слова s высотой в 2 символа*/
size_t GetSizeLargeWord(char* s) {
	size_t len = 0;
	char ch;
	while (*s) {
		ch = GetLowCh(*s);
		if (ch == 'г' || ch == 'е' || ch == 'e' || ch == 'ё' || ch == 'з'
			|| ch == 'к' || ch == 'с' || ch == 'х' || ch == 'э' || ch == 'x'
			|| ch == 'k' || ch == 'l' || ch == 'c' || ch == 'f' || ch == 'z')
			len += 2;
		else if (ch == 'м' || ch == 'm' || ch == 'ц' || ch == 'ъ' || ch == 'ы')
			len += 4;
		else if (ch == 'д' || ch == 'ж' || ch == 'ш' || ch == 'ф' || ch == 'ю')
			len += 5;
		else if (ch == 'щ' || ch == 'w')
			len += 6;
		else if (ch == ' ' || ch == 'i' || ch == '.' || ch == ',' || ch == '!' || ch == '-')
			len += 1;
		else if (ch >= 'а' && ch <= 'я' || ch >= 'a' && ch <= 'z' || ch == '?'
			|| ch >= '2' && ch <= '9' || ch >= '0')
			len += 3;
		len++;
		s++;
	}
	len--;
	return len;
}

/*возвращает длину стандартной кнопки высоты высотой в 5 символов*/
size_t GetSizeButtonStandart(char* s) {
	return GetSizeLargeWord(s) + 5;
}

/*возвращает длину маркированной однострочной кнопки*/
size_t GetSizeButtonMark(char* s) {
	return strlen(s) + 5;
}

/*возвращает длину однострочной кнопки ввода данных*/
size_t GetSizeButtonInputNumber(char* s) {
	return strlen(s) + 4;
}

/*вывод окне с дескриптором h, в точке point символов 
русского, латинского алфавита, цифр из строки s 
высотой в два символа, минимальная ширина вывода - w*/
void PrintWordLarge(HANDLE h, COORD point, char* s, size_t w) {
	const char line_spacing[] = " ";
	char* ps = s;
	SetConsoleCursorPosition(h, point);

	size_t len = GetSizeLargeWord(s);
	size_t parity = 1; // четность
	// отступы от краев блока
	if (w > len) {
		w -= len;
		parity = w % 2 == 0;
		w /= 2;
	} else
		w = 1;

	for (size_t i = parity; i <= w; i++) {
		printf(" ");
	}
	char ch;
	// первая строка
	while (*ps) {
		ch = GetLowCh(*ps);
		if (ch == 'а' || ch == 'б' || ch == 'в' || (ch >= 'о' && ch <= 'р') 
			|| ch == 'я' || ch == 'q' || ch == 'r' || ch == 'o' || ch == 'p'
			|| ch == 'a' || ch == 's' || ch == 'd' || ch == 'g' || ch == 'b'
			|| ch == '2' || ch == '6' || ch == '8' || ch == '9' || ch == '0'
			|| ch == '5')
			printf(" _ ");
		else if (ch == 'д')
			printf("  _  ");
		else if (ch == 'ж' || ch == 'ш')
			printf("     ");
		else if (ch == 'и' || ch == 'л' || ch == 'н' || ch == 'у' || ch == 'y' 
			|| ch == 'ч' || ch == 'ь' || ch == 'h' || ch == 'v' || ch == 'n'
			|| ch == '4' || ch == 'j' || ch == 'u')
			printf("   ");
		else if (ch == 'г' || ch == 'е' || ch == 'e' || ch == 'ё' || ch == 'f'
			|| ch == 'с' || ch == 'c')
			printf(" _");
		else if (ch == 'м' || ch == 'ц' || ch == 'ы' || ch == 'm')
			printf("    ");
		else if (ch == '7')
			printf("_ ");
		else if (ch == 'т' || ch == 't')
			printf("___");
		else if (ch == 'х' || ch == 'к' || ch == 'k' || ch == 'x' || ch == '1'
			|| ch == 'l')
			printf("  ");
		else if (ch == 'ф')
			printf(" ___ ");
		else if (ch == 'щ' || ch == 'w')
			printf("      ");
		else if (ch == 'з' || ch == '3' || ch == 'э' || ch == '?')
			printf("_ ");
		else if (ch == 'ъ')
			printf("_   ");
		else if (ch == 'ю')
			printf("   _ ");
		else if (ch == 'й')
			printf(" v ");
		else if (ch == 'z')
			printf("__");
		else if (ch == ' ' || ch == '!' || ch == ':' || ch == '.' || ch == ',' 
			|| ch == 'i' || ch == '-')
			printf(" ");
		if (*(ps + 1))
			printf("%s", line_spacing);
		ps++;
	}
	for (size_t i = 0; i < w; i++) {
		printf(" ");
	}
	MoveConsoleCursorPoint(h, &point, 0, 1);
	ps = s;
	for (size_t i = parity; i <= w; i++) {
		printf(" ");
	}
	// вторая строка
	while (*ps) {
		ch = GetLowCh(*ps);
		if (ch == 'i' || ch == '!')
			printf("|");
		else if (ch == 'а' || ch == 'в' || ch == 'н' || ch == 'у' || ch == 'у' 
			|| ch == 'р' || ch == 'ч' || ch == 'я' || ch == 'r' || ch == 'p'
			|| ch == 'a' || ch == 'h' || ch == 'b' || ch == '4' || ch == '8'
			|| ch == '9' || ch == 'y')
			printf("|_|");
		else if (ch == 'б' || ch == 'ь' || ch == 's' || ch == '5' || ch == '6')
			printf("|_ ");
		else if (ch == 'е' || ch == 'e' || ch == 'ё' || ch == 'f')
			printf("|_");
		else if (ch == 'г' || ch == 'с' || ch == 'l' || ch == 'c')
			printf("| ");
		else if (ch == 'д')
			printf(" |_| ");
		else if (ch == 'ж')
			printf("\\_|_/");
		else if (ch == 'з' || ch == '3')
			printf("_|");
		else if (ch == '2')
			printf(" _|");
		else if (ch == 'и' || ch == 'й' || ch == 'о' || ch == 'o' || ch == 'п' 
			|| ch == 'q' || ch == 'u' || ch == 'n' || ch == '0')
			printf("| |");
		else if (ch == 'к' || ch == 'k')
			printf("|/");
		else if (ch == 'л')
			printf(" /|");
		else if (ch == 'м' || ch == 'm')
			printf("|\\/|");
		else if (ch == 'т' || ch == 't')
			printf(" | ");
		else if (ch == 'ф')
			printf("|_|_|");
		else if (ch == 'х' || ch == 'x')
			printf("\\/");
		else if (ch == 'ц')
			printf("| | ");
		else if (ch == 'ш')
			printf("| | |");
		else if (ch == 'щ')
			printf("| | | ");
		else if (ch == 'ъ')
			printf(" |_ ");
		else if (ch == 'ы')
			printf("|_ |");
		else if (ch == 'э')
			printf("_\\");
		else if (ch == 'w')
			printf("\\    /");
		else if (ch == 'ю')
			printf("|_| |");
		else if (ch == 'v')
			printf("\\ |");
		else if (ch == 'd')
			printf("| \\");
		else if (ch == 'g')
			printf("| _");
		else if (ch == 'j')
			printf("  |");
		else if (ch == '1' || ch == '7')
			printf(" |");
		else if (ch == 'z' || ch == '?')
			printf(" /");
		else if (ch == ':')
			printf(".");
		else if (ch == '-')
			printf("_");
		else if (ch == ' ' || ch == '.' || ch == ',')
			printf(" ");
		if (*(ps + 1))
			printf("%s", line_spacing);
		ps++;
	}
	for (size_t i = 0; i < w; i++) {
		printf(" ");
	}
	MoveConsoleCursorPoint(h, &point, 0, 1);
	ps = s;
	for (size_t i = parity; i <= w; i++) {
		printf(" ");
	}
	// третья строка
	while (*ps) {
		ch = GetLowCh(*ps);
		if (ch == 'i')
			printf("|");
		else if (ch == 'а' || ch == 'н' || ch == 'п' || ch == 'a' || ch == 'h')
			printf("| |");
		else if (ch == 'б' || ch == 'в' || ch == 'о' || ch == 'ь' || ch == 'u'
			|| ch == 'o' || ch == 'g' || ch == 'b' || ch == '6' || ch == '8'
			|| ch == '0')
			printf("|_|");
		else if (ch == 'г' || ch == 'f')
			printf("| ");
		else if (ch == 'д')
			printf("|   |");
		else if (ch == 'е' || ch == 'e' || ch == 'ё')
			printf("|_");
		else if (ch == 'ж')
			printf("/ | \\");
		else if (ch == 'з' || ch == '3')
			printf("_|");
		else if (ch == '9')
			printf(" _|");
		else if (ch == 'и' || ch == 'й')
			printf("|/|");
		else if (ch == 'к' || ch == 'k')
			printf("|\\");
		else if (ch == 'л')
			printf("/ |");
		else if (ch == 'w')
			printf(" \\/\\/ ");
		else if (ch == 'м' || ch == 'm')
			printf("|  |");
		else if (ch == 'р' || ch == 'p')
			printf("|  ");
		else if (ch == 'с' || ch == 'c' || ch == 'l')
			printf("|_");
		else if (ch == '2')
			printf("|_ ");
		else if (ch == 'т' || ch == 't')
			printf(" | ");
		else if (ch == 'у' || ch == 'y' || ch == 's' || ch == '5')
			printf(" _|");
		else if (ch == 'ф')
			printf("  |  ");
		else if (ch == 'х' || ch == 'x')
			printf("/\\");
		else if (ch == 'ц')
			printf("|_|_");
		else if (ch == 'ч' || ch == '4')
			printf("  |");
		else if (ch == '1' || ch == '7')
			printf(" |");
		else if (ch == 'ш')
			printf("|_|_|");
		else if (ch == 'щ')
			printf("|_|_|_");
		else if (ch == 'ъ')
			printf(" |_|");
		else if (ch == 'ы')
			printf("|_||");
		else if (ch == 'э')
			printf("_/");
		else if (ch == 'ю')
			printf("| |_|");
		else if (ch == 'я')
			printf("/ |");
		else if (ch == 'v')
			printf(" \\|");
		else if (ch == 'd')
			printf("|_/");
		else if (ch == 'z')
			printf("/_");
		else if (ch == 'j')
			printf("\\_|");
		else if (ch == 'r')
			printf("|\\ ");
		else if (ch == 'n')
			printf("|\\|");
		else if (ch == 'q')
			printf("|_\\");
		else if (ch == '?')
			printf(". ");
		else if (ch == '!' || ch == ':' || ch == '.')
			printf(".");
		else if (ch == ',')
			printf(",");
		else if (ch == ' ' || ch == '-')
			printf(" ");
		if (*(ps + 1))
			printf("%s", line_spacing);
		ps++;
	}
	for (size_t i = 0; i < w; i++) {
		printf(" ");
	}
}

/*вывод в окне с дескриптором h в позицию point
кнопки высоты в 6 символов, адаптивной
минимальной ширины w, начиная с левого верхнего угла
содержащей русские символы строки s*/
void PrintImgButton(HANDLE h, COORD point, char* s, size_t w) {
	size_t len = GetSizeLargeWord(s) + 5;
	if (len > w)
		w = len;

	char outline[SIZE];
	outline[0] = ' ';
	outline[1] = ' ';
	outline[w - 1] = ' ';
	outline[w] = '\0';
	size_t w_1 = w - 1;
	for (size_t i = 1; i < w_1; i++) {
		outline[i] = '_';
	}
	size_t baseX = point.X;
	size_t baseY = point.Y;
	SetConsoleCursorPosition(h, point); // 1 строка начало
	printf("%s", outline);

	MoveConsoleCursorPoint(h, &point, 0, 1); // 2 строка начало
	printf("/|");
	size_t Y_old = point.Y, X_old = point.X;
	MoveConsoleCursorPoint(h, &point, 0, 1); // 3 строка начало
	printf("||");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 4 строка начало
	printf("||");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 5 строка начало
	printf("%s", outline);
	SetConsoleCursorPosition(h, point); // 5 строка начало
	printf("||");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 6 строка начало
	printf("%s", outline);
	SetConsoleCursorPosition(h, point); // 5 строка начало
	printf("|/");

	MoveConsoleCursorPoint(h, &point, w - 1, 0); // 6 строка конец
	printf("/");
	for (size_t i = 0; i < 4; i++) {
		MoveConsoleCursorPoint(h, &point, 0, -1);; // (6 - i - 1) строка конец
		printf("|");
	}
	SetConsoleCursorPoint(h, &point, baseX + 2, baseY + 1);
	PrintWordLarge(h, point, s, w - 3);
}

/*вывод в окне с дескриптором h в позицию point нажатой 
кнопки высоты в 5 символов, минимальной ширины w, начиная 
с левого верхнего угла содержащей русские символы строки 
s с цветовой темой структуры по адресу ptheme*/
void PrintImgPressedButton(HANDLE h, COORD point, char* s,
	size_t w, Ttheme* ptheme) {
	point.Y++;
	point.X--;
	size_t len = GetSizeLargeWord(s) + 5;
	if (len > w)
		w = len;

	char outline[SIZE];
	outline[0] = ' ';
	outline[1] = ' ';
	outline[w - 1] = ' ';
	outline[w] = '\0';
	size_t w_1 = w - 1;
	for (size_t i = 1; i < w_1; i++) {
		outline[i] = '_';
	}
	size_t baseX = point.X;
	size_t baseY = point.Y;

	SetColor(h, "textbase", "bgbase", ptheme);
	SetConsoleCursorPosition(h, point); // 1 строка начало
	printf("%s", outline);

	MoveConsoleCursorPoint(h, &point, 1, 1); // 2 строка начало
	printf("|");
	size_t Y_old = point.Y, X_old = point.X;
	MoveConsoleCursorPoint(h, &point, 0, 1); // 3 строка начало
	printf("|");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 4 строка начало
	printf("|");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 5 строка начало
	printf("%s", outline);
	SetConsoleCursorPosition(h, point); // 5 строка начало
	printf("|");

	MoveConsoleCursorPoint(h, &point, w - 2, 0); // 5 строка конец
	for (size_t i = 0; i < 4; i++) {
		printf("|");
		MoveConsoleCursorPoint(h, &point, 0, -1); // (5 - i - 1) строка конец
	}
	SetConsoleCursorPoint(h, &point, baseX + 2, baseY + 1);
	PrintWordLarge(h, point, s, w - 3);

	SetConsoleCursorPoint(h, &point, baseX, baseY - 1);
	SetColor(h, "bgbase", "bgbase", ptheme);
	printf("%s", outline);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	SetColor(h, "bgbase", "textbase", ptheme);
	printf("%s ", outline);
	MoveConsoleCursorPoint(h, &point, w, 0);
	for (size_t i = 0; i < 4; i++) {
		MoveConsoleCursorPoint(h, &point, 0, 1);
		printf(" ");
	}
}

/*возвращает 1, если координаты курсора мыши консольного 
окна попадают в блок block или 2, если в этом блоке 
нажата ЛКМ, иначе 0*/
size_t CursoreInBlock(Tblock block) {
	HWND hwnd = GetConsoleWindow();
	POINT mouse_pos; // координаты мыши
	POINT sell_size = GetSellSize(hwnd); // размер символа в пикселях
	mouse_pos = GetMousePos(hwnd, sell_size);

	if (mouse_pos.x >= block.pos.X
		&& mouse_pos.x < block.pos.X + block.lenX
		&& mouse_pos.y >= block.pos.Y
		&& mouse_pos.y < block.pos.Y + block.lenY) {
		if (GetKeyState(VK_LBUTTON) < 0)
			return BUTTON_CHOISE;
		else
			return BUTTON_HOVER;
	}
	else
		return BUTTON_NONE;
}

/*запись в строку s символа ch в колчестве n, возвращая 
указтель на конец строки*/
char* GetStrSingleChar(char* s, char ch, size_t n) {
	char* ps = s;
	for (size_t i = 0; i < n; i++) {
		*s++ = ch;
	}
	*s = '\0';
	return s;
}

/*выводит 5-строчную кнопку и возвращает значение
"истина", если в окне с дескриптором h кнопка в
блоке по адресу pblock с текстом s минимальной
ширины w нажата, иначе значение "ложь", с
цветовой темой структуры по адресу ptheme*/
size_t PrintButtonStandart(HANDLE h, Tblock* pblock, char* s,
	size_t w, Ttheme* ptheme) {
	static clock_t time_start;
	size_t cursor;
	if (GetKeyState(VK_SPACE) < 0 && pblock->cond == BUTTON_HOVER_CUR) {
		cursor = BUTTON_CHOISE;
		goto fButtonStandart;
	}
	Tblock block = *pblock;
	block.pos.Y++;
	cursor = CursoreInBlock(block);
	if (cursor != BUTTON_CHOISE && (pblock->cond == BUTTON_HOVER_KEY ||
		pblock->cond == BUTTON_HOVER_CUR))
		cursor = BUTTON_HOVER_KEY;

	// курсор не наведен 
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			SetColor(h, "bgbase", "textbase", ptheme);
			PrintImgButton(h, pblock->pos, s, w);
			pblock->cond = BUTTON_NONE;
		}
	}
	// кнопка выбрана курсором мыши или клавиатурой
	else if (cursor == BUTTON_HOVER || cursor == BUTTON_HOVER_KEY) {
		if (pblock->cond != BUTTON_HOVER && pblock->cond != BUTTON_HOVER_CUR) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonSwitch1.mp3"),
					NULL, 0, NULL); // звук
			}
			SetColor(h, "textbase", "bgbase", ptheme);
			PrintImgButton(h, pblock->pos, s, w);

			// вывод верхней линии контура кнопки
			w = max(GetSizeButtonStandart(s), w);

			char outline[WIDTH];
			GetStrSingleChar(outline, '_', w - 2);
			SetConsoleCursorPosition(h, pblock->pos);
			SetColor(h, "bgbase", "textbase", ptheme);
			printf(" %s ", outline);

			if (cursor == BUTTON_HOVER_KEY)
				pblock->cond = BUTTON_HOVER_CUR;
			else
				pblock->cond = BUTTON_HOVER;
		}
	}
	// кнопка нажата
	else if (cursor == BUTTON_CHOISE) {
	fButtonStandart:
		if (TIMER(time_start, SPEED_CLICK)) {
			pblock->cond = BUTTON_CHOISE;
			PrintImgPressedButton(h, pblock->pos, s, w, ptheme);
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
					NULL, 0, NULL); //звук
			}
			time_start = clock();
			return 1;
		}
	}
	return 0;
}

/*вывод в окне с дескриптором h кнопки в виде таблички 
с надписью правила в блоке pblock с цветовой темой 
структуры по адресу ptheme*/
size_t PrintButtonBookRule(HANDLE h, Tblock* pblock, Ttheme* ptheme) {
	static clock_t time_start;
	size_t cursor;
	if (GetKeyState(VK_SPACE) < 0 && pblock->cond == BUTTON_HOVER_CUR) {
		cursor = BUTTON_CHOISE;
		goto fButtonBookRule;
	}
	Tblock tmp_block = *pblock;
	tmp_block.pos.Y++;
	cursor = CursoreInBlock(tmp_block);
	if (cursor != BUTTON_CHOISE && (pblock->cond == BUTTON_HOVER_KEY ||
		pblock->cond == BUTTON_HOVER_CUR))
		cursor = BUTTON_HOVER_KEY;

	// курсор не наведен 
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			SetColor(h, "bgbase", "textbase", ptheme);
			PrintImgBookRuleButton(h, pblock->pos);
			pblock->cond = BUTTON_NONE;
		}
		// кнопка выбрана курсором мыши или клавиатурой
	}
	else if (cursor == BUTTON_HOVER || cursor == BUTTON_HOVER_KEY) {
		if (pblock->cond != BUTTON_HOVER && pblock->cond != BUTTON_HOVER_CUR) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonSwitch1.mp3"),
					NULL, 0, NULL); // звук
			}
			SetColor(h, "textbase", "bgbase", ptheme);
			PrintImgBookRuleButton(h, pblock->pos);
			SetColor(h, "bgbase", "textbase", ptheme);
			// вывод верхней линии контура кнопки
			SetConsoleCursorPosition(h, pblock->pos);
			printf(" _________ ");

			if (cursor == BUTTON_HOVER_KEY)
				pblock->cond = BUTTON_HOVER_CUR;
			else
				pblock->cond = BUTTON_HOVER;
		}
		// кнопка нажата
	}
	else if (cursor == BUTTON_CHOISE) {
	fButtonBookRule:
		if (TIMER(time_start, SPEED_CLICK)) {
			pblock->cond = BUTTON_CHOISE;
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
					NULL, 0, NULL); //звук
			}
			time_start = clock();
			return 1;
		}
	}
	return 0;
}

/*вывод в окне с дескриптором h кнопки таблицы достижений
в блоке pblock с цветовой темой структуры по адресу ptheme*/
size_t PrintButtonAchievementTable(HANDLE h, Tblock* pblock, Ttheme* ptheme) {
	size_t cursor = CursoreInBlock(*pblock);
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			SetColor(h, "bgbase", "textbase", ptheme);
			PrintAchievementTable(h, pblock->pos, ptheme);
			pblock->cond = BUTTON_NONE;
		}
	} else if (pblock->cond != BUTTON_HOVER) {
		if (ptheme->onSounds) {
			mciSendString(TEXT("play sourse\\sound\\menu\\buttonSwitch1.mp3"),
				NULL, 0, NULL); // звук
		}
		SetColor(h, "bgbase", "texttarget", ptheme);
		PrintAchievementTable(h, pblock->pos, ptheme);
		SetColor(h, "bgbase", "textbase", ptheme);
		pblock->cond = BUTTON_HOVER;
	}
	if (cursor == 2 && ptheme->onSounds) {
		mciSendString(TEXT("play sourse\\sound\\menu\\crickets.mp3"),
			NULL, 0, NULL); // звук
	}
	return cursor == 2;
}

/*выводит однострочную кнопку и возвращает значение "истина", 
если в окне с дескриптором h кнопка в блоке pblock с текстом 
s минимальной ширины w нажата, иначе значение "ложь", с 
цветовой темой структуры по адресу ptheme*/
size_t PrintButtonSmall(HANDLE h, Tblock* pblock, char* s, size_t w, Ttheme* ptheme) {
	size_t cursor;
	static clock_t time_start = 0;
	if (pblock->cond == BUTTON_CHOISE) {
		cursor = BUTTON_HOVER_KEY;
		goto flagReButtonSmall;
	}
	else if (GetKeyState(VK_SPACE) < 0 && pblock->cond == BUTTON_HOVER_CUR) {
		cursor = BUTTON_CHOISE;
		goto flagButtonSmall;
	}

	Tblock tmp_block = *pblock;
	cursor = CursoreInBlock(tmp_block);
	if (cursor != BUTTON_CHOISE && (pblock->cond == BUTTON_HOVER_KEY ||
		pblock->cond == BUTTON_HOVER_CUR))
		cursor = BUTTON_HOVER_KEY;

	// курсор не наведен 
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			w = max(pblock->lenX, w);
			SetConsoleCursorPosition(h, pblock->pos);
			PrintColorWidth(h, s, "bgmsg", "textmsg", w, ptheme);
			pblock->cond = BUTTON_NONE;
		}
	} 
	// кнопка выбрана курсором мыши или клавиатурой
	else if (cursor == BUTTON_HOVER || cursor == BUTTON_HOVER_KEY) {
		if (pblock->cond != BUTTON_HOVER && pblock->cond != BUTTON_HOVER_CUR) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonSwitch1.mp3"),
					NULL, 0, NULL); // звук
			}
			flagReButtonSmall:
			w = max(pblock->lenX, w);
			SetConsoleCursorPosition(h, pblock->pos);
			PrintColorWidth(h, s, "textmsg", "bgmsg", w, ptheme);

			if (cursor == BUTTON_HOVER_KEY)
				pblock->cond = BUTTON_HOVER_CUR;
			else
				pblock->cond = BUTTON_HOVER;
		}
	}
	// кнопка нажата
	else if (cursor == BUTTON_CHOISE) {
		flagButtonSmall:
		if (TIMER(time_start, SPEED_CLICK)) {
			pblock->cond = BUTTON_CHOISE;
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
					NULL, 0, NULL); //звук
			}
			time_start = clock();
			return 1;
		}
	}
	return 0;
}

/*выводит однострочную кнопку с маркером и возвращает значение 
"истина", если в окне с дескриптором h кнопка в блоке pblock 
с текстом s нажата, меняя по адресу pvalue значение на 
"истина", если оно "ложь", иначе наоборот, иначе возвращает 
значение "ложь", с цветовой темой структуры по адресу ptheme*/
size_t PrintButtonMark(HANDLE h, Tblock* pblock, char* s, size_t* pvalue, Ttheme* ptheme) {
	size_t cursor;
	static clock_t time_start = 0;
	char stmp[WIDTH];
	Tblock tmp_block = *pblock;
	
	if (GetKeyState(VK_SPACE) < 0 && pblock->cond == BUTTON_HOVER_CUR) {
		cursor = BUTTON_CHOISE;
		goto flagButtonMark;
	}

	cursor = CursoreInBlock(tmp_block);
	if (cursor != BUTTON_CHOISE && (pblock->cond == BUTTON_HOVER_KEY ||
		pblock->cond == BUTTON_HOVER_CUR))
		cursor = BUTTON_HOVER_KEY;

	// курсор не наведен 
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			MoveConsoleCursorPoint(h, &tmp_block.pos, 0, -1);
			PrintColor(h, "\\textmsg-bgmsg: __ ", ptheme);
			MoveConsoleCursorPoint(h, &tmp_block.pos, 0, 1);
			if (*pvalue)
				PrintColor(h, "\\textmsg-bgmsg:|\\textmsg-bgtarget:__\\textmsg-bgmsg:| ", ptheme);
			else
				PrintColor(h, "\\textmsg-bgmsg:|__| ", ptheme);
			MoveConsoleCursorPoint(h, &tmp_block.pos, 5, 0);
			PrintColorWidth(h, s, "bgmsg", "textmsg", 0, ptheme);
			pblock->cond = BUTTON_NONE;
		}
	} 
	// кнопка выбрана курсором мыши или клавиатурой
	else if (cursor == BUTTON_HOVER || cursor == BUTTON_HOVER_KEY) {
		if (pblock->cond != BUTTON_HOVER && pblock->cond != BUTTON_HOVER_CUR) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonSwitch1.mp3"),
					NULL, 0, NULL); // звук
			}
			MoveConsoleCursorPoint(h, &tmp_block.pos, 5, 0);
			PrintColorWidth(h, s, "bgmsg", "texttarget", 0, ptheme);

			if (cursor == BUTTON_HOVER_KEY)
				pblock->cond = BUTTON_HOVER_CUR;
			else
				pblock->cond = BUTTON_HOVER;
		}
	} 
	// кнопка нажата
	else if (cursor == BUTTON_CHOISE) {
		flagButtonMark:
		if (TIMER(time_start, SPEED_CLICK)) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
					NULL, 0, NULL); //звук
			}
			SetConsoleCursorPosition(h, tmp_block.pos);
			if (*pvalue)
				PrintColor(h, "\\textmsg-bgmsg:|__| ", ptheme);
			else
				PrintColor(h, "\\textmsg-bgmsg:|\\textmsg-bgtarget:__\\textmsg-bgmsg:| ", ptheme);
			*pvalue = (*pvalue + 1) % 2;
			time_start = clock();
			return 1;
		}
	}
	return 0;
}

/*выводит кнопку-изображение по функции f и возвращает значение 
"истина", если в окне с дескриптором h кнопка в блоке pblock 
нажата, меняя по адресу pvalue значение на "истина", если оно 
"ложь", иначе наоборот, иначе возвращает значение "ложь", 
с цветовой темой структуры по адресу ptheme*/
size_t PrintButtonMarkImg(HANDLE h, Tblock* pblock, void f(HANDLE, COORD), 
	size_t* pvalue, Ttheme* ptheme) {
	size_t cursor;
	static clock_t time_start = 0;
	char stmp[WIDTH];
	
	if (GetKeyState(VK_SPACE) < 0 && pblock->cond == BUTTON_HOVER_CUR) {
		cursor = BUTTON_CHOISE;
		goto flagButtonMarkImg;
	}

	Tblock tmp_block = *pblock;
	cursor = CursoreInBlock(tmp_block);
	if (cursor != BUTTON_CHOISE && (pblock->cond == BUTTON_HOVER_KEY ||
		pblock->cond == BUTTON_HOVER_CUR))
		cursor = BUTTON_HOVER_KEY;

	// курсор не наведен 
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			if (*pvalue)
				SetColor(h, "bgtarget", "textbase", ptheme);
			else
				SetColor(h, "bgmsg", "textmsg", ptheme);
			f(h, pblock->pos);
			pblock->cond = BUTTON_NONE;
			SetColor(h, "bgbase", "textbase", ptheme);
		}
	} 
	// кнопка выбрана курсором мыши или клавиатурой
	else if (cursor == BUTTON_HOVER || cursor == BUTTON_HOVER_KEY) {
		if (pblock->cond != BUTTON_HOVER && pblock->cond != BUTTON_HOVER_CUR) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonSwitch1.mp3"),
					NULL, 0, NULL); // звук
			}
			if (*pvalue)
				SetColor(h, "bgtarget", "texttarget", ptheme);
			else
				SetColor(h, "bgmsg", "texttarget", ptheme);
			f(h, pblock->pos);
			if (cursor == BUTTON_HOVER_KEY)
				pblock->cond = BUTTON_HOVER_CUR;
			else
				pblock->cond = BUTTON_HOVER;
			SetColor(h, "bgbase", "textbase", ptheme);
		}
	} 
	// кнопка нажата
	else if (cursor == BUTTON_CHOISE) {
		flagButtonMarkImg:
		if (TIMER(time_start, SPEED_CLICK)) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
					NULL, 0, NULL); //звук
			}
			if (*pvalue)
				SetColor(h, "bgmsg", "textmsg", ptheme);
			else
				SetColor(h, "bgtarget", "textbase", ptheme);
			f(h, pblock->pos);
			*pvalue = (*pvalue + 1) % 2;
			time_start = clock();
			SetColor(h, "bgbase", "textbase", ptheme);
			return 1;
		}
	}
	return 0;
}

/*обращение строки s*/
static void reverse(char* s) {
	size_t i = 0, j = strlen(s) - 1;
	char t;
	while (i < j) {
		t = s[i];
		s[i] = s[j];
		s[j] = t;
		i++;
		j--;
	}
}

/*запись целого беззнакового числа n в строку s, при
этом возвращая указатель на символ после записанного числа*/
static char* itos(size_t n, char* s) {
	char* p = s;
	do {
		*s++ = n % 10 + '0';
	} while ((n /= 10) > 0);
	*s = '\0';
	reverse(p); // обращение строки по адресу p
	return s;
}

/*вывод в окне с дескриптором h в блоке pblock элемента 
по функции f, который подсвечивается при наведении на 
него курсором мыши, с цветовой темой структуры по адресу 
ptheme, возвращая значение "истина", если в этой области 
был клик ЛКМ, иначе значение "ложь"*/
size_t PrintElCursorHover(HANDLE h, Tblock* pblock, void f(HANDLE, COORD), Ttheme* ptheme) {
	size_t cursor = CursoreInBlock(*pblock);
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			SetColor(h, "bgbase", "textbase", ptheme);
			f(h, pblock->pos);
			pblock->cond = BUTTON_NONE;
		}
	} else if (pblock->cond != BUTTON_HOVER) {
		SetColor(h, "bgbase", "texttarget", ptheme);
		f(h, pblock->pos);
		SetColor(h, "bgbase", "textbase", ptheme);
		pblock->cond = BUTTON_HOVER;
	}
	return cursor == 2;
}

/*вывод в окне с дескриптором h изображения кота в точке point*/
void PrintCat(HANDLE h, COORD point) {
	MoveConsoleCursorPoint(h, &point, 8, 0);
	printf("/>__/>");
	MoveConsoleCursorPoint(h, &point, -1, 1);
	printf("| _  _\\");
	MoveConsoleCursorPoint(h, &point, -1, 1);
	printf("(`= _x =)");
	MoveConsoleCursorPoint(h, &point, -1, 1);
	printf("/       /");
	MoveConsoleCursorPoint(h, &point, -4, 1);
	printf("__/ `      )");
	MoveConsoleCursorPoint(h, &point, -1, 1);
	printf("/  _    | | |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("| (_ \\___`_)_)");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" \\__>");
}

/*вывод в окне с дескриптором h в блоке pblock изображения 
кота, нажимая на которого воспроизводятся звуки мяукания, 
с цветовой темой структуры по адресу ptheme, возвращая 
значение "истина", если в этой области был клик ЛКМ, 
иначе значение "ложь"*/
size_t PrintButtonCat(HANDLE h, Tblock* pblock, Ttheme* ptheme) {
	static clock_t time_start = 0;
	size_t click = PrintElCursorHover(h, pblock, PrintCat, ptheme);
	if (click && ptheme->onSounds && TIMER(time_start, 1000)) {
		if (rand() % 2)
			mciSendString(TEXT("play sourse\\sound\\menu\\cat1.mp3"),
				NULL, 0, NULL); // звук мяу
		else
			mciSendString(TEXT("play sourse\\sound\\menu\\cat2.mp3"),
				NULL, 0, NULL); // звук мяу
		time_start = clock();
	}
	return click;
}

/*вывод в окне с дескриптором h в блоке block кнопки 
с текстом s, которая подсвечивается при наведении на 
нее курсора мыши, с цветовой темой структуры по адресу 
ptheme, возвращая значение "истина", если в этой области 
был клик ЛКМ, иначе значение "ложь*/
size_t PrintWordCursorHover(HANDLE h, Tblock* pblock, char* s, Ttheme* ptheme) {
	size_t cursor = CursoreInBlock(*pblock);
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			SetColor(h, "bgbase", "textbase", ptheme);
			PrintWordLarge(h, pblock->pos, s, 0);
			pblock->cond = BUTTON_NONE;
		}
	} else if (pblock->cond != BUTTON_HOVER) {
		SetColor(h, "bgbase", "texttarget", ptheme);
		PrintWordLarge(h, pblock->pos, s, 0);
		SetColor(h, "bgbase", "textbase", ptheme);
		pblock->cond = BUTTON_HOVER;
	}
	return cursor == 2;
}

/*вывод в окне с дескриптором h поле ввода положительного 
числа в точке point ширины w с введенным числом с 
допустимым диапазоном значений от min до max включительно, 
записывая по адресу pvalue введенное число при подтверждении
ввода, возвращая значение "истина", если ввод подтвержден 
иначе значение "ложь", с цветовой темой структуры по адресу ptheme*/
size_t InputNumber(HANDLE h, COORD point, size_t w, size_t min, 
	size_t max, size_t* pvalue, Ttheme* ptheme) {
	clock_t time_start = clock();
	char s_value[13]; // строка с вводимым числом
	itos(*pvalue, s_value);
	size_t cur_value = *pvalue; // текущее введенное значение
	COORD cur_point = point;
	size_t i = strlen(s_value);
	cur_point.X += i;
	char stmp[100];

	SetConsoleCursorPosition(h, point);
	if (cur_value == 0)
		PrintColorWidth(h, "0", "bgmsg", "darkgray", w, ptheme);
	else
		PrintColorWidth(h, s_value, "bgmsg", "textmsg", w, ptheme);

	flagReInputNumber:
	SetConsoleCursorPosition(h, cur_point);
	char ch = getch();
	while (ch != 13) {
		if (TIMER(time_start, TIME_CLEAR_BUF)) {
			if (ch >= '0' && ch <= '9') {
				if (i < w && (ch != '0' || i > 0)) {
					s_value[i] = ch;
					s_value[++i] = '\0';
					if (i == 1)
						cur_value = ch - '0';
					else
						cur_value = cur_value * 10 + (ch - '0');

					cur_point.X++;
					SetConsoleCursorPosition(h, point);
					if (cur_value >= min && cur_value <= max)
						PrintColorWidth(h, s_value, "bgmsg", "textmsg", w, ptheme);
					else
						PrintColorWidth(h, s_value, "bgmsg", "lightred", w, ptheme);
				}
			}
			else if (ch == '\b') {
				if (i > 0) {
					s_value[--i] = '\0';
					cur_value /= 10;

					cur_point.X--;
					SetConsoleCursorPosition(h, point);
					if (i == 0)
						PrintColorWidth(h, "0", "bgmsg", "darkgray", w, ptheme);
					else if (cur_value >= min && cur_value <= max)
						PrintColorWidth(h, s_value, "bgmsg", "textmsg", w, ptheme);
					else
						PrintColorWidth(h, s_value, "bgmsg", "lightred", w, ptheme);
				}
			}
			else if (ch == '\t') {
				SetColor(h, "bgbase", "textbase", ptheme);
				return 0;
			}
			SetColor(h, "bgmsg", "textmsg", ptheme);
		}
		SetConsoleCursorPosition(h, cur_point);
		ch = getch();
	}
	if (cur_value < min || cur_value > max) {
		if (ptheme->onSounds) {
			mciSendString(TEXT("play sourse\\sound\\menu\\inputError.mp3"),
				NULL, 0, NULL); //звук
		}
		goto flagReInputNumber;
	}

	if (ptheme->onSounds) {
		mciSendString(TEXT("play sourse\\sound\\menu\\inputSuccess.mp3"),
			NULL, 0, NULL); //звук
	}
	if (i == 0)
		*pvalue = cur_value;
	else
		*pvalue = cur_value;
	SetColor(h, "bgbase", "textbase", ptheme);
	return 1;
}

/*вывод в окне с дескриптором h поле ввода строки с именем 
в точке point ширины w с введенным числом с допустимыми 
символами русского и латинского алфавита, пробелами и цифрами, 
записывая в строку name введенную строку с диапазоном длины 
от min до max включительно, при подтверждении ввода, или 
строку по уиолчанию name_default если введеная строка пустая, 
возвращая значение "истина", если ввод подтвержден иначе 
значение "ложь", с цветовой темой структуры по адресу ptheme*/
size_t InputName(HANDLE h, COORD point, size_t w, char* name, 
	size_t min, size_t max, char* name_default, Ttheme* ptheme) {
	clock_t time_start = clock();
	char tmp_name[100]; // строка с вводимым числом
	strcpy(tmp_name, name);
	size_t i = strlen(tmp_name);

	if (!strcmp(name_default, name))
		i = 0;
	SetConsoleCursorPosition(h, point);
	if (i == 0)
		PrintColorWidth(h, name_default, "bgmsg", "darkgray", w, ptheme);
	else
		PrintColorWidth(h, tmp_name, "bgmsg", "textmsg", w, ptheme);
	COORD cur_point = point;
	cur_point.X += i;

	flagReInputName:
	SetConsoleCursorPosition(h, cur_point);
	char ch = getch();
	while (ch != 13) {
		if (TIMER(time_start, TIME_CLEAR_BUF)) {
			if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z'
				|| ch >= 'а' && ch <= 'я' || ch >= 'А' && ch <= 'Я'
				|| ch >= '0' && ch <= '9' || ch == ' ') {
				if (i < max && (ch != ' ' || tmp_name[i - 1] != ' ' && i > 0)) {
					tmp_name[i] = ch;
					tmp_name[++i] = '\0';
					cur_point.X++;
					SetConsoleCursorPosition(h, point);
					if (i < min)
						PrintColorWidth(h, tmp_name, "bgmsg", "lightred", w, ptheme);
					else
						PrintColorWidth(h, tmp_name, "bgmsg", "textmsg", w, ptheme);
				}
			}
			else if (ch == '\b') {
				if (i > 0) {
					tmp_name[--i] = '\0';
					cur_point.X--;
					SetConsoleCursorPosition(h, point);
					if (i == 0)
						PrintColorWidth(h, name_default, "bgmsg", "darkgray", w, ptheme);
					else if (i < min)
						PrintColorWidth(h, tmp_name, "bgmsg", "lightred", w, ptheme);
					else
						PrintColorWidth(h, tmp_name, "bgmsg", "textmsg", w, ptheme);
				}
			}
			else if (ch == '\t') {
				SetColor(h, "bgbase", "textbase", ptheme);
				return 0;
			}
			SetColor(h, "bgmsg", "textmsg", ptheme);
		}
		SetConsoleCursorPosition(h, cur_point);
		ch = getch();
	}
	if ((i < min || i > max) && i > 0) {
		if (ptheme->onSounds) {
			mciSendString(TEXT("play sourse\\sound\\menu\\inputError.mp3"),
				NULL, 0, NULL); //звук
		}
		goto flagReInputName;
	}
	if (ptheme->onSounds) {
		mciSendString(TEXT("play sourse\\sound\\menu\\inputSuccess.mp3"),
			NULL, 0, NULL); //звук
	}

	if (tmp_name[i - 1] == ' ')
		tmp_name[--i] = '\0';
	if (i > 0)
		strcpy(name, tmp_name);
	else
		strcpy(name, name_default);
	SetColor(h, "bgbase", "textbase", ptheme);
	return 1;
}

/*выводит однострочную кнопку с полем ввода числа и 
возвращает значение "истина", если в окне с дескриптором h 
кнопка в блоке pblock с текстом s минимальной ширины ввода w нажата,
записывая по адресу pvalue введенное, иначе возвращает 
"ложь", с цветовой темой структуры по адресу ptheme*/
size_t PrintButtonInputNumber(HANDLE h, Tblock* pblock, char* s, size_t w,
	size_t* pvalue, size_t min, size_t max, Ttheme* ptheme) {
	size_t cursor;
	static clock_t time_start = 0;

	if (GetKeyState(VK_SPACE) < 0 && pblock->cond == BUTTON_HOVER_CUR) {
		cursor = BUTTON_CHOISE;
		goto flagButtonMark;
	}

	Tblock tmp_block = *pblock;
	cursor = CursoreInBlock(tmp_block);
	if (cursor != BUTTON_CHOISE && (pblock->cond == BUTTON_HOVER_KEY ||
		pblock->cond == BUTTON_HOVER_CUR))
		cursor = BUTTON_HOVER_KEY;

	// курсор не наведен 
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			SetConsoleCursorPosition(h, pblock->pos);
			SetColor(h, "bgmsg", "textmsg", ptheme);
			printf("%s", s);

			COORD point = pblock->pos;
			char space[WIDTH];
			GetStrSingleChar(space, ' ', w);
			char space_len_s[WIDTH];
			GetStrSingleChar(space_len_s, ' ', strlen(s));
			char outline[WIDTH];
			GetStrSingleChar(outline, '-', w);

			SetColor(h, "bgmsg", "textmsg", ptheme);
			printf(": |%s|", space);
			MoveConsoleCursorPoint(h, &point, 0, -1);
			printf("%s  .%s.", space_len_s, outline);
			MoveConsoleCursorPoint(h, &point, 0, 2);
			printf("%s  '%s'", space_len_s, outline);
			MoveConsoleCursorPoint(h, &point, strlen(s) + 3, -1);
			printf("%u", *pvalue);

			pblock->cond = BUTTON_NONE;
			SetColor(h, "bgbase", "textbase", ptheme);
		}
	}
	// кнопка выбрана курсором мыши или клавиатурой
	else if (cursor == BUTTON_HOVER || cursor == BUTTON_HOVER_KEY) {
		if (pblock->cond != BUTTON_HOVER && pblock->cond != BUTTON_HOVER_CUR) {
			flagReButtonMark:
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonSwitch1.mp3"),
					NULL, 0, NULL); // звук
			}
			SetConsoleCursorPosition(h, pblock->pos);
			SetColor(h, "bgmsg", "texttarget", ptheme);
			printf("%s", s);

			COORD point = pblock->pos;
			char space[WIDTH];
			GetStrSingleChar(space, ' ', w);
			char space_len_s[WIDTH];
			GetStrSingleChar(space_len_s, ' ', strlen(s));
			char outline[WIDTH];
			GetStrSingleChar(outline, '-', w);

			SetColor(h, "bgmsg", "textmsg", ptheme);
			printf(": |%s|", space);
			MoveConsoleCursorPoint(h, &point, 0, -1);
			printf("%s  x%sx", space_len_s, outline);
			MoveConsoleCursorPoint(h, &point, 0, 2);
			printf("%s  x%sx", space_len_s, outline);
			SetColor(h, "bgmsg", "texttarget", ptheme);
			MoveConsoleCursorPoint(h, &point, strlen(s) + 3, -1);
			printf("%u", *pvalue);

			if (cursor == BUTTON_HOVER_KEY)
				pblock->cond = BUTTON_HOVER_CUR;
			else
				pblock->cond = BUTTON_HOVER;
			SetColor(h, "bgbase", "textbase", ptheme);
		}
	}
	// кнопка нажата
	else if (cursor == BUTTON_CHOISE) {
		flagButtonMark:
		if (TIMER(time_start, SPEED_CLICK)) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
					NULL, 0, NULL); //звук
			}
			COORD point = pblock->pos;
			point.X += strlen(s) + 3;
			InputNumber(h, point, w, min, max, pvalue, ptheme);
			cursor = BUTTON_HOVER_KEY;
			time_start = clock();
			goto flagReButtonMark;
			return 1;
		}
	}
	return 0;
}

/*вывод в окне с дескриптором h в блоке pblock
кнопки с текстом s, которая подсвечивается при
наведении на нее курсора мыши цветом текста ctarget
с базовым фоном cbg и цветом текста ctext, с
цветовой темой структуры по адресу ptheme*/
void PrintStrCursorHover(HANDLE h, Tblock* pblock, char* s,
	char* cbg, char* ctext, char* ctarget, Ttheme* ptheme) {
	size_t cursor = CursoreInBlock(*pblock);
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			SetColor(h, cbg, ctext, ptheme);
			SetConsoleCursorPosition(h, pblock->pos);
			printf("%s", s);
			SetColor(h, "bgbase", "textbase", ptheme);
			pblock->cond = BUTTON_NONE;
			SetColor(h, "bgbase", "textbase", ptheme);
		}
	}
	else if (pblock->cond != BUTTON_HOVER) {
		SetColor(h, cbg, ctarget, ptheme);
		SetConsoleCursorPosition(h, pblock->pos);
		printf("%s", s);
		SetColor(h, "bgbase", "textbase", ptheme);
		pblock->cond = BUTTON_HOVER;
	}
}

/*запись в строку s_in длины len слов из строки s_out 
с цветовой темой структуры по адресу ptheme, возвращая 
указатель на следующий после последнего записанного слова 
символ строки для чтения*/
char* GetStrWords(char* s_in, size_t maxlen, char* s_out, Ttheme* ptheme) {
	char w[SIZE]; // слово
	char* ps_prev = s_out; // позиция перед полученным словом
	char* ps = GetWord(w, s_out, SIZE); // получение слова
	size_t len_word = StrLengthWithoutColor(w, ptheme); // длина полученного слова
	size_t current_len = 0; // текущая длина строки
	*s_in = '\0';

	// пропуск слов, длина которых больше строки для записи
	while (*ps_prev && len_word > maxlen && current_len + 4 <= maxlen) {
		if (current_len) {
			strcat(s_in, " "); // разделитель слов
			current_len++;
		}
		strcat(s_in, "...");
		current_len += 4;
		ps_prev = ps;
		ps = GetWord(w, ps, SIZE);
		len_word = StrLengthWithoutColor(w, ptheme);
	}
	while (*ps_prev && current_len + len_word + 1 < maxlen) {
		if (current_len) {
			strcat(s_in, " "); // разделитель слов
			current_len++;
		}
		strcat(s_in, w);
		current_len += len_word;
		ps_prev = ps;
		ps = GetWord(w, ps, SIZE);
		len_word = StrLengthWithoutColor(w, ptheme);

		// пропуск слов, длина которых больше строки для записи
		while (*ps_prev && len_word > maxlen && current_len + 4 <= maxlen) {
			strcat(s_in, " ...");
			current_len += 4;
			ps_prev = ps;
			ps = GetWord(w, ps, SIZE);
			len_word = StrLengthWithoutColor(w, ptheme);
		}
	}
	if (!*ps_prev) {
		strcat(s_in, w);
		return ps;
	}
	return ps_prev;
}

/*вывод в окне с дескриптором h в блоке block текста 
строки s с цветовой темой структуры по адресу ptheme*/
void PrintStrInBlock(HANDLE h, Tblock block, char* s, 
	char* cbg, char* ctext, Ttheme* ptheme) {
	COORD point = block.pos;
	size_t y_max = block.pos.Y + block.lenY;
	char stmp[SIZE];
	char* pstmp; // указатель на символ строки stmp
	char* ps_out = s;
	char color[50] = ""; // хранение цвета слова
	char color_tmp[50] = ""; // временное хранение цвета слова

	SetConsoleCursorPosition(h, point);
	while (*ps_out && point.Y < y_max) {
		if (*color != '\0') // если в слове был задан цвет
			pstmp = strcpy(stmp, color);
		else
			pstmp = stmp;
		ps_out = GetStrWords(pstmp, block.lenX, ps_out, ptheme);
		AddColorBg(stmp, cbg);
		CopyColorCodeStrEnd(color_tmp, stmp); // получить цвет из строки w
		if (*color_tmp != '\0') { // если получен непустой цвет
			strcpy(color, color_tmp);
		}
		PrintColorWidth(h, stmp, cbg, ctext, block.lenX, ptheme);
		MoveConsoleCursorPoint(h, &point, 0, 1);
	}
}

/*вывод в окне с дескриптором h списка в точке point
с вариантами ответов массива строк options с n параметрами 
с минимальной шириной вывода w, возвращая индекс выборанной 
кнопки или -1, если выбор был отменен, с цветовой темой 
структуры по адресу ptheme*/
int PrintArrButtonSmall(HANDLE h, COORD point, char(*options)[300],
	size_t n, size_t w, Ttheme* ptheme) {
	Tblock* blocks = (Tblock*)calloc(n, sizeof(Tblock));
	// массив указателей на состояния кнопок меню
	size_t** conditions = (size_t**)calloc(n, sizeof(size_t*));

	blocks[0].pos.X = point.X + 1;
	blocks[0].pos.Y = point.Y + 1;
	blocks[0].lenX = w - 2;
	blocks[0].lenY = 1;
	blocks[0].cond = BUTTON_INIT;
	conditions[0] = &blocks[0].cond;
	for (size_t i = 1; i < n; i++) {
		blocks[i] = blocks[i - 1];
		blocks[i].pos.Y++;
		conditions[i] = &blocks[i].cond;
	}
	blocks[0].cond = BUTTON_HOVER_KEY;

	w -= 2;
	char outline[WIDTH];
	GetStrSingleChar(outline, '-', w);
	char space[WIDTH];
	GetStrSingleChar(space, ' ', w);
	SetConsoleCursorPosition(h, point);
	SetColor(h, "bgmsg", "textmsg", ptheme);
	printf(".%s.", outline);
	for (size_t i = 0; i < n; i++) {
		MoveConsoleCursorPoint(h, &point, 0, 1);
		printf("|%s|", space);
	}
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("'%s'", outline);

	// индекс помеченной кнопки
	int target = 0;
	// индекс помеченной кнопки по курсору мыши
	int target_cursore = 0;
	clock_t time_start = 0;
	int choise = -1; // индекс выбранной кнопки
	size_t i = 0;

	Sleep(SPEED_CLICK);
	while (choise < 0 && GetKeyState(VK_ESCAPE) >= 0) {
		if (TIMER(time_start, SPEED_SWITCH_BUTTON)) {
			i = 0;
			target = GetIndexNumberPointer(conditions, n, BUTTON_HOVER_CUR);
			target_cursore = GetIndexNumberPointer(conditions, n, BUTTON_HOVER);
			// перключение между кнопками клавишами
			if (GetKeyState(VK_UP) < 0 && target > 1) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[--target]) = BUTTON_HOVER_KEY;
				time_start = clock();
			}
			else if (GetKeyState(VK_DOWN) < 0 && target + 1 < n) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[++target]) = BUTTON_HOVER_KEY;
				time_start = clock();
			}
			// если был зафиксирован выбор кнопки курсором
			if (target >= 0 && target_cursore >= 0 && target != target_cursore) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[target_cursore]) = BUTTON_HOVER_KEY;
			}
		}
		while (i < n && !PrintButtonSmall(h, &blocks[i], options[i], w, ptheme)) {
			i++;
		}

		if (i < n)
			choise = i;
		SetConsoleCursorPosition(h, point);
	}
	free(blocks);
	Sleep(SPEED_CLICK);
	return choise;
}

/*вывод в окне с дескриптором h кнопки выпадающего списка в 
блоке block с именем s с вариантами ответов массива двумерных 
строк options с n параметрами и их описанием, с минимальной 
шириной вывода w, записывая по адресу pvalue результат выбора 
с цветовой темой структуры по адресу ptheme*/
void PrintDropDownList(HANDLE h, Tblock* pblock, char* s, 
	char (*options)[2][300], size_t n, size_t* pvalue, Ttheme* ptheme) {
	size_t cursor;
	static clock_t time_start = 0;
	Tblock tmp_block = *pblock;
	tmp_block.pos.X++;
	tmp_block.pos.Y++;
	tmp_block.lenX -= 2;
	tmp_block.lenY -= 2;
	
	if (GetKeyState(VK_SPACE) < 0 && pblock->cond == BUTTON_HOVER_CUR) {
		cursor = BUTTON_CHOISE;
		goto flagDropDownList;
	}

	cursor = CursoreInBlock(tmp_block);
	if (cursor != BUTTON_CHOISE && (pblock->cond == BUTTON_HOVER_KEY ||
		pblock->cond == BUTTON_HOVER_CUR))
		cursor = BUTTON_HOVER_KEY;

	// курсор не наведен 
	if (cursor == BUTTON_NONE) {
		if (pblock->cond != BUTTON_NONE) {
			flagReDropDownList:

			COORD point = pblock->pos;
			// вывод верхней линии контура
			size_t w = max(strlen(s) + 2, pblock->lenX);
			char outline[WIDTH];
			GetStrSingleChar(outline, '-', w - 2);
			char space[WIDTH];
			GetStrSingleChar(space, ' ', w - 2);

			SetConsoleCursorPosition(h, pblock->pos);
			SetColor(h, "bgmsg", "textmsg", ptheme);
			printf(".%s.", outline);
			for (size_t i = 0; i < 4; i++) {
				MoveConsoleCursorPoint(h, &point, 0, 1);
				if (i % 2 == 0)
					printf("|%s|", space);
				else
					printf("|%s|", outline);
			}
			size_t i = point.Y, i_max = pblock->pos.Y + pblock->lenY - 2;
			while (i < i_max) {
				MoveConsoleCursorPoint(h, &point, 0, 1);
				printf("|%s|", space);
				i++;
			}
			MoveConsoleCursorPoint(h, &point, 0, 1);
			printf("'%s'", outline);

			// вывод текста на блок
			SetConsoleCursorPoint(h, &point, pblock->pos.X + 1, pblock->pos.Y + 1);
			PrintColorCenter(h, s, "bgmsg", "textmsg", w - 2, ptheme);
			MoveConsoleCursorPoint(h, &point, 1, 2);
			char stmp[WIDTH];
			sprintf(stmp, "%u. %s", *pvalue, options[*pvalue][0]);
			PrintColorWidth(h, stmp, "bgmsg", "textmsg", w - 4, ptheme);
			MoveConsoleCursorPoint(h, &point, 0, 2);
			Tblock tmp_block = *pblock;
			tmp_block.pos.X += 2;
			tmp_block.pos.Y += 5;
			tmp_block.lenX -= 4;
			tmp_block.lenY -= 4;
			PrintStrInBlock(h, tmp_block, options[*pvalue][1], "bgmsg", "textmsg", ptheme);

			pblock->cond = BUTTON_NONE;
		}
	} 
	// кнопка выбрана курсором мыши или клавиатурой
	else if (cursor == BUTTON_HOVER || cursor == BUTTON_HOVER_KEY) {
		if (pblock->cond != BUTTON_HOVER && pblock->cond != BUTTON_HOVER_CUR) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonSwitch1.mp3"),
					NULL, 0, NULL); // звук
			}
			size_t w = max(strlen(s) + 2, pblock->lenX);
			COORD point = pblock->pos;
			SetConsoleCursorPoint(h, &point, pblock->pos.X + 1, pblock->pos.Y + 1);
			PrintColorCenter(h, s, "bgmsg", "texttarget", w - 2, ptheme);
			MoveConsoleCursorPoint(h, &point, 1, 2);
			char stmp[WIDTH];
			sprintf(stmp, "%u. %s", *pvalue, options[*pvalue][0]);
			PrintColorWidth(h, stmp, "bgmsg", "texttarget", w - 4, ptheme);

			if (cursor == BUTTON_HOVER_KEY)
				pblock->cond = BUTTON_HOVER_CUR;
			else
				pblock->cond = BUTTON_HOVER;
		}
	} 
	// кнопка нажата
	else if (cursor == BUTTON_CHOISE) {
		flagDropDownList:
		if (TIMER(time_start, SPEED_CLICK)) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
					NULL, 0, NULL); //звук
			}
			size_t w = max(strlen(s) + 2, pblock->lenX);
			COORD point = pblock->pos;
			point.Y += 2;
			char(*tmp_options)[300] = (char**)calloc(n, sizeof(char) * 300);
			for (size_t i = 0; i < n; i++) {
				sprintf(tmp_options[i], " %u. %s", i, options[i][0]);
			}
			int choise = PrintArrButtonSmall(h, point, tmp_options, n, w, ptheme);
			free(tmp_options);
			if (choise >= 0)
				*pvalue = choise;
			time_start = clock();
			goto flagReDropDownList;
		}
	}
}
