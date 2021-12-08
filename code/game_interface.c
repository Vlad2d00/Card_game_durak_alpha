#include "header.h"

#if !defined(__PRINT_ELEMENTS_H)
void PrintSpecialCard(HANDLE h, COORD point);
#endif 

#if !defined(__BUTTONS_H) 
POINT GetSellSize(HWND h);
POINT GetMousePos(HWND h, POINT sellSz);
#endif 

/*возвращает символ достоинства карты для номинала n*/
char GetCharDigintyCard(size_t n) {
	switch (n) {
		case 11: return 'В';
		case 12: return 'Д';
		case 13: return 'К';
		case 14: return 'Т';
		default: return n + '0';
	}
}

/*возвращает число - достоинство карты для символа ch*/
char GetNomanalDigintyCard(char ch) {
	switch (ch) {
		case 'В': return 11;
		case 'Д': return 12;
		case 'К': return 13;
		case 'Т': return 14;
	}
}

/*вывод карты a*/
void PrintCard(Tcard a) {
	printf("%c%c ", GetCharDigintyCard(a.n), a.m);
}

/*вывод массива карт a размера n*/
void PrintArrCard(Tcard* a, size_t n) {
	for (size_t i = 0; i < n; i++)
		PrintCard(a[i]);
	putchar('\n');
}

/*запись в строку s номинала и масти карты a, 
возвращая ее новую длину*/
void StrPrintCardText(char* s, Tcard a) {
	switch (a.n) {
		case 11:
			sprintf(s, "Валет "); break;
		case 12:
			sprintf(s, "Дама "); break;
		case 13:
			sprintf(s, "Король "); break;
		case 14:
			sprintf(s, "Туз "); break;
		default:
			sprintf(s, "%u ", a.n); break;
	}
	s += strlen(s);
	switch (a.m) {
		case 'ч':
			sprintf(s, "черви"); break;
		case 'б':
			sprintf(s, "бубны"); break;
		case 'п':
			sprintf(s, "пик"); break;
		case 'к':
			sprintf(s, "крест"); break;
	}
}

/*вывод в окне с дескриптором h, по структуре по адресу 
pblocks заголовка игрового стола, включающего в себя 
кнопку меню, игроков, чей ход и от кого ожидается ответ, 
событийный эффект из стркутуры по адресу pGameTable с 
цветовой темой структуры по адресу ptheme*/
void PrintHeaderGame(HANDLE h, TblocksGame* pblocks, TgameTable* pGameTable, Ttheme* ptheme) {
	SetConsoleCursorPosition(h, pblocks->header.pos);
	PrintColorCenter(h, "", "bgmsg", "bgmsg", WIDTH, ptheme);
	char s[SIZE];

	if (pGameTable->end_game) { // если конец игры
		PrintColorCenter(h, "Игра завершена!", "bgmsg", "textmsg", WIDTH, ptheme);
		PrintColorCenter(h, "", "bgmsg", "bgmsg", WIDTH, ptheme);
	}
	else if (pGameTable->end_move) {
		PrintColorCenter(h, "Конец хода! Нажмите [Shift], чтобы продолжить", "bgmsg", "textmsg", WIDTH, ptheme);
		PrintColorCenter(h, "", "bgmsg", "bgmsg", WIDTH, ptheme);
	} 
	else {
		if (pGameTable->defend_player == pGameTable->user && pGameTable->mode != GAME_AI &&
			pGameTable->mode != GAME_SIMULATION)
			PrintColorCenter(h, "Вы под атакой!", "bgmsg", "lightred", WIDTH, ptheme);
		else if (pGameTable->move < 6) {
			sprintf(s, "%u-й игрок под атакой!", pGameTable->defend_player + 1);
			PrintColorCenter(h, s, "bgmsg", "green", WIDTH, ptheme);
		}
		if (pGameTable->priority == pGameTable->user && pGameTable->mode != GAME_AI &&
			pGameTable->mode != GAME_SIMULATION) {
			if (pGameTable->player_state[pGameTable->user] == ATTACK)
				PrintColorCenter(h, "(ождание вашего ответа)",
					"bgmsg", "textmsg", WIDTH, ptheme);
			else if (pGameTable->player_state[pGameTable->user] == PROTECTION)
				PrintColorCenter(h, "(ождание вашего ответного действия)",
					"bgmsg", "textmsg", WIDTH, ptheme);
			else if (pGameTable->player_state[pGameTable->user] == CAN_BE_THROWN)
				PrintColorCenter(h, "(можно подкинуть противнику карт)",
					"bgmsg", "textmsg", WIDTH, ptheme);
			else
				PrintColorCenter(h, "(вы пасанули)",
					"bgmsg", "textmsg", WIDTH, ptheme);
		} else {
			sprintf(s, "(ождание ответа от %u-го игрока)", pGameTable->priority + 1);
			PrintColorCenter(h, s, "bgmsg", "textmsg", WIDTH, ptheme);
		}
	}
	
	SetConsoleCursorPosition(h, pblocks->esc.pos);
	SetColor(h, "bgmsg", "textmsg", ptheme);
	printf("|=| Esc"); // кнопка вызова небольшого меню

	SetConsoleCursorPosition(h, pblocks->effect.pos);
	// скопировать название событийного эфекта в структуру
	sprintf(pblocks->s_effect, "Событийный эффект: %s", 
		optionsEffects[pGameTable->event_effect][0]);
	printf("%s", pblocks->s_effect);
	pblocks->effect.lenX = strlen(pblocks->s_effect);
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*запись по адресам pdist и pindent расстояния 
между базовыми точками масива карт и отступов 
до этих карт в блочном элементе block с n картами*/
void GetDistanceAndIndentCards(size_t* pdist, size_t* pindent, 
	Tblock block, size_t n) {
	*pdist = 12; // растояние между базовыми точками карт
	int t = block.lenX - (12 * n - 1);
	// кол-во символов, на которое необходимо сжать карты
	size_t compress = t < 0 ? (size_t)-t : 0;
	if (compress > 0) { // если не хватает места картам в окне
		*pdist -= compress / n + (compress % n > 0);
	}
	if (*pdist * (n - 1) + 11 > block.lenX) {
		(*pdist)--;
	}
	// отступы от краеев блока
	*pindent = (block.lenX - *pdist * (n - 1) - 11) / 2;
}

/*вывод в окне с дескриптором h изображений карт 
в один горизонтальный ряд, в блочном элементе block, 
из массива карт a  размера n с цветовой темой 
структуры по адресу pthemeт*/
void PrintImgCards(HANDLE h, Tblock block, Tcard* a, size_t n, Ttheme* ptheme) {
	size_t distance = 0; // расстояние между базовыми точками массива карт
	size_t baseX = block.pos.X;
	size_t baseY = block.pos.Y;

	/*сделано для того, чтобы у пользователя каждый раз при переходе
	с карты на карту не создавался эффект мелькания его массива карт*/
	// кол-во карт в массиве при предыдущем вызове функции
	static size_t old_count_cards = 0;
	static Tblock old_block = { 0 };
	if (old_count_cards != n || old_block.pos.X != block.pos.X
		|| old_block.pos.Y != block.pos.Y) {
		char s_space[WIDTH];
		GetStrSingleChar(s_space, ' ', block.lenX);

		SetConsoleCursorPosition(h, block.pos);
		SetColor(h, "bgbase", "textbase", ptheme);
		for (size_t i = 0; i < 8; i++) { // очистить область блока
			printf("%s", s_space);
			MoveConsoleCursorPoint(h, &block.pos, 0, 1);
		}
	}
	old_count_cards = n;
	old_block.pos.X = block.pos.X;
	old_block.pos.Y = block.pos.Y;

	if (n) {
		SetColor(h, "bgbase", "textbase", ptheme);
		size_t indentation = 0;
		GetDistanceAndIndentCards(&distance , &indentation, block, n);

		SetConsoleCursorPoint(h, &block.pos, baseX, baseY);
		block.pos.X += indentation;
		for (size_t i = 0; i < n; i++) { // вывод карт
			PrintImgCard(h, block.pos, a[i], ptheme);
			block.pos.X += distance;
		}

	} else { // если карт нет в массиве
		SetConsoleCursorPoint(h, &block.pos, baseX + block.lenX / 2 - 5, baseY + 3);
		PrintColor(h, "\\darkgray:- Пусто -", ptheme);
	}
}

/*вывод в окне с дескриптором h, начиная с точки 
point, n рубашек карт в один горизонтальный ряд 
размера n в блочном элементе block с цветовой темой
структуры по адресу ptheme*/
void PrintShirtCards(HANDLE h, Tblock block, size_t n, Ttheme* ptheme) {
	size_t distance = 0; // расстояние между базовыми точками массива карт
	size_t baseX = block.pos.X;
	size_t baseY = block.pos.Y;

	SetConsoleCursorPosition(h, block.pos);
	SetColor(h, "bgbase", "textbase", ptheme);
	for (size_t i = 0; i < 8; i++) { // очистить область блока
		for (size_t j = 0; j < block.lenX; j++) {
			printf(" ");
		}
		MoveConsoleCursorPoint(h, &block.pos, 0, 1);
	}

	if (n) {
		size_t indentation = 0;
		GetDistanceAndIndentCards(&distance, &indentation, block, n);

		SetConsoleCursorPoint(h, &block.pos, baseX, baseY);
		SetColor(h, "bgbase", "texttarget", ptheme);
		block.pos.X += indentation;
		for (size_t i = 0; i < n; i++) { // вывод карт
			PrintShirtCard(h, block.pos, ptheme);
			block.pos.X += distance;
		}

	} else { // если карт нет в массиве
		SetConsoleCursorPoint(h, &block.pos, baseX + block.lenX / 2 - 5, baseY + 3);
		PrintColor(h, "\\darkgray:- Пусто -", ptheme);
	}
}

/*вывод в окне с дескриптором h в точку point из массива 
карт a размера n области k-й карты при дистанции между 
базовыми точками карт distance с цветовой темой 
структуры по адресу ptheme*/
void RePrintImgRegionCards(HANDLE h, COORD point, Tcard* a,
	size_t n, size_t k, size_t distance, Ttheme* ptheme) {
	if (distance >= 10) {
		PrintImgCard(h, point, a[k], ptheme);

	} else {
		size_t posX[11]; // массив позиций карт по оси X
		size_t x_end = point.X - 11; // конечная точка
		size_t x0 = point.X - distance;
		size_t i_max = 0; // сколько карт нужно перевывести с одной стороны базовой карт
		//size_t minX = point.X - k * distance - indentation;
		//size_t maxX = point.X + (n - 1 - k) * distance + indentation;
		while (x0 >= x_end) {
			posX[i_max++] = x0;
			x0 -= distance;
		}
		size_t i = 0;
		size_t baseX = point.X;
		point.X -= distance * i_max;
		while (i < i_max && (int)(k - i) > 0) { // вывод частей карт до базовой
			PrintRegionImgCardColor(h, point, a[k - (i_max - i)], 0, distance, ptheme);
			point.X += distance;
			i++;
		}
		point.X = baseX;
		i = 0;
		while (i <= i_max && k + i < n - 1) { // вывод частей карт после базовой
			PrintRegionImgCardColor(h, point, a[k + i], 0, distance, ptheme);
			point.X += distance;
			i++;
		}
		if (k + i == n - 1) {
			PrintImgCard(h, point, a[k + i], ptheme);
		}
	}
}

/*возвращает точку для вывода k-й карты из 
массива состояний карт cond_battle в блоке block*/
COORD GetPointCardBattle(size_t k, size_t* cond_battle, Tblock block) {
	const size_t biasX = 5; // смещение карты по Ox, которая бъет
	const size_t biasY = 1; // смещение карты по Oy, которая бъет
	const size_t distance = 11 + biasX + 2; // растояние между базовыми точками карт

	COORD point = block.pos;
	size_t count_cards_row = block.lenX / distance;
	size_t count_cond = 0; // кол-во карт таких же стостояний
	for (size_t i = 0; i < k; i++) {
		if (cond_battle[i] == cond_battle[k])
			count_cond++;
	}
	point.X += distance * (count_cond % count_cards_row);
	point.Y += 9 * (count_cond / count_cards_row);

	if (cond_battle[k] == PROTECTION) {
		point.X += biasX;
		point.Y += biasY;
	}
	return point;
}

/*вывод в окне с дескриптором h изображений карт
высотой до двух горизонтальный рядов, начиная с 
точки point, из массива карт a размера n с состоянием 
карт cond_battle в блоке длины size с цветовой 
темой структуры по адресу ptheme*/
void PrintCardsBattle(HANDLE h, Tblock block, Tcard* a,
	size_t n, size_t* cond_battle, size_t size, Ttheme* ptheme) {
	COORD point = block.pos;
	SetConsoleCursorPosition(h, point);
	SetColor(h, "bgbase", "textbase", ptheme);
	for (size_t i = 0; i < 19; i++) { // очистить область блока
		for (size_t j = 0; j < size; j++) {
			printf(" ");
		}
		MoveConsoleCursorPoint(h, &point, 0, 1);
	}
	SetConsoleCursorPoint(h, &point,
		block.pos.X + WIDTH_BATTLE / 2 - 9, block.pos.Y - 1);
	printf("Карты на поле боя");

	if (n) {
		size_t c_attack = 0, c_protect = 0;
		for (size_t i = 0; i < n; i++) { // вывод карт
			point = GetPointCardBattle(i, cond_battle, block);
			PrintImgCard(h, point, a[i], ptheme);
			if (cond_battle[i] == PROTECTION) {
				SetColorBySuit(h, a[i].m, ptheme);
				MoveConsoleCursorPoint(h, &point, 5, 0);
				printf("|");
			}
		}
		if (cond_battle[n - 1] == PROTECTION)
			MoveConsoleCursorPoint(h, &point, -5, 0);

	} else { // если карт нет в массиве
		SetConsoleCursorPoint(h, &point, block.pos.X + size / 2 - 5, block.pos.Y + 8);
		PrintColor(h, "\\darkgray:- Пусто -", ptheme);
	}
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*вывод в окне с дескриптором h блока размера 
24 x 16 состощего из общей колоды, начиная с точки 
 point карт общей колоды вверх рубашкой с нижней 
 открытой картой, козырной масти и номера хода с 
 цветовой темой структуры по адресу ptheme*/
void PrintInfoGame(HANDLE h, COORD point, TgameTable* pGameTable, Ttheme* ptheme) {
	size_t baseX = point.X;
	size_t baseY = point.Y;
	static f = 1; // есть ли карты в колоде карт

	if (pGameTable->c_deck) {
		f = 1;
		MoveConsoleCursorPoint(h, &point, 6, 0);
		PrintImgCard(h, point, pGameTable->bottom_card, ptheme);
		SetColor(h, "bgbase", "texttarget", ptheme);
		MoveConsoleCursorPoint(h, &point, -3, 4); // 1-я строка
		if (pGameTable->c_deck > 10) {
			printf(" /|/\\/\\/\\/\\/\\/\\/\\/|");
			for (size_t i = 0, f = 1; i < 3; i++, f++) {
				MoveConsoleCursorPoint(h, &point, 0, 1); // (2 + i)-я строка
				if (f % 2)
					printf("| |/\\/\\/\\/\\/\\/\\/\\/|");
				else
					printf("| |\\/\\/\\/\\/\\/\\/\\/\\|");
			}
			MoveConsoleCursorPoint(h, &point, 0, 1); // 5-я строка
			printf("| |_______________|");
			MoveConsoleCursorPoint(h, &point, 0, 1); // 6-я строка
			printf("|/_______________/ ");
		} else {
			printf("   ");
			MoveConsoleCursorPoint(h, &point, 14, 0);
			printf("     ");
			MoveConsoleCursorPoint(h, &point, -14, 0);
			for (size_t i = 0, f = 1; i < 4; i++, f++) {
				MoveConsoleCursorPoint(h, &point, 0, 1); // (2 + i)-я строка
				if (f % 2)
					printf("|/\\/\\/\\/\\/\\/\\/\\/|  ");
				else
					printf("|\\/\\/\\/\\/\\/\\/\\/\\|  ");
			}
			MoveConsoleCursorPoint(h, &point, 0, 1); // 5-я строка
			printf("|_______________|  ");
		}
	} else {
		if (f) { // очищение места, в котором была колода карт
			Tblock block;
			block.pos = point;
			block.lenX = 19;
			block.lenY = 10;
			MoveConsoleCursorPoint(h, &point, 3, 0);
			PrintRectangle(h, block, "bgbase", ptheme);
			MoveConsoleCursorPoint(h, &point, -3, 0);
			f = 0;
		}
	}

	SetConsoleCursorPoint(h, &point, baseX, baseY + 11);
	SetColor(h, "bgbase", "textbase", ptheme);
	printf("Кол-во карт в колоде: %u  ", pGameTable->c_deck);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "Козырная масть: ", ptheme);
	switch (pGameTable->trump) {
		case 'ч':
			PrintColor(h, "\\suit1:черва  ", ptheme); break;
		case 'б':
			PrintColor(h, "\\suit1:бубна  ", ptheme); break;
		case 'п':
			PrintColor(h, "\\suit2:пика   ", ptheme); break;
		case 'к':
			PrintColor(h, "\\suit2:креста ", ptheme); break;
	}
	char s[SIZE];
	MoveConsoleCursorPoint(h, &point, 0, 2);
	sprintf(s, "Ход №%u", pGameTable->move_number);
	PrintColorCenter(h, s, "bgbase", "textbase", 24, ptheme);

	MoveConsoleCursorPoint(h, &point, 0, 1);
	if (pGameTable->mode == GAME_SIMULATION) {
		printf("Время игры: - ");
	} else {
		size_t sec = (clock() - pGameTable->time_start) / CLOCKS_PER_SEC;
		sprintf(s, "Время игры: %02u:%02u", sec / 60, sec % 60);
		pGameTable->time_sec = sec;
	}
	PrintColorCenter(h, s, "bgbase", "textbase", 24, ptheme);
}

/*вывод в окне с дескриптором h, в блоке block строки 
сообщеий чата chat с цветовой темой структуры по 
адресу ptheme*/
void PrintChat(HANDLE h, Tblock block, char(*chat)[SIZE], Ttheme* ptheme) {
	SetConsoleCursorPosition(h, block.pos);
	PrintColorCenter(h, "- ЧАТ -", "bgmsg", 
		"texttarget", block.lenX, ptheme);

	size_t i_max = block.lenY - 4;
	for (size_t i = 0; i <= i_max; i++) {
		MoveConsoleCursorPoint(h, &block.pos, 0, 1);
		PrintColorWidth(h, chat[i], "bgmsg", "textmsg", block.lenX, ptheme);
	}
	MoveConsoleCursorPoint(h, &block.pos, 0, 1);
	char s[SIZE];
	for (size_t i = 0; i < block.lenX; i++) {
		s[i] = '_';
	}
	s[block.lenX] = '\0';
	PrintColorCenter(h, s, "bgmsg", "textmsg", block.lenX, ptheme);
	MoveConsoleCursorPoint(h, &block.pos, 0, 1);
	PrintColorWidth(h, "", "bgmsg", "darkgray", block.lenX, ptheme);
}

/*запись в строку w слова из строки s, длиной 
не более size символов при этом возвращая указатель 
на следующий символ после считанного слова*/
char* GetWord(char* w, char* s, size_t size) {
	size_t i = 0, j = 0;
	// пропуск пустых символов
	while ((unsigned char)s[i] <= ' ' && s[i] != '\0') 
		i++;
	size_t f = 0;
	// получение слова или полуслова, если внутри слова есть '-'
	while (j < size && (unsigned char)s[i] > ' ' && s[i] != '\0') {
		if (s[i] == '\\')
			f = 1;
		if (s[i] == ':' && f)
			f = 0;
		if (s[i] == '-' && !f)
			goto flagGetWord;
		w[j++] = s[i++];
	}
	flagGetWord:
	if (s[i] == '-') {
		w[j++] = '-';
		i++;
	}
	w[j] = '\0';
	return s + i;
}

/*перемещение строк массива строк a размера n на один 
индекс назад, стирая содержимое строки с нулевым индексом*/
void ChatMsgPosOffset(char (*a)[SIZE], size_t n) {
	size_t max_i = n - 1;
	for (size_t i = 0; i < max_i; i++) {
		strcpy(a[i], a[i + 1]);
	}
	a[max_i][0] = '\0';
}

/*запись в массив строк чата chat в блоке block сообщения 
из строки s с цветовой темой структуры по адресу ptheme*/
void UpdateChat(char (*chat)[SIZE], Tblock block, char* s, Ttheme* ptheme) {
	char w[SIZE]; // слово
	char* ps = GetWord(w, s, SIZE); // получение слова из сообщения
	size_t current_len = StrLengthWithoutColor(w, ptheme); // длина временной строки
	char stmp[SIZE]; // временная строка для записи
	strcpy(stmp, w); // запись слова во временную строку для записи

	size_t i_str = 0; // индекс строки для вывода сообщения
	size_t max_i_str = block.lenY - 4;
	while (i_str < max_i_str && chat[i_str][0] != '\0') {
		i_str++;
	}

	ps = GetWord(w, ps, SIZE);
	size_t len;
	char color[50] = ""; // хранение цвета слова
	char color_tmp[50] = ""; // временное хранение цвета слова

	if (i_str >= max_i_str && *chat[i_str] != '\0') // если чат переполнен
		ChatMsgPosOffset(chat, block.lenY - 2); // сдвинуть строки чата вверх на 1
	while (*w) {
		len = StrLengthWithoutColor(w, ptheme);
		if (len > block.lenX) {
			strcpy(w, "..."); // замена полученного слова на троеточие
			len = 3;
		} 
		if (current_len + len + 2 > block.lenX) { // если будет переполнена строка чата
			strcpy(chat[i_str], stmp); // поместить строку в чат
			if (*color != '\0') // если в слове был задан цвет
				strcpy(stmp, color);
			else
				strcpy(stmp, "\0"); // обнулить временную строку

			if (i_str >= max_i_str) // если чат переполнен
				ChatMsgPosOffset(chat, block.lenY - 3); // сдвинуть строки чата вверх на 1
			else
				i_str++;
			current_len = 0;
		} else if (*w && stmp[strlen(stmp) - 1] != '-'){ // добавить пробел между словами
			strcat(stmp, " ");
			current_len++;
		}

		AddColorBg(w, "bgmsg");
		strcat(stmp, w); // поместить слово во временную строку
		current_len += len;
		CopyColorCodeStr(color_tmp, w); // получить цвет из строки w
		if (*color_tmp != '\0') { // если получен непустой цвет
			strcpy(color, color_tmp);
		}
		ps = GetWord(w, ps, SIZE);
	}
	strcpy(chat[i_str], stmp); // поместить строку в чат
}

/*запись в строку s_out сообщения s_in от игрока 
с именем name цветом color с цветовой темой 
структуры по адресу ptheme*/
void GetMsgForChat(char* s_out, char* s_in, char* name,
	char* color, Ttheme* ptheme) {
	sprintf(s_out, "\\%s-bgmsg:%s:\\textmsg-bgmsg: %s", color, name, s_in);
}

/*возвращает значение "истина", если в строке s есть 
текст команды, возвращая ее индекс и записывая в 
строку args ее аргументы иначе, если команда не найдена, 
в списке доступных команд, возвращает значение "ложь"*/
int GetCommandFromStr(char* s, char* args) {
	while (*s && *s <= ' ') { // пропуск пробелов
		s++;
	}
	if (*s && *s == '\\') {
		s++;
		// считывание команды
		char command[100];
		char* pcommand = command;
		while (*s && ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') 
			|| (*s >= '1' && *s <= '9'))) {
			*pcommand++ = GetLowCh(*s++);
		}
		*pcommand = '\0';
		while (*s && *s <= ' ') { // пропуск пустых символов
			s++;
		}
		if (*s) {
			// считывание аргументов команды, пропуская подстроки пустых символов длины больше 1
			while (*s) {
				if (*s <= ' ' && *(s - 1) <= ' ')
					*s++;
				else
					*args++ = *s++;
			}
			if (*(args - 1) <= ' ')
				args--;
		}
		*args = '\0';
		// поиск команды среди тех, что есть в базе данных
		for (size_t i = 1; i <= countCommand; i++) {
			char tmp_command[100];
			char* ptmp_command = tmp_command;
			strcpy(tmp_command, commandList[i]);
			// приведение строки команды к нижнему регистру
			while (*ptmp_command) {
				*ptmp_command = GetLowCh(*ptmp_command);
				ptmp_command++;
			}
			if (!strcmp(tmp_command, command)) {
				return i;
			}
		}
	}
	return 0;
}

/*ввод в строку s строки максимальной длины MAX_LEN_MESSAGE, 
отображая в окне с дескриптором h в точке point ввод 
ширины len_input, учитывая цветные теги структуры по 
адресу ptheme, возвращая положительное значение, если ввод 
подтвержден, иначе если ошибка, то значение отрицательное, иначе 0*/
int InputTextInChat(HANDLE h, COORD point, char* s, size_t len_input, Ttheme* ptheme) {
	static clock_t time_start_mes = 0; // время отправления сообщения
	clock_t time_start = clock();
	size_t i = 0, j = 0;
	size_t pos = 0;
	unsigned char ch = 0;
	unsigned char* ps = s;

	*s = '\0';
	SetConsoleCursorPosition(h, point);
	PrintColorWidth(h, "\\darkgray-bgmsg:Введите сообщение или нажмите \\texttarget-bgmsg:<Tab>\\darkgray-bgmsg:, чтобы закрыть чат", "bgmsg", "textmsg", len_input, ptheme);
	SetColor(h, "bgmsg", "textmsg", ptheme);
	SetConsoleCursorPosition(h, point);
	ch = getch();
	while (ch != 13 || s[0] == '\0') {
		if (TIMER(time_start, TIME_CLEAR_BUF)) {
			if (ch == '\b') { // удаление символа
				if (i > 0)
					s[--i] = '\0';
				if (i >= len_input)
					ps--;
			} 
			else if (ch == '\t' && TIMER(time_start, SPEED_CLICK)) { // отмена ввода
				return 0;
			}
			else if (i < MAX_LEN_MESSAGE && ch >= ' ' && TIMER(time_start, SPEED_CLICK)) { // ввод символа
				if (i >= len_input)
					ps++;
				s[i] = ch;
				s[++i] = '\0';
			}

			SetConsoleCursorPosition(h, point);
			if (i == 0)
				PrintColorWidth(h, "\\darkgray-bgmsg:Введите сообщение или нажмите \\texttarget-bgmsg:<Tab>\\darkgray-bgmsg:, чтобы закрыть чат", "bgmsg", "textmsg", len_input, ptheme);
			else
				PrintColorTagWidth(h, ps, "bgmsg", "textmsg", len_input, ptheme);
			SetColor(h, "bgmsg", "textmsg", ptheme);
		}
		SetConsoleCursorCoord(h, point.X + (i > len_input ? len_input : i) - pos, point.Y);
		ch = getch();
	}

	if (!TIMER(time_start_mes, 3000)) {
		return -1;
	}
	time_start_mes = clock();
	return 1;
}

/*возвращает блок, в котором располагаются карты k-го 
игрока из структуры по адресу game_table по координатам 
структуры по адресу pblocks*/
Tblock GetBlockPlayer(size_t k, TgameTable* pGameTable, TblocksGame* pblocks) {
	size_t position = 0; // позиция на игровом столе после пользователя
	Tblock block; // блок, в котором находится выводимый элемент
	if (k == pGameTable->user) { // если вывод карт игрока
		block = pblocks->cards_user;
	}
	else { // если вывод карт одного из противников
		size_t count_moving = 0;
		position = pGameTable->mode == GAME_AI ? 0 : pGameTable->user;
		while (position != k) {
			position = (position + 1) % pGameTable->count_players;
			count_moving++;
		}
		position = count_moving;

		// кол-во игроков за столом
		if (pGameTable->count_players == 2) { // если 2 игрока
			if (position == 0)
				block = pblocks->cards_user;
			else
				block = pblocks->cards_p2_2;
		} else if (pGameTable->count_players == 3) { // если 3 игрока
			switch (position) {
				case 0:
					block = pblocks->cards_user; break;
				case 1:
					block = pblocks->cards_p2_3; break;
				case 2:
					block = pblocks->cards_p3_3; break;
			}
		} else if (pGameTable->count_players == 4) { // если 4 игрока
			switch (position) {
				case 0:
					block = pblocks->cards_user; break;
				case 1:
					block = pblocks->cards_p2_4; break;
				case 2:
					block = pblocks->cards_p3_4; break;
				case 3:
					block = pblocks->cards_p4_4; break;
			}
		} else { // если игроков 5+ (включительно)
			switch (position) {
			case 0:
				block = pblocks->cards_user; break;
			case 1:
				block = pblocks->cards_p5_5; break;
			case 2:
				block = pblocks->cards_p2_4; break;
			case 3:
				block = pblocks->cards_p3_4; break;
			case 4:
				block = pblocks->cards_p4_4; break;
			case 5:
				block = pblocks->cards_p6_6; break;
			}
		}
	}
}

/*запись в строку имени k-го игрока и его состояния 
в игре из структуры по адресу game_table в блоке 
block, с цветом фона cbg и цветом текста ctext, с 
цветовой темой структуры по адресу ptheme, 
возвращая растояние между базовыми точками карт*/
void GetHeaderNamePlayer(char *s, size_t k, TgameTable* pGameTable, 
	Tblock block, char* cbg, char* ctext, Ttheme* ptheme) {
	char condition[50];
	if (k == pGameTable->defend_player)
		strcpy(condition, "(x)");
	else if (k == pGameTable->priority)
		strcpy(condition, "(...)");
	else
		strcpy(condition, "");

	if (pGameTable->c_player[k]) { // если у игрока есть карты
		if (k == pGameTable->user && (pGameTable->mode == GAME_STANDART
			|| pGameTable->mode == GAME_STANDART_SEE)) {
			sprintf(s, "\\%s-%s:Карты на ваших руках \\suit1-%s:%s", 
				ctext, cbg, cbg, condition);

		} else {
			if (pGameTable->name_player[k][0] == '\0')
				sprintf(s, "\\%s-%s:Карты на руках %u-го игрока \\suit1-%s:%s", 
					ctext, cbg, k + 1, cbg, condition);
			else
				sprintf(s, "\\%s-%s:Карты на руках %s \\suit1-%s:%s",
					ctext, cbg, pGameTable->name_player[k], cbg, condition);
		}
	} else {
		if (k == pGameTable->user && (pGameTable->mode == GAME_STANDART
			|| pGameTable->mode == GAME_STANDART_SEE)) {
			sprintf(s, "\\%s-%s:Вы вышли из игры победителем :)", ctext, cbg);

		} else {
			if (pGameTable->name_player[k][0] == '\0')
				sprintf(s, "\\%s-%s:%u-й игрок вышел из игры", ctext, cbg, k + 1);
			else
				sprintf(s, "\\suit1-%s:%s \\textbase:вышел из игры",
					cbg, pGameTable->name_player[k]);
		}
	}
}

/*вывод в окне с дескриптором h массива карт a
k-го игрока стороной face и его имени и состояния 
из структуры по адресу game_table по координатам 
структуры по адресу pblocks, с цветовой темой 
структуры по адресу ptheme, возвращая растояние 
между базовыми точками карт*/
void PrintCardsAndNamePlayer(HANDLE h, Tcards* a, size_t k, size_t face, 
	TgameTable* pGameTable, TblocksGame* pblocks, Ttheme* ptheme) {
	Tblock block = GetBlockPlayer(k, pGameTable, pblocks);
	if (face) { // если карты нужно вывести лицом вверх
		PrintImgCards(h, block, a, pGameTable->c_player[k], ptheme);
	} else {
		PrintShirtCards(h, block, pGameTable->c_player[k], ptheme);
	}
	block.pos.Y--;
	char s[SIZE];
	SetConsoleCursorPosition(h, block.pos);
	GetHeaderNamePlayer(s, k, pGameTable, block, "bgbase", "textbase", ptheme);
	PrintColorCenter(h, s, "bgbase", "textbase", block.lenX, ptheme);
}

/*возвращает индекс карты игрового стола, на которою
наведен курсор в позиции mouse_pos и координатам
структуры по адресу pblocks с количеством карт 
пользователя n, иначе возвращает -1*/
int CursoreCardGameTable(TblocksGame* pblocks, size_t n) {
	HWND hwnd = GetConsoleWindow();
	POINT mouse_pos; // координаты мыши
	POINT sellSize = GetSellSize(hwnd); // размер символа в пикселях
	mouse_pos = GetMousePos(hwnd, sellSize);

	int elem = -1;
	size_t n1 = n - 1;
	if (mouse_pos.y > pblocks->cards_user.pos.Y && mouse_pos.y 
		<= pblocks->cards_user.pos.Y + pblocks->cards_user.lenY) {
		for (size_t i = 0; i < n1; i++) {
			if (mouse_pos.x >= pblocks->pos_cards[i])
				if (mouse_pos.x < pblocks->pos_cards[i + 1])
					return i;
		}
		if (mouse_pos.x >= pblocks->pos_cards[n1]
			&& mouse_pos.x < pblocks->pos_cards[n1] + 11)
			return n1;
	}
	return elem;
}

/*вывод в окне с дескриптором h в точке point 
карты card в инвертированном цвете и приподнятой
на 2 символа с цветовой темой структуры по адресу ptheme*/
void PrintfChoiseCardGameTable(HANDLE h, COORD point, Tcard card, Ttheme* ptheme) {
	point.Y -= 2;
	PrintImgCardColor(h, point, card, "textbase", "bgbase", ptheme);
	point.Y += 8;

	Tblock block;
	block.pos = point;
	block.lenX = 11;
	block.lenY = 2;
	PrintRectangle(h, block, "bgbase", ptheme);
}

/*вывод в окне с дескриптором h в блоке block
ячейки, для карты, наводя на которую курсор мыши 
выводится карта card инвертированном цвете с 
цветовой темой структуры по адресу ptheme*/
void PrintCellForCard(HANDLE h, Tblock* block, Tcard card, Ttheme* ptheme) {
	size_t cursor = CursoreInBlock(*block);
	if (cursor == BUTTON_NONE) {
		if (block->cond != BUTTON_NONE) {
			block->pos.Y++;
			PrintRectangle(h, *block, "bgtarget", ptheme);
			block->pos.Y--;
			block->cond = BUTTON_NONE;
		}
	} else if (block->cond != BUTTON_HOVER) {
		PrintImgCardColor(h, block->pos, card, "textbase", "bgtarget", ptheme);
		block->cond = BUTTON_HOVER;
	}
}

/*запись в массив pos_cards координат карт с 
началом блока их вывода по оси x равным posX 
с расстоянием между ними distance и количеством n*/
void GetCoordArrCards(size_t* pos_cards, size_t posX, size_t distance, size_t n) {
	if (n) {
		pos_cards[0] = posX;
		for (size_t i = 1; i < n; i++) {
			pos_cards[i] = pos_cards[i - 1] + distance;
		}
	}
}

/*вывод в окне с дескриптором h в точке point время, 
которое прошло с начала момента времени start*/
void UpdateTime(HANDLE h, COORD point, clock_t start) {
	size_t sec = (clock() - start) / CLOCKS_PER_SEC;
	static size_t old_sec = 0;
	if (old_sec != sec) {
		SetConsoleCursorPosition(h, point);
		printf("%02u:%02u", sec / 60, sec % 60);
		old_sec = sec;
	}
}

/*вывод в окне с дескриптором h интерфейса меню паузы 
в определенном блоке из блоков по адресу pblocks, 
возвращая индекс следующего интерфейса, в который 
необходимо перейти, с цветовой темой структуры 
по адресу ptheme*/
size_t PrintMenuPause(HANDLE h, TblocksGame* pblocks, Ttheme* ptheme) {
	int answer = 0; // ответ, полученный от пользователя
	pblocks->menu_header.cond = BUTTON_INIT;
	pblocks->menu_continue.cond = BUTTON_INIT;
	pblocks->menu_exit.cond = BUTTON_INIT;

	// инвертировать базовые цвета темы
	SwapStr(ptheme->colorBgBase, ptheme->colorTextBase);
	PrintRectangle(h, pblocks->menu_block, "bgbase", ptheme);
	Sleep(250);

	clock_t time_start = clock();
	while (!answer) {
		MusicBgControl(CONTEXT_PAUSE_GAME, ptheme->onMusicBg);
		PrintWordCursorHover(h, &pblocks->menu_header, "игра приостановлена", ptheme);
		answer += PrintButtonStandart(h, &pblocks->menu_continue, 
			"продолжить", 0, ptheme) * CONTINUE;
		answer += PrintButtonStandart(h, &pblocks->menu_exit,
			"в главное меню", 0, ptheme) * CUSTOM_GAME_GOTO_MENU;
		// задержка после нажатия кнопки
		if (answer)
			Sleep(SPEED_CLICK * 1.5);
		if (GetKeyState(VK_ESCAPE) < 0 && TIMER(time_start, 750)) {
			answer = CONTINUE;
		}
		SetConsoleCursorPosition(h, pblocks->cursore);
	}

	// инвертировать базовые цвета темы
	SwapStr(ptheme->colorBgBase, ptheme->colorTextBase);

	if (answer == CUSTOM_GAME_GOTO_MENU) {
		PrintTransitionEffect(h, pblocks->window.pos, ptheme);
		return CUSTOM_GAME_GOTO_MENU;
	} else
		return answer;
}

/*вывод в окне с дескриптором h игрового интерфейса
карточной игры в дурака из структуры по адресу
pGameTable и карт из матрицы карт player, располагая
элементы вывода по координатам структуры по адресу
pblocks, с цветовой темой структуры по адресу ptheme*/
void PrintGameInterface(HANDLE h, TgameTable* pGameTable,
	Tcard** player, TblocksGame* pblocks, Ttheme* ptheme) {
	SetColor(h, "bgbase", "textbase", ptheme);
	system("cls");
	// шапка 
	PrintHeaderGame(h, pblocks, pGameTable, ptheme);
	if (ptheme->printChat)
		PrintChat(h, pblocks->chat, pGameTable->chat, ptheme);

	// поле боя
	PrintCardsBattle(h, pblocks->cards_battle,
		pGameTable->battle, pGameTable->c_batt,
		pGameTable->cond_battle, WIDTH_BATTLE, ptheme);

	// общая информация
	PrintInfoGame(h, pblocks->cards_deck.pos, pGameTable, ptheme);

	// специальная карта
	PrintSpecialCard(h, pblocks->card_special.pos);

	// массивы карт игроков
	size_t face = pGameTable->mode == GAME_STANDART ? 0 : 1;

	for (size_t i = 0; i < pGameTable->count_players; i++) {
		if (i == pGameTable->user)
			PrintCardsAndNamePlayer(h, player[i], i, 1,
				pGameTable, pblocks, ptheme);
		else
			PrintCardsAndNamePlayer(h, player[i], i, face,
				pGameTable, pblocks, ptheme);
	}
}

/*вывод в окне с дескриптором h у k-го игрока структуры 
игрового стола по адресу pGameTable в соответствующем 
блоке по адресу pblocks, с цветовой темой структуры по адресу ptheme*/
void PrintBlinkingNamePlayer(HANDLE h, size_t k, TgameTable* pGameTable,
	TblocksGame* pblocks, Ttheme* ptheme) {
	Tblock block = GetBlockPlayer(k, pGameTable, pblocks);
	block.pos.Y--;
	char s[SIZE];

	GetHeaderNamePlayer(s, k, pGameTable, block,
		"bgtarget", "textbase", ptheme);
	SetConsoleCursorPosition(h, block.pos);
	PrintColorCenter(h, s, "bgtarget", "textbase", block.lenX, ptheme);
	Sleep(TIME_BLINKING_ANSWER);

	GetHeaderNamePlayer(s, k, pGameTable, block,
		"bgbase", "textbase", ptheme);
	SetConsoleCursorPosition(h, block.pos);
	PrintColorCenter(h, s, "bgbase", "textbase", block.lenX, ptheme);

}

/*вывод в окне с дескриптором h в вокруг блока block 
эффекта размещение элемента с длительностью time миллисекунд 
с цветом фонома cbg и цветом эффектом ctext с цветовой 
темой структуры по адресу ptheme*/
void PrintEffectPlaceEl(HANDLE h, Tblock block, size_t time, 
	char* cbg, char* ctext, Ttheme* ptheme) {
	const arr_ch[] = { '%', '#', '%' , '&' , '*' };
	// кол-во символов, которые могут быть размещены
	const size_t n = 5;
	const size_t time_change = 50; // время одного изменения в мс

	COORD p1, p2;
	COORD p;
	p1.X = block.pos.X - 1;
	p1.Y = block.pos.Y - 1;
	p2.X = block.pos.X + block.lenX;
	p2.Y = block.pos.Y + block.lenY;
	p = p1;
	p.Y = p2.Y;

	size_t percent = 0; // процент заполнения символами пространства
	// максимальное кол-во изменений эффекта
	size_t max_count = time / time_change;
	// текущее кол-во изменений эффекта
	size_t cur_count = 0; 

	SetColor(h, cbg, ctext, ptheme);
	char ch;
	while (cur_count <= max_count) {
		percent = (float)cur_count / max_count * 100;

		// обводка блока по оси y
		for (size_t i = p1.Y + 1; i < p2.Y; i++) {
			SetConsoleCursorCoord(h, p1.X, i);
			ch = rand() % 100 < percent ? ' ' : arr_ch[rand() % n];
			putchar(ch);
		}
		for (size_t i = p1.Y + 1; i < p2.Y; i++) {
			SetConsoleCursorCoord(h, p2.X, i);
			ch = rand() % 100 < percent ? ' ' : arr_ch[rand() % n];
			putchar(ch);
		}

		// обводка блока по оси x
		SetConsoleCursorPosition(h, p1);
		for (size_t i = p1.X; i <= p2.X; i++) {
			ch = rand() % 100 < percent ? ' ' : arr_ch[rand() % n];
			putchar(ch);
		}
		SetConsoleCursorPosition(h, p);
		for (size_t i = p1.X; i <= p2.X; i++) {
			ch = rand() % 100 < percent ? ' ' : arr_ch[rand() % n];
			putchar(ch);
		}
		cur_count++;
		Sleep(time_change);
	}
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*вывод в окне с дескриптором h вокруг карты card в блоке 
block эффекта ее размещения с длительностью time 
миллисекунд с цветом фонома cbg и цветом эффектом ctext 
с цветовой темой структуры по адресу ptheme*/
void PrintEffectPlaceCard(HANDLE h, Tcard card, Tblock block, size_t time, 
	char* cbg, char* ctext, Ttheme* ptheme) {
	block.pos.Y++;
	PrintEffectPlaceEl(h, block, TIME_EFFECT_CARD, cbg, ctext, ptheme);
	block.pos.Y--;
	PrintImgCard(h, block.pos, card, ptheme);
}

/*вывод в окне с дескриптором h в блоке block по центру строки 
в количестве n с длительностью time и временем удержания момента 
мигания glow_time миллисекунд с цветом фонома cbg, цветом текста 
ctext, цветом текста при мигании ctarget с цветовой темой 
структуры по адресу ptheme*/
void PrintLargeMsg(HANDLE h, Tblock block, char (*strs)[100], size_t n, 
	size_t time, size_t glow_time, char* cbg, char* ctext, char* ctarget, Ttheme* ptheme) {
	size_t time_start = clock();
	int f = 1;
	COORD* points = (COORD*)malloc(n * sizeof(COORD));
	points[0].X = block.pos.X + (block.lenX - GetSizeLargeWord(strs[0])) / 2;
	points[0].Y = block.pos.Y + (block.lenY - 3 * n) / 2;
	for (size_t i = 1; i < n; i++) {
		points[i].X = block.pos.X + (block.lenX - GetSizeLargeWord(strs[i])) / 2;
		points[i].Y = points[i - 1].Y + 3;
	}

	while (!TIMER(time_start, time)) {
		if (f > 0)
			SetColor(h, cbg, ctext, ptheme);
		else
			SetColor(h, cbg, ctarget, ptheme);
		f = -f;

		for (size_t i = 0; i < n; i++) {
			PrintWordLarge(h, points[i], strs[i], 0);
		}
		Sleep(glow_time);
	}
	free(points);
	PrintRectangle(h, block, cbg, ptheme);
}

/*постепенный вывод в окне с дескриптором h игрового интерфейса
карточной игры в дурака из структуры по адресу pGameTable и 
карт из матрицы карт player, располагая элементы вывода по 
координатам структуры по адресу pblocks и инициализация начальных 
сообщений в чате, с цветовой темой структуры по адресу ptheme*/
void IntroductionInGame(HANDLE h, TgameTable* pGameTable,
	Tcard** player, TblocksGame* pblocks, Ttheme* ptheme) {
	char s[SIZE];
	char stmp[SIZE];
	GetMsgForChat(s, "\\green:Игра началась!", "@a", "darkgray", ptheme);
	UpdateChat(pGameTable->chat, pblocks->chat, s, ptheme);

	if (pGameTable->mode != GAME_AI) {
		// звуки тасовки карт
		MusicBgControl(CONTEXT_GAME, ptheme->onMusicBg);
		if (ptheme->onSounds) {
			mciSendString(TEXT("play sourse\\sound\\game_table\\cardsShuffle1.mp3"),
				NULL, 0, NULL); // звук
			Sleep(2000);
			mciSendString(TEXT("play sourse\\sound\\game_table\\cardsShuffle2.mp3"),
				NULL, 0, NULL); // звук
		}
		Sleep(1000);

		// массивы карт игроков
		size_t face = pGameTable->mode == GAME_STANDART ? 0 : 1;

		for (size_t i = 0; i < pGameTable->count_players; i++) {
			Sleep(640);
			if (ptheme->onSounds)
				PlaySoundCard(); // звук выкладыывания карты
			if (i == pGameTable->user)
				PrintCardsAndNamePlayer(h, player[i], i, 1,
					pGameTable, pblocks, ptheme);
			else
				PrintCardsAndNamePlayer(h, player[i], i, face,
					pGameTable, pblocks, ptheme);
		}

		// общая информация
		Sleep(1000);
		pGameTable->time_start = clock(); // время начала игры
		if (ptheme->onSounds)
			mciSendString(TEXT("play sourse\\sound\\game_table\\cardsDistribution1.mp3"), NULL, 0, NULL); // звук
		PrintInfoGame(h, pblocks->cards_deck.pos, pGameTable, ptheme);
		
		// шапка 
		Sleep(1800);
		PrintHeaderGame(h, pblocks, pGameTable, ptheme);
		if(ptheme->onSounds)
			mciSendString(TEXT("play sourse\\sound\\game_table\\initHeader.mp3"), NULL, 0, NULL); // звук
		
		// чат
		Sleep(1300);
		if (ptheme->printChat) {
			if (ptheme->onSounds)
				mciSendString(TEXT("play sourse\\sound\\menu\\electroClick.mp3"), NULL, 0, NULL); // звук
			PrintChat(h, pblocks->chat, pGameTable->chat, ptheme);
		}
		Sleep(1300);
	}
	else {
		Sleep(500);
		if (ptheme->onSounds)
			mciSendString(TEXT("play sourse\\sound\\game_table\\cardsDistribution1.mp3"), NULL, 0, NULL); // звук
	}

	GetMsgForChat(s, "Для того, чтобы увидеть список доступных команд, введите команду \
\"\\texttarget:\\\\getCommandList\\textmsg:\"", "@a", "darkgray", ptheme);
	UpdateChat(pGameTable->chat, pblocks->chat, s, ptheme);

	// сообщение о том, кто на кого ходит в чате
	char sname_out[MAX_LEN_NICKNAME + 1];
	if (pGameTable->name_player[pGameTable->move][0] == '\0')
		sprintf(sname_out, "%u-го игрока", pGameTable->move + 1);
	else
		strcpy(sname_out, pGameTable->name_player[pGameTable->move]);

	char sname_in[MAX_LEN_NICKNAME + 1];
	if (pGameTable->name_player[pGameTable->defend_player][0] == '\0')
		sprintf(sname_in, "%u-го игрока", pGameTable->defend_player + 1);
	else
		strcpy(sname_in, pGameTable->name_player[pGameTable->defend_player]);

	sprintf(stmp, "\\texttarget:Начался ход %s под %s!",
		sname_out, sname_in);
	GetMsgForChat(s, stmp, "@a", "darkgray", ptheme);
	UpdateChat(pGameTable->chat, pblocks->chat, s, ptheme);

	pGameTable->time_start = clock(); // время начала игры
	PrintGameInterface(h, pGameTable, player, pblocks, ptheme); // вывод игрового интерфейса
	if (pGameTable->mode == GAME_AI) {
		GetMsgForChat(s, "Для того, чтобы игра продолжалась \
зажимайте клавишу \\texttarget:[Space]", "@a", "darkgray", ptheme);
		UpdateChat(pGameTable->chat, pblocks->chat, s, ptheme);

		COORD point = pblocks->cards_battle.pos;
		point.X += (pblocks->cards_battle.lenX - GetSizeLargeWord("жми space")) / 2;
		point.Y += pblocks->cards_battle.lenY / 2 - 1;
		if (ptheme->onSounds) {
			mciSendString(TEXT("play sourse\\sound\\game_table\\newMove.mp3"),
				NULL, 0, NULL); //звук
		}
		clock_t time_start_only_ai = clock();
		int f = 1;
		while (GetKeyState(VK_SPACE) >= 0) {
			if (TIMER(time_start_only_ai, 500)) {
				if (f == 1)
					SetColor(h, "bgbase", "texttarget", ptheme);
				else
					SetColor(h, "bgbase", "textbase", ptheme);
				PrintWordLarge(h, point, "жми space", 0);
				f = -f;
				time_start_only_ai = clock();
			}
		}
		if (ptheme->onSounds) {
			mciSendString(TEXT("play sourse\\sound\\menu\\inputSuccess.mp3"),
				NULL, 0, NULL); //звук
		}
		Sleep(SPEED_SWITCH_BUTTON);
		PrintRectangle(h, pblocks->cards_battle, "bgbase", ptheme);
	}
}

/*вывод в окне с дескриптором h интерактивного интерфейса 
игрового стола по информации структуры по адресу 
pGameTable, выводя карты игроков из матрицы карт player 
по блокам по адресу pblocks, выводя по запросу некторые элементы
массива psettingsAI, возвращая ответ текущего отвечающего игрока, 
или -3, если пользователь выбрал перейти в главное меню, 
с цветовой темой структуры по адресу ptheme*/
int InteractiveGameInterface(HANDLE h, TgameTable* pGameTable,
	Tcard** player, TblocksGame* pblocks, TsettingsAI* settingsAI[6], Ttheme* ptheme) {
	// была ли инициализация предыдущей выбраной карты пользователем
	static size_t init_prev_card;
	static size_t dynamic = 1; // нужно ли показыавть динамику элементов после захода в функцию
	static size_t msg_move_start; // было ли выведено сообщение о начале хода
	static clock_t time_start_switch = 0;
	static clock_t time_start_cick = 0;
	static clock_t time_choise_AI = 0; // время начала принятия решения ИИ
	static COORD point_card; // точка с началом выбранной карты

	static size_t prev_ans_player; // игрок, который дал ответ перед текущим
	static size_t prev_c_batt; // предыдущее кол-во карт на поле боя
	static COORD point_prev_card; // точка с началом предыдущей выбранной карты
	static size_t prev_card; // предыдущая выбранная карта
	static size_t prev_cond_matr_ai = BUTTON_OFF; // предыдущее состояние ывода матрицы памяти карт ИИ

	size_t answer_menu_pause = 0; // ответ, полученный из меню паузы
	size_t target_current = pblocks->target_card; // текущая выбранная карта
	int answer = 0; // ответ от игрока получен
	int mouse = 0; // был ли курсор мыши наведен на карту
	size_t prev_pass = 0; // педыдущее значение кнопки пасс
	size_t pass = 0; // значение кнопки пасс
	size_t press_pass = 0; // зажата ли кнопка пасс
	static clock_t time_start_pass = 0;

	size_t re_print_cards = 0; // нужно ли заново вывести масив карт
	char suit_color[20];
	size_t indentation = 0; // отступы от краев блока массива карт
	size_t distance = 0; // расстояние между базовыми точками массива карт
	size_t speed_switch; // скорость переключения между картами с помощью клавиш
	Tblock block_card_battle; // ячейка на поле боя для выкладки карты
	// показывать ли лица карт противников
	size_t face_cards_enemy = pGameTable->mode == GAME_STANDART ? 0 : 1;

	int choise = -2; // выбранная карта

	size_t card_was_chosen = 0; // была ли выбрана карта
	char header_name_user[WIDTH_CRADS_BASE];

	if (!pGameTable->game_start) {
		prev_ans_player = pGameTable->priority;
		prev_c_batt = 0;
		init_prev_card = 1;
		msg_move_start = 0;
		pGameTable->game_start = 1;
	}

	if (dynamic) {
		target_current = pblocks->target_card + 1;
		// обновление поле боя
		PrintCardsBattle(h, pblocks->cards_battle,
			pGameTable->battle, pGameTable->c_batt,
			pGameTable->cond_battle, WIDTH_BATTLE, ptheme);
		if (pGameTable->priority != pGameTable->user)
			time_choise_AI = clock();
		time_start_cick = clock();
		pblocks->button_pass.cond = BUTTON_INIT;
		pblocks->button_chat.cond = BUTTON_INIT;

		// обновление шапки игрового стола
		PrintHeaderGame(h, pblocks, pGameTable, ptheme);
		// обновление карт игрока, который отвечал перед текущим
		if (prev_ans_player == pGameTable->user) {
			if (pblocks->target_card >= pGameTable->c_player[pGameTable->user])
				pblocks->target_card--;
			PrintCardsAndNamePlayer(h, player[pGameTable->user],
				pGameTable->user, 1, pGameTable, pblocks, ptheme);
		}
		else {
			PrintCardsAndNamePlayer(h, player[prev_ans_player],
				prev_ans_player, face_cards_enemy, pGameTable, pblocks, ptheme);
		}
	}

	if (pGameTable->mode != GAME_AI) {
		point_card.Y = pblocks->cards_user.pos.Y;
		speed_switch = 60 + 90 * (1 - pGameTable->c_player[pGameTable->user] / SIZE_DECK);
		
		block_card_battle.lenX = 11;
		block_card_battle.lenY = 7;
		block_card_battle.cond = BUTTON_INIT;

		if (pGameTable->c_batt && dynamic) {
			block_card_battle.pos = GetPointCardBattle(pGameTable->c_batt - 1,
				pGameTable->cond_battle, pblocks->cards_battle);
			// спецэффекты овтета игрока
			PrintBlinkingNamePlayer(h, prev_ans_player, pGameTable, pblocks, ptheme);

			if (prev_c_batt != pGameTable->c_batt) {
				PrintImgCard(h, block_card_battle.pos,
					pGameTable->battle[pGameTable->c_batt - 1], ptheme);
				if (ptheme->specialEffects && pGameTable->mode != GAME_AI) { // спецэффекты выкладки карт на поле боя
					if (pGameTable->cond_battle[pGameTable->c_batt - 1] == ATTACK) {
						if (ptheme->onSounds) {
							mciSendString(TEXT("play sourse\\sound\\game_table\\cardAttack1.mp3"),
								NULL, 0, NULL); // звук атаки
						}
						PrintEffectPlaceCard(h, pGameTable->battle[pGameTable->c_batt - 1],
							block_card_battle, TIME_EFFECT_CARD, "bgbase", "suit1", ptheme);
					} else {
						if (ptheme->onSounds) {
							mciSendString(TEXT("play sourse\\sound\\game_table\\cardProtection1.mp3"),
								NULL, 0, NULL); // звук защиты
						}
						PrintEffectPlaceCard(h, pGameTable->battle[pGameTable->c_batt - 1],
							block_card_battle, TIME_EFFECT_CARD, "bgbase", "texttarget", ptheme);
					}
					PrintImgCard(h, block_card_battle.pos,
						pGameTable->battle[pGameTable->c_batt - 1], ptheme);
				} else if (ptheme->onSounds) {
					PlaySoundCard(); // звук выкладывания карты
				}
			} else {
				if (ptheme->onSounds) {
					mciSendString(TEXT("play sourse\\sound\\cardPass1.mp3"),
						NULL, 0, NULL); // звук защиты
				}
			}
		} 
		else if (!msg_move_start) {
			// сообщение о том, кто на кого ходит
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\game_table\\newMove.mp3"),
					NULL, 0, NULL); //звук
			}
			Tblock block = pblocks->cards_battle;
			block.pos.X -= 2;
			block.lenX += 4;
			char strs[2][100];
			strcpy(strs[0], "начался ход под");
			if (pGameTable->name_player[pGameTable->defend_player][0] == '\0')
				sprintf(strs[1], "%u-го игрока", pGameTable->defend_player + 1);
			else
				sprintf(strs[1], "%s", pGameTable->name_player[pGameTable->defend_player]);
			PrintLargeMsg(h, block, strs, 2, 2500, 500, "bgbase", "textbase", "texttarget", ptheme);
			msg_move_start = 1;
		} 

		if (pGameTable->priority == pGameTable->user) {
			// точка для размещения карты игрока
			if (pGameTable->player_state[pGameTable->user] == ATTACK
				|| pGameTable->player_state[pGameTable->user] == CAN_BE_THROWN)
				pGameTable->cond_battle[pGameTable->c_batt] = ATTACK;
			else
				pGameTable->cond_battle[pGameTable->c_batt] = PROTECTION;
			block_card_battle.pos = GetPointCardBattle(pGameTable->c_batt,
				pGameTable->cond_battle, pblocks->cards_battle);

			// получим массив позиций карт массива карт пользователя по оси X 
			GetDistanceAndIndentCards(&distance, &indentation,
				pblocks->cards_user, pGameTable->c_player[pGameTable->user]);
			GetCoordArrCards(pblocks->pos_cards, pblocks->cards_user.pos.X + indentation,
				distance, pGameTable->c_player[pGameTable->user]);
			GetHeaderNamePlayer(header_name_user, pGameTable->user,
				pGameTable, pblocks->cards_user, "bgbase", "textbase", ptheme);

			point_prev_card.X = pblocks->cards_user.pos.X + indentation
				+ pblocks->target_card * distance;
			if (init_prev_card) {
				prev_card = 1;
				point_prev_card.X = pblocks->cards_user.pos.X + distance + indentation;
				point_prev_card.Y = pblocks->cards_user.pos.Y;
				init_prev_card = 0;
			}
		}
	}
	else if (prev_c_batt != pGameTable->c_batt && ptheme->onSounds)
 		PlaySoundCard(); // звук выкладывания карты
	
	// если включен вывод матрицы памяти карт ИИ, то выводить его
	if (pblocks->matr_cards_ai.cond != BUTTON_OFF) { ///////////////////////////////////////////////////
		SetColor(h, "bgmsg", "textmsg", ptheme);
		PrintMatrCardsAI(h, settingsAI[pblocks->index_matr_ai]->info.matr_cards,
			pblocks->matr_cards_ai.pos);
		SetColor(h, "bgbase", "textbase", ptheme);
		prev_cond_matr_ai = pblocks->matr_cards_ai.cond;
	}
	if (prev_cond_matr_ai != pblocks->matr_cards_ai.cond && prev_cond_matr_ai != BUTTON_OFF) {
		PrintGameInterface(h, pGameTable, player, pblocks, ptheme);
		prev_cond_matr_ai = pblocks->matr_cards_ai.cond;
	}

	// --------------------- ЦИКЛ ОБНОВЛЕНИЯ -----------------------------

	while (!answer) { // пока игрок не дал ответ
		MusicBgControl(CONTEXT_GAME, ptheme->onMusicBg);
		CountTimeSpenInGame(FILE_PATH_SETTINGS, "minutsInGame", &ptheme->minutsInGame);
		UpdateTime(h, pblocks->time, pGameTable->time_start);

		// если был клик по выведенной матрице памяти карт ИИ
		if (CursoreInBlock(pblocks->matr_cards_ai) == 2 && pblocks->matr_cards_ai.cond != BUTTON_OFF) {
			pGameTable->command = COMMAND_DELETE_MATR_CARDS_AI;
			return GAME_EXECUTE_COMMAND;
		}

		// кнопка чата для ввода сообщения
		if (ptheme->printChat) {
			PrintStrCursorHover(h, &pblocks->button_chat, "[ нажмите, чтобы вести сообщение ]",
				"bgmsg", "darkgray", "texttarget", ptheme);
			if (CursoreInBlock(pblocks->button_chat) == 2 || (GetKeyState(VK_TAB) < 0)
				&& TIMER(time_start_cick, SPEED_CLICK)) {
				char s_in[MAX_LEN_MESSAGE];
				// если пользоватеь подтвердил введенное сообщение, то отправить его
				if (InputTextInChat(h, pblocks->input_chat.pos, s_in,
					pblocks->input_chat.lenX, ptheme)) {

					char s_out[MAX_LEN_MESSAGE];
					// проверить, является ли веденное сообщение командой
					pGameTable->command = GetCommandFromStr(s_in, pGameTable->args);
					if (pGameTable->command != COMMAND_NONE) {
						// вернуться в главную функцию и выполнить команду
						dynamic = 0;
						prev_c_batt = pGameTable->c_batt;
						PrintRectangle(h, pblocks->input_chat, "bgbase", ptheme);
						pblocks->button_chat.cond = BUTTON_INIT;
						return GAME_EXECUTE_COMMAND;
					} else {
						if (pGameTable->mode != GAME_AI)
							GetMsgForChat(s_out, s_in, pGameTable->name_player[pGameTable->user], "darkgray", ptheme);
						else
							GetMsgForChat(s_out, s_in, ptheme->userName, "darkgray", ptheme);
						UpdateChat(pGameTable->chat, pblocks->chat, s_out, ptheme);
					}
				}
				pblocks->button_chat.cond = BUTTON_INIT;
				PrintRectangle(h, pblocks->input_chat, "bgbase", ptheme);
				if (ptheme->printChat)
					PrintChat(h, pblocks->chat, pGameTable->chat, ptheme);
				time_start_cick = clock();
			}
		}

		// кнопка для перехода на следющий ход, если он закончен
		if (pGameTable->end_move || pGameTable->end_game) { // если конец хода
			pass = PrintButtonStandart(h, &pblocks->button_pass, "ок",
				pblocks->button_pass.lenX, ptheme);
		} 
		else if (pGameTable->priority == pGameTable->user) {
			pass = PrintButtonStandart(h, &pblocks->button_pass, "пасс",
				pblocks->button_pass.lenX, ptheme);
		}
		if ((pass || GetKeyState(VK_SHIFT) < 0) && TIMER(time_start_cick, SPEED_CLICK)) {
			if (pGameTable->end_move) {
				PrintImgPressedButton(h, pblocks->button_pass.pos, "ок",
					pblocks->button_pass.lenX, ptheme);
				Sleep(SPEED_SWITCH_BUTTON);
				prev_ans_player = pGameTable->priority;
				msg_move_start = 0;
				if (ptheme->onSounds) {
					mciSendString(TEXT("play sourse\\sound\\game_table\\cardsDistribution1.mp3"),
						NULL, 0, NULL); //звук
				}
				dynamic = 1;
				return GAME_CONTINUE;

			} else {
				if (prev_pass == 0)
					time_start_pass = clock();
				if (!press_pass && GetKeyState(VK_SHIFT) < 0) { // создане эффекта зажатия кнопки без мигания
					if (ptheme->onSounds) {
						mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
							NULL, 0, NULL); //звук
					}
					PrintImgPressedButton(h, pblocks->button_pass.pos, "пасс",
						pblocks->button_pass.lenX, ptheme);
					press_pass = 1;
				}
				if (pass || TIMER(time_start_pass, TIME_PRESS_PASS)) {
					Sleep(SPEED_SWITCH_BUTTON);
					choise = -1; // пользователь пасанул
					answer = 1;
				}
				prev_pass = 1;
			}
		} else if (press_pass) {
			pblocks->button_pass.cond = BUTTON_INIT;
			press_pass = 0;
			prev_pass = 0;
			time_start_cick = clock();
		}

		// вызов меню паузы
		PrintStrCursorHover(h, &pblocks->esc, "|=| Esc",
			"bgmsg", "textmsg", "texttarget", ptheme);
		if (CursoreInBlock(pblocks->esc) == 2 || (GetKeyState(VK_ESCAPE) < 0 
			&& choise < 0) && TIMER(time_start_cick, 750) || GetKeyState(0xc0) < 0) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
					NULL, 0, NULL); // звук
			}
			answer_menu_pause = PrintMenuPause(h, pblocks, ptheme);

			if (answer_menu_pause == CONTINUE)
				PrintGameInterface(h, pGameTable, player, pblocks, ptheme);
			else if (answer_menu_pause == CUSTOM_GAME_GOTO_MENU) {
				dynamic = 1;
				return GAME_GOTO_MENU;
			}

			time_start_cick = clock();
		}

		// получение сообщения о событийном эффекте
		PrintStrCursorHover(h, &pblocks->effect, pblocks->s_effect,
			"bgmsg", "textmsg", "texttarget", ptheme);
		if (CursoreInBlock(pblocks->effect) == 2 && TIMER(time_start_cick, 750)) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\game_table\\notice1.mp3"),
					NULL, 0, NULL); // звук
			}
			char s[SIZE];
			GetMsgForChat(s, optionsEffects[pGameTable->event_effect][1], 
				"Событийный эффект", "darkgray", ptheme);
			UpdateChat(pGameTable->chat, pblocks->chat, s, ptheme);
			if (ptheme->printChat)
				PrintChat(h, pblocks->chat, pGameTable->chat, ptheme);
			pblocks->button_chat.cond = BUTTON_INIT;
			time_start_cick = clock();
		}

		PrintElCursorHover(h, &pblocks->card_special, PrintSpecialCard, ptheme);
		if (CursoreInBlock(pblocks->card_special) == 2 && TIMER(time_start_cick, 750)) {
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\game_table\\notice1.mp3"),
					NULL, 0, NULL); // звук
			}
			char s[SIZE];
			GetMsgForChat(s, "На ваших руках специальных карт нет. Чтобы их \
получить, проходите сюжетную линию, которой еще нет.", "Специальная карта", "darkgray", ptheme);
			UpdateChat(pGameTable->chat, pblocks->chat, s, ptheme);
			if (ptheme->printChat)
				PrintChat(h, pblocks->chat, pGameTable->chat, ptheme);
				pblocks->button_chat.cond = BUTTON_INIT;
			time_start_cick = clock();
		}

		// если не конец хода и не конец игры
		if (!pGameTable->end_move || !pGameTable->end_game) { 
			// если ход пользователя
			if (pGameTable->priority == pGameTable->user) {
				// перемещение указателя на карту клавишой влево
				if (GetKeyState(VK_LEFT) < 0 && target_current > 0
					&& TIMER(time_start_switch, speed_switch)) {
					pblocks->target_card--;
					if (choise >= 0) {
						choise = -2;
						re_print_cards = 1;
					}
					time_start_switch = clock();

					// перемещение указателя на карту клавишой вправо
				} else if (GetKeyState(VK_RIGHT) < 0 && target_current + 1
					< pGameTable->c_player[pGameTable->user]
					&& TIMER(time_start_switch, speed_switch)) {
					pblocks->target_card++;
					if (choise >= 0) {
						choise = -2;
						re_print_cards = 1;
					}
					time_start_switch = clock();
				}
				// перемещение указателя на карту указателем мыши
				if (target_current != pblocks->target_card || re_print_cards) {
					if (ptheme->onSounds) {
						mciSendString(TEXT("play sourse\\sound\\game_table\\cardSwitch1.mp3"),
							NULL, 0, NULL); // звук
					}
					point_card.X = pblocks->pos_cards[pblocks->target_card];
					GetColorSuit(suit_color, player[pGameTable->user]
						[pblocks->target_card].m, ptheme);

					if (ptheme->improvedAlgGameInterface) {
						if (card_was_chosen) {
							// перевывод шапки имени пользователя
							pblocks->cards_user.pos.Y--;
							SetConsoleCursorPosition(h, pblocks->cards_user.pos);
							PrintColorCenter(h, header_name_user, "bgbase", "textbase",
								pblocks->cards_user.lenX, ptheme);
							pblocks->cards_user.pos.Y++;

							card_was_chosen = 0;
						}
						// перевывод части массива карт пользователя, где была подсвеченная карта
						RePrintImgRegionCards(h, point_prev_card, player[pGameTable->user],
							pGameTable->c_player[pGameTable->user], prev_card,
							distance, ptheme);
					} else {
						PrintCardsAndNamePlayer(h, player[pGameTable->user],
							pGameTable->user, 1, pGameTable, pblocks, ptheme);
					}

					// вывод новой посвеченной карты
					PrintImgCardColor(h, point_card, player[pGameTable->user]
						[pblocks->target_card], "bgtarget", suit_color, ptheme);
					target_current = pblocks->target_card;
					prev_card = target_current;
					point_prev_card = point_card;
				}
				// обновить поле боя
				if (re_print_cards) {
					PrintCardsBattle(h, pblocks->cards_battle,
						pGameTable->battle, pGameTable->c_batt,
						pGameTable->cond_battle, WIDTH_BATTLE, ptheme);
					// сборосить состояние ячейки для выкладки карты
					block_card_battle.cond = BUTTON_HOVER;
					re_print_cards = 0;
				}
				mouse = CursoreCardGameTable(pblocks, pGameTable->c_player[pGameTable->user]);
				if (mouse >= 0 && mouse < pGameTable->c_player[pGameTable->user] && choise < 0)
					pblocks->target_card = mouse;

				if (TIMER(time_start_cick, SPEED_SWITCH_BUTTON)) {
					// если карта не выбрана
					if (choise < 0) {
						if (GetKeyState(VK_SPACE) < 0 || (mouse ==
							pblocks->target_card && GetKeyState(VK_LBUTTON) < 0)) {

							target_current = pblocks->target_card;
							// вывод выбранной карты в новом цвете
							PrintfChoiseCardGameTable(h, point_card,
								player[pGameTable->user][pblocks->target_card], ptheme);

							choise = pblocks->target_card;
							card_was_chosen = 1;

							// вывод на поле боя ячейки для выкладки карты
							PrintCellForCard(h, &block_card_battle,
								player[pGameTable->user][pblocks->target_card], ptheme);
							if (ptheme->onSounds) {
								mciSendString(TEXT("play sourse\\sound\\game_table\\cardSelect1.mp3"),
									NULL, 0, NULL); // звук
							}
							time_start_cick = clock();
						}
					} else { // если карта выбрана
				  // вывод на поле боя ячейки для выкладки карты
						PrintCellForCard(h, &block_card_battle,
							player[pGameTable->user][pblocks->target_card], ptheme);

						// если клик ЛКМ по выбранной карте или нажата escape
						if (((mouse == pblocks->target_card && GetKeyState(VK_LBUTTON) < 0))
							|| GetKeyState(VK_ESCAPE) < 0) {
							// отменить выбор
							choise = -2;
							re_print_cards = 1;
							time_start_cick = clock();

							// если выбор подтвержден
						} else if (GetKeyState(VK_SPACE) < 0 || CursoreInBlock(block_card_battle) == 2) {
							PrintImgCard(h, block_card_battle.pos,
								player[pGameTable->user][pblocks->target_card], ptheme);
							answer = 1;
						}
					}
				}
			} 
			else { // если ход не пользователя
				if (pGameTable->mode == GAME_AI) {
					if (GetKeyState(VK_SPACE) < 0 && !pGameTable->end_move && !pGameTable->end_game) {
 						prev_c_batt = pGameTable->c_batt;
						prev_ans_player = pGameTable->priority;
						dynamic = 1;
						Sleep(SPEED_ANSWER_ONLY_AI);
						return GAME_REQUEST_SOLUTION_AI;
					}
				} else if (TIMER(time_choise_AI, pGameTable->count_wait_ms_AI)) {
					prev_c_batt = pGameTable->c_batt;
					prev_ans_player = pGameTable->priority;
					dynamic = 1;
					return GAME_REQUEST_SOLUTION_AI;
				}
			}
		}
		SetConsoleCursorPosition(h, pblocks->cursore);
	}
	prev_c_batt = pGameTable->c_batt;
	prev_ans_player = pGameTable->priority;
	dynamic = 1;
	return choise;
}
