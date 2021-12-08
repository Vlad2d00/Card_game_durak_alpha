#include "header.h"

/*возвращает блочную структуру с координатами начала
(x, y), размером dx на dy и начальным состоянием cond*/
Tblock GetBlock(int x, int y, size_t dx, size_t dy, size_t cond) {
	Tblock block;
	block.pos.X = x;
	block.pos.Y = y;
	block.lenX = dx;
	block.lenY = dy;
	block.cond = cond;
	return block;
}

/*возвращает точку координатами (x, y)*/
COORD GetPoint(int x, int y) {
	COORD point;
	point.X = x;
	point.Y = y;
	return point;
}

/*инициализация в структуре по адресу pblocks
координат точек начала блоков с выводом информации
в главном меню игры, пользуясь некотрыми блоками
структуры по адресу p_allblock*/
void InitblocksMainMenu(TblocksMainMenu* pblocks, TblocksMenu* p_allblocks) {
	pblocks->header = GetBlock( // шапка меню
		WIN_X0 + WIDTH / 2 - 81 / 2,
		WIN_Y0 + 1,
		81,
		6,
		BUTTON_INIT
	);

	pblocks->buttons = GetBlock( // кнопки главного меню
		WIN_X0 + (WIDTH - WIDTH_BUTTON_MENU) / 2,
		WIN_Y0 + 8,
		WIDTH_BUTTON_MENU,
		(5 + DISTANCE_BUTTON) * 5,
		BUTTON_INIT
	);

	pblocks->story = GetBlock( // кнопка сюжетная игра
		pblocks->buttons.pos.X,
		pblocks->buttons.pos.Y,
		WIDTH_BUTTON_MENU,
		5,
		BUTTON_INIT
	);

	pblocks->custom_game = GetBlock( // кнопка начать игру
		pblocks->buttons.pos.X,
		pblocks->story.pos.Y + 5 + DISTANCE_BUTTON,
		WIDTH_BUTTON_MENU,
		5,
		BUTTON_INIT
	);

	pblocks->simulation = GetBlock( // кнопка симуляция
		pblocks->buttons.pos.X,
		pblocks->custom_game.pos.Y + 5 + DISTANCE_BUTTON,
		WIDTH_BUTTON_MENU,
		5,
		BUTTON_INIT
	);

	pblocks->settings = GetBlock( // кнопка настройки
		pblocks->buttons.pos.X,
		pblocks->simulation.pos.Y + 5 + DISTANCE_BUTTON,
		WIDTH_BUTTON_MENU,
		5,
		BUTTON_INIT
	);

	pblocks->exit = GetBlock( // кнопка выход
		pblocks->buttons.pos.X,
		pblocks->settings.pos.Y + 5 + DISTANCE_BUTTON,
		WIDTH_BUTTON_MENU,
		5,
		BUTTON_INIT
	);

	pblocks->book_rule = GetBlock( // кнопка перехода на книгу правил
		WIN_X0 + WIDTH - 35,
		WIN_Y0 + HEIGHT - 5,
		13,
		3,
		BUTTON_INIT
	);

	pblocks->achievement_table = GetBlock( // таблица достижений
		WIN_X0 + 3,
		WIN_Y0 + HEIGHT - 20,
		39,
		14,
		BUTTON_INIT
	);

	// общие элементы для каждого меню
	pblocks->pwindow = p_allblocks->pwindow;
	pblocks->pversion = p_allblocks->pversion;
	pblocks->pfooter = p_allblocks->pfooter;
	pblocks->pcat = p_allblocks->pcat;
	pblocks->pcursore = p_allblocks->pcursore;
}

/*инициализация в структуре по адресу pblocks
координат точек начала блоков с выводом информации
в главном меню настроек новой игры, пользуясь
некотрыми блоками структуры по адресу p_allblock*/
void InitblocksCustomGame(TblocksCustomGame* pblocks, TblocksMenu* p_allblocks) {
	pblocks->header = GetBlock( // шапка меню
		WIN_X0 + (WIDTH - GetSizeLargeWord("пользовательская игра")) / 2,
		WIN_Y0 + 1,
		GetSizeLargeWord("пользовательская игра") + 1,
		5,
		BUTTON_INIT
	);

	pblocks->info = GetBlock( // область настроек
		WIN_X0 + WIDTH / 8,
		WIN_Y0 + 6,
		WIDTH * 3 / 4,
		23,
		BUTTON_INIT
	);

	pblocks->table = GetBlock( // таблица настроек игроков
		pblocks->info.pos.X + 3,
		pblocks->info.pos.Y + 1,
		65,
		15,
		BUTTON_INIT
	);

	pblocks->players[0] = GetBlock( // кнопки настроек игроков
		pblocks->table.pos.X + 1,
		pblocks->table.pos.Y + 3,
		63,
		1,
		BUTTON_INIT
	);
	for (size_t i = 1; i < 6; i++) {
		pblocks->players[i] = pblocks->players[i - 1];
		pblocks->players[i].pos.Y += 2;
	}

	pblocks->see_mode = GetBlock( // включить режим всевидящего
		pblocks->table.pos.X,
		pblocks->table.pos.Y + pblocks->table.lenY + 2,
		GetSizeButtonMark("вкл. режим всевидящего (чит-режим)"),
		1,
		BUTTON_INIT
	);

	pblocks->only_ai = GetBlock( // включить режим только ИИ
		pblocks->see_mode.pos.X,
		pblocks->see_mode.pos.Y + 2,
		GetSizeButtonMark("вкл. режим \"только ИИ\" (без пользователя)"),
		1,
		BUTTON_INIT
	);

	pblocks->effect = GetBlock( // событийный эффекты
		pblocks->info.pos.X + pblocks->info.lenX - 43,
		pblocks->info.pos.Y + 1,
		40,
		15,
		BUTTON_INIT
	);

	pblocks->special_card = GetBlock( // включить специальные карты
		pblocks->table.pos.X + pblocks->table.lenX - 4,
		pblocks->table.pos.Y + pblocks->table.lenY + 2,
		GetSizeButtonMark("вкл. использование специальных карт (не работает, зараза)"),
		1,
		BUTTON_INIT
	);

	pblocks->multiplayer = GetBlock( // включить мультиплеер
		pblocks->special_card.pos.X,
		pblocks->special_card.pos.Y + 2,
		GetSizeButtonMark("вкл. игру по локальной сети (которая не работает)"),
		1,
		BUTTON_INIT
	);

	pblocks->chat = GetBlock( // чат 
		WIN_X0 + 2,
		pblocks->info.pos.Y + pblocks->info.lenY + 1,
		50,
		18,
		BUTTON_INIT
	);

	pblocks->button_chat = GetBlock( // кнопка чата
		pblocks->chat.pos.X,
		pblocks->chat.pos.Y + pblocks->chat.lenY - 1,
		pblocks->chat.lenX,
		1,
		BUTTON_INIT
	);

	pblocks->input_chat = GetBlock( // всплывающее поле ввода текста чата
		pblocks->button_chat.pos.X,
		pblocks->button_chat.pos.Y,
		WIDTH / 2,
		1,
		BUTTON_INIT
	);

	pblocks->start = GetBlock( // кнопка запуска игровой сессии
		WIN_X0 + (WIDTH - GetSizeButtonStandart("начать игру")) / 2,
		pblocks->info.pos.Y + pblocks->info.lenY + 1,
		GetSizeButtonStandart("начать игру"),
		5,
		BUTTON_INIT
	);

	pblocks->goto_menu = GetBlock( // кнопка выхода в главное меню
		WIN_X0 + (WIDTH - GetSizeButtonStandart("в главное меню")) / 2,
		pblocks->start.pos.Y + pblocks->start.lenY + DISTANCE_BUTTON,
		GetSizeButtonStandart("в главное меню"),
		5,
		BUTTON_INIT
	);

	// общие элементы для каждого меню
	pblocks->pwindow = p_allblocks->pwindow;
	pblocks->pversion = p_allblocks->pversion;
	pblocks->pfooter = p_allblocks->pfooter;
	pblocks->pcat = p_allblocks->pcat;
	pblocks->pcursore = p_allblocks->pcursore;
}

/*инициализация в структуре по адресу pblocks
координат точек начала блоков с выводом информации
в главном меню симуляций игр, пользуясь некотрыми
блоками структуры по адресу p_allblock*/
void InitblocksSimulation(TblocksSimulation* pblocks, TblocksMenu* p_allblocks) {
	pblocks->header = GetBlock( // шапка меню
		WIN_X0 + (WIDTH - GetSizeLargeWord("меню симуляции игр")) / 2,
		WIN_Y0 + 1,
		GetSizeLargeWord("меню симуляции игр") + 1,
		3,
		BUTTON_INIT
	);

	pblocks->info = GetBlock( // область настроек и процесса симуляции
		WIN_X0 + (WIDTH - WIDTH_SIMULATION_INFO) / 2,
		WIN_Y0 + 6,
		WIDTH_SIMULATION_INFO,
		23,
		BUTTON_INIT
	);

	pblocks->table = GetBlock( // таблица настроек игроков
		pblocks->info.pos.X + (pblocks->info.lenX - 65) / 2 - 1,
		pblocks->info.pos.Y + 1,
		65,
		15,
		BUTTON_INIT
	);

	pblocks->players[0] = GetBlock( // кнопки настроек игроков
		pblocks->table.pos.X + 1,
		pblocks->table.pos.Y + 3,
		63,
		1,
		BUTTON_INIT
	);
	for (size_t i = 1; i < 6; i++) {
		pblocks->players[i] = pblocks->players[i - 1];
		pblocks->players[i].pos.Y += 2;
	}

	pblocks->count_sim = GetBlock( // кнопка настроки кол-ва симуляций игр
		WIN_X0 + (WIDTH - GetSizeButtonInputNumber("Количество симуляций игр") - 10) / 2,
		pblocks->table.pos.Y + pblocks->table.lenY + 2,
		GetSizeButtonInputNumber("Количество симуляций игр") + 10,
		1,
		BUTTON_INIT
	);

	pblocks->start = GetBlock( // кнопка запуска симуляции
		WIN_X0 + (WIDTH - GetSizeButtonStandart("запуск")) / 2,
		pblocks->info.pos.Y + pblocks->info.lenY + 1,
		GetSizeButtonStandart("запуск"),
		5,
		BUTTON_INIT
	);

	pblocks->goto_menu = GetBlock( // кнопка выхода в главное меню
		WIN_X0 + (WIDTH - GetSizeButtonStandart("в главное меню")) / 2,
		pblocks->start.pos.Y + pblocks->start.lenY + DISTANCE_BUTTON,
		GetSizeButtonStandart("в главное меню"),
		5,
		BUTTON_INIT
	);

	pblocks->stop = GetBlock( // кнопка остановки симуляции
		WIN_X0 + (WIDTH - GetSizeButtonStandart("остановить")) / 2,
		pblocks->start.pos.Y,
		GetSizeButtonStandart("остановить"),
		pblocks->start.lenY,
		BUTTON_INIT
	);

	pblocks->anew = GetBlock( // кнопка вызова повторной симуляции
		WIN_X0 + (WIDTH - GetSizeButtonStandart("новая симуляция")) / 2,
		pblocks->start.pos.Y,
		GetSizeButtonStandart("новая симуляция"),
		pblocks->start.lenY,
		BUTTON_INIT
	);

	// общие элементы для каждого меню
	pblocks->pwindow = p_allblocks->pwindow;
	pblocks->pversion = p_allblocks->pversion;
	pblocks->pfooter = p_allblocks->pfooter;
	pblocks->pcat = p_allblocks->pcat;
	pblocks->pcursore = p_allblocks->pcursore;
}

/*инициализация в структуре по адресу pblocks
координат точек начала блоков с выводом информации
в главном меню настроек, пользуясь некотрыми блоками
структуры по адресу p_allblock*/
void InitblocksSettings(TblocksSettings* pblocks, TblocksMenu* p_allblocks) {
	pblocks->header = GetBlock( // шапка меню
		WIN_X0 + (WIDTH - GetSizeButtonStandart("меню настроек")) / 2,
		WIN_Y0 + 1,
		GetSizeLargeWord("меню настроек") + 1,
		3,
		BUTTON_INIT
	);

	pblocks->table = GetBlock( // фоновая вывеска
		WIN_X0 + 3,
		WIN_Y0 + 5,
		WIDTH - 6,
		17,
		BUTTON_INIT
	);

	pblocks->table_control_keys = GetBlock( // таблица управляющих клавиш
		WIN_X0 + 2,
		WIN_Y0 + HEIGHT - 16,
		54,
		12,
		BUTTON_INIT
	);

	pblocks->theme = GetBlock( // заголовок темы оформления 
		pblocks->table.pos.X + pblocks->table.lenX - 34,
		pblocks->table.pos.Y,
		GetSizeLargeWord("тема"),
		3,
		BUTTON_INIT
	);
	
	pblocks->theme_day = GetBlock( // дневная тема оформления
		pblocks->theme.pos.X - 12,
		pblocks->theme.pos.Y + 6,
		GetSizeButtonMark("ДЕНЬ (светлый фон)"),
		1,
		BUTTON_INIT
	);

	pblocks->theme_night = GetBlock( // ночная тема оформления
		pblocks->theme_day.pos.X,
		pblocks->theme_day.pos.Y + 2,
		GetSizeButtonMark("НОЧЬ (черный фон)"),
		1,
		BUTTON_INIT
	);

	pblocks->theme_east = GetBlock( // востояная тема оформления 
		pblocks->theme_night.pos.X,
		pblocks->theme_night.pos.Y + 2,
		GetSizeButtonMark("ВОСТОК (красный, желтый, черный)"),
		1,
		BUTTON_INIT
	);

	pblocks->theme_black_blue = GetBlock( // черно-синяя тема оформления 
		pblocks->theme_east.pos.X,
		pblocks->theme_east.pos.Y + 2,
		GetSizeButtonMark("ЧЕРНО-СИНЯЯ (синий и черный)"),
		1,
		BUTTON_INIT
	);

	pblocks->theme_new_year = GetBlock( // новогодняя тема оформления 
		pblocks->theme_black_blue.pos.X,
		pblocks->theme_black_blue.pos.Y + 2,
		GetSizeButtonMark("НОВЫЙ ГОД (белый и красный)"),
		1,
		BUTTON_INIT
	);


	pblocks->table_weather = GetBlock( // фоновая вывеска для погодных настроек
		WIN_X0 + WIDTH * 3 / 4 - 7,
		pblocks->table.pos.Y + pblocks->table.lenY + 2,
		47,
		13,
		BUTTON_INIT
	);

	pblocks->weather = GetBlock( // заголовок погодных настроек
		pblocks->table_weather.pos.X + (pblocks->table_weather.lenX 
			- GetSizeButtonStandart("погода")) / 2 + 1,
		pblocks->table_weather.pos.Y,
		GetSizeButtonStandart("погода"),
		3,
		BUTTON_INIT
	);

	pblocks->weather_snow = GetBlock( //  осадки: снег
		pblocks->weather.pos.X + (pblocks->weather.lenX - 14) / 2,
		pblocks->weather.pos.Y + 5,
		13,
		6,
		BUTTON_INIT
	);

	pblocks->weather_clear = GetBlock( // осадки: ясно
		pblocks->weather_snow.pos.X - 14,
		pblocks->weather_snow.pos.Y,
		13,
		6,
		BUTTON_INIT
	);

	pblocks->weather_rain = GetBlock( // осадки: дождь
		pblocks->weather_snow.pos.X + 14,
		pblocks->weather_snow.pos.Y,
		13,
		6,
		BUTTON_INIT
	);


	pblocks->volume = GetBlock( // заголовок настройки звуков и музыки
		pblocks->table.pos.X + (pblocks->table.lenX - GetSizeLargeWord("звуки и музыка")) / 2 + 4,
		pblocks->table.pos.Y,
		GetSizeLargeWord("звуки и музыка"),
		3,
		BUTTON_INIT
	);

	pblocks->music_bg = GetBlock( // фоновая музыка
		pblocks->volume.pos.X + 10,
		pblocks->volume.pos.Y + 4,
		GetSizeButtonMark("Вкл. фоновую музыку"),
		1,
		BUTTON_INIT
	);

	pblocks->sounds_weather = GetBlock( // звуки погоды
		pblocks->music_bg.pos.X,
		pblocks->music_bg.pos.Y + 2,
		GetSizeButtonMark("Вкл. звки погоды"),
		1,
		BUTTON_INIT
	);

	pblocks->sounds = GetBlock( // прочие звуки
		pblocks->sounds_weather.pos.X,
		pblocks->sounds_weather.pos.Y + 2,
		GetSizeButtonMark("Вкл. прочие звуки"),
		1,
		BUTTON_INIT
	);


	pblocks->game = GetBlock( // заголовок игровых настроек
		pblocks->table.pos.X + 20,
		pblocks->table.pos.Y,
		GetSizeLargeWord("игра"),
		3,
		BUTTON_INIT
	);

	pblocks->chat = GetBlock( // чат
		pblocks->game.pos.X - 16,
		pblocks->game.pos.Y + 4,
		GetSizeButtonMark("Выводить чат на игровом столе"),
		1,
		BUTTON_INIT
	);

	pblocks->messages_chat = GetBlock( // сообщения о действиях в чате
		pblocks->chat.pos.X,
		pblocks->chat.pos.Y + 2,
		GetSizeButtonMark("Вкл. сообщения о действиях игроков в чате"),
		1,
		BUTTON_INIT
	);

	pblocks->effects = GetBlock( // игровые спецэффекты
		pblocks->messages_chat.pos.X,
		pblocks->messages_chat.pos.Y + 2,
		GetSizeButtonMark("Вкл. игровые спецэффекты"),
		1,
		BUTTON_INIT
	);

	pblocks->improved_alg = GetBlock( // оптимизированные алгоритмы вывода элементов игры
		pblocks->effects.pos.X,
		pblocks->effects.pos.Y + 2,
		GetSizeButtonMark("Оптимизировать алгоритмы вывода элементов игрового стола"),
		1,
		BUTTON_INIT
	);

	pblocks->full_screen_mode = GetBlock( // полноэкранный режим
		pblocks->improved_alg.pos.X,
		pblocks->improved_alg.pos.Y + 3,
		GetSizeButtonMark("Вкл. полноэкранный режим (не работает: не нажимай, пожалуйста)"),
		1,
		BUTTON_INIT
	);


	pblocks->nickname = GetBlock( // иземнить никнейм
		WIN_X0 + (WIDTH - GetSizeButtonStandart("изменить никнейм")) / 2,
		pblocks->table.pos.Y + pblocks->table.lenY + DISTANCE_BUTTON - 1,
		GetSizeButtonStandart("изменить никнейм"),
		5,
		BUTTON_INIT
	);

	pblocks->reset_progress = GetBlock( // сброс пргресса
		WIN_X0 + (WIDTH - GetSizeButtonStandart("сброс пргресса")) / 2 - 2,
		pblocks->nickname.pos.Y + pblocks->nickname.lenY + DISTANCE_BUTTON,
		GetSizeButtonStandart("сброс прогресса"),
		5,
		BUTTON_INIT
	);

	pblocks->goto_menu = GetBlock( // кнопка выхода
		WIN_X0 + (WIDTH - GetSizeButtonStandart("в главное меню")) / 2,
		pblocks->reset_progress.pos.Y + pblocks->reset_progress.lenY + DISTANCE_BUTTON,
		GetSizeButtonStandart("в главное меню"),
		5,
		BUTTON_INIT
	);


	pblocks->table_input_name = GetBlock( // вывеска ввода имени
		WIDTH / 6,
		HEIGHT / 6 - 2,
		WIDTH * 2 / 3,
		HEIGHT * 2 / 3,
		BUTTON_INIT
	);

	// общие элементы для каждого меню
	pblocks->pwindow = p_allblocks->pwindow;
	pblocks->pversion = p_allblocks->pversion;
	pblocks->pfooter = p_allblocks->pfooter;
	pblocks->pcat = p_allblocks->pcat;
	pblocks->pcursore = p_allblocks->pcursore;
}

/*инициализация в структуре по адресу pblocks
координат точек начала блоков с выводом информации
в главном меню правил игры, пользуясь некотрыми
блоками структуры по адресу p_allblock*/
void InitblocksGameRule(TblocksGameRule* pblocks, TblocksMenu* p_allblocks) {
	pblocks->header = GetBlock( // шапка меню
		WIN_X0 + (WIDTH - GetSizeLargeWord("правила игры")) / 2,
		WIN_Y0 + 5,
		GetSizeLargeWord("правила игры"),
		5,
		BUTTON_INIT
	);

	pblocks->book = GetBlock( // книга
		WIN_X0 + (WIDTH - 141) / 2,
		WIN_Y0 + 3,
		141,
		40,
		BUTTON_INIT
	);

	pblocks->voice_acting = GetBlock( // озвучка текста
		pblocks->book.pos.X - 10,
		pblocks->book.pos.Y,
		8,
		5,
		BUTTON_INIT
	);

	pblocks->invert_lighting = GetBlock( // инвертировать освещение
		pblocks->book.pos.X + pblocks->book.lenX + 2,
		pblocks->book.pos.Y,
		9,
		6,
		BUTTON_INIT
	);

	pblocks->page_left = GetBlock( // кнопка перелистнуть страницу влево
		pblocks->book.pos.X - 10,
		pblocks->book.pos.Y + pblocks->book.lenY - 4,
		8,
		3,
		BUTTON_INIT
	);

	pblocks->page_right = GetBlock( // кнопка перелистнуть страницу вправо
		pblocks->book.pos.X + pblocks->book.lenX + 2,
		pblocks->page_left.pos.Y,
		8,
		3,
		BUTTON_INIT
	);

	pblocks->goto_menu = GetBlock( // кнопка выхода в главное меню
		WIN_X0 + (WIDTH - GetSizeButtonStandart("в главное меню")) / 2,
		WIN_Y0 + HEIGHT - 7,
		GetSizeButtonStandart("в главное меню"),
		5,
		BUTTON_INIT
	);

	// общие элементы для каждого меню
	pblocks->pwindow = p_allblocks->pwindow;
	pblocks->pversion = p_allblocks->pversion;
	pblocks->pfooter = p_allblocks->pfooter;
	pblocks->pcat = p_allblocks->pcat;
	pblocks->pcursore = p_allblocks->pcursore;
}

/*инициализация в структуре по адресу pblocks
координат точек начала блоков с выводом информации
в всех видов меню игры, начиная с точки
отсчета (baseX, baseY)*/
void InitblocksMenu(TblocksMenu* pblocks, size_t baseX, size_t baseY) {
	pblocks->window = GetBlock( // рабочее окно
		baseX,
		baseY,
		WIDTH,
		HEIGHT,
		BUTTON_INIT
	);

	pblocks->version = GetBlock( // надпись версия игры
		baseX + WIDTH - strlen(VERSION) - 9,
		baseY + HEIGHT - 2,
		strlen(VERSION),
		1,
		BUTTON_INIT
	);

	pblocks->footer = GetBlock( // подвал меню
		baseX,
		baseY + HEIGHT - 4,
		WIDTH,
		4,
		BUTTON_INIT
	);

	pblocks->cat = GetBlock( // изображение кота
		baseX + WIDTH - 52,
		baseY + HEIGHT - 9,
		16,
		8,
		BUTTON_INIT
	);

	pblocks->cursore = GetPoint( // позиция курсора
		pblocks->version.pos.X + pblocks->version.lenX,
		pblocks->version.pos.Y
	);

	pblocks->pwindow = &pblocks->window;
	pblocks->pversion = &pblocks->version;
	pblocks->pfooter = &pblocks->footer;
	pblocks->pcat = &pblocks->cat;
	pblocks->pcursore = &pblocks->cursore;

	InitblocksMainMenu(&pblocks->mainMenu, pblocks, baseX, baseY);
	InitblocksCustomGame(&pblocks->customGame, pblocks, baseX, baseY);
	InitblocksSimulation(&pblocks->simulation, pblocks, baseX, baseY);
	InitblocksSettings(&pblocks->settings, pblocks, baseX, baseY);
	InitblocksGameRule(&pblocks->gameRule, pblocks, baseX, baseY);
}

/*инициализация в структуре по адресу pblocks
координат точек начала блоков с выводом информации
на игровом поле, начиная с точки отсчета (baseX, baseY)*/
void InitBlockGame(TblocksGame* pblocks, size_t baseX, size_t baseY) {
	pblocks->window = GetBlock( // рабочее окно
		baseX,
		baseY,
		WIDTH,
		HEIGHT,
		BUTTON_INIT
	);

	pblocks->target_card = 0; // выбранная карта игрока

	pblocks->matr_cards_ai = GetBlock( // матрица карт определенного ИИ
		baseX,
		baseY,
		60,
		8,
		BUTTON_OFF
	);


	pblocks->header = GetBlock( // шапка игрового меню
		baseX,
		baseY,
		WIDTH,
		3,
		BUTTON_INIT
	);

	strcpy(pblocks->s_effect, "Событийный эффект: отсутствует");
	pblocks->effect = GetBlock( // событийный эффект
		WIDTH * 0.67,
		pblocks->header.pos.Y + 1,
		strlen(pblocks->s_effect),
		2,
		BUTTON_INIT
	);

	pblocks->esc = GetBlock( // вызов меню пауза
		pblocks->header.pos.X + 2,
		pblocks->header.pos.Y + 1,
		7,
		1,
		BUTTON_INIT
	);

	pblocks->menu_block = GetBlock( // меню пауза
		baseX + WIDTH / 8,
		baseY + HEIGHT / 8,
		WIDTH * 3 / 4,
		HEIGHT * 3 / 4,
		BUTTON_INIT
	);

	pblocks->menu_header = GetBlock( // шапка меню паузы
		pblocks->menu_block.pos.X + (pblocks->menu_block.lenX
			- GetSizeButtonStandart("игра приостановлена")) / 2,
		pblocks->menu_block.pos.Y + 2,
		GetSizeButtonStandart("игра приостановлена"),
		5,
		BUTTON_INIT
	);

	pblocks->menu_continue = GetBlock( // продолжить игру
		pblocks->menu_block.pos.X + (pblocks->menu_block.lenX
			- GetSizeButtonStandart("продолжить")) / 2,
		pblocks->menu_block.pos.Y + 10,
		GetSizeButtonStandart("продолжить"),
		5,
		BUTTON_INIT
	);

	pblocks->menu_exit = GetBlock( // выход в главное меню
		pblocks->menu_block.pos.X + (pblocks->menu_block.lenX
			- GetSizeButtonStandart("в главное меню")) / 2,
		pblocks->menu_continue.pos.Y + 5 + DISTANCE_BUTTON,
		GetSizeButtonStandart("в главное меню"),
		5,
		BUTTON_INIT
	);

	pblocks->cards_p2_2 = GetBlock( // карты 2-го игрока для игры вдвоем
		baseX + (WIDTH - WIDTH_CRADS_BASE) / 2,
		baseY + 5,
		WIDTH_CRADS_BASE,
		8,
		BUTTON_INIT
	);

	pblocks->cards_battle = GetBlock( // поле боя
		baseX + (WIDTH - WIDTH_CRADS_MEDIUM) / 2,
		pblocks->cards_p2_2.pos.Y + 10,
		WIDTH_CRADS_MEDIUM,
		18,
		BUTTON_INIT
	);

	pblocks->cards_user = GetBlock( // карты пользователя
		pblocks->cards_p2_2.pos.X,
		pblocks->cards_battle.pos.Y + 20,
		WIDTH_CRADS_BASE,
		8,
		BUTTON_INIT
	);

	pblocks->chat = GetBlock( // чат
		baseX + 2,
		pblocks->cards_user.pos.Y + 10 - 22,
		(WIDTH - WIDTH_CRADS_BASE) / 2 - 3,
		22,
		BUTTON_INIT
	);

	pblocks->button_chat = GetBlock( // кнопка чата
		pblocks->chat.pos.X,
		pblocks->chat.pos.Y + pblocks->chat.lenY - 1,
		pblocks->chat.lenX,
		1,
		BUTTON_INIT
	);

	pblocks->input_chat = GetBlock( // всплывающее поле ввода текста чата
		pblocks->button_chat.pos.X,
		pblocks->button_chat.pos.Y,
		WIDTH / 2,
		1,
		BUTTON_INIT
	);

	pblocks->cards_deck = GetBlock( // общая колода карт
		pblocks->cards_user.pos.X + WIDTH_CRADS_BASE + 3,
		pblocks->chat.pos.Y,
		32,
		16,
		BUTTON_INIT
	);

	pblocks->time = GetPoint( // время
		pblocks->cards_deck.pos.X + pblocks->cards_deck.lenX - 17,
		pblocks->cards_deck.pos.Y + pblocks->cards_deck.lenY - 1
	);

	pblocks->card_special = GetBlock( // специальная карта
		baseX + WIDTH - 16,
		pblocks->cards_user.pos.Y,
		11,
		8,
		BUTTON_INIT
	);

	pblocks->button_pass = GetBlock( // кнопка пасс
		pblocks->cards_deck.pos.X,
		pblocks->cards_deck.pos.Y + pblocks->cards_deck.lenY,
		GetSizeLargeWord("пасс") + 5 + 6,
		5,
		BUTTON_INIT
	);

	// карты 2-го игрока для игры втроем
	pblocks->cards_p2_3 = GetBlock(
		baseX + WIDTH / 4 - (WIDTH_CRADS_BASE / 2),
		baseY + pblocks->cards_p2_2.pos.Y,
		WIDTH_CRADS_BASE,
		8,
		BUTTON_INIT
	);

	// карты 3-го игрока для игры втроем
	pblocks->cards_p3_3 = GetBlock(
		baseX + (WIDTH * 3) / 4 - (WIDTH_CRADS_BASE / 2),
		baseY + pblocks->cards_p2_2.pos.Y,
		WIDTH_CRADS_BASE,
		8,
		BUTTON_INIT
	);

	// карты 2-го игрока для игры вчетвером
	pblocks->cards_p2_4 = GetBlock(
		baseX + WIDTH / 6 - (WIDTH_CRADS_SMALL / 2) + 1,
		baseY + pblocks->cards_p2_2.pos.Y,
		WIDTH_CRADS_SMALL,
		8,
		BUTTON_INIT
	);

	// карты 3-го игрока для игры вчетвером
	pblocks->cards_p3_4 = GetBlock(
		baseX + (WIDTH) / 2 - (WIDTH_CRADS_SMALL / 2),
		baseY + pblocks->cards_p2_2.pos.Y,
		WIDTH_CRADS_SMALL,
		8,
		BUTTON_INIT
	);

	// карты 4-го игрока для игры вчетвером
	pblocks->cards_p4_4 = GetBlock(
		baseX + (WIDTH * 5) / 6 - (WIDTH_CRADS_SMALL / 2) - 1,
		baseY + pblocks->cards_p2_2.pos.Y,
		WIDTH_CRADS_SMALL,
		8,
		BUTTON_INIT
	);

	// карты 5-го игрока для игры впятером
	pblocks->cards_p5_5 = GetBlock(
		baseX + pblocks->cards_p2_4.pos.X,
		baseY + pblocks->cards_p2_2.pos.Y + 10,
		WIDTH_CRADS_SMALL,
		8,
		BUTTON_INIT
	);

	// карты 6-го игрока для игры впятером
	pblocks->cards_p6_6 = GetBlock(
		baseX + pblocks->cards_p4_4.pos.X,
		baseY + pblocks->cards_p5_5.pos.Y,
		WIDTH_CRADS_SMALL,
		8,
		BUTTON_INIT
	);

	// // позиция курсора
	pblocks->cursore = GetPoint(
		pblocks->cards_deck.pos.X + pblocks->cards_deck.lenX - 12,
		pblocks->cards_deck.pos.Y + pblocks->cards_deck.lenY - 1
	);
}
