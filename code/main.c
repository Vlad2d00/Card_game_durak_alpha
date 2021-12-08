#include "header.h"
#include "init.h"
#include "color_console.h"
#include "print_elements.h"
#include "weather.h"
#include "buttons.h"
#include "game_process.h"
#include "menu_interface.h"
#include "game_interface.h"
#include "artificial_Intellig.h"
#include <mmsystem.h>

// подключение иконки приложения
#define IDI_ICON1
#define _WIN32_WINNT 0x0A00 // устанавливаем версию ОС

#pragma comment (lib, "Winmm.lib")

const size_t NoError = 0; // ошибок нет
const size_t CardNotFoundInArr = 1; // в колоде не существует данной карты
const size_t ImpossibleToPlaceCard = 2; // карта не может быть размещена на поле боя
const size_t CardCannotBeBeaten = 3; // данная карта не может побить другую заданную карту
const size_t WrongFirstMove = 4; // пас не может быть в начале хода
const size_t DiscoveredDuplicated = 5; // обнаружена пара повторяющихся карт
const size_t DiscoveredSuspiciousCard = 6; // обнаружена подозрительная карта

size_t Error = 0; // переменная ошибок

const size_t NoMessage = 0; // нет сообщений
const size_t PlayerPulledCards = 1; // игрок решил затянуть карты
const size_t PlayerThrewCard = 2; // игрок подкинул карту в придачу
const size_t PlayerAnswered = 3; // игрок ответил картой
const size_t PlayerLaidOutCard = 4; // игрок выложил карту на поле боя
const size_t PlayerAnsweresPass = 5; // игрок ответил пасс
const size_t PlayerOutOfCards = 6; // у игрока закончились карты
const size_t BattleIsCrowded = 7; // поле боя переполнено
const size_t BattleCanNotBeThrown = 8; // на поле боя больше нельзя подбросить карт
const size_t PlayerOutOfTheGame = 9; // игрок вышел из игры победителем

size_t SayAction = 0; // сообщение о последнем действии игрока
size_t SayCondition = 0; // сообщение о состоянии игрока или поле боя

size_t SimCountGamesDone = 0;

int main() {
	SetConsoleCP(1251);  /*кодировка для вывода символов русского алфавита на экран*/
	SetConsoleOutputCP(1251);  /*кодировка для ввода символов русского алфавита с клавиатуры в консоль*/
	srand(time(NULL)); // получить ключ для рандомайзера из текущего момента времени
	system("title Карточная игра в дурака 0.3.0");
	
	char s[SIZE];
	sprintf(s, "mode con cols=%u lines=%u", WIDTH, HEIGHT);
	system(s); // установка размера окна приложения
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // дескриптор консоли вывода

	Ttheme theme; // структура с информацией о текщуей цветовой теме
	// загрузка данных из файла сохранений
	// если файла нет, то он создается и в нем инициализируются нужные ключи
	LoadDataInGame(FILE_PATH_SETTINGS, &theme);
	WriteToTextFileSettings(FILE_PATH_SETTINGS_TXT, FILE_PATH_SETTINGS);
	SetTheme(&theme, theme.designTheme);

	// структура с информацией о картах на игровом поле
 	Tcards cards;
	// структура с информацией об игровом поле
	TgameTable gameTable;
	// массив указателей на структуру с настройками ИИ
	TsettingsAI* psettingsAI[6];
	// структура с координатами точек начала блоков информации игрового стола
	TblocksGame blocksGame;
	InitBlockGame(&blocksGame, 0, 0);
	InitChat(&gameTable.chat, HEIGHT_CHAT);
	// структура с координатами точек начала блоков всех меню игры
	TblocksMenu blocksMenu;
	InitblocksMenu(&blocksMenu, 0, 0);
	// структура с информацией о матрице осадков
	Tweather weather;
	InitWeather(&weather, 0, 0, &theme);
	InitMatrObstacBase(weather.matr_obstac_footer, &blocksMenu, '#');

	size_t difficulty[6]; // уровень игры игроков, за которых играет ИИ
	size_t answer_menu; // ответ, полученный от игрока в главном меню

	if (theme.userName[0] == '\0') // если у игрока нет никнейма
		InputNameFromUser(h, &blocksMenu.settings, &weather, theme.userName, &theme);

	HelloUser(h, &blocksMenu.settings, &weather, theme.userName, !theme.launch, &theme);
	theme.launch = ChangeValueData(FILE_PATH_SETTINGS, "launch", 1);

	// ------------------------- МЕНЮ -----------------------------

	// вызов главного меню
	flagMainMenu:
	if (weather.type_bg_sounds)
		weather.type_bg_sounds = 0;
	answer_menu = PrintWindowMainMenu(h, &blocksMenu.mainMenu, &weather, &theme);
	switch (answer_menu) {
		case MAIN_MENU_STORY:
			goto flagMainMenu; 
		case MAIN_MENU_CUSTOM_GAME:
			goto flagCustomGame;
		case MAIN_MENU_SIMULATION:
			goto flagSimulation; 
		case MAIN_MENU_SETTINGS:
			goto flagSettings;
		case MAIN_MENU_GAME_RULE:
			goto flagGameRule;
		case MAIN_MENU_EXIT:
			free(gameTable.chat);
			SetColor(h, "bgbase", "darkgray", &theme);
			exit(0);
	}
	
	// вызов меню симуляции игр
	flagSimulation:
	if (PrintWindowSimulation(h, &blocksMenu.simulation, &weather,
		&gameTable, difficulty, &theme)) {
		SimCountGamesDone++;
		goto flagGameStart;
	} else {
		SimCountGamesDone = 0;
		goto flagMainMenu;
	}

	// вызов меню настроек приложения
	flagSettings:
	answer_menu = PrintWindowSettings(h, &blocksMenu.settings, &weather, &theme);
	switch (answer_menu) {
		case SETTINGS_RE_NICKNAME:
			InputNameFromUser(h, &blocksMenu.settings, &weather, theme.userName, &theme);
			SaveKeyValueInFile(FILE_PATH_SETTINGS, "userName", &theme.userName, sizeof(theme.userName));
			WriteToTextFileSettings(FILE_PATH_SETTINGS_TXT, FILE_PATH_SETTINGS);
			goto flagSettings;

		case SETTINGS_RESET_PROGRESS:
			size_t prev_launch = theme.launch;
			remove(FILE_PATH_SETTINGS); // удаление файла с настройками пользователя
			LoadDataInGame(FILE_PATH_SETTINGS, &theme);
			SaveKeyValueInFile(FILE_PATH_SETTINGS, "launch", prev_launch, sizeof(size_t));
			WriteToTextFileSettings(FILE_PATH_SETTINGS_TXT, FILE_PATH_SETTINGS);
			InputNameFromUser(h, &blocksMenu.settings, &weather, theme.userName, &theme);
			SaveKeyValueInFile(FILE_PATH_SETTINGS, "userName", &theme.userName, sizeof(theme.userName));
			WriteToTextFileSettings(FILE_PATH_SETTINGS_TXT, FILE_PATH_SETTINGS);
			goto flagSettings;

		case SETTINGS_GOTO_MENU:
			goto flagMainMenu; 
	}

	// вызов окна правил игры
	flagGameRule:
	PrintWindowGameRule(h, &blocksMenu.gameRule, &theme);
	goto flagMainMenu;

	// вызов окна настройки игрового сеанса
	flagCustomGame:
	if (!PrintWindowCustomGame(h, &blocksMenu.customGame, &weather,
		&gameTable, difficulty, &theme))
		goto flagMainMenu;

	// -------------------- ЗАПУСК ИГРОВОГО САЕНСА -------------------------

	flagGameStart:
	InitStructCards(&cards, &gameTable, gameTable.count_players);

	if (gameTable.mode == GAME_AI || gameTable.mode == GAME_SIMULATION)
		gameTable.user = 6; // несуществующий игрок
	
	if (theme.onSoundsWeather && gameTable.mode != GAME_SIMULATION) {
		// отключить старые фоновые звуки
		if (weather.type_bg_sounds == '*')
			mciSendString(TEXT("close sourse\\music\\snow1.mp3"),
				NULL, 0, NULL);
		else if (weather.type_bg_sounds == '|') {
			if (weather.shower)
				mciSendString(TEXT("close sourse\\music\\rain2Level.mp3"),
					NULL, 0, NULL);
			else
				mciSendString(TEXT("close sourse\\music\\rain1Level.mp3"),
					NULL, 0, NULL);
		}
		else if (weather.type_bg_sounds == '-')
			mciSendString(TEXT("close sourse\\music\\birds.mp3"),
				NULL, 0, NULL);
	}

	// состояние игроков
	for (size_t i = 0; i < gameTable.count_players; i++) {
		if (i == gameTable.defend_player)
			gameTable.player_state[i] = PROTECTION;
		else
			gameTable.player_state[i] = ATTACK;
	}

	// настройка игроков, за которых играет ИИ
	for (size_t i = 0; i < gameTable.count_players; i++) {
		if (i != gameTable.user || gameTable.mode == GAME_AI ||
			gameTable.mode == GAME_SIMULATION) {
			psettingsAI[i] = (TsettingsAI*)malloc(sizeof(TsettingsAI));
			InitGameSettingsAI(psettingsAI[i], difficulty[i]);
		}
	}

	int i; // индекс выбранной карты игроком
	size_t add_player[6]; // кол-во добавленных карт игрокам в конце хода
	size_t add_retr = 0; // кол-во карт, ушедших в отбой
	int player_pulled = -1; // игрок, который последний затянул карты с поле боя
	size_t player_out_of_cards = 0; // игрок, у которого закончились карты
	size_t player_mark = 0; // предыдущий игрок, давший ответ
	// оставшееся кол-во перемещений между игроками, которые подкидывают карты
	size_t transitions = gameTable.cur_count_players - 2;
	// игрок, на котором остановилась очередь атаковать
	size_t stop_player_attack = gameTable.move;
	size_t game_exit = 0; // закончить игру преждевременно

	size_t ideck_one, ideck_two; // индексы колод с обнаруженными ошибками

	// ----------------------------- НАЧАЛО ИГРЫ ----------------------------------

	char stmp[SIZE];
	// аолагание начала игровой сессии
	if (gameTable.mode != GAME_SIMULATION) {
		ChatClear(gameTable.chat, HEIGHT_CHAT);
		IntroductionInGame(h, &gameTable, cards.player, &blocksGame, &theme);
	}
	
	/*пока у хотя бы двух игроков есть карты на руках или в общей 
	колоде есть карты или пока всего-лишь у одного игрока нет 
	одной единственной карты на руках и на поле боя есть хотя бы одна карта*/
	while ( GetCountNonZerolArr(gameTable.c_player, gameTable.count_players) >= 2 
		|| gameTable.c_deck || (CountElArrValue(gameTable.c_player, 
			gameTable.count_players, 1, 1) && gameTable.c_deck)) {

		// ------------------ БЛОК ВЫВОДА СООБЩЕНИЙ ---------------------------

		// если выбран режим игры, позволяющий выводить интерфейс
		if (gameTable.mode != GAME_SIMULATION) {
			if (SayAction != NoMessage && theme.messagesChat) {

				char sname[MAX_LEN_NICKNAME + 1];
				if (gameTable.name_player[player_mark][0] == '\0')
					sprintf(sname, "%u-й игрок", player_mark + 1);
				else
					strcpy(sname, gameTable.name_player[player_mark]);

				if (SayAction == PlayerPulledCards) { // игрок решил затянуть карты с поле боя
					sprintf(stmp, "\\green:%s решил затянуть карты с поле боя", sname);

				} else if (SayAction == PlayerPulledCards) { // игрок докинул карту в придачу
					char scard[20];
					StrPrintCardText(scard, gameTable.battle[gameTable.c_batt - 1]);
					sprintf(stmp, "%s докинул на поле боя еще одну карту в придачу: \\texttarget:%s",
								sname, scard);

				} else if (SayAction == PlayerAnswered) { // игрок ответил картой
					char scard[20];
					StrPrintCardText(scard, gameTable.battle[gameTable.c_batt - 1]);
					sprintf(stmp, "%s ответил картой \\texttarget:%s", sname, scard);
					
				} else if (SayAction == PlayerLaidOutCard) { // игрок подкинул карту
					char scard[20];
					StrPrintCardText(scard, gameTable.battle[gameTable.c_batt - 1]);
					sprintf(stmp, "%s подкинул на поле боя карту \\texttarget:%s", sname, scard);

				} else if (SayAction == PlayerAnsweresPass) { // игрок ответил пасс
					sprintf(stmp, "%s ответил пасс", sname);
				}
				GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
				UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
				SayAction = NoMessage;
			}
			if (SayCondition != NoMessage) {

				if (SayCondition == PlayerOutOfCards) { // у игрока закончились карты на руках
					if (gameTable.name_player[player_mark][0] == '\0')
						sprintf(stmp, "У %u-го игрока закончились карты на руках",
							player_out_of_cards + 1);
					else
						sprintf(stmp, "У %s закончились карты на руках",
							gameTable.name_player[player_mark]);

					// сообщение о переполнении поле боя
				} else if (SayCondition == BattleIsCrowded) {
					sprintf(stmp, "Поле боя переполненно (%u карт)", SIZE_BATTLEFIELD);

					// сообщение о победителе и его индексе очереди из игры
				} else if (SayCondition == PlayerOutOfTheGame) {
					char s_number[10];
					switch (gameTable.pos_out_player[player_mark]) {
						case 1: strcpy(s_number, "первым"); break;
						case 2: strcpy(s_number, "вторым"); break;
						case 3: strcpy(s_number, "третьим"); break;
						case 4: strcpy(s_number, "четвертым"); break;
						case 5: strcpy(s_number, "пятым"); break;
						case 6: strcpy(s_number, "шестым"); break;
					}
					if (gameTable.name_player[player_mark][0] == '\0')
						sprintf(stmp, "\\green:%u-й игрок вышел из игры %s победителем!",
							player_mark + 1, s_number);
					else
						sprintf(stmp, "%s вышел из игры %s победителем!",
							gameTable.name_player[player_mark]);
				}
				GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
				UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
				SayCondition = NoMessage;
			}

			if (theme.printChat)
				PrintChat(h, blocksGame.chat, gameTable.chat, &theme);
		}
		if (Error != NoError) {
			if (theme.onSounds)
				mciSendString(TEXT("play sourse\\sound\\game_table\\erro.mp3"), NULL, 0, NULL); // звук
			char splayer[20];
			char stmp[100];
			if (player_mark == gameTable.user && gameTable.mode != 
				GAME_SIMULATION && gameTable.mode != GAME_AI)
				sprintf(splayer, "");
			else {
				if (gameTable.name_player[player_mark][0] == '\0')
					sprintf(splayer, " %u-го игрока", player_mark + 1);
				else
					sprintf(splayer, " %s", gameTable.name_player[player_mark]);
			}

			if (Error == CardNotFoundInArr)
				sprintf(stmp, "\\lightred:Ошибка%s: в колоде не существует \
выбранной карты!", splayer);
			else if (Error == ImpossibleToPlaceCard)
				sprintf(stmp, "\\lightred:Ошибка%s: выбранная карта не может \
быть подкинута на поле боя!", splayer);
			else if (Error == CardCannotBeBeaten)
				sprintf(stmp, "\\lightred:Ошибка%s: выбранная карта не может \
побить карту противника!", splayer);
			else if (Error == WrongFirstMove)
				sprintf(stmp, "\\lightred:Ошибка%s: пас не может быть в начале хода!", 
					splayer);
			else if (Error == DiscoveredDuplicated) {
				char s_ideck_one[20], s_ideck_two[20];
				switch (ideck_one) {
					case 6: 
						strcpy(s_ideck_one, "общей"); break;
					case 7:
						strcpy(s_ideck_one, "поле боя"); break;
					case 8:
						strcpy(s_ideck_one, "отбоя"); break;
					default:
						sprintf(s_ideck_one, "%u-го игрока", ideck_one + 1); break;
				}
				switch (ideck_two) {
					case 6:
						strcpy(s_ideck_two, "общей"); break;
					case 7:
						strcpy(s_ideck_two, "поле боя"); break;
					case 8:
						strcpy(s_ideck_two, "отбоя"); break;
					default:
						sprintf(s_ideck_two, "%u-го игрока", ideck_one + 1); break;
				}
				sprintf(stmp, "\\lightred:Ошибка%s: обнаружена пара повторяющихся \
карт в колодах карт %s и %s!", s_ideck_one, s_ideck_two);
			} else if (Error == DiscoveredSuspiciousCard) {
				char s_ideck_one[20];
				switch (ideck_one) {
					case 6: 
						strcpy(s_ideck_one, "общей"); break;
					case 7:
						strcpy(s_ideck_one, "поле боя"); break;
					case 8:
						strcpy(s_ideck_one, "отбоя"); break;
					default:
						sprintf(s_ideck_one, "%u-го игрока", ideck_one + 1); break;
				}
				sprintf(stmp, "\\lightred:Ошибка%s: обнаружена подозрительная карта \
в колоде карт %s!", s_ideck_one);
			}

			GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
			UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
			if (gameTable.mode == GAME_SIMULATION || gameTable.mode == GAME_AI) {
				sprintf(stmp, "\\lightred:индекс ответа равен %d", i);
				GetMsgForChat(s, stmp, "Подсказка", "darkgray", &theme);
				UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
			}

			if (gameTable.mode == GAME_SIMULATION) {
				sprintf(stmp, "\\lightred: Симуляция игр остановлена на %u-й игре", 
					SimCountGamesDone);
				GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
				UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);

				gameTable.mode = GAME_AI;
				GetMsgForChat(s, "\\texttarget:Игра автоматически переведа \
в режим игры \"только ИИ\" для выявления ошибки ;)", "@a", "darkgray", &theme);
				UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
				GetMsgForChat(s, "Для того, чтобы игра продолажалась \
зажимайте клавишу \\texttarget:[Space]", "@a", "darkgray", &theme);
				UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
				if (theme.printChat)
					PrintChat(h, blocksGame.chat, gameTable.chat, &theme);
				Sleep(500);

				PrintGameInterface(h, &gameTable, cards.player,
					&blocksGame, &theme); // вывод игрового интерфейса
				UntilKeyIsPressedSpace();
			} else
				if (theme.printChat)
					PrintChat(h, blocksGame.chat, gameTable.chat, &theme);
			Error = NoError;
		}

		// ---------------- ДЕЙСТВИЯ ДЛЯ ЗАКОНЧЕНННОГО ХОДА -----------------------

		if (gameTable.end_move) { // если конец хода
			if (gameTable.mode != GAME_SIMULATION) {
				GetMsgForChat(s, "Конец хода. Нажмите \\texttarget:[Shift] \
\\textmsg:для того, чтобы продолжить", "@a", "darkgray", &theme);
				UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
				if (theme.printChat)
					PrintChat(h, blocksGame.chat, gameTable.chat, &theme);
				InteractiveGameInterface(h, &gameTable, cards.player,
					&blocksGame, psettingsAI, &theme); // интерактивность интерфейса игрового стола
			}

			// запомнить кол-во карт игроков, чтобы потом вычислить разницу
			for (size_t i = 0; i < gameTable.count_players; i++) {
				add_player[i] = gameTable.c_player[i];
			}
			add_retr = gameTable.c_batt;
			if (gameTable.player_state[gameTable.defend_player] == PASS) {
				RedistribCardsPass(&cards, K, &gameTable);
				MoveToNextPlayer(&gameTable.move, 2, &gameTable);
			} else {
				RedistribCards(&cards, K, &gameTable);
				MoveToNextPlayer(&gameTable.move, 1, &gameTable);
			}
			// запишем в матрицы карт ИИ изменения на игровом столе
			int pass = (gameTable.player_state[gameTable.defend_player] == PASS ? gameTable.defend_player : -1);
			for (size_t i = 0; i < gameTable.count_players; i++) {
				if (i != gameTable.user) {
					TransitCardsMatrAIEndMove(psettingsAI[i]->info.matr_cards, gameTable.battle, add_retr, pass);
					psettingsAI[i]->info.prev_c_batt = 0;
				}
			}

			// вычислим, сколько карт получил каждый игрок
			for (size_t i = 0; i < gameTable.count_players; i++) {
				add_player[i] = gameTable.c_player[i] - add_player[i];
			}
			gameTable.move_number++;

			gameTable.priority = gameTable.move;
			stop_player_attack = gameTable.move;
			gameTable.defend_player = (gameTable.move + 1)
				% gameTable.count_players;
			gameTable.count_can_throw = 
				min(gameTable.c_player[gameTable.defend_player], SIZE_BATTLEFIELD);
			while (gameTable.c_player[gameTable.defend_player] == 0) {
				gameTable.defend_player = (gameTable.defend_player + 1)
					% gameTable.count_players;
			}

			// игрок, который защищался на прошедшем ходу
			size_t old_defend_player = gameTable.defend_player;

			// задать новые состояния игроков
			for (size_t i = 0; i < gameTable.count_players; i++) {
				if (i == gameTable.defend_player)
					gameTable.player_state[i] = PROTECTION;
				else
					gameTable.player_state[i] = ATTACK;
			}

			size_t player_out[6] = { 0 }; // игроки, которые вышли из игры
			/*если для у игрока нет карт после раздачи карт
			и он еще не считаетвы вышедшим из игры*/
			for (size_t i = 0; i < gameTable.count_players; i++) {
				if (!gameTable.c_player[i] && !gameTable.pos_out_player[i]) {
					// игрок выходит победителем из игры
					gameTable.cur_count_players--;
					gameTable.pos_out_player[i] =
						gameTable.count_players - gameTable.cur_count_players;
					player_out[i] = 1;
				}
			}
			if (gameTable.mode != GAME_SIMULATION) {
				// сообщения о конце хода
				{
					char sname_def[MAX_LEN_NICKNAME + 1];
					if (gameTable.name_player[old_defend_player][0] == '\0')
						sprintf(sname_def, "%u-й игрок", old_defend_player + 1);
					else
						strcpy(sname_def, gameTable.name_player[player_mark]);

					if (player_pulled < 0) {
						sprintf(stmp, "\\green:%u-й ход завершен. %s успешно отбился!",
							gameTable.move_number - 1, sname_def);
					} else {
						sprintf(stmp, "\\green:%u-й ход завершен. %s обрел неуспех",
							gameTable.move_number - 1, sname_def);
					}
					GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
					UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);

					if (player_pulled >= 0) { // если игрок затянул карты
						if (gameTable.name_player[player_pulled][0] == '\0')
							sprintf(stmp, "%u-й игрок зятянул с поле боя \\texttarget:%u карт(ы)",
								player_pulled + 1, add_player[player_pulled]);
						else
							sprintf(stmp, "%s зятянул с поле боя \\texttarget:%u карт(ы)",
								gameTable.name_player[player_pulled], add_player[player_pulled]);

						GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
						UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);

						for (size_t i = 0; i < gameTable.count_players; i++) {
							if (add_player[i] && player_pulled != i) {
								if (gameTable.name_player[i][0] == '\0')
									sprintf(stmp, "%u-й игрок взял с общей колоды \\texttarget:%u карт(ы)",
										i + 1, add_player[i]);
								else
									sprintf(stmp, "%s взял из взял с общей колоды \\texttarget:%u карт(ы)",
										gameTable.name_player[i], add_player[i]);
								GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
								UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
							}
						}
						player_pulled = -1; // убрать пометку, что игрок затянул карты
					} 
					else { // если игрок отбился
						for (size_t i = 0; i < gameTable.count_players; i++) {
							if (add_player[i]) {
								if (gameTable.name_player[i][0] == '\0')
									sprintf(stmp, "%u-й игрок взял с общей колоды \\texttarget:%u карт(ы)",
										i + 1, add_player[i]);
								else
									sprintf(stmp, "%s взял из взял с общей колоды \\texttarget:%u карт(ы)",
										gameTable.name_player[i], add_player[i]);

								GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
								UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
							}
						}
						if (add_retr) {
							sprintf(stmp, "\\texttarget:%u карт(ы)\\textmsg: были перемещены из поле боя в отбой",
								add_retr);
							GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
							UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
						}
					}
					for (size_t i = 0; i < gameTable.count_players; i++) {
						if (player_out[i]) {
							char s_number[10];
							switch (gameTable.pos_out_player[player_mark]) {
							case 1: strcpy(s_number, "первым"); break;
							case 2: strcpy(s_number, "вторым"); break;
							case 3: strcpy(s_number, "третьим"); break;
							case 4: strcpy(s_number, "четвертым"); break;
							case 5: strcpy(s_number, "пятым"); break;
							case 6: strcpy(s_number, "шестым"); break;
							}
							if (gameTable.name_player[player_mark][0] == '\0')
								sprintf(stmp, "\\green:%u-й игрок вышел из игры %s победителем!",
									player_mark + 1, s_number);
							else
								sprintf(stmp, "\\green:%s вышел из игры %s победителем!",
									gameTable.name_player[player_mark], s_number);
							GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
							UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
						}
					}

					// сообщение о том, кто на кого ходит
					char sname_out[MAX_LEN_NICKNAME + 1];
					if (gameTable.name_player[gameTable.move][0] == '\0')
						sprintf(sname_out, "%u-го игрока", gameTable.move + 1);
					else
						strcpy(sname_out, gameTable.name_player[gameTable.move]);

					char sname_in[MAX_LEN_NICKNAME + 1];
					if (gameTable.name_player[gameTable.defend_player][0] == '\0')
						sprintf(sname_in, "%u-го игрока", gameTable.defend_player + 1);
					else
						strcpy(sname_in, gameTable.name_player[gameTable.defend_player]);

					sprintf(stmp, "\\texttarget:Начался ход %s под %s!",
						sname_out, sname_in);
					GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
					UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
				}
				// обновление игрововго интерфейса
				PrintGameInterface(h, &gameTable, cards.player,
					&blocksGame, &theme); // вывод игрового интерфейса
			}
			gameTable.end_move = 0;
		}

		// ------------- ПОЛУЧЕНИЕ ОТВЕТА ОТ ТЕКУЩЕГО ОТВЕЧАЮЩЕГО ИГРОКА ----------------

		// пропуск тех игроков, у которых нет карт
		while (!gameTable.c_player[gameTable.priority])
			MoveToNextPlayer(&gameTable.priority, 1, &gameTable);

		player_mark = gameTable.priority; // пометка текущего отвечающего игрока
		// получение ответа от игрока
		if (gameTable.mode != GAME_SIMULATION) {
			i = InteractiveGameInterface(h, &gameTable, cards.player,
				&blocksGame, psettingsAI, &theme); // интерактивность интерфейса игрового стола

			// пока пользователь вводит команды
			while (i == GAME_EXECUTE_COMMAND) {
				char s_res[MAX_LEN_MESSAGE];
				CallCommand(&gameTable, &cards, psettingsAI, &blocksGame, s_res, &theme);
				GetMsgForChat(s, s_res, "@p", "darkgray", &theme);
				UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
				if (theme.printChat)
					PrintChat(h, blocksGame.chat, gameTable.chat, &theme);

				i = InteractiveGameInterface(h, &gameTable, cards.player,
					&blocksGame, psettingsAI, &theme); // интерактивность интерфейса игрового стола
			}
			if (i == GAME_GOTO_MENU) { // выход в главное меню
				game_exit = 1;
				goto flagGameEnd;
			}
			// если очередь ИИ давать ответ
			else if (gameTable.priority != gameTable.user) {
				i = DecisionAI(&gameTable, psettingsAI[gameTable.priority],
					cards.player[gameTable.priority], gameTable.priority);
			}
		} else {
			i = DecisionAI(&gameTable, psettingsAI[gameTable.priority],
				cards.player[gameTable.priority], gameTable.priority);
		}
		gameTable.count_priority++;

		// --------- ПРОВЕРКА КОРРЕКТНОСТИ ПОЛУЧЕНИЯ ОТВЕТА ОТ ИГРОКА -----------------

  		if (i < 0 && gameTable.c_batt == 0) { // если в начале хода игрок выбрал "пас"
			Error = WrongFirstMove;
		} // если карта введена неправильно
		if (i >= 0) {
			if (i >= gameTable.c_player[gameTable.priority]) {
				gameTable.count_priority--;
				Error = CardNotFoundInArr;

			} else {
				// если игрок атакует, на поле боя есть карты и там нет карты с таким же номиналом
				if ((gameTable.player_state[gameTable.priority] == ATTACK ||
					gameTable.player_state[gameTable.priority] == CAN_BE_THROWN)
					&& gameTable.c_batt > 0 && ThereIsNominal(gameTable.battle,
						gameTable.c_batt, cards.player[gameTable.priority][i].n) < 0) {
					gameTable.count_priority--;
					Error = ImpossibleToPlaceCard;
				} 
				// если игрок защищается и выбранная карта не может побить последнюю карту на поле боя
				else if (gameTable.player_state[gameTable.priority] == PROTECTION
					&& !CardCanBeat(cards.player[gameTable.priority][i],
						gameTable.battle[gameTable.c_batt - 1], gameTable.trump)) {
					gameTable.count_priority--;
					Error = CardCannotBeBeaten;
				} 
				else {
					size_t error = ChekingAllCards(&cards, &gameTable,
						gameTable.count_players, &ideck_one, &ideck_two);
					if (error == 1) {
						gameTable.count_priority--;
						Error = DiscoveredDuplicated;
					} 
					else if (error == 2) {
						gameTable.count_priority--;
						Error = DiscoveredSuspiciousCard;
					}
				}
			}
		}
		
		// ------------------------ ПРОЦЕСС ХОДА --------------------------------

		if (Error == NoError) {
			// если игрок в состоянии нападения (подкидывание карт)
			if (gameTable.player_state[player_mark] == ATTACK ||
				gameTable.player_state[player_mark] == CAN_BE_THROWN) {
				if (i == -1) { // если игрок закончил свой ход

					// если у защищающегося игрока нет карт
					if (!gameTable.c_player[gameTable.defend_player]) {
						gameTable.end_move = 1;
					} else {
						if (!gameTable.count_can_throw) { // если поле боя переполненно 
							gameTable.end_move = 1;
							if (gameTable.c_player[gameTable.defend_player] == SIZE_BATTLEFIELD)
								SayCondition = BattleIsCrowded;
							else
								SayCondition = BattleCanNotBeThrown;
						} else {
							// если игрок, на которого походили, решил затянуть карты
							if (gameTable.player_state[gameTable.defend_player] == PASS) {
								if (transitions) { // если не пройден полный цикл по игрокам
									transitions--;
									MoveToNextPlayer(&gameTable.priority, 1, &gameTable);
									// если перешли на игрока, который защищается
									if (gameTable.priority == gameTable.defend_player)
										MoveToNextPlayer(&gameTable.priority, 1, &gameTable);
								} else {
									gameTable.end_move = 1;
								}
							} else { // если игрок, на которого походили, все еще отбивается
								MoveToNextPlayer(&gameTable.priority, 1, &gameTable);
								// если перешли на игрока, который защищается
								if (gameTable.priority == gameTable.defend_player)
									MoveToNextPlayer(&gameTable.priority, 1, &gameTable);
								stop_player_attack = gameTable.priority;
								// если был пройден полный цикл по игрокам
								if (gameTable.priority == gameTable.move) {
									gameTable.end_move = 1;
								}
							}
						}
					}
					SayAction = PlayerAnsweresPass;

				} else {
					// обозначить карту на поле боя как атакующую
					gameTable.cond_battle[gameTable.c_batt] = ATTACK;
					// переместить i-ю карту из массива 1-го игрока на поле боя
					MoveCardInArr(cards.player[player_mark],
						&gameTable.c_player[player_mark],
						i, gameTable.battle, &gameTable.c_batt);
					SayAction = PlayerLaidOutCard;

					gameTable.count_can_throw--;
					if (!gameTable.count_can_throw) { // если поле боя переполненно 
						// если игрок, на которого ходят, пасанул 
						if (gameTable.player_state[gameTable.defend_player] == PASS) {
							gameTable.end_move = 1;
							if (gameTable.c_player[gameTable.defend_player] == SIZE_BATTLEFIELD)
								SayCondition = BattleIsCrowded;
							else
								SayCondition = BattleCanNotBeThrown;
						} else
							gameTable.priority = gameTable.defend_player;
					} 
					// если игрок, под которого ходили не пасанул
					else if (gameTable.player_state[gameTable.defend_player] != PASS) {
						gameTable.priority = gameTable.defend_player;
					}
					// если у игрока не осталось карт
					if (!gameTable.c_player[player_mark]) {
						SayCondition = PlayerOutOfCards;
						if (!gameTable.c_deck) { // если в общей колоде нет карт
							// игрок выходит победителем из игры
							gameTable.cur_count_players--;
							gameTable.pos_out_player[player_mark] =
								gameTable.count_players - gameTable.cur_count_players;
							SayCondition = PlayerOutOfTheGame;
						}
					}
					// если у защищающегося игрока нет карт
					if (!gameTable.c_player[gameTable.defend_player]) {
						gameTable.end_move = 1;
					}
				}

			} // если игрок в состоянии защиты (отбивает карты)
			else if (gameTable.player_state[player_mark] == PROTECTION) {
				if (i == -1) { // если игрок пасанул
					// задать новые состояния игроков
					for (size_t j = 0; j < gameTable.count_players; j++) {
						if (j == gameTable.defend_player)
							gameTable.player_state[j] = PASS;
						else
							gameTable.player_state[j] = CAN_BE_THROWN;
					}
					player_pulled = gameTable.defend_player;
					gameTable.priority = stop_player_attack;
					transitions = gameTable.cur_count_players - 2;
					SayAction = PlayerPulledCards;

					// если поле боя переполенно
					if (!gameTable.count_can_throw) {
						gameTable.end_move = 1;
						if (gameTable.c_player[gameTable.defend_player] == SIZE_BATTLEFIELD)
							SayCondition = BattleIsCrowded;
						else
							SayCondition = BattleCanNotBeThrown;
					}
				} else {
					// обозначить карту на поле боя как защищающую
					gameTable.cond_battle[gameTable.c_batt] = PROTECTION;
					// переместить i-ю карту из массива 1-го игрока на поле боя
					MoveCardInArr(cards.player[player_mark], &gameTable.c_player[player_mark],
						i, gameTable.battle, &gameTable.c_batt);
					gameTable.priority = stop_player_attack;
					SayAction = PlayerAnswered;

					// если поле боя переполенно
					if (!gameTable.count_can_throw) {
						gameTable.end_move = 1;
						if (gameTable.c_player[player_mark] == SIZE_BATTLEFIELD)
							SayCondition = BattleIsCrowded;
						else
							SayCondition = BattleCanNotBeThrown;
					}
					// если у игрока не осталось карт
					if (!gameTable.c_player[player_mark]) {
						gameTable.end_move = 1;
						SayCondition = PlayerOutOfCards;
						if (!gameTable.c_deck) { // если в общей колоде нет карт
							// игрок выходит победителем из игры
							gameTable.cur_count_players--;
							gameTable.pos_out_player[player_mark] =
								gameTable.count_players - gameTable.cur_count_players;
							SayCondition = PlayerOutOfTheGame;
						}
					}
				}
			}
		}
	}
	for (size_t i = 0; i < gameTable.count_players; i++) {
		if (!gameTable.pos_out_player[i]) {
			if (gameTable.c_player[i])
				gameTable.pos_out_player[i] = gameTable.count_players;
			else
				gameTable.pos_out_player[i] = gameTable.count_players - 1;
		}
	}

	// ---------------------- КОНЕЦ ИГРОВОГО СЕАНСА -------------------------

	if (gameTable.mode == GAME_SIMULATION) { // если запущен режим симуляции игр
		DeleteCardsPlayers(cards.player, gameTable.count_players);
		for (size_t i = 0; i < gameTable.count_players; i++) {
			if (i != gameTable.user || gameTable.mode == GAME_AI ||
				gameTable.mode == GAME_SIMULATION) {
				free(psettingsAI[i]);
			}
		}
		goto flagSimulation;
	} 
	else {
		Sleep(1500);
		if (theme.onSounds)
			mciSendString(TEXT("play sourse\\sound\\game_table\\questComplete1.mp3"), NULL, 0, NULL);
		PrintGameInterface(h, &gameTable, cards.player,
			&blocksGame, &theme); // вывод игрового интерфейса

		int player_lose = 0; // индекс проигравшего игрока
		gameTable.end_game = 1; // конец игрового сеанса
		// получить индекс програвшего игрока
		while (player_lose < gameTable.count_players &&
			!gameTable.c_player[player_lose]) {
			player_lose++;
		}
		if (player_lose == gameTable.count_players)
			player_lose = -1;

		GetMsgForChat(s, "\\green:Игра завершена!", "@a", "darkgray", &theme);
		UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);

		float coeff_reward = (gameTable.count_players - gameTable.pos_out_player[gameTable.user] + 1)
			/ gameTable.count_players;

		int change_raiting = 0; // изменение рейтинга

		Tblock block = blocksGame.cards_battle;
		block.pos.X -= 2;
		block.lenX += 4;
		if (player_lose < 0) { // если ничья
			if (theme.onSounds) {
				mciSendString(TEXT("play sourse\\sound\\game_table\\questComplete1.mp3"),
					NULL, 0, NULL); //звук
			}
			GetMsgForChat(s, "\\green:Ничья! Никто не остался в дураках.", "@a", "darkgray", &theme);
			if (gameTable.mode == GAME_STANDART) {
				theme.countWins = ChangeValueData(FILE_PATH_SETTINGS, "countWins", 1);
				change_raiting = 4100 / theme.raiting * 30 * coeff_reward;
			}
			UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
			char strs[2][100];
			strcpy(strs[0], "ничья!");
			strcpy(strs[1], "выиграли все");
			PrintLargeMsg(h, block, strs, 2, 8000, 1000, "bgmsg", "textbase", "texttarget", &theme);
		}
		else { // если есть проигравший
			if (player_lose != gameTable.user && gameTable.mode != GAME_AI) {
				GetMsgForChat(s, "\\lightred:Вы проиграли и остались в дураках!", "@a", "darkgray", &theme);
				UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
			} else {
				sprintf(s, "\\green:%u-й игрок остался в дураках!", player_lose + 1);
				GetMsgForChat(s, stmp, "@a", "darkgray", &theme);
			}
			if (gameTable.mode == GAME_AI) { // если игра ИИ
				if (theme.onSounds) {
					mciSendString(TEXT("play sourse\\sound\\game_table\\questComplete1.mp3"),
						NULL, 0, NULL); //звук
				}
				char strs[3][100];
				if (gameTable.name_player[player_lose] == '\0')
					sprintf(strs[0], "%u-й игрок", player_lose + 1);
				else
					sprintf(strs[0], "%s", gameTable.name_player[player_lose]);
				strcpy(strs[1], "остался в");
				strcpy(strs[2], "дураках");
				PrintLargeMsg(h, block, strs, 3, 8000, 1000, "bgmsg", "textbase", "texttarget", &theme);
			} 
			else { // если игра пользовтеля
				if (gameTable.mode == GAME_STANDART)
					theme.countGames = ChangeValueData(FILE_PATH_SETTINGS, "countGames", 1);

				if (gameTable.user != player_lose) { // пользователь выиграл
					if (gameTable.mode == GAME_STANDART) {
						theme.countWins = ChangeValueData(FILE_PATH_SETTINGS, "countWins", 1);
						change_raiting = 4100 / theme.raiting * 30 * coeff_reward;
					}
					if (theme.onSounds) {
						mciSendString(TEXT("play sourse\\sound\\game_table\\winGame1.mp3"),
							NULL, 0, NULL); //звук
					}
					char strs[4][100];
					strcpy(strs[0], "вы выиграли!");
					if (gameTable.name_player[player_lose] == '\0')
						sprintf(strs[1], "%u-й игрок", player_lose + 1);
					else
						sprintf(strs[1], "%s", gameTable.name_player[player_lose]);
					strcpy(strs[2], "остался в");
					strcpy(strs[3], "дураках");
					PrintLargeMsg(h, block, strs, 4, 8000, 1000, "bgmsg", "textbase", "texttarget", &theme);
				}
				else { // пользователь проиграл
					if (gameTable.mode == GAME_STANDART) {
						theme.countLose = ChangeValueData(FILE_PATH_SETTINGS, "countLose", 1);
						change_raiting = -(theme.raiting / 4100 * 300 * powf(gameTable.count_players, 0.67));
					}
					if (theme.onSounds) {
						mciSendString(TEXT("play sourse\\sound\\game_table\\loseGame1.mp3"),
							NULL, 0, NULL); //звук
					}
					char strs[3][100];
					strcpy(strs[0], "вы проиграли!");
					strcpy(strs[1], "и остались в");
					strcpy(strs[2], "дураках");
					PrintLargeMsg(h, block, strs, 3, 8000, 1000, "bgmsg", "textbase", "texttarget", &theme);
				}
				if (gameTable.mode == GAME_STANDART_SEE) {
					GetMsgForChat(s, "\\lightred:Вы только что сыграли партию в режиме всевидящего. \
Такой режим особо не повлияет на вашу статистику и достижения: в этом плане он никуда не годится.", "@a", "darkgray", &theme);
					UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
				}
				theme.raiting = ChangeValueData(FILE_PATH_SETTINGS, "raiting", change_raiting);
				WriteToTextFileSettings(FILE_PATH_SETTINGS_TXT, FILE_PATH_SETTINGS);
				sprintf(stmp, "Ваш рейтинг изменен:\\texttarget: %+d", change_raiting);
				GetMsgForChat(s, stmp, "@p", "darkgray", &theme);
				UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);

			}
		}
		GetMsgForChat(s, "Игра окончена, как вы видите. Нажмите \\texttarget:[Shift] \
\\textmsg:для того, чтобы выйти в главное меню", "@a", "darkgray", &theme);
		UpdateChat(gameTable.chat, blocksGame.chat, s, &theme);
		PrintChat(h, blocksGame.chat, gameTable.chat, &theme);

		gameTable.end_game = 1;
		i = InteractiveGameInterface(h, &gameTable, cards.player,
			&blocksGame, psettingsAI, &theme); // интерактивность интерфейса игрового стола

		flagGameEnd:
		gameTable.end_game = 0;
		// освобождение динамической памяти ИИ, массивов карт игроков
		DeleteCardsPlayers(cards.player, gameTable.count_players);
		for (size_t i = 0; i < gameTable.count_players; i++) {
			if (i != gameTable.user || gameTable.mode == GAME_AI) {
				free(psettingsAI[i]);
			}
		}
		ChatClear(gameTable.chat, HEIGHT_CHAT);
		goto flagMainMenu;
	}

	SetColor(h, "bgbase", "darkgray", &theme);
	return 0;
}
