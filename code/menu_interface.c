#include "header.h"

#if !defined(__PRINT_ELEMENTS_H)
void PrintImgHeaderMainMenu(HANDLE h, COORD point);
void PrintPointerMainMenu(HANDLE h, COORD point);
void PrintSymbolIconSun(HANDLE h, COORD point);
void PrintSymbolIconRain(HANDLE h, COORD point);
void PrintSymbolIconSnow(HANDLE h, COORD point);
void PrintSymbolIconLeft(HANDLE h, COORD point);
void PrintSymbolIconRight(HANDLE h, COORD point);
void PrintSymbolIconBulb(HANDLE h, COORD point);
void PrintSymbolIconVoice(HANDLE h, COORD point);
#endif 

char optionsEffects[][2][300] = {
	{"без событийных эффектов", "На ход игры не влияют никакие допольнительные условия. Это \\green:классическая \\textmsg:игра в дурака."},
	{"смена козыря каждый ход", "Времена меняются быстро, а вместе с ними и козырная масть. Каждый ход козырная масть меняется случайным образом, причем не важно, какая карта лежит нижней в общей колоде."},
	{"случайные обмены", "Каждый ход приносит с собой крупицу неизвестности: одна случайная карта у каждого игрока оказывается у другого игрока. Прекрасно."},
	{"переводной", "Выкинув на поле боя карту такого же номинала, какой на тебя походили, вы переводите обязанность защищаться на следующего игрока на игровом столе. А ловко это придумано!"},
	{"широкие руки", "Жадность игроков достигла максимума. Все карты из колоды карт будут разданы игрокам поровну. Справедливая жадность. Больше всего подходит для игры с малым количеством игроков."},
	{"номинальный переворот", "Сильные становятся слабыми, а слыбые - сильными... Это значит, что ценнность ранга номиналов обращена в обратную сторону."},
	{"табу на масть", "Каждый ход всевышний определяет, какая масть должна сидеть на своем месте и не высовываться. Если у атакующего игрока на данном ходу нет дргих карт, кроме карт запрещенной масти, то он проигрывает."},
	{"переполох на игровом столе", "Никогда не знаешь, чем все кончится, ведь каждый ход все карты на игровом столе перемещиваются - сохраняется лишь количество карт в каждой колоде."},
	{"слабая масть", "Если ранее была сильная масть - козырная, которая сильнее любой другой, то теперь есть и слабая масть, которая слабее любой другой."},
	{"равенство мастей", "Козырь - отменить!"},
	{"время быстрого принятия решений", "Каждому игроку дается определенное количество времени на все его ответы. Если время истекает - пиши пропало - выбываешь из игры."}
};
size_t countEffects = 11; // кол-во событийных эффектов

/*запись в строку s в позицию k текста кнопки 
со сложностью difficulty*/
void SetDifficultyInStr(char* s, size_t k, size_t difficulty) {
	static char s_cond[][50] = {
	"         новичок     --> ",
	" <--     опытный     --> ",
	" <--     мастер      --> ",
	" <--   божественный      ",
	"       пользователь      ",
	"#########################"
	};

	char* ps = s + k;
	strcpy(ps, s_cond[difficulty]);
	ps += strlen(s_cond[difficulty]);
	*ps = '|';
}

/*вывод в окне с дескриптором h блоков-кнопок block_players, 
записывая по адресe pcount_players количество выбранных 
игроков, в массив difficulty уровень их игры, в массив 
строк names их имена, с цветовой темой структуры по адресу ptheme*/
void PrintTableChoiseAI(HANDLE h, Tblock* blocks_player, size_t* pcount_players, 
	size_t* diff, char name[6][MAX_LEN_NICKNAME + 1], Ttheme* ptheme) {
	static clock_t time_start = 0;
	static size_t diff_prev[6] = { NONE_DIFF, NONE_DIFF, NONE_DIFF, NONE_DIFF, NONE_DIFF, NONE_DIFF };
	static char players[][WIDTH] = { 
		" V |    1-й   |#########################|######################",
		" V |    2-й   |#########################|######################",
		" X |    3-й   |#########################|######################",
		" X |    4-й   |#########################|######################",
		" X |    5-й   |#########################|######################",
		" X |    6-й   |#########################|######################"
	};
	size_t button_hover_key = 1000;

	for (size_t i = 0; i < 6; i++) {
		// если была нажата кнопка
		if (PrintButtonSmall(h, &blocks_player[i], players[i], 0, ptheme)) {
			Tblock block_get = blocks_player[i];
			block_get.lenX = 15;
			// если выбран игрок, включенный в игру и он не пользователь
			if (i >= 2 && diff[i] != USER) {
				if (diff[i] == NONE_DIFF || CursoreInBlock(block_get) == 2 || GetKeyState(VK_SPACE) < 0) {
					if (i < *pcount_players) {
						size_t k = i;
						while (k < *pcount_players) {
							players[k][1] = 'X';
							diff[k] = NONE_DIFF;
							k++;
						}
						*pcount_players = i;
					} else {
						size_t k = *pcount_players;
						while (k <= i) {
							players[k][1] = 'V';
							diff[k] = EASY;
							k++;
						}
						*pcount_players = i + 1;
					}
					button_hover_key = i;
				} 
			} else if (ptheme->onSounds && CursoreInBlock(block_get) == 2 
				|| GetKeyState(VK_SPACE) < 0 || diff[i] == USER) {
				mciSendString(TEXT("play sourse\\sound\\menu\\inputError.mp3"),
					NULL, 0, NULL); // звук
			}
		}
		/* если эта кнопка - активная и выбран игрок, включенный в игру, 
		то проверить нажатие клавиш или клик мыши по стрелкми*/
		if ((blocks_player[i].cond == BUTTON_HOVER_CUR || blocks_player[i].cond 
			== BUTTON_HOVER) && i < *pcount_players && diff[i] != USER) {
			Tblock block_arrow_left = blocks_player[i];
			block_arrow_left.pos.X += 15;
			block_arrow_left.lenX = 13;

			Tblock block_arrow_right = block_arrow_left;
			block_arrow_right.lenX--;
			block_arrow_right.pos.X += block_arrow_left.lenX;

			Tblock block_name = block_arrow_right;
			block_name.lenX = 24;
			block_name.pos.X += block_arrow_right.lenX;

			if ((GetKeyState(VK_LEFT) < 0 || CursoreInBlock(block_arrow_left) == 2) && diff[i] > EASY) {
				if (TIMER(time_start, SPEED_SWITCH_BUTTON)) {
					diff[i]--;
					button_hover_key = i;
					time_start = clock();
				}

			} else if ((GetKeyState(VK_RIGHT) < 0 || CursoreInBlock(block_arrow_right) == 2) && diff[i] < UNREAL) {
				if (TIMER(time_start, SPEED_SWITCH_BUTTON)) {
					diff[i]++;
					button_hover_key = i;
					time_start = clock();
				}
			}
			// ввод имени игрока
			if (CursoreInBlock(block_name) == 2 || GetKeyState(VK_SHIFT) < 0) { 
				COORD point = block_name.pos;
				point.X++;
				SetConsoleCursorPosition(h, point);
				PrintColor(h, "\\textmsg-bgmsg: ", ptheme);
				MoveConsoleCursorPoint(h, &point, MAX_LEN_NICKNAME + 1, 0);
				PrintColor(h, "\\textmsg-bgmsg: ", ptheme);

				MoveConsoleCursorPoint(h, &point, -MAX_LEN_NICKNAME, 0);
				char sname[MAX_LEN_NICKNAME + 1];
				sprintf(sname, "%u-й игрок", i + 1);
				InputName(h, point, MAX_LEN_NICKNAME, name[i],
					3, MAX_LEN_NICKNAME, sname, ptheme);
				diff_prev[i] = NONE_DIFF;
				button_hover_key = i;
			}
		}
	}
	// изменение строки после изменений параметров блока
	for (size_t i = 0; i < 6; i++) { 
		if (diff_prev[i] != diff[i]) {
			diff_prev[i] = diff[i];
			SetDifficultyInStr(players[i], 15, diff[i]);
			if (i == button_hover_key)
				blocks_player[i].cond = BUTTON_HOVER_KEY;
			else
				blocks_player[i].cond = BUTTON_INIT;

			char* ps = players[i] + 41;
			if (diff[i] == NONE_DIFF)
				strcpy(ps, "######################");
			else if (name[i][0] == '\0') {
				char sname[MAX_LEN_NICKNAME + 1];
				sprintf(sname, " %u-й игрок          ", i + 1);
				strcpy(ps, sname);
			} else {
				strcpy(ps, "                      ");
				strcpy(++ps, name[i]);
			}
		}
	}
}

/*возвращает из массива указателей a размера n, 
индекс натурального числа value по указателю, 
иначе, если число не найдено, возвращает -1*/
int GetIndexNumberPointer(size_t* a[20], size_t n, size_t value) {
	size_t i = a[0] == NULL ? 1 : 0;
	while (i < n && *(a[i]) != value) {
		i++;
	}
	if (i >= n)
		i = -1;
	return i;
}

/*вывод в окне с дескриптором h эффекта перехода 
между экранами, начиная с точки point с цветовой 
темой структуры по адресу ptheme*/
void PrintTransitionEffect(HANDLE h, COORD point, Ttheme* ptheme) {
	char s[WIDTH]; // строка пробелов
	char line[WIDTH + 22]; // строка нижнего подчеркивания
	for (size_t i = 0; i < WIDTH; i++) {
		s[i] = ' ';
	}
	s[WIDTH - 1] = '\0';
	sprintf(line, "\\textbase-textbase:%s", s);
	static const size_t time = SPEED_TRANSIT / HEIGHT;

	SetColor(h, "bgbase", "textbase", ptheme);
	SetConsoleCursorPosition(h, point);
	PrintColor(h, line, ptheme);

	if (ptheme->onSounds) {
		mciSendString(TEXT("play sourse\\sound\\menu\\transition1.mp3"),
			NULL, 0, NULL); //звук
	}
	for (size_t i = 0; i < HEIGHT; i++) {
		SetConsoleCursorPosition(h, point);
		printf("%s", s);
		MoveConsoleCursorPoint(h, &point, 0, 1);
		PrintColor(h, line, ptheme);
		Sleep(time);
	}
	system("cls");
	Sleep(300);
}

/*вывод в окне с дескриптором h эффекта перехода между темами 
интерфейса в блоке block, с цветовой темой структуры по адресу ptheme*/
void TransitionDesignTheme(HANDLE h, COORD point, Ttheme* ptheme) {
	SetColor(h, "bgbase", "textbase", ptheme);
	const size_t count_pix = HEIGHT * WIDTH;
	const size_t stop_delay = count_pix * 0.1;
	uint8_t a[HEIGHT][WIDTH] = { 0 };
	COORD cur_point = point;
	size_t cur_count_pix = 0;
	size_t i, j;

	Sleep(800);
	if (ptheme->onSounds)
		mciSendString(TEXT("play sourse\\sound\\menu\\transitionDesignTheme.mp3"),
			NULL, 0, NULL); // звуки смены темы
	clock_t time_start = clock();

	while (cur_count_pix < count_pix) {
		do {
			i = rand() % HEIGHT;
			j = rand() % WIDTH;
		} while (a[i][j]);

		a[i][j] = 1;
		cur_point.X = point.X + j;
		cur_point.Y = point.Y + i;
		SetConsoleCursorPosition(h, cur_point);
		putchar(' ');
		cur_count_pix++;
		if (!TIMER(time_start, 2800)) {
			Sleep(2);
		}
	}
	system("cls");
	while (!TIMER(time_start, 6000));
	if (ptheme->onSounds)
		mciSendString(TEXT("play sourse\\sound\\menu\\interference.mp3"),
			NULL, 0, NULL); // звук помех
}

/*вывод в окне с дескриптором h в блоках block1
и block2 подвала главного меню*/
void PrintFooterMainMenu(HANDLE h, Tblock block1, Tblock block2) {
	static char line[SIZE];
	line[WIDTH] = '\0';
	for (size_t i = 0; i < WIDTH; i++) {
		line[i] = '-';
	}
	SetConsoleCursorPosition(h, block1.pos);
	printf("%s", line);

	char cat[8][WIDTH]; // изображение кота
	SetCatMatr(cat);
	PrintMatrPoint(h, cat, 8, 15, block2.pos);

	COORD point = block1.pos;
	MoveConsoleCursorPoint(h, &point, 21, 1);
	printf(". __/\\  ___ .. _ .    .");
	MoveConsoleCursorPoint(h, &point, 24, 0);
	printf("    ____ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" __/    \\");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("/  \\     |");

	MoveConsoleCursorPoint(h, &point, 18, -1);
	printf(" ______");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("/      \\");

	MoveConsoleCursorPoint(h, &point, 12, -2);
	printf(" ___");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|___\\");

}

/*запись в матрицу перпятствий a размера HEIGHT x WIDTH 
таблицы достижений по блоку block символами ch*/
void SetBlockAchievementTableMatr(char a[HEIGHT][WIDTH], Tblock block, char ch) {
	SetBlockMatr(a, block, ch);
	Tblock new_block;
	new_block.pos.X = block.pos.X + 4;
	new_block.pos.Y = block.pos.Y - 1;
	new_block.lenX = 1;
	new_block.lenY = 1;
	SetBlockMatr(a, new_block, ch);

	new_block.pos.X += 30;
	SetBlockMatr(a, new_block, ch);

	new_block.pos.Y += 14;
	new_block.lenX = 3;
	new_block.lenY = 5;
	SetBlockMatr(a, new_block, ch);

	new_block.pos.X -= 31;
	SetBlockMatr(a, new_block, ch);
}

/*вывод в окне с дескриптором h интерфейса главного меню с 
расположением элементов структуры по адресу pblocks с погодой 
и цветовой темой структур по адресам pweather и ptheme, 
возвращая индекс следующего интерфейса, в который необходимо перейти*/
size_t PrintWindowMainMenu(HANDLE h, TblocksMainMenu* pblocks,
	Tweather* pweather, Ttheme* ptheme) {
	// массив указателей на состояния кнопок меню
	size_t* conditions[] = {
		NULL,
		&pblocks->story.cond,
		&pblocks->custom_game.cond,
		&pblocks->simulation.cond,
		&pblocks->settings.cond,
		&pblocks->exit.cond,
		&pblocks->book_rule.cond
	};
	const size_t count_button = 7;
	// индекс помеченной кнопки
	int target = 0; 
	// индекс помеченной кнопки по курсору мыши
	int target_cursore = 0; 
	size_t pressed = 0; // индекс нажатой кнопки
	size_t lightning = 0; // был ли удар молнии
	clock_t time_start = 0;
	CopyCharMatr(pweather->matr_obstac, pweather->matr_obstac_footer);
	SetBlockMatr(pweather->matr_obstac, pblocks->header, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->buttons, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->book_rule, '#');
	SetBlockAchievementTableMatr(pweather->matr_obstac, pblocks->achievement_table, '#');

	flagMainMenuReCreate:

	// вывод статичных элементов меню
	SetColor(h, "bgbase", "textbase", ptheme);
	PrintFooterMainMenu(h, *pblocks->pfooter, *pblocks->pcat);
	SetConsoleCursorPosition(h, pblocks->pversion->pos);
	PrintColor(h, VERSION, ptheme);

	// инициализация состояния кнопок
	pblocks->story.cond = BUTTON_HOVER_KEY;
	pblocks->custom_game.cond = BUTTON_INIT;
	pblocks->simulation.cond = BUTTON_INIT;
	pblocks->settings.cond = BUTTON_INIT;
	pblocks->exit.cond = BUTTON_INIT;
	pblocks->book_rule.cond = BUTTON_INIT;
	pblocks->achievement_table.cond = BUTTON_INIT;
	pblocks->header.cond = BUTTON_INIT;
	
	while (!pressed) {
		MusicBgControl(CONTEXT_MENU, ptheme->onMusicBg);
		CountTimeSpenInGame(FILE_PATH_SETTINGS, "minutsInGame", &ptheme->minutsInGame);

		// если была нажата клавиша, то сделать задержку времени
		if (TIMER(time_start, SPEED_SWITCH_BUTTON)) {
			target = GetIndexNumberPointer(conditions, count_button, BUTTON_HOVER_CUR);
			target_cursore = GetIndexNumberPointer(conditions, count_button, BUTTON_HOVER);
			// перключение между кнопками клавишами
			if (GetKeyState(VK_UP) < 0 && target > MAIN_MENU_STORY) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[--target]) = BUTTON_HOVER_KEY;
				time_start = clock();
			}
			else if (GetKeyState(VK_DOWN) < 0 && target < MAIN_MENU_GAME_RULE) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[++target]) = BUTTON_HOVER_KEY;
				time_start = clock();
			}
			else if (GetKeyState(VK_RIGHT) < 0 && target != MAIN_MENU_GAME_RULE) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[MAIN_MENU_GAME_RULE]) = BUTTON_HOVER_KEY;
				time_start = clock();
			}
			else if (GetKeyState(VK_LEFT) < 0 && target == MAIN_MENU_GAME_RULE) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[MAIN_MENU_EXIT]) = BUTTON_HOVER_KEY;
				time_start = clock();
			}

			// если был зафиксирован выбор кнопки курсором
			if (target >= 0 && target_cursore >= 0 && target != target_cursore) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[target_cursore]) = BUTTON_HOVER_KEY;
			}

			// вывод кнопок меню
			pressed += PrintButtonStandart(h, &pblocks->story, "сюжетная игра",
				WIDTH_BUTTON_MENU, ptheme) * MAIN_MENU_STORY;
			pressed += PrintButtonStandart(h, &pblocks->custom_game, "начать игру",
				WIDTH_BUTTON_MENU, ptheme) * MAIN_MENU_CUSTOM_GAME;
			pressed += PrintButtonStandart(h, &pblocks->simulation, "симуляция",
				WIDTH_BUTTON_MENU, ptheme) * MAIN_MENU_SIMULATION;
			pressed += PrintButtonStandart(h, &pblocks->settings, "настройки",
				WIDTH_BUTTON_MENU, ptheme) * MAIN_MENU_SETTINGS;
			pressed += PrintButtonStandart(h, &pblocks->exit, "выход",
				WIDTH_BUTTON_MENU, ptheme) * MAIN_MENU_EXIT;
			pressed += PrintButtonBookRule(h, &pblocks->book_rule, ptheme)
				* MAIN_MENU_GAME_RULE;
		}
		if (PrintElCursorHover(h, &pblocks->header, PrintImgHeaderMainMenu, ptheme))
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\electroClick.mp3"),
					NULL, 0, NULL); // звук электро-клика
				mciSendString(TEXT("play sourse\\sound\\voice_acting\\menuCardGameDurak.mp3"),
					NULL, 0, NULL); // сообщение
			}
		PrintButtonCat(h, pblocks->pcat, ptheme);
		PrintButtonAchievementTable(h, &pblocks->achievement_table, ptheme);
		SetConsoleCursorPosition(h, *pblocks->pcursore);

		// если прошло достаточное кол-во мс после прошлого вывода осадков
		if (TIMER(pweather->time_start, pweather->delay)) {
			lightning = WeatherDynamics(h, pweather, ptheme);
			MoveWeather(pweather, pweather->matr_obstac);
			PrintWeather(h, pweather, pweather->matr_obstac,
				ptheme->onSoundsWeather);
			if (lightning)
				goto flagMainMenuReCreate;
		}

		//if (ptheme->launch == 1) { // для первого входа в игру
		//	Sleep(1500);
		//	mciSendString(TEXT("play sourse\\sound\\voice_acting\\introduction.mp3"),
		//		NULL, 0, NULL); // сообщение
		//	Sleep(120000);
		//	TransitionDesignTheme(h, pblocks->pwindow->pos, ptheme);
		//	mciSendString(TEXT("play sourse\\sound\\voice_acting\\forward.mp3"),
		//		NULL, 0, NULL); // сообщение
		//	ptheme->launch++;
		//	goto flagMainMenuReCreate;
		//}
	}
	if (ptheme->onSounds) {
		mciSendString(TEXT("close sourse\\sound\\voice_acting\\menuCardGameDurak.mp3"),
			NULL, 0, NULL); // сообщение
		if (pressed == MAIN_MENU_STORY) {
			mciSendString(TEXT("play sourse\\sound\\menu\\toBeContinued.mp3"),
				NULL, 0, NULL); //звук
			MusicBgControl(CONTEXT_NONE, ptheme->onMusicBg);
			Sleep(100);
			PrintTransitionEffect(h, pblocks->pwindow->pos, ptheme);
			char strs[1][100];
			strcpy(strs[0], "to be continued...");
			PrintRectangle(h, *pblocks->pwindow, "bgmsg", ptheme);
			PrintLargeMsg(h, *pblocks->pwindow, strs, 1, 7000, 1000, "bgmsg", "textmsg", "texttarget", ptheme);
			PrintLargeMsg(h, *pblocks->pwindow, strs, 1, 1000, 200, "bgmsg", "textmsg", "texttarget", ptheme);
			system("cls");
		}
	}
	PrintTransitionEffect(h, pblocks->pwindow->pos, ptheme);
	return pressed;
}

/*вывод в окне с дескриптором h интерфейса настроек игровой сессии с
расположением элементов структуры по адресу pblocks с погодой
и цветовой темой структур по адресам pweather и ptheme, используя
информацию структуры по адресу pGameTable, записывая в массив difficulty
уровень игры игроков, с цветовой темой структуры по адресу ptheme,
возвращая значение "ложь", если осуществляется переход к главное меню,
иначе значение "истина"*/
size_t PrintWindowCustomGame(HANDLE h, TblocksCustomGame* pblocks,
	Tweather* pweather, TgameTable* pGameTable, size_t* difficulty, Ttheme* ptheme) {
	size_t lightning = 0; // был ли удар молнии
	// индекс помеченной кнопки
	int target = 0;
	// индекс помеченной кнопки по курсору мыши
	int target_cursore = 0;
	size_t pressed = 0; // индекс нажатой кнопки
	clock_t time_start = 0;

	size_t see_mode = 0;
	size_t ai_mode = 0;
	size_t multiplayer = 0; // игра по локальной сети
	size_t update_menu = 0; // было ли меню обновлено мультиплеером

	// массив указателей на состояния кнопок меню
	size_t* conditions[] = {
		NULL,
		&pblocks->players[0].cond,
		&pblocks->players[1].cond,
		&pblocks->players[2].cond,
		&pblocks->players[3].cond,
		&pblocks->players[4].cond,
		&pblocks->players[5].cond,
		&pblocks->see_mode.cond,
		&pblocks->only_ai.cond,
		&pblocks->effect.cond,
		&pblocks->special_card.cond,
		&pblocks->multiplayer.cond,
		&pblocks->start.cond,
		&pblocks->goto_menu.cond
	};
	const size_t count_button = 14;

	pGameTable->count_players = 2;
	difficulty[0] = USER;
	difficulty[1] = EASY;
	difficulty[2] = NONE_DIFF;
	difficulty[3] = NONE_DIFF;
	difficulty[4] = NONE_DIFF;
	difficulty[5] = NONE_DIFF;
	for (size_t i = 0; i < 6; i++) // инициализация имен игроков
		pGameTable->name_player[i][0] = '\0';
	pGameTable->event_effect = 0;
	pGameTable->special_card = 0;
	pGameTable->move_number = 0;
	pGameTable->user = 0;
	pGameTable->game_start = 0;
	pGameTable->end_game = 0;
	strcpy(pGameTable->name_player[pGameTable->user], ptheme->userName);

	pblocks->start.lenY++;
	pblocks->goto_menu.lenY++;
	CopyCharMatr(pweather->matr_obstac, pweather->matr_obstac_footer);
	SetBlockMatr(pweather->matr_obstac, pblocks->header, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->info, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->start, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->goto_menu, '#');
	pblocks->start.lenY--;
	pblocks->goto_menu.lenY--;

	flagCustomGameReCreate:

	// вывод статичных элементов меню
	PrintRectangle(h, pblocks->info, "bgmsg", ptheme);
	PrintFooterMainMenu(h, *pblocks->pfooter, *pblocks->pcat);
	SetConsoleCursorPosition(h, pblocks->pversion->pos);
	PrintColor(h, VERSION, ptheme);

	PrintTableSimulation(h, pblocks->table, ptheme);

	// инициализация состояния кнопок
	pblocks->start.cond = BUTTON_HOVER_KEY;
	pblocks->goto_menu.cond = BUTTON_INIT;
	pblocks->header.cond = BUTTON_INIT;
	pblocks->see_mode.cond = BUTTON_INIT;
	pblocks->only_ai.cond = BUTTON_INIT;
	pblocks->special_card.cond = BUTTON_INIT;
	pblocks->multiplayer.cond = BUTTON_INIT;
	pblocks->effect.cond = BUTTON_INIT;
	pblocks->players[0].cond = BUTTON_INIT;
	for (size_t i = 1; i < 6; i++) {
		pblocks->players[i].cond = BUTTON_INIT;
	}

	while (!pressed) {
		MusicBgControl(CONTEXT_MENU, ptheme->onMusicBg);
		CountTimeSpenInGame(FILE_PATH_SETTINGS, "minutsInGame", &ptheme->minutsInGame);

		if (TIMER(time_start, SPEED_SWITCH_BUTTON)) {
			target = GetIndexNumberPointer(conditions, count_button, BUTTON_HOVER_CUR);
			target_cursore = GetIndexNumberPointer(conditions, count_button, BUTTON_HOVER);
			// перключение между кнопками клавишами
			if (GetKeyState(VK_UP) < 0 && target > 1) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[--target]) = BUTTON_HOVER_KEY;
				time_start = clock();
			}
			else if (GetKeyState(VK_DOWN) < 0 && target + 1 < count_button) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[++target]) = BUTTON_HOVER_KEY;
				time_start = clock();
			}

			// если был зафиксирован выбор кнопки курсором
			if (target >= 0 && target_cursore >= 0 && target != target_cursore) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[target_cursore]) = BUTTON_HOVER_KEY;
			}

			PrintButtonMark(h, &pblocks->see_mode, "вкл. режим всевидящего (чит-режим)",
				&see_mode, ptheme);
			PrintButtonMark(h, &pblocks->only_ai, "вкл. режим \"только ИИ\" (без пользователя)",
				&ai_mode, ptheme);
			if (ai_mode && pGameTable->mode != GAME_AI) {
				pGameTable->mode = GAME_AI;
				difficulty[pGameTable->user] = EASY;
				pGameTable->name_player[pGameTable->user][0] = '\0';
				see_mode = 1;
				pblocks->see_mode.cond = BUTTON_INIT;
			} 
			else if (see_mode && !ai_mode && pGameTable->mode != GAME_STANDART_SEE) {
				pGameTable->mode = GAME_STANDART_SEE;
			} 
			else if (!ai_mode && !see_mode && pGameTable->mode != GAME_STANDART) {
				pGameTable->mode = GAME_STANDART;
				difficulty[pGameTable->user] = USER;
				strcpy(pGameTable->name_player[pGameTable->user], ptheme->userName);
			}

			PrintButtonMark(h, &pblocks->special_card, "вкл. использование специальных карт (не работает, зараза)",
				&pGameTable->special_card, ptheme);
			PrintButtonMark(h, &pblocks->multiplayer, "вкл. игру по локальной сети (которая не работает)",
				&multiplayer, ptheme);
			if (update_menu != multiplayer) {
				if (multiplayer) { // если игра открыта для локальной сети
					if (ptheme->onSounds) {
						mciSendString(TEXT("play sourse\\sound\\game_table\\notice1.mp3"),
							NULL, 0, NULL); //звук
					}
					char s[SIZE];
					SetBlockMatr(pweather->matr_obstac, pblocks->chat, '#');
					ChatClear(pGameTable->chat, HEIGHT_CHAT);
					GetMsgForChat(s, "\\green:Игра открыта для локальной сети. \\textmsg:Однако никто \
не сможет к вам подключиться, господин, ибо данная функция еще в разработке!", "@", "darkgray", ptheme);
					UpdateChat(pGameTable->chat, pblocks->chat, s, ptheme);
					PrintChat(h, pblocks->chat, pGameTable->chat, ptheme);

				} else {
					SetBlockMatr(pweather->matr_obstac, pblocks->chat, ' ');
					PrintRectangle(h, pblocks->chat, "bgbase", ptheme);
				}
				update_menu = multiplayer;
				pblocks->button_chat.cond = BUTTON_INIT;
			}
			if (multiplayer) {
				PrintStrCursorHover(h, &pblocks->button_chat, "[ нажмите, чтобы вести сообщение ]",
					"bgmsg", "darkgray", "texttarget", ptheme);
				if (CursoreInBlock(pblocks->button_chat) == 2 || (GetKeyState(VK_TAB) < 0)
					&& TIMER(time_start, SPEED_CLICK)) {
					char s_in[MAX_LEN_MESSAGE];
					// если пользователь подтвердил введенное сообщение, то отправить его
					if (InputTextInChat(h, pblocks->input_chat.pos, s_in,
						pblocks->input_chat.lenX, ptheme)) {
						char s_out[MAX_LEN_MESSAGE];
						GetMsgForChat(s_out, s_in, pGameTable->name_player[pGameTable->user], "darkgray", ptheme);
						UpdateChat(pGameTable->chat, pblocks->chat, s_out, ptheme);
					}
					PrintRectangle(h, pblocks->input_chat, "bgbase", ptheme);
					if (ptheme->printChat)
						PrintChat(h, pblocks->chat, pGameTable->chat, ptheme);
					time_start = clock();
					pblocks->button_chat.cond = BUTTON_INIT;
				}
			}

			PrintDropDownList(h, &pblocks->effect, "СОБЫТИЙНЫЕ ЭФФЕКТЫ (не работает)",
				optionsEffects, countEffects, &pGameTable->event_effect, ptheme);

			pressed += PrintButtonStandart(h, &pblocks->start, "начать игру",
				0, ptheme) * 1;
			pressed += PrintButtonStandart(h, &pblocks->goto_menu, "в главное меню",
				0, ptheme) * 2;
			PrintTableChoiseAI(h, pblocks->players, &pGameTable->count_players,
				difficulty, pGameTable->name_player, ptheme);

		}

		if (PrintWordCursorHover(h, &pblocks->header, "пользовательская игра", ptheme))
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\electroClick.mp3"),
					NULL, 0, NULL); // звук электро-клика
				mciSendString(TEXT("play sourse\\sound\\voice_acting\\menuCustomGame.mp3"),
					NULL, 0, NULL); // сообщение
			}
		PrintButtonCat(h, pblocks->pcat, ptheme);

		// если прошло достаточное кол-во мс после прошлого вывода осадков
		if (TIMER(pweather->time_start, pweather->delay)) {
			lightning = WeatherDynamics(h, pweather, ptheme);
			MoveWeather(pweather, pweather->matr_obstac);
			PrintWeather(h, pweather, pweather->matr_obstac,
				ptheme->onSoundsWeather);
			if (lightning)
				goto flagCustomGameReCreate;
		}
		SetConsoleCursorPosition(h, *pblocks->pcursore);
	}

	if (ptheme->onSounds)
		mciSendString(TEXT("close sourse\\sound\\voice_acting\\menuSimulation.mp3"),
			NULL, 0, NULL); // сообщение
	PrintTransitionEffect(h, pblocks->pwindow->pos, ptheme);
	return pressed == 1 ? 1 : 0;
}

/*вывод в окне с дескриптором h интерфейса симуляции игр с 
расположением элементов структуры по адресу pblocks с погодой 
и цветовой темой структур по адресам pweather и ptheme, используя 
информацию структуры по адресу pGameTable, записывая в массив difficulty 
уровень игры игроков, получая позиции выхода игроков из игры в массив 
pos_out_player, с цветовой темой структуры по адресу ptheme, 
возвращая индекс следующего интерфейса, в который необходимо перейти*/
size_t PrintWindowSimulation(HANDLE h, TblocksSimulation* pblocks,
	Tweather* pweather, TgameTable* pGameTable, size_t* difficulty, Ttheme* ptheme) {
	// количество симуляций игр по умолчанию
	static size_t count_games = 500;
	// количество прошедших симуляций игр
	static size_t count_games_done = 0;
	// количество побед игроков
	static size_t count_wins_p[6] = { 0,0,0,0,0,0 };
	// количество очков игроков
	static size_t count_points_p[6] = { 0,0,0,0,0,0 };
	// сумма очков игроков
	static size_t sum_points = 0;
	// количество ничейных результатов игр
	static size_t count_tie_results = 0;

	// сумма количеств ходов игровых сессий
	static long long unsigned sum_count_move = 0;
	// минимальное количество ходов за одну игровую сессию
	static size_t min_count_move = 1e9;
	// максимальное количество ходов за одну игровую сессию
	static size_t max_count_move = 0;

	// сумма количеств ответов игроков
	static long long unsigned sum_count_priority = 0;
	// минимальное количество ответов игроков за одну игровую сессию
	static size_t min_count_priority = 1e9;
	// максимальное количество ответов игроков за одну игровую сессию
	static size_t max_count_priority = 0;

	static size_t launched = 0; // запущен ли режим симуляции игр
	static size_t sim_finish = 0; // симуляция завершена
	static size_t lightning = 0; // был ли удар молнии
	static clock_t time_start_sim = 0; // время начала работы симуляции
	static size_t re_print = 1; // нужно ли вывеси статичные элементы на экран
	static size_t type_simulation = 1; // тип вывода элементов меню для симуляции

	static clock_t init_time_start_sim = 0; // инициализация времени начала работы симуляции
	static clock_t init_settings = 0; // инициализация настроек игроков была

	static char sname[6][MAX_LEN_NICKNAME + 1];
	static char sdiff[6][20];

	// массив указателей на состояния кнопок меню
	size_t* conditions[] = {
		NULL,
		&pblocks->players[0].cond,
		&pblocks->players[1].cond,
		&pblocks->players[2].cond,
		&pblocks->players[3].cond,
		&pblocks->players[4].cond,
		&pblocks->players[5].cond,
		&pblocks->count_sim.cond,
		&pblocks->start.cond,
		&pblocks->goto_menu.cond
	};
	const size_t count_button = 10;

	// индекс помеченной кнопки
	int target = 0;
	// индекс помеченной кнопки по курсору мыши
	int target_cursore = 0;
	size_t pressed = 0; // индекс нажатой кнопки
	size_t sec; // количество секунд, которое прошло с начала работы симуляции
	COORD point = pblocks->info.pos;
	clock_t time_start = 0;
	char s[SIZE];

	if (launched) { // если запущен режим симуляции
		count_games_done++;
		for (size_t i = 0; i < pGameTable->count_players; i++) {
			pGameTable->pos_out_player[i] = pGameTable->count_players 
				- pGameTable->pos_out_player[i];
			sum_points += pGameTable->pos_out_player[i];
			if (pGameTable->pos_out_player[i]) {
				count_wins_p[i]++;
				count_points_p[i] += pGameTable->pos_out_player[i];
			}
		}
		if (IsEqualElArr(pGameTable->pos_out_player, pGameTable->count_players))
			count_tie_results++;
		sum_count_move += pGameTable->move_number;
		sum_count_priority += pGameTable->count_priority;

		if (pGameTable->move_number < min_count_move)
			min_count_move = pGameTable->move_number;
		if(pGameTable->move_number > max_count_move)
			max_count_move = pGameTable->move_number;

		if (pGameTable->count_priority < min_count_priority)
			min_count_priority = pGameTable->count_priority;
		if (pGameTable->count_priority > max_count_priority)
			max_count_priority = pGameTable->count_priority;

	} else if (!init_settings) { // настройки по умолчанию
		pGameTable->count_players = 2;
		difficulty[0] = EASY;
		difficulty[1] = EASY;
		difficulty[2] = NONE_DIFF;
		difficulty[3] = NONE_DIFF;
		difficulty[4] = NONE_DIFF;
		difficulty[5] = NONE_DIFF;
		init_settings = 1;
		for (size_t i = 0; i < 6; i++) // инициализация имен игроков
			pGameTable->name_player[i][0] = '\0';
	}
	flagSimulationReCreate:

	if (re_print) {
		if (type_simulation == 3) {
			pblocks->anew.lenY++;
			pblocks->goto_menu.lenY++;
			SetBlockMatr(pweather->matr_obstac, pblocks->anew, '#');
			SetBlockMatr(pweather->matr_obstac, pblocks->goto_menu, '#');
			pblocks->anew.lenY--;
			pblocks->goto_menu.lenY--;

			// инициализация состояния кнопок
			pblocks->anew.cond = BUTTON_INIT;
			pblocks->goto_menu.cond = BUTTON_INIT;
			pblocks->header.cond = BUTTON_INIT;
		} else {
			CopyCharMatr(pweather->matr_obstac, pweather->matr_obstac_footer);
			SetBlockMatr(pweather->matr_obstac, pblocks->header, '#');
			SetBlockMatr(pweather->matr_obstac, pblocks->info, '#');

			// вывод статичных элементов меню
			PrintRectangle(h, pblocks->info, "bgmsg", ptheme);
			PrintFooterMainMenu(h, *pblocks->pfooter, *pblocks->pcat);
			SetConsoleCursorPosition(h, pblocks->pversion->pos);
			PrintColor(h, VERSION, ptheme);

			if (type_simulation == 1) {
				pblocks->start.lenY++;
				pblocks->goto_menu.lenY++;
				SetBlockMatr(pweather->matr_obstac, pblocks->table, '#');
				SetBlockMatr(pweather->matr_obstac, pblocks->start, '#');
				SetBlockMatr(pweather->matr_obstac, pblocks->goto_menu, '#');
				pblocks->start.lenY--;
				pblocks->goto_menu.lenY--;
				PrintTableSimulation(h, pblocks->table, ptheme);

				// инициализация состояния кнопок
				pblocks->start.cond = BUTTON_HOVER_KEY;
				pblocks->count_sim.cond = BUTTON_INIT;
				pblocks->goto_menu.cond = BUTTON_INIT;
				pblocks->header.cond = BUTTON_INIT;
				pblocks->players[0].cond = BUTTON_INIT;
				for (size_t i = 1; i < 6; i++) {
					pblocks->players[i].cond = BUTTON_INIT;
				}
			} else if (type_simulation == 2) {
				pblocks->stop.lenY++;
				SetBlockMatr(pweather->matr_obstac, pblocks->stop, '#');
				pblocks->stop.lenY--;
				// инициализация состояния кнопок
				pblocks->stop.cond = BUTTON_INIT;
			}
		}
		re_print = 0;
	}

	while (pressed != SIMULATION_GOTO_MENU && pressed != SIMULATION_START) {
		if (launched && count_games >= 1000) {
			MusicBgControl(CONTEXT_SIMULATION, ptheme->onMusicBg);
		} else
			MusicBgControl(CONTEXT_MENU, ptheme->onMusicBg);
		CountTimeSpenInGame(FILE_PATH_SETTINGS, "minutsInGame", &ptheme->minutsInGame);
		pressed = 0;

		if (PrintWordCursorHover(h, &pblocks->header, "меню симуляции игр", ptheme))
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\electroClick.mp3"),
					NULL, 0, NULL); // звук электро-клика
				mciSendString(TEXT("play sourse\\sound\\voice_acting\\menuSimulation.mp3"),
					NULL, 0, NULL); // сообщение
			}
		PrintButtonCat(h, pblocks->pcat, ptheme);

		if (launched) { // если запущен режим симуляции
			if (!init_time_start_sim) {
				if (ptheme->onSounds) {
					mciSendString(TEXT("play sourse\\sound\\menu\\simulationStart.mp3"),
						NULL, 0, NULL); // звук старта симуляции
				}
				time_start_sim = clock();
				init_time_start_sim = 1;

				for (size_t i = 0; i < pGameTable->count_players; i++) {
					if (pGameTable->name_player[i][0] == '\0')
						sprintf(sname[i], "%u-й игрок", i + 1);
					else
						strcpy(sname[i], pGameTable->name_player[i]);

					switch (difficulty[i]) {
						case EASY:
							strcpy(sdiff[i], "новичок"); break;
						case NORMAL:
							strcpy(sdiff[i], "опытный"); break;
						case HARD:
							strcpy(sdiff[i], "мастер"); break;
						case UNREAL:
							strcpy(sdiff[i], "бог"); break;
					}
				}
			}

			// вывод кнопок меню
			pressed += PrintButtonStandart(h, &pblocks->stop, "остановить",
				pblocks->stop.lenX, ptheme) * SIMULATION_STOP;
			if (GetKeyState(VK_ESCAPE) < 0) {
				if (ptheme->onSounds) {
					mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
						NULL, 0, NULL); //звук
				}
				PrintImgPressedButton(h, pblocks->stop.pos, "остановить", 0, ptheme);
				pressed = SIMULATION_STOP;
				Sleep(SPEED_CLICK);
			}

			if (count_games_done == count_games) {
				launched = 0;
				sim_finish = 1;
			}
			point = pblocks->info.pos;
			SetConsoleCursorPosition(h, point);
			sec = TIME_SEC(time_start_sim);

			// информция о завершенности симуляции
			if (sim_finish) {
				init_time_start_sim = 0;
				launched = 0;
				type_simulation = 3;
				re_print = 1;

				point = pblocks->info.pos;
				SetConsoleCursorPosition(h, point);
				if (count_games_done < count_games) {
					if (ptheme->onSounds) {
						mciSendString(TEXT("play sourse\\sound\\menu\\simulationComplete2.mp3"),
							NULL, 0, NULL); // звук досрочного завершения симуляции
					}
					PrintColorCenter(h, "Симуляция игр завершена досрочно",
						"bgmsg", "lightred", pblocks->info.lenX, ptheme);
				} else {
					if (ptheme->onSounds) {
						mciSendString(TEXT("play sourse\\sound\\menu\\simulationComplete1.mp3"),
							NULL, 0, NULL); // звук завершения симуляции
					}
					PrintColorCenter(h, "Симуляция игр успешно завершена!",
						"bgmsg", "green", pblocks->info.lenX, ptheme);
				}
			} else {
				PrintColor(h, "\\texttarget-bgmsg: Процесс симуляции игр запущен", ptheme);
				for (int i = sec % 3; i >= 0; i--) {
					PrintColor(h, "\\texttarget-bgmsg:.", ptheme);
				}
			}
			MoveConsoleCursorPoint(h, &point, 0, 2);
			sprintf(s, "\\texttarget-bgmsg: Сыграно %u из %u игр", count_games_done, count_games);
			PrintColor(h, s, ptheme);

			// информация о процессе симуляции
			MoveConsoleCursorPoint(h, &point, 0, 1);
			for (size_t i = 0; i < pGameTable->count_players; i++) {
				MoveConsoleCursorPoint(h, &point, 0, 1);

				sprintf(s, "\\green-bgmsg:%s \\textmsg-bgmsg:уровня \\green-bgmsg:%s \
\\textmsg-bgmsg:выиграл \\texttarget-bgmsg:%u раз (%.1f%%) \\textmsg-bgmsg:и набрал \
\\texttarget-bgmsg:%u очков (%.1f%%)", sname[i], sdiff[i], count_wins_p[i], (float)count_wins_p[i] / 
count_games_done * 100, count_points_p[i], (float)count_points_p[i] / sum_points * 100);
				PrintColor(h, s, ptheme);
			}
			MoveConsoleCursorPoint(h, &point, 0, 1);
			sprintf(s, "\\textmsg-bgmsg: Количество ничейных результатов: \\texttarget-bgmsg:%u (%.1f%%)",
				count_tie_results, (float)count_tie_results / count_games_done * 100);
			PrintColor(h, s, ptheme);

			MoveConsoleCursorPoint(h, &point, 0, 2);
			sprintf(s, "\\textmsg-bgmsg: Затраченное время: \\texttarget-bgmsg:%02u:%02u:%02u",
				sec / 3600, sec / 60, sec % 60);
			PrintColor(h, s, ptheme);

			if (sim_finish) {
				MoveConsoleCursorPoint(h, &point, 0, 2);
				sprintf(s, "\\textmsg-bgmsg: Среднее количество просимулированных игр в секунду: \\texttarget-bgmsg:%u",
					count_games_done / (!sec ? 1 : sec));
				PrintColor(h, s, ptheme);

				MoveConsoleCursorPoint(h, &point, 0, 1);
				sprintf(s, "\\textmsg-bgmsg: Среднее количество ходов за игру: \\texttarget-bgmsg:%u (%u\b%u ... %u)",
					sum_count_move / count_games_done, min_count_move, max_count_move);
				PrintColor(h, s, ptheme);

				MoveConsoleCursorPoint(h, &point, 0, 1);
				sprintf(s, "\\textmsg-bgmsg: Среднее количество ответов игроков за игру: \\texttarget-bgmsg:%u (%u\b%u ... %u)",
					sum_count_priority / count_games_done, min_count_priority, max_count_priority);
				PrintColor(h, s, ptheme);
				goto flagSimulationReCreate;
			}

		} else if (type_simulation == 3) {
			pressed += PrintButtonStandart(h, &pblocks->anew, "новая симуляция",
				0, ptheme) * SIMULATION_ANEW;
			if (GetKeyState(VK_SPACE) < 0) {
				if (ptheme->onSounds) {
					mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
						NULL, 0, NULL); //звук
				}
				PrintImgPressedButton(h, pblocks->anew.pos, "новая симуляция", 0, ptheme);
				pressed = SIMULATION_ANEW;
			}

			pressed += PrintButtonStandart(h, &pblocks->goto_menu, "в главное меню",
				0, ptheme) * SIMULATION_GOTO_MENU;
			if (GetKeyState(VK_ESCAPE) < 0)
				pressed = SIMULATION_GOTO_MENU;

		} else {
			if (TIMER(time_start, SPEED_SWITCH_BUTTON)) {
				target = GetIndexNumberPointer(conditions, count_button, BUTTON_HOVER_CUR);
				target_cursore = GetIndexNumberPointer(conditions, count_button, BUTTON_HOVER);
				// перключение между кнопками клавишами
				if (GetKeyState(VK_UP) < 0 && target > 1) {
					*(conditions[target]) = BUTTON_INIT;
					*(conditions[--target]) = BUTTON_HOVER_KEY;
					time_start = clock();
				}
				else if (GetKeyState(VK_DOWN) < 0 && target < SIMULATION_GOTO_MENU) {
					*(conditions[target]) = BUTTON_INIT;
					*(conditions[++target]) = BUTTON_HOVER_KEY;
					time_start = clock();
				}
				PrintButtonInputNumber(h, &pblocks->count_sim, "Количество симуляций игр", 
					10, &count_games, 1, MAX_COUNT_SIMULATION, ptheme);
			}

			// если был зафиксирован выбор кнопки курсором
			if (target >= 0 && target_cursore >= 0 && target != target_cursore) {
				*(conditions[target]) = BUTTON_INIT;
				*(conditions[target_cursore]) = BUTTON_HOVER_KEY;
			}
			// вывод кнопок меню
			if (!sim_finish) {
				pressed += PrintButtonStandart(h, &pblocks->start, "запуск",
					0, ptheme) * SIMULATION_START;
				if (pressed == SIMULATION_START)
					pGameTable->mode = GAME_SIMULATION;
			}
			pressed += PrintButtonStandart(h, &pblocks->goto_menu, "в главное меню",
				0, ptheme) * SIMULATION_GOTO_MENU;
			PrintTableChoiseAI(h, pblocks->players, &pGameTable->count_players, 
				difficulty, pGameTable->name_player, ptheme);

		}

		// проверка нажатых кнопок
		if (launched) { // если запущен режим симуляции
			if (pressed == SIMULATION_STOP) { // остановить симуляцию
				sim_finish = 1;
			} else
				pressed = SIMULATION_START;
			// если режим симуляции не запущен
		} else if (pressed == SIMULATION_START) { // запуск симуляции
			launched = 1;
			re_print = 1;
			Sleep(SPEED_CLICK);
			system("cls");
			goto flagSimulationReCreate;

		} else if (pressed == SIMULATION_ANEW) { // новая симуляция
			// обнуление информации
			count_games_done = 0;
			count_tie_results = 0;
			sum_points = 0;
			sum_count_move = 0;
			sum_count_priority = 0;
			min_count_move = 1e9;
			max_count_move = 0;
			min_count_priority = 1e9;
			max_count_priority = 0;
			for (size_t i = 0; i < pGameTable->count_players; i++) {
				count_wins_p[i] = 0;
				count_points_p[i] = 0;
			}
			sim_finish = 0;

			type_simulation = 1;
			re_print = 1;
			Sleep(SPEED_CLICK);
			system("cls");
			goto flagSimulationReCreate;
		}

		// если прошло достаточное кол-во мс после прошлого вывода осадков
		if (TIMER(pweather->time_start, pweather->delay) ) {
			lightning = WeatherDynamics(h, pweather, ptheme);
			MoveWeather(pweather, pweather->matr_obstac);
			PrintWeather(h, pweather, pweather->matr_obstac,
				ptheme->onSoundsWeather);

			if (!re_print || lightning) {
				if (lightning) {
					re_print = 1;
					goto flagSimulationReCreate;
				} else
					re_print = 0;
			}
		}
		SetConsoleCursorPosition(h, *pblocks->pcursore);
	}

	if (sim_finish) {
		// обнуление информации
		count_games_done = 0;
		count_tie_results = 0;
		sum_points = 0;
		sum_count_move = 0;
		sum_count_priority = 0;
		min_count_move = 1e9;
		max_count_move = 0;
		min_count_priority = 1e9;
		max_count_priority = 0;
		for (size_t i = 0; i < pGameTable->count_players; i++) {
			count_wins_p[i] = 0;
			count_points_p[i] = 0;
		}
		sim_finish = 0;
	}
	if (!count_games_done) {
		type_simulation = 2;
		re_print = 1;
	}
	if (!launched) {
		type_simulation = 1;
		re_print = 1;
		init_settings = 0;
		if (ptheme->onSounds)
			mciSendString(TEXT("close sourse\\sound\\voice_acting\\menuSimulation.mp3"),
				NULL, 0, NULL); // сообщение
		PrintTransitionEffect(h, pblocks->pwindow->pos, ptheme);
	}
	return launched;
}

/*возвращает из матрицы указателей a размера m x n,
координату натурального числа value по указателю, иначе, 
если число не найдено, возвращает отрицательную координату*/
COORD GetIndexNumberPointerMatr(size_t* (*a)[5], size_t m, size_t n, size_t value) {
	size_t i = 0, j;
	while (i < m) {
		j = 0;
		while (j < n) {
			if (a[i][j] != NULL && *(a[i][j]) == value)
				goto flagGetPointerMatr;
			j++;
		}
		i++;
	}
	flagGetPointerMatr:
	COORD point;
	if (i == m && j == n) {
		point.X = -1;
		point.Y = -1;
	} else {
		point.X = j;
		point.Y = i;
	}
	return point;
}

/*вывод в окне с дескриптором h интерфейса меню настроек с
расположением элементов структуры по адресу pblocks с погодой
и цветовой темой структур по адресам pweather и ptheme,
возвращая индекс следующего интерфейса, в который необходимо перейти*/
size_t PrintWindowSettings(HANDLE h, TblocksSettings* pblocks, Tweather* pweather, Ttheme* ptheme) {
	// массив указателей на состояния кнопок меню
	size_t* conditions[8][5] = { NULL };
	conditions[0][0] = &pblocks->chat.cond;
	conditions[1][0] = &pblocks->messages_chat.cond;
	conditions[2][0] = &pblocks->effects.cond;
	conditions[3][0] = &pblocks->improved_alg.cond;
	conditions[4][0] = &pblocks->full_screen_mode.cond;

	conditions[0][1] = &pblocks->music_bg.cond;
	conditions[1][1] = &pblocks->sounds_weather.cond;
	conditions[2][1] = &pblocks->sounds.cond;
	conditions[5][1] = &pblocks->nickname.cond;
	conditions[6][1] = &pblocks->reset_progress.cond;
	conditions[7][1] = &pblocks->goto_menu.cond;

	conditions[0][2] = &pblocks->theme_day.cond;
	conditions[1][2] = &pblocks->theme_night.cond;
	conditions[2][2] = &pblocks->theme_east.cond;
	conditions[3][2] = &pblocks->theme_black_blue.cond;
	conditions[4][2] = &pblocks->theme_new_year.cond;

	conditions[6][2] = &pblocks->weather_clear.cond;
	conditions[6][3] = &pblocks->weather_snow.cond;
	conditions[6][4] = &pblocks->weather_rain.cond;

	const size_matrX = 5; // размеры матрицы указателей на состояния кнопок оп оси X
	const size_matrY = 8; // размеры матрицы указателей на состояния кнопок оп оси Y
	COORD target; // коордианты помеченной кнопки в матрице
	COORD target_cursore; // коордианты помеченной кнопки по курсору мыши в матрице
	size_t pressed = 0; // индекс нажатой кнопки
	size_t lightning = 0; // был ли удар молнии
	clock_t time_start = 0;
	size_t full_screen_mode = 0; // полноэкранный режим включен

	size_t design_theme[5] = {0}; // тип цветовой темы
	design_theme[ptheme->designTheme] = 1;
	size_t design_theme_prev = ptheme->designTheme;

	size_t weather[3] = { 0 }; // тип погоды
	weather[ptheme->typeWeather] = 1;
	size_t weather_prev = ptheme->typeWeather;

	pblocks->nickname.lenY++;
	pblocks->reset_progress.lenY++;
	pblocks->goto_menu.lenY++;
	CopyCharMatr(pweather->matr_obstac, pweather->matr_obstac_footer);
	SetBlockMatr(pweather->matr_obstac, pblocks->header, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->table, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->table_weather, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->table_control_keys, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->nickname, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->reset_progress, '#');
	SetBlockMatr(pweather->matr_obstac, pblocks->goto_menu, '#');
	pblocks->nickname.lenY--;
	pblocks->reset_progress.lenY--;
	pblocks->goto_menu.lenY--;

	flagMainMenuReCreate:

	// вывод статичных элементов меню
	PrintRectangle(h, pblocks->table, "bgmsg", ptheme);
	PrintRectangle(h, pblocks->table_weather, "bgmsg", ptheme);
	SetColor(h, "bgmsg", "textmsg", ptheme);
	PrintWordLarge(h, pblocks->volume.pos, "звуки и музыка", 0);
	PrintWordLarge(h, pblocks->game.pos, "игра", 0);
	PrintWordLarge(h, pblocks->theme.pos, "тема", 0);
	PrintWordLarge(h, pblocks->weather.pos, "погода", 0);

	PrintOutlineBlock(h, pblocks->weather_clear);
	PrintOutlineBlock(h, pblocks->weather_snow);
	PrintOutlineBlock(h, pblocks->weather_rain);

	SetConsoleCursorCoord(h, pblocks->theme_day.pos.X, pblocks->theme_day.pos.Y - 2);
	printf("Выбор одного из нижеперечисленных вариантов:");

	SetColor(h, "bgbase", "textbase", ptheme);
	PrintFooterMainMenu(h, *pblocks->pfooter, *pblocks->pcat);
	PrintTableControlKeys(h, pblocks->table_control_keys.pos, ptheme);
	SetConsoleCursorPosition(h, pblocks->pversion->pos);
	PrintColor(h, VERSION, ptheme);

	// инициализация состояния кнопок
	pblocks->header.cond = BUTTON_INIT;
	pblocks->nickname.cond = BUTTON_INIT;
	pblocks->full_screen_mode.cond = BUTTON_INIT;
	pblocks->reset_progress.cond = BUTTON_INIT;

	pblocks->theme_day.cond = BUTTON_INIT;
	pblocks->theme_night.cond = BUTTON_INIT;
	pblocks->theme_east.cond = BUTTON_INIT;
	pblocks->theme_black_blue.cond = BUTTON_INIT;
	pblocks->theme_new_year.cond = BUTTON_INIT;

	pblocks->weather_clear.cond = BUTTON_INIT;
	pblocks->weather_snow.cond = BUTTON_INIT;
	pblocks->weather_rain.cond = BUTTON_INIT;

	pblocks->music_bg.cond = BUTTON_INIT;
	pblocks->sounds_weather.cond = BUTTON_INIT;
	pblocks->sounds.cond = BUTTON_INIT;

	pblocks->chat.cond = BUTTON_INIT;
	pblocks->messages_chat.cond = BUTTON_INIT;
	pblocks->effects.cond = BUTTON_INIT;
	pblocks->improved_alg.cond = BUTTON_INIT;

	pblocks->goto_menu.cond = BUTTON_HOVER_KEY;
	target.Y = 7;
	target.X = 1;
	target_cursore.Y = 7;
	target_cursore.X = 1;
	while (!pressed) {
		MusicBgControl(CONTEXT_MENU, ptheme->onMusicBg);
		CountTimeSpenInGame(FILE_PATH_SETTINGS, "minutsInGame", &ptheme->minutsInGame);

		// если была нажата клавиша, то сделать задержку времени
		if (TIMER(time_start, SPEED_SWITCH_BUTTON)) {
			target = GetIndexNumberPointerMatr(conditions, size_matrY, size_matrX, BUTTON_HOVER_CUR);
			target_cursore = GetIndexNumberPointerMatr(conditions, size_matrY, size_matrX, BUTTON_HOVER);

			// переключение между кнопками клавишами
			if (GetKeyState(VK_UP) < 0 && target.Y > 0) {
				int i, j;
				size_t k = 0;
				size_t max_k = max(size_matrX - target.X, target.X);
				while (k < max_k) {
					i = target.Y - 1;
					if (target.X + k < size_matrX) {
						j = target.X + k;
						while (i >= 0) {
							if (conditions[i][j] != NULL)
								goto flagSettingsUp;
							i--;
						}
					}
					i = target.Y - 1;
					if ((int)target.X - k >= 0) {
						j = target.X - k;
						while (i >= 0) {
							if (conditions[i][j] != NULL)
								goto flagSettingsUp;
							i--;
						}
					}
					k++;
				}
				flagSettingsUp:
				if (k < max_k) {
					*(conditions[target.Y][target.X]) = BUTTON_INIT;
					*(conditions[i][j]) = BUTTON_HOVER_KEY;
				}
				time_start = clock();
			}
			else if (GetKeyState(VK_DOWN) < 0 && target.Y + 1 < size_matrY) {
				int i, j;
				size_t k = 0;
				size_t max_k = max(size_matrX - target.X, target.X);
				while (k < max_k) {
					i = target.Y + 1;
					if (target.X + k < size_matrX) {
						j = target.X + k;
						while (i < size_matrY) {
							if (conditions[i][j] != NULL)
								goto flagSettingsDown;
							i++;
						}
					}
					i = target.Y + 1;
					if ((int)target.X - k >= 0) {
						j = target.X - k;
						while (i < size_matrY) {
							if (conditions[i][j] != NULL)
								goto flagSettingsDown;
							i++;
						}
					}
					k++;
				}
				flagSettingsDown:
				if (k < max_k) {
					*(conditions[target.Y][target.X]) = BUTTON_INIT;
					*(conditions[i][j]) = BUTTON_HOVER_KEY;
				}
				time_start = clock();
			}
			else if (GetKeyState(VK_RIGHT) < 0 && target.X + 1 < size_matrX) {
				int i, j = target.X + 1;
				while (j < size_matrX) {
					i = target.Y;
					while (i >= 0) {
						if (conditions[i][j] != NULL)
							goto flagSettingsRight;
						i--;
					}
					j++;
				}
				flagSettingsRight:
				if (i >= 0 && j < size_matrX) {
					*(conditions[target.Y][target.X]) = BUTTON_INIT;
					*(conditions[i][j]) = BUTTON_HOVER_KEY;
				}
				time_start = clock();
			}
			else if (GetKeyState(VK_LEFT) < 0 && target.X > 0) {
				int i, j = target.X - 1;
				while (j >= 0) {
					i = target.Y;
					while (i >= 0) {
						if (conditions[i][j] != NULL)
							goto flagSettingsLeft;
						i--;
					}
					j--;
				}
				flagSettingsLeft:
				if (i >= 0 && j >= 0) {
					*(conditions[target.Y][target.X]) = BUTTON_INIT;
					*(conditions[i][j]) = BUTTON_HOVER_KEY;
				}
				time_start = clock();
			}
			// если был зафиксирован выбор кнопки курсором
			if (target_cursore.X >= 0 && target_cursore.Y >= 0 &&
				(target.X != target_cursore.X || target.Y != target_cursore.Y)) {
				*(conditions[target.Y][target.X]) = BUTTON_INIT;
				*(conditions[target_cursore.Y][target_cursore.X]) = BUTTON_HOVER_KEY;
			}
		}
		if (PrintWordCursorHover(h, &pblocks->header, "меню настроек", ptheme))
			if (ptheme->onSounds) {
				mciSendString(TEXT("play sourse\\sound\\menu\\electroClick.mp3"),
					NULL, 0, NULL); // звук электро-клика
				mciSendString(TEXT("play sourse\\sound\\voice_acting\\menuSettings.mp3"),
					NULL, 0, NULL); // сообщение
			}
		PrintButtonCat(h, pblocks->pcat, ptheme);

		PrintButtonMark(h, &pblocks->theme_day, "ДЕНЬ (светлый фон)",
			&design_theme[THEME_DAY], ptheme);
		PrintButtonMark(h, &pblocks->theme_night, "НОЧЬ (черный фон)",
			&design_theme[THEME_NIGHT], ptheme);
		PrintButtonMark(h, &pblocks->theme_east, "ВОСТОК (красный, желтый, черный)",
			&design_theme[THEME_EAST], ptheme);
		PrintButtonMark(h, &pblocks->theme_black_blue, "ЧЕРНО-СИНЯЯ (синий и черный)",
			&design_theme[THEME_BLACK_BLUE], ptheme);
		PrintButtonMark(h, &pblocks->theme_new_year, "НОВЫЙ ГОД (белый и красный)",
			&design_theme[THEME_NEW_YEAR], ptheme);

		if (!CountElArrValue(design_theme, 5, 1, 1)) {
			design_theme[design_theme_prev] = 0;
			if (!GetCountNonZerolArr(design_theme, 5)) {
				weather[design_theme_prev] = 1;
			} else {
				size_t i = 0; // индекс новой цветовой темы
				while (!design_theme[i]) {
					i++;
				}
				ptheme->designTheme = i;
				design_theme_prev = i;
				TransitionDesignTheme(h, pblocks->pwindow->pos, ptheme);
				SetTheme(ptheme, i);
				SaveKeyValueInFile(FILE_PATH_SETTINGS, "designTheme",
					&ptheme->designTheme, sizeof(ptheme->designTheme));
				goto flagMainMenuReCreate;
			}
		}

		// настройка климата погоды
		PrintButtonMarkImg(h, &pblocks->weather_clear, PrintSymbolIconSun,
			&weather[WEATHER_CLEAR], ptheme);
		PrintButtonMarkImg(h, &pblocks->weather_snow, PrintSymbolIconSnow,
			&weather[WEATHER_SNOW], ptheme);
		PrintButtonMarkImg(h, &pblocks->weather_rain, PrintSymbolIconRain,
			&weather[WEATHER_RAIN], ptheme);

		if (!CountElArrValue(weather, 3, 1, 1)) {
			weather[weather_prev] = 0;
			if (!GetCountNonZerolArr(weather, 3)) {
				weather[weather_prev] = 1;
			} else {
				size_t i = 0; // индекс новой погоды
				while (!weather[i]) {
					i++;
				}
				ptheme->typeWeather = i;
				weather_prev = i;
				pblocks->weather_clear.cond = BUTTON_INIT;
				pblocks->weather_snow.cond = BUTTON_INIT;
				pblocks->weather_rain.cond = BUTTON_INIT;
				switch (i) {
					case WEATHER_CLEAR:
						pweather->type = '-';
						pweather->count = 0;
						pblocks->weather_clear.cond = BUTTON_HOVER_KEY;
						break;
					case WEATHER_SNOW:
						pweather->type = '*';
						pblocks->weather_snow.cond = BUTTON_HOVER_KEY;
						break;
					case WEATHER_RAIN:
						pweather->type = '|';
						pblocks->weather_rain.cond = BUTTON_HOVER_KEY;
						break;
				}
				SaveKeyValueInFile(FILE_PATH_SETTINGS, "typeWeather",
					&ptheme->typeWeather, sizeof(ptheme->typeWeather));
			}
		}

		if (PrintButtonMark(h, &pblocks->music_bg, "Вкл. фоновую музыку",
			&ptheme->onMusicBg, ptheme))
			SaveKeyValueInFile(FILE_PATH_SETTINGS, "onMusicBg",
				&ptheme->onMusicBg, sizeof(ptheme->onMusicBg));

		if (PrintButtonMark(h, &pblocks->sounds_weather, "Вкл. звки погоды",
			&ptheme->onSoundsWeather, ptheme)) {
			if (ptheme->onSoundsWeather) { // вкл. звуки
				if (pweather->type_bg_sounds == '*')
					mciSendString(TEXT("play sourse\\music\\snow1.mp3 repeat"),
						NULL, 0, NULL);
				else if (pweather->type_bg_sounds == '|') {
					if (pweather->shower)
						mciSendString(TEXT("play sourse\\music\\rain2Level.mp3 repeat"),
							NULL, 0, NULL);
					else
						mciSendString(TEXT("play sourse\\music\\rain1Level.mp3 repeat"),
							NULL, 0, NULL);
				} else if (pweather->type_bg_sounds == ' ')
					mciSendString(TEXT("close sourse\\music\\birds.mp3"),
						NULL, 0, NULL);
			} else { // выкл. звуки
				if (pweather->type_bg_sounds == '*')
					mciSendString(TEXT("close sourse\\music\\snow1.mp3"),
						NULL, 0, NULL); // звуки снега
				else if (pweather->type_bg_sounds == '|') {
					if (pweather->shower)
						mciSendString(TEXT("close sourse\\music\\rain2Level.mp3"),
							NULL, 0, NULL); // звуки ливня
					else
						mciSendString(TEXT("close sourse\\music\\rain1Level.mp3"),
							NULL, 0, NULL);  // звуки дождя
				} else if (pweather->type_bg_sounds == ' ')
					mciSendString(TEXT("play sourse\\music\\birds.mp3 repeat"),
						NULL, 0, NULL);  // звуки птиц
			}
			SaveKeyValueInFile(FILE_PATH_SETTINGS, "onSoundsWeather", 
				&ptheme->onSoundsWeather, sizeof(ptheme->onSoundsWeather));
		}
		if (PrintButtonMark(h, &pblocks->sounds, "Вкл. прочие звуки",
			&ptheme->onSounds, ptheme))
			SaveKeyValueInFile(FILE_PATH_SETTINGS, "onSounds",
				&ptheme->onSounds, sizeof(ptheme->onSounds));

		if (PrintButtonMark(h, &pblocks->chat, "Выводить чат на игровом столе",
			&ptheme->printChat, ptheme))
			SaveKeyValueInFile(FILE_PATH_SETTINGS, "printChat",
				&ptheme->printChat, sizeof(ptheme->printChat));

		if (PrintButtonMark(h, &pblocks->messages_chat, "Вкл. сообщения о действиях игроков в чате",
			&ptheme->messagesChat, ptheme))
			SaveKeyValueInFile(FILE_PATH_SETTINGS, "messagesChat",
				&ptheme->messagesChat, sizeof(ptheme->messagesChat));

		if (PrintButtonMark(h, &pblocks->effects, "Вкл. игровые спецэффекты",
			&ptheme->specialEffects, ptheme))
			SaveKeyValueInFile(FILE_PATH_SETTINGS, "specialEffects",
				&ptheme->specialEffects, sizeof(ptheme->specialEffects));

		if (PrintButtonMark(h, &pblocks->improved_alg, "Оптимизировать алгоритм вывода элементов игрового стола",
			&ptheme->improvedAlgGameInterface, ptheme))
			SaveKeyValueInFile(FILE_PATH_SETTINGS, "improvedAlgGameInterface",
				&ptheme->improvedAlgGameInterface, sizeof(ptheme->improvedAlgGameInterface));

		if (PrintButtonMark(h, &pblocks->full_screen_mode, "Вкл. полноэкранный режим (не работает: не нажимай, пожалуйста)",
			&full_screen_mode, ptheme)) {
			mciSendString(TEXT("play sourse\\sound\\other\\scream.mp3"),
				NULL, 0, NULL); // крик
			Sleep(1000);
			mciSendString(TEXT("play sourse\\sound\\other\\dimooon.mp3"),
				NULL, 0, NULL); // крик
		}

		// кнопки
		pressed += PrintButtonStandart(h, &pblocks->nickname, "изменить никнейм", 
			0, ptheme) * SETTINGS_RE_NICKNAME;
		pressed += PrintButtonStandart(h, &pblocks->reset_progress, "сброс прогресса",
			0, ptheme) * SETTINGS_RESET_PROGRESS;
		pressed += PrintButtonStandart(h, &pblocks->goto_menu, "в главное меню",
			0, ptheme) * SETTINGS_GOTO_MENU;
		if (GetKeyState(VK_ESCAPE) < 0)
			pressed = SETTINGS_GOTO_MENU;

		SetConsoleCursorPosition(h, *pblocks->pcursore);
		// если прошло достаточное кол-во мс после прошлого вывода осадков
		if (TIMER(pweather->time_start, pweather->delay)) {
			SetColor(h, "bgbase", "textbase", ptheme);
			lightning = WeatherDynamics(h, pweather, ptheme);
			MoveWeather(pweather, pweather->matr_obstac);
			PrintWeather(h, pweather, pweather->matr_obstac,
				ptheme->onSoundsWeather);
			if (lightning)
				goto flagMainMenuReCreate;
		}
	}
	WriteToTextFileSettings(FILE_PATH_SETTINGS_TXT, FILE_PATH_SETTINGS);
	if (ptheme->onSounds)
		mciSendString(TEXT("close sourse\\sound\\voice_acting\\menuSettings.mp3"),
			NULL, 0, NULL); // сообщение
	PrintTransitionEffect(h, pblocks->pwindow->pos, ptheme);
	return pressed;
}

/*чтение текста из текстового файла fname, начиная с 
позиции pos и вывод его в окне с дескриптором h в точки 
по двумерному массиву точек a размера n с заданными длинами 
с цветовой темой структуры по адресу ptheme*/
long PrintTextFromFile(char* fname, long pos, HANDLE h, Trows a[2][32], size_t n, Ttheme* ptheme) {
	const size_t paragraph = 4; // отступ абазца в символах

	FILE* f = fopen(fname, "rt");
	if (f == NULL) {
		char stmp[150];
		char* pstmp = stmp;
		char s_in[150];
		sprintf(stmp, "\\lightred:Ошибка: файл %s не найден. Именно в нем хранилось содержимое данной книги.", fname);
		
		size_t i = 0;
		pstmp = GetStrWords(s_in, a[0][i].lenX - paragraph, pstmp, ptheme);
		a[0][0].pos.X += paragraph; // поставить абзац
		while (*s_in && i + 1 < n) {
			SetConsoleCursorPosition(h, a[0][i].pos);
			PrintColor(h, s_in, ptheme);
			i++;
			if (i < n)
				pstmp = GetStrWords(s_in, a[0][i].lenX, pstmp, ptheme);
		}
		a[0][0].pos.X -= paragraph; // убрать абзац
		return 0;
	} 
	else {
		size_t i_arr = 0; // индекс массива точек для вывода строк
		char buf[10000]; // буфер для хранения выводимого абзаца
		char stmp[10000];
		char s_in[SIZE];
		char* pstmp;
		char* pbuf;

		char color[50] = ""; // хранение цвета слова
		char color_tmp[50] = ""; // временное хранение цвета слова

		fseek(f, pos, SEEK_SET);
		size_t i = 0;
		// пока не конец файла и не перебран полностью массив точек
		flagNewPage:
		while (!feof(f) && i_arr < 2) { 
			buf[0] = '\0';
			stmp[0] = '\0';
			pstmp = stmp;
			pbuf = buf;

			// считывание абзаца текста в буфер
			fgets(stmp, 10000, f);
			while (!feof(f) && *stmp != '\n') {
				strcat(buf, stmp);
				fgets(stmp, 10000, f);
			}

			// команда переносит текст на следующую страницу
			if (!strcmp(buf, "\\newpage\n")) {
				i = 0;
				i_arr++;
				goto flagNewPage;
			}
			// поставить отступ перед абазцам, кроме первого на странице
			if (i > 0)
				i++;
			// начало абзаца на последней строке станицы переносится
			if (i + 1 >= n) {
				i = 0;
				i_arr++;
			}

			flagTextFromFile:
			if (i_arr < 2) {
				pbuf = GetStrWords(s_in, a[0][i].lenX - paragraph, pbuf, ptheme);
				size_t i_paragr = i;

				while (*s_in && i < n) {
					if (i == i_paragr) { // если строка является абзацной
						COORD point = a[i_arr][i].pos;
						point.X += paragraph;
						SetConsoleCursorPosition(h, point);
					} else {
						SetConsoleCursorPosition(h, a[i_arr][i].pos);
					}
					if (*color != '\0') { // если в слове был задан цвет
						char s_in_tmp[SIZE];
						sprintf(s_in_tmp, "%s%s", color, s_in);
						strcpy(s_in, s_in_tmp);
					}
					PrintColor(h, s_in, ptheme); // вывод строки
					CopyColorCodeStrEnd(color_tmp, s_in); // получить цвет из строки w
					if (*color_tmp != '\0') // если получен непустой цвет
						strcpy(color, color_tmp);

					i++;
					if (i < n) {
						pbuf = GetStrWords(s_in, a[0][i].lenX, pbuf, ptheme);
					} else { // если переход на следующую страницу
						i = 0;
						i_arr++;
						if (i_arr >= 2)
							goto flagTextFromFile;
					}
				}
			}
		}
		pos = ftell(f) - (!strcmp(pbuf, "\\newpage\n") ? 0 : strlen(pbuf));
		fclose(f);
		return pos;
	}
}

/*вывод в окне с дескриптором h меню книги правил в блоке 
по адресу pblocks, с цветовой темой структуры по адресу ptheme*/
void PrintWindowGameRule(HANDLE h, TblocksGameRule* pblocks, Ttheme* ptheme) {
	Trows rows[2][32] = {
		// первая страница
		{ 15, 2, 50,
		15, 3, 52,
		15, 4, 52,
		15, 5, 52,
		15, 6, 52,
		14, 7, 53,
		14, 8, 53,
		14, 9, 53,

		14, 10, 53,
		14, 11, 53,
		14, 12, 53,
		14, 13, 53,
		14, 14, 53,
		13, 15, 54,
		13, 16, 54,
		13, 17, 54,

		13, 18, 54,
		13, 19, 54,
		13, 20, 54,
		13, 21, 54,
		12, 22, 55,
		12, 23, 55,
		12, 24, 55,
		12, 25, 55,

		12, 26, 55,
		12, 27, 55,
		12, 28, 55,
		12, 29, 55,
		11, 30, 56,
		11, 31, 56,
		11, 32, 56,
		11, 33, 56},

		// вторая страница
		{ 74, 2, 52,
		72, 3, 52,
		72, 4, 52,
		72, 5, 52,
		72, 6, 53,
		72, 7, 53,
		72, 8, 53,
		72, 9, 53,

		72, 10, 53,
		72, 11, 54,
		72, 12, 54,
		72, 13, 54,
		72, 14, 54,
		72, 15, 54,
		72, 16, 54,
		72, 17, 55,

		72, 18, 55,
		72, 19, 55,
		72, 20, 55,
		72, 21, 55,
		72, 22, 56,
		72, 23, 56,
		72, 24, 56,
		72, 25, 56,

		72, 26, 56,
		72, 27, 56,
		72, 28, 57,
		72, 29, 57,
		72, 30, 57,
		72, 31, 57,
		72, 32, 57,
		72, 33, 57}
	};
	COORD page_num_left, page_num_right;
	page_num_left.X = pblocks->book.pos.X + 36;
	page_num_left.Y = pblocks->book.pos.Y + 35;
	page_num_right.X = pblocks->book.pos.X + 99;
	page_num_right.Y = page_num_left.Y;

	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < 32; j++) {
			rows[i][j].pos.X += pblocks->book.pos.X;
			rows[i][j].pos.Y += pblocks->book.pos.Y;
		}
	}

	clock_t time_start = clock();
	if (ptheme->onSounds) {
		mciSendString(TEXT("play sourse\\sound\\menu\\openBook1.mp3"),
			NULL, 0, NULL); // звук перелистывания страницы
	}
	size_t cur_page_spread = 1; // текущий разворот страницы
	size_t prev_page_spread = 1; // предыдущий разворот страницы
	size_t goto_menu = 0;
	size_t left, right;
	size_t bulb = 0, voice = 0;
	size_t prev_bulb = 0, prev_voice = 0;
	size_t print_rectangle = 1;
	// массив позиций начала вывода текста в текстовом файле для i-й страницы
	long pos_text[100] = { 0 };

	flagGameRuleReCreate:
	if (voice) {
		switch (prev_page_spread) {
			case 1:
				mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage1.mp3"),
					NULL, 0, NULL); // озвучка текста
			case 2:
				mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage2.mp3"),
					NULL, 0, NULL); // озвучка текста
			case 3:
				mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage3.mp3"),
					NULL, 0, NULL); // озвучка текста
			case 4:
				mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage4.mp3"),
					NULL, 0, NULL); // озвучка текста
		}
	}

	pblocks->book.cond = BUTTON_INIT;
	pblocks->invert_lighting.cond = BUTTON_INIT;
	pblocks->voice_acting.cond = BUTTON_INIT;
	pblocks->page_left.cond = BUTTON_INIT;
	pblocks->page_right.cond = BUTTON_INIT;
	pblocks->goto_menu.cond = BUTTON_INIT;

	// вывод статичных элементов
	SetConsoleCursorPosition(h, pblocks->pversion->pos);
	PrintColor(h, VERSION, ptheme);
	PrintLargeBook(h, pblocks->book); // вывод пустого разворота книги
	// вывод текста в книгу
	pos_text[cur_page_spread] = PrintTextFromFile(FILE_PATH_GAMERULE_TXT,
		pos_text[cur_page_spread - 1], h, rows, 32, ptheme);
	left = 0;
	right = 0;
	voice = 0;
	SetConsoleCursorPosition(h, page_num_left);
	printf("- %u -", BOOK_START_PAGE - 2 + cur_page_spread * 2);
	SetConsoleCursorPosition(h, page_num_right);
	printf("- %u -", BOOK_START_PAGE - 1 + cur_page_spread * 2);

	PrintRectangle(h, pblocks->page_left, "bgbase", ptheme);
	PrintRectangle(h, pblocks->page_right, "bgbase", ptheme);

	while (!goto_menu && GetKeyState(VK_ESCAPE) >= 0) {
		MusicBgControl(CONTEXT_MENU, ptheme->onMusicBg);
		CountTimeSpenInGame(FILE_PATH_SETTINGS, "minutsInGame", &ptheme->minutsInGame);

		if (TIMER(time_start, 1200)) {
			// если это не первая страница
			if (cur_page_spread > 1) {
				if (GetKeyState(VK_LEFT) < 0 || PrintButtonMarkImg(h,
					&pblocks->page_left, PrintSymbolIconLeft, &left, ptheme)) {
					left = 1;
					if (ptheme->onSounds) {
						mciSendString(TEXT("play sourse\\sound\\menu\\flippingPage1.mp3"),
							NULL, 0, NULL); // звук перелистывания страницы
					}
					pblocks->page_left.cond = BUTTON_INIT;
					PrintButtonMarkImg(h, &pblocks->page_left, PrintSymbolIconLeft, &left, ptheme);
					prev_page_spread = cur_page_spread;
					cur_page_spread--;
					time_start = clock();
					goto flagGameRuleReCreate;
				}
			}
			// если это не последняя страница
			if (pos_text[cur_page_spread] != pos_text[cur_page_spread - 1] 
				&& pos_text[cur_page_spread] != pos_text[cur_page_spread + 1]) {
				if (GetKeyState(VK_RIGHT) < 0 || PrintButtonMarkImg(h,
					&pblocks->page_right, PrintSymbolIconRight, &right, ptheme)) {
					right = 1;
					if (ptheme->onSounds) {
						mciSendString(TEXT("play sourse\\sound\\menu\\flippingPage1.mp3"),
							NULL, 0, NULL); // звук перелистывания страницы
					}
					pblocks->page_right.cond = BUTTON_INIT;
					PrintButtonMarkImg(h, &pblocks->page_right, PrintSymbolIconRight, &right, ptheme);
					prev_page_spread = cur_page_spread;
					cur_page_spread++;
					time_start = clock();
					goto flagGameRuleReCreate;
				}
			} 
		}
		if (TIMER(time_start, SPEED_CLICK)) {
			if (GetKeyState(VK_SHIFT) < 0) {
				if (ptheme->onSounds) {
					mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
						NULL, 0, NULL); //звук
				}
				bulb = (bulb + 1) % 2;
				pblocks->invert_lighting.cond = BUTTON_INIT;
			}
			PrintButtonMarkImg(h, &pblocks->invert_lighting, PrintSymbolIconBulb, &bulb, ptheme);
			if (prev_bulb != bulb) {
				if (ptheme->onSounds) {
					if (bulb) {
						mciSendString(TEXT("play sourse\\sound\\menu\\onBulb.mp3"),
							NULL, 0, NULL); // звук включения лампы
						Sleep(900);
					} else {
						mciSendString(TEXT("play sourse\\sound\\menu\\offBulb.mp3"),
							NULL, 0, NULL); // звук выключения лампы
						Sleep(330);
					}
				} else
					Sleep(SPEED_SWITCH_BUTTON);
				SwapStr(ptheme->colorBgBase, ptheme->colorTextBase);
				SetConsoleColor(ptheme->colorBgBase, ptheme->colorTextBase);
				prev_bulb = bulb;
				time_start = clock();
				goto flagGameRuleReCreate;
			}
			if (GetKeyState(VK_TAB) < 0) {
				if (ptheme->onSounds) {
					mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"),
						NULL, 0, NULL); //звук
				}
				voice = (voice + 1) % 2;
				pblocks->voice_acting.cond = BUTTON_INIT;
			}
			PrintButtonMarkImg(h, &pblocks->voice_acting, PrintSymbolIconVoice, &voice, ptheme);
			if (prev_voice != voice) {
				switch (cur_page_spread) {
					case 1:
						if (voice)
							mciSendString(TEXT("play sourse\\sound\\voice_acting\\voiceBookPage1.mp3"),
								NULL, 0, NULL); // озвучка текста
						else
							mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage1.mp3"),
								NULL, 0, NULL); // озвучка текста
						break;
					case 2:
						if (voice)
							mciSendString(TEXT("play sourse\\sound\\voice_acting\\voiceBookPage2.mp3"),
								NULL, 0, NULL); // озвучка текста
						else
							mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage2.mp3"),
								NULL, 0, NULL); // озвучка текста
						break;
					case 3:
						if (voice)
							mciSendString(TEXT("play sourse\\sound\\voice_acting\\voiceBookPage3.mp3"),
								NULL, 0, NULL); // озвучка текста
						else
							mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage3.mp3"),
								NULL, 0, NULL); // озвучка текста
						break;
					case 4:
						if (voice)
							mciSendString(TEXT("play sourse\\sound\\voice_acting\\voiceBookPage4.mp3"),
								NULL, 0, NULL); // озвучка текста
						else
							mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage4.mp3"),
								NULL, 0, NULL); // озвучка текста
						break;
				}
				prev_voice = voice;
				time_start = clock();
			}
			goto_menu = PrintButtonStandart(h, &pblocks->goto_menu, "в главное меню", 0, ptheme);
		}
			
		SetConsoleCursorPosition(h, *pblocks->pcursore);
	}

	if (voice) {
		switch (cur_page_spread) {
		case 1:
			mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage1.mp3"),
				NULL, 0, NULL); // озвучка текста
		case 2:
			mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage2.mp3"),
				NULL, 0, NULL); // озвучка текста
		case 3:
			mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage3.mp3"),
				NULL, 0, NULL); // озвучка текста
		case 4:
			mciSendString(TEXT("close sourse\\sound\\voice_acting\\voiceBookPage4.mp3"),
				NULL, 0, NULL); // озвучка текста
		}
	}
	PrintTransitionEffect(h, pblocks->pwindow->pos, ptheme);
	if (bulb) { // выключить смену цветов, если она включена
		SwapStr(ptheme->colorBgBase, ptheme->colorTextBase);
		SetConsoleColor(ptheme->colorBgBase, ptheme->colorTextBase);
	}
}

/*вывод в окне с дескриптором h меню ввода имени пользователя 
в блоке по адресу pblocks с погодой структуры по адресу 
pweather, записывая в строку s результат ввода, с цветовой 
темой структуры по адресу ptheme*/
void InputNameFromUser(HANDLE h, TblocksSettings* pblocks, 
	Tweather* pweather, char* name, Ttheme* ptheme) {
	size_t i = 0;
	char ch = 0;
	char stmp[100];
	char tmp_name[MAX_LEN_NICKNAME + 1];
	char* ptmp_name = tmp_name;
	ptmp_name[0] = '\0';

	COORD point_output; // точка вывода ввода пользователя большими буквами
	COORD point_cursore; // точка вывода курсора консольного окна
	COORD point_output_small; // точка вывода ввода пользователя обычными буквами
	size_t lightning = 0; // был ли удар молнии
	CopyCharMatr(pweather->matr_obstac, pweather->matr_obstac_footer);
	SetBlockMatr(pweather->matr_obstac, pblocks->table_input_name, '#');

	// вывод статичных элементов меню
	SetColor(h, "bgbase", "textbase", ptheme);
	PrintFooterMainMenu(h, *pblocks->pfooter, *pblocks->pcat);
	SetConsoleCursorPosition(h, pblocks->pversion->pos);
	PrintColor(h, VERSION, ptheme);
	PrintRectangle(h, pblocks->table_input_name, "bgmsg", ptheme);

	point_output.X = pblocks->table_input_name.pos.X;
	point_output.Y = pblocks->table_input_name.pos.Y +
		(pblocks->table_input_name.lenY - 4) / 2 - 8;
	SetColor(h, "bgmsg", "textmsg", ptheme);
	PrintWordLarge(h, point_output, "введите свой никнейм:",
		pblocks->table_input_name.lenX);

	size_t first = 1; // первый ли это вввод никнейма за все время игры
	point_output.Y = pblocks->table_input_name.pos.Y + pblocks->table_input_name.lenY - 5;
	// проверить, изменят ли игрок уже существующий никнейм
	if (name[0] != '\0') {
		SetConsoleCursorPosition(h, point_output);
		sprintf(stmp, "Нажмите \\texttarget-bgmsg:[Tab] \\textmsg-bgmsg:чтобы отменить ввод.", MAX_LEN_NICKNAME);
		PrintColorCenter(h, stmp, "bgmsg", "textmsg", pblocks->table_input_name.lenX, ptheme);
		first = 0;
	}

	point_output.Y += 2;
	SetConsoleCursorPosition(h, point_output);
	sprintf(stmp, "Допустимая длина никнейма \\texttarget-bgmsg:от 3 до %u \
символов\\textmsg-bgmsg:.", MAX_LEN_NICKNAME);
	PrintColorCenter(h, stmp, "bgmsg", "textmsg", pblocks->table_input_name.lenX, ptheme);

	point_output.Y++;
	SetConsoleCursorPosition(h, point_output);
	PrintColorCenter(h, "\\green-bgmsg:Никнейм может содержать только \
\\textmsg-bgmsg:символы русского и латинского алфавита, пробелы и цифры.",
"bgmsg", "textmsg", pblocks->table_input_name.lenX, ptheme);

	point_output.Y = pblocks->table_input_name.pos.Y + (pblocks->table_input_name.lenY - 4) / 2;
	point_cursore.X = pblocks->table_input_name.pos.X + pblocks->table_input_name.lenX / 2;
	point_cursore.Y = point_output.Y + 4;

	point_output_small = point_output;
	point_output_small.Y += 13;

	clock_t time_start = clock();

	flagReInputNameFromUser:
	MusicBgControl(CONTEXT_PAUSE_GAME, ptheme->onMusicBg);
	WeatherDynamics(h, pweather, ptheme);
	SetColor(h, "bgmsg", "textmsg", ptheme);
	SetConsoleCursorPosition(h, point_cursore);

	ch = getch();
	while (ch != 13) {
		MusicBgControl(CONTEXT_PAUSE_GAME, ptheme->onMusicBg);
		if ((ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= 'а' && ch <= 'я' 
			|| ch >= 'А' && ch <= 'Я' || ch >= '0' && ch <= '9' || ch == ' ')
			&& TIMER(time_start, SPEED_CLICK)) {
			if (i < MAX_LEN_NICKNAME && (ch != ' ' || ptmp_name[i - 1] != ' ' && i > 0) ) {
				ptmp_name[i] = ch;
				ptmp_name[++i] = '\0';
				if (i < 3)
					SetColor(h, "bgmsg", "lightred", ptheme);

				PrintWordLarge(h, point_output, ptmp_name, pblocks->table_input_name.lenX);
				sprintf(stmp, "< %s >", ptmp_name);
				SetConsoleCursorPosition(h, point_output_small);
				PrintColorCenter(h, stmp, "bgmsg", "textmsg", pblocks->table_input_name.lenX, ptheme);
			}
		} else if (ch == '\b' && TIMER(time_start, SPEED_CLICK)) {
			if (i > 0) {
				ptmp_name[--i] = '\0';
				if (i < 3)
					SetColor(h, "bgmsg", "lightred", ptheme);

				PrintWordLarge(h, point_output, ptmp_name, pblocks->table_input_name.lenX);
				sprintf(stmp, "< %s >", ptmp_name);
				SetConsoleCursorPosition(h, point_output_small);
				PrintColorCenter(h, stmp, "bgmsg", "textmsg", pblocks->table_input_name.lenX, ptheme);

				if (i == 0) {
					ptmp_name[0] = '\0';
					SetColor(h, "bgmsg", "textmsg", ptheme);
					PrintWordLarge(h, point_output, "   ", pblocks->table_input_name.lenX);
					SetConsoleCursorPosition(h, point_output_small);
					PrintColorCenter(h, " ", "bgmsg", "textmsg", pblocks->table_input_name.lenX, ptheme);
				}
			} 
		} else if (!first && ch == '\t' && TIMER(time_start, SPEED_CLICK)) {
			PrintTransitionEffect(h, pblocks->pwindow->pos, ptheme);
			return;
		}

		SetColor(h, "bgbase", "textbase", ptheme);
		// если прошло достаточное кол-во мс после прошлого вывода осадков
		if (TIMER(pweather->time_start, pweather->delay)) {
			WeatherDynamics(h, pweather, ptheme);
			MoveWeather(pweather, pweather->matr_obstac);
			PrintWeather(h, pweather, pweather->matr_obstac,
				ptheme->onSoundsWeather);
		}

		SetConsoleCursorPosition(h, point_cursore);
		SetColor(h, "bgmsg", "textmsg", ptheme);
		ch = getch();
	}
	if (*ptmp_name == ' ')
		ptmp_name[--i] = '\0';
	if (i < 3) {
		if (ptheme->onSounds) {
			mciSendString(TEXT("play sourse\\sound\\menu\\inputError.mp3"),
				NULL, 0, NULL); //звук
		}
		goto flagReInputNameFromUser;
	}

	if (ptheme->onSounds) {
		mciSendString(TEXT("play sourse\\sound\\menu\\simulationComplete1.mp3"),
			NULL, 0, NULL); //звук
	}
	strcpy(name, tmp_name);
	SaveKeyValueInFile(FILE_PATH_SETTINGS, "userName", name, sizeof(tmp_name));
	WriteToTextFileSettings(FILE_PATH_SETTINGS_TXT, FILE_PATH_SETTINGS);
	PrintTransitionEffect(h, pblocks->pwindow->pos, ptheme);
}

/*вывод в окне с дескриптором h в блоке по адресу pblocks 
с погодой структуры по адресу pweather, приветствия 
пользователя с именем name, выводя дополнительную информацию 
при истинности занчения first_launch, с цветовой темой 
структуры по адресу ptheme*/
void HelloUser(HANDLE h, TblocksSettings* pblocks, Tweather* pweather, 
	char* name, size_t first_launch, Ttheme* ptheme) {
	clock_t time_start = clock();
	COORD point_output; // точка вывода приветствия пользователя
	size_t lightning = 0; // был ли удар молнии
	CopyCharMatr(pweather->matr_obstac, pweather->matr_obstac_footer);
	SetBlockMatr(pweather->matr_obstac, pblocks->table_input_name, '#');

	flagHelloReCreate:

	// вывод статичных элементов меню
	SetColor(h, "bgbase", "textbase", ptheme);
	PrintFooterMainMenu(h, *pblocks->pfooter, *pblocks->pcat);
	SetConsoleCursorPosition(h, pblocks->pversion->pos);
	PrintColor(h, VERSION, ptheme);
	PrintRectangle(h, pblocks->table_input_name, "bgmsg", ptheme);

	point_output.X = pblocks->table_input_name.pos.X;
	point_output.Y = pblocks->table_input_name.pos.Y +
		(pblocks->table_input_name.lenY - 4) / 2 - 2;
	SetColor(h, "bgmsg", "textmsg", ptheme);

	size_t time_waiting;
	if (first_launch) {
		if (ptheme->onSounds) {
			mciSendString(TEXT("play sourse\\sound\\menu\\newStage.mp3"),
				NULL, 0, NULL); // звук новой стадии развития
		}
		PrintWordLarge(h, point_output, "с первым запуском,",
			pblocks->table_input_name.lenX);
		time_waiting = 12000;
	} else {
		PrintWordLarge(h, point_output, "добро пожаловать,",
			pblocks->table_input_name.lenX);
		time_waiting = 5000;
	}
	if (ptheme->onSounds) {
		mciSendString(TEXT("play sourse\\sound\\voice_acting\\chikiBriki.mp3"),
			NULL, 0, NULL); // приветствие
	}

	point_output.Y += 3;
	char stmp[MAX_LEN_NICKNAME + 2];
	sprintf(stmp, "%s!", name);
	PrintWordLarge(h, point_output, stmp, pblocks->table_input_name.lenX);
	PrintButtonCat(h, pblocks->pcat, ptheme);

	SetColor(h, "bgbase", "textbase", ptheme);
	while (!TIMER(time_start, time_waiting)) {
		if (!first_launch)
			MusicBgControl(CONTEXT_MENU, ptheme->onMusicBg);
		else
			MusicBgControl(CONTEXT_NONE, ptheme->onMusicBg);

		SetConsoleCursorPosition(h, *pblocks->pcursore);
		// если прошло достаточное кол-во мс после прошлого вывода осадков
		if (TIMER(pweather->time_start, pweather->delay)) {
			lightning = WeatherDynamics(h, pweather, ptheme);
			MoveWeather(pweather, pweather->matr_obstac);
			PrintWeather(h, pweather, pweather->matr_obstac,
				ptheme->onSoundsWeather);
			if (lightning)
				goto flagHelloReCreate;
		}
	}
	PrintTransitionEffect(h, pblocks->pwindow->pos, ptheme);
}
