#if !defined(__HEADER_H) 
#define __HEADER_H 

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <io.h>

// общие макросы
#define TRUE 1
#define FALSE 0
#define PI 3.14159265
#define EPS 0.00001

// название программы
#define TITLE_PROGRAM "Карточная игра в дурака 0.3.0"
// версия программы
#define VERSION "Alpha 0.3.0" 
// путь бинарного файла для записи и чтения сохранений
#define FILE_PATH_SETTINGS "settings.bin" 
// путь текстового файла, предтавляющего сохранения в текстовом виде
#define FILE_PATH_SETTINGS_TXT "sourse\\settings.txt" 
// путь текстового файла для чтения текта правил игры
#define FILE_PATH_GAMERULE_TXT "sourse\\gamerule.txt" 

// размеры рабочего окна
#define SIZE 500 // размер строк для различного назначения
#define WIDTH 172 // ширина вывода консольного окна
#define HEIGHT 50 // высота вывода консольного окна
// точка начала рабочего окна по оси y для инициализации меню
#define WIN_X0 p_allblocks->window.pos.X
 // точка начала рабочего окна по оси x для инициализации меню
#define WIN_Y0 p_allblocks->window.pos.Y

// размеры элементов
#define SIZE_DECK 36 // размер колоды карт
#define K 6 // кол-во карт, которое выдается каждому игроку на старте
#define SIZE_BATTLEFIELD 6 // размер поле боя в картах
#define WIDTH_CRADS_BASE 72 // основная ширина вывода массива карт
#define WIDTH_CRADS_MEDIUM 56 // средняя ширина вывода массива карт
#define WIDTH_CRADS_SMALL 48 // укороченнная ширина вывода массива карт
#define WIDTH_BATTLE 52 // ширина поле боя
#define MAX_LEN_NICKNAME 20 // максимальная длина имени игрока
#define MAX_LEN_MESSAGE 200 // максимальная длина для ввода сообщения
#define DISTANCE_BUTTON 2 // расстояние между стандартными кнопками
#define WIDTH_BUTTON_MENU 55 // ширина кнопок в главном меню
#define HEIGHT_CHAT 24 // максимальное кол-во строк чата
// ширина информационного окна в меню симуляций игр
#define WIDTH_SIMULATION_INFO WIDTH / 2 

// максимально допустимое количество симуляций игр за один прогон
#define MAX_COUNT_SIMULATION 10000
// начальная страница книги в меню книги "справка"
#define BOOK_START_PAGE 5

// память ИИ в виде матрицы
#define SIZE_COLUMN_AI 18 // кол-во колонок матрицы ИИ
#define SIZE_LINE_AI 5 // кол-во строк матрицы ИИ
#define CARDS_UNKNOWN 15 // колонка неизвестных карт
#define CARDS_RETR 16 // колонка карт в отбое
#define CARDS_BATTLE 17 // колонка карт на поле боя

// задание временных рамок событий
#define SPEED_SWITCH_BUTTON 200 // скорость преключения между кнопками (мс)
#define SPEED_CLICK 350 // скорость клика (мс)
#define SPEED_TRANSIT 900 // скорость перехода между окнами (мс)
#define SPEED_ANSWER_ONLY_AI 75 // скорость ответов игроков в режиме "только ИИ" (мс)
#define DECISION_TIME_AI 2200 // задержка времени принятия решения ИИ (мс)
#define TIME_PRESS_PASS 200 // время активной кнопки пасс для активации (мс)
#define TIME_EFFECT_CARD 500 // время эффекта появления карты
#define TIME_BLINKING_ANSWER 200 // время мигания имени игрока при ответе
#define TIME_CLEAR_BUF 150 // время на чистку буфера ввода

// погодные константы
#define CHANCE_LIGHTNING 1300 // шанс удара одного удара молнии на кол-во обновлений погоды
// начальный коэффициент интенсивности погоды (0...1.0)
#define START_COEFF_WEATHER 0

// состояние игрока на текущем ходу
#define PROTECTION 0
#define ATTACK 1
#define PASS 2
#define CAN_BE_THROWN 3

// уровень игры игрока
#define EASY 0
#define NORMAL 1
#define HARD 2
#define UNREAL 3
#define USER 4
#define NONE_DIFF 5

// режимы работы игрового процесса
#define GAME_STANDART 0
#define GAME_STANDART_SEE 1
#define GAME_AI 2
#define GAME_SIMULATION 3

// цветовые темы
#define THEME_DAY 0
#define THEME_NIGHT 1
#define THEME_EAST 2
#define THEME_BLACK_BLUE 3
#define THEME_NEW_YEAR 4

// тип погоды
#define WEATHER_CLEAR 0
#define WEATHER_SNOW 1
#define WEATHER_RAIN 2

// кнопки в главном меню
#define MAIN_MENU_STORY 1
#define MAIN_MENU_CUSTOM_GAME 2
#define MAIN_MENU_SIMULATION 3
#define MAIN_MENU_SETTINGS 4
#define MAIN_MENU_EXIT 5
#define MAIN_MENU_GAME_RULE 6

// кнопки в меню симуляции
#define SIMULATION_START 8
#define SIMULATION_GOTO_MENU 9
#define SIMULATION_STOP 10
#define SIMULATION_ANEW 11

// кнопки в меню настроек
#define SETTINGS_RE_NICKNAME 1
#define SETTINGS_RESET_PROGRESS 2
#define SETTINGS_GOTO_MENU 3

// состояния кнопок
#define BUTTON_NONE 0 // кнопка не актиана
#define BUTTON_HOVER 1 // наведен курсор мыши на кнопку
#define BUTTON_CHOISE 2 // кнопка нажата
#define BUTTON_HOVER_KEY 3 // кнопка активна: переход с помощью клавиш
#define BUTTON_HOVER_CUR 4 // текущая кнопка активная (если подключен переход с помощью клавиш)
#define BUTTON_INIT 5 // инициализация кнопки
#define BUTTON_OFF 6 // отключена кнопка

// возвращаемые значение игрового интерфейса
#define GAME_GOTO_MENU -2
#define GAME_EXECUTE_COMMAND -3
#define GAME_REQUEST_SOLUTION_AI -4
#define GAME_CONTINUE -5

// кнопки в меню паузы
#define CONTINUE 1
#define CUSTOM_GAME_GOTO_MENU 2

// работа с музыкой
#define CONTEXT_NONE 0
#define CONTEXT_MENU 1
#define CONTEXT_GAME 2
#define CONTEXT_PAUSE_GAME 3
#define CONTEXT_SIMULATION 4

// событийные эффекты
#define EE_NONE 0 // без собыйных эффектов
#define EE_CHANGE_OF_TRUMP 1 // смена козыря каждый ход
#define EE_RANDOM_CARD_EXCHANGE 2 // случайные обмены
#define EE_TRANSFERABLE 3 // переводной
#define EE_MAXIMUM_CARDS_IN_HAND 4 // широкие руки
#define EE_REVERSAL_OF_NOMINAL 5 // номинальный переворот
#define EE_BAN_ON_SUIT 6 // табу на масть
#define EE_MIXING_CARDS 7  // переполох на игровом столе
#define EE_SHORT_SUIT 8 // слабая масть
#define EE_ABOLITION_TRUMP 9 // равенство мастей
#define EE_TIME_LIMIT 10 // время быстрго принятия решений 
#define EE_CHANGE_COLOR_CARDS 11 // цветное веселье

// команды, вводимые в чат
#define COMMAND_NONE 0
#define COMMAND_KEY_ADMIN 1
#define COMMAND_GET_COMMAND_LIST 2
#define COMMAND_SET_GAME_MODE 3
#define COMMAND_DELETE_CARD_PLAYER 4
#define COMMAND_GIVE_CARD_PLAYER 5
#define COMMAND_DELETE_CARDS_PLAYER 6
#define COMMAND_GET_CARDS_PLAYER 7
#define COMMAND_DECREASE_COUNT_CARDS_DECK 8
#define COMMAND_SET_TRUMP 9
#define COMMAND_SET_EVENT_EFFECT 10
#define COMMAND_PRINT_MATR_CARDS_AI 11
#define COMMAND_DELETE_MATR_CARDS_AI 12
#define COMMAND_END_MOVE 13
#define COMMAND_END_GAME 14
#define COMMAND_TURN_ON_SOUND 15
#define COMMAND_GET_COLOR_LIST 16

// состояние введенной строки аргументов
#define ARGS_OK 0
#define ARGS_FEW -1
#define ARGS_MANY -2
#define COMMAND_NO_AVAILABLE -3
#define ERROR_NO_INIT_MATR_AI -4
#define ERROR_IS_INDEX_USER -5

/*возвращает значение "истина", если с момента 
времени start прошло хотя бы target миллисекунд*/
#define TIMER(start, target) ((clock() - (start)) >= (target))

/*возвращает количество секунд, которое прошло 
с момента времени start*/
#define TIME_SEC(start) (double)(( clock() - (start) ) / CLOCKS_PER_SEC)
/*возвращает количество миллисекунд, которое прошло
с момента времени start*/
#define TIME_MSEC(start) (clock_t)( clock() - (start) )

// структура с координатами точек начала блоков меню игры
typedef struct str_block {
	COORD pos; // координаты начала элемента (левый верхний угол)
	size_t lenX; // длина элемента по оси X
	size_t lenY; // длина элемента по оси Y
	size_t cond; // состояние блока
} Tblock;

// структура с информацией о матрице осадков
typedef struct str_weather {
	Tblock window; // рабочее окно
	char type; // тип осадков ('*', или '|', или ' ')
	size_t change_speed; // скорость изменения погоды (1...100)
	float step_change; // шаг приращения изменений (0...1.0)
	float coeff; // коэффициент плотности появления осадков (0...1.0)
	float max_coeff; // максимальный коэф. плотности появления осадков (0...1.0)
	float min_coeff; // минимальный коэф. плотности появления осадков (0...1.0)
	int direction_wind; // напрвление ветра (-1 или 1)

	char ch; // символ осадков (*, |, ', $,)
	size_t angle; // угол наклона (0...90)
	size_t fall_mess; // степень хаотичности падения (1...100)
	size_t delay; // задержка падения осадков (мс)
	float count; // кол-во осадков за итерацию

	clock_t time_start; // время последнего вывода осадков
	// матрица с местоположениями символов осадков
	char matr[HEIGHT][WIDTH + 1];

	// матрица препятствий
	char matr_obstac[HEIGHT][WIDTH];
	// основа матрицы препятствий для меню
	char matr_obstac_footer[HEIGHT][WIDTH];

	char type_bg_sounds; // тип фоновых звуков
	size_t shower; // есть ли ливень
} Tweather;

// структура с информацией элементов главного меню
typedef struct str_blocks_menu {
	Tblock header; // шапка
	Tblock buttons; // кнопки главного меню
	Tblock story; // кнопка сюжетная игра
	Tblock custom_game; // кнопка начать игру 
	Tblock simulation; // кнопка симуляция
	Tblock settings; // кнопка настройки 
	Tblock exit; // кнопка выход
	Tblock book_rule; // кнопка перехода на книгу правил
	Tblock achievement_table; // таблица достижений

	Tblock* pwindow; // рабочее окно
	Tblock* pversion; // надпись версия
	Tblock* pfooter; // подвал
	Tblock* pcat; // изображение кота
	COORD* pcursore; // позиция курсора
} TblocksMainMenu;

// структура с информацией элементов меню настроек новой игры
typedef struct str_blocks_customgame {
	Tblock header; // заголовок
	Tblock info; // область настроек
	Tblock table; // таблица настроек игроков
	Tblock players[6]; // кнопки настроек игроков
	Tblock effect; // событийный эффекты

	Tblock see_mode; // включить режим всевидящего
	Tblock only_ai; // включить режим только ИИ
	Tblock chat; // чат 
	Tblock button_chat; // кнопка чата
	Tblock input_chat; // всплывающее поле ввода текста чата
	Tblock special_card; // включить специальные карты
	Tblock multiplayer; // включить мультиплеер

	Tblock start; // запуск новой игры
	Tblock goto_menu; // кнопка выхода в главное меню

	Tblock* pwindow; // рабочее окно
	Tblock* pversion; // надпись версия
	Tblock* pfooter; // подвал
	Tblock* pcat; // изображение кота
	COORD* pcursore; // позиция курсора
} TblocksCustomGame;

// структура с информацией элементов меню симуляций игр
typedef struct str_blocks_simulation {
	Tblock header; // заголовок меню симуляции
	Tblock info; // область настроек и процесса симуляции
	Tblock table; // таблица настроек игроков
	Tblock players[6]; // кнопки настроек игроков
	Tblock count_sim; // кнопка настроки кол-ва симуляций игр
	Tblock start; // кнопка запуска симуляции
	Tblock goto_menu; // кнопка выхода в главное меню

	Tblock stop; // кнопка остановки симуляции
	Tblock anew; // кнопка вызова повторной симуляции

	Tblock* pwindow; // рабочее окно
	Tblock* pversion; // надпись версия
	Tblock* pfooter; // подвал
	Tblock* pcat; // изображение кота
	COORD* pcursore; // позиция курсора
} TblocksSimulation;

// структура с информацией элементов меню настроек
typedef struct str_blocks_settings {
	Tblock header; // заголовок
	Tblock table; // фоновая вывеска
	Tblock table_weather; // фоновая вывеска для погодных настроек
	Tblock table_control_keys; // таблица управляющих клавиш

	Tblock nickname; // иземнить никнейм
	Tblock reset_progress; // сброс пргресса
	Tblock full_screen_mode; // полноэкранный режим

	Tblock theme; // заголовок темы оформления 
	Tblock theme_day; // дневная тема оформления 
	Tblock theme_night; // ночная тема оформления 
	Tblock theme_east; // востояная тема оформления 
	Tblock theme_black_blue; // черно-синяя тема оформления 
	Tblock theme_new_year; // новогодняя тема оформления 

	Tblock weather; // заголовок погодных настроек
	Tblock weather_clear; // осадки: нет
	Tblock weather_snow; // осадки: снег
	Tblock weather_rain; // осадки: дождь

	Tblock volume; // заголовок настройки звуков
	Tblock music_bg; // фоновая музыка
	Tblock sounds_weather; // звуки погоды
	Tblock sounds; // прочие звуки

	Tblock game; // заголовок игровых настроек
	Tblock chat; // чат
	Tblock messages_chat; // сообщения о действиях в чате
	Tblock effects; // игровые спецэффекты
	Tblock improved_alg; // оптимизированный алгоритм перевывода элементов игры

	Tblock goto_menu; // кнопка выхода

	Tblock* pwindow; // рабочее окно
	Tblock* pversion; // надпись версия
	Tblock* pfooter; // подвал
	Tblock* pcat; // изображение кота
	COORD* pcursore; // позиция курсора

	Tblock table_input_name; // вывеска ввода имени
} TblocksSettings;

// структура с информацией элементов меню правил игры
typedef struct str_blocks_gamerule {
	Tblock header; // заголовок
	Tblock book; // книга
	Tblock voice_acting; // озвучка текста
	Tblock invert_lighting; // инвертировать освещение
	Tblock page_left; // кнопка перелистнуть страницу влево
	Tblock page_right; // кнопка перелистнуть страницу вправо
	Tblock goto_menu; // кнопка выхода в главное меню

	Tblock* pwindow; // рабочее окно
	Tblock* pversion; // надпись версия
	Tblock* pfooter; // подвал
	Tblock* pcat; // изображение кота
	COORD* pcursore; // позиция курсора
} TblocksGameRule;

// структура с информацией элементов каждого окна меню
typedef struct str_all_blocks {
	Tblock window; // рабочее окно
	Tblock* pwindow;
	Tblock version; // надпись версия
	Tblock* pversion;
	Tblock footer; // подвал
	Tblock* pfooter;
	Tblock cat; // изображение кота
	Tblock* pcat;
	COORD cursore; // позиция курсора
	COORD* pcursore;

	TblocksMainMenu mainMenu;
	TblocksCustomGame customGame;
	TblocksSimulation simulation;
	TblocksSettings settings;
	TblocksGameRule gameRule;
} TblocksMenu;

// структура с информацией элементов игрового стола
typedef struct str_blocks_game {
	Tblock window; // рабочее окно
	/*доступная позиция для следующей атакующей и защищающей 
	карты на поле боя*/
	size_t target_card; // выбранная карта пользователя
	// координаты каждой карты пользователя по оси X
	size_t pos_cards[SIZE_DECK]; 
	COORD time; // время
	Tblock matr_cards_ai; // матрица карт определенного ИИ
	size_t index_matr_ai; // индекс игрока ИИ, матрица карт которого выведена

	Tblock header; // шапка окна
	char s_effect[100]; // название событийного эффекта
	Tblock effect; // событийный эффект
	Tblock esc; // вызов меню паузы

	Tblock menu_block; // меню паузы
	Tblock menu_header; // шапка меню паузы
	Tblock menu_continue; // продолжить игру
	Tblock menu_exit; // выход в главное меню

	Tblock chat; // чат
	Tblock button_chat; // кнопка чата
	Tblock input_chat; // всплывающее поле ввода текста чата
	Tblock cards_deck; // колода карт верх рубашкой
	Tblock cards_battle; // поле боя
	Tblock card_special; // специальная карты
	Tblock button_pass; // кнопка пасс

	Tblock cards_user; // карты пользователя
	Tblock cards_p2_2; // карты 2-го игрока для игры вдвоем

	Tblock cards_p2_3; // карты 2-го игрока для игры втроем
	Tblock cards_p3_3; // карты 3-го игрока для игры втроем

	Tblock cards_p2_4; // карты 2-го игрока для игры вчетвером
	Tblock cards_p3_4; // карты 3-го игрока для игры вчетвером
	Tblock cards_p4_4; // карты 4-го игрока для игры вчетвером

	Tblock cards_p5_5; // карты 5-го игрока для игры впятером
	Tblock cards_p6_6; // карты 6-го игрока для игры впятером

	COORD cursore; // позиция курсора
} TblocksGame;

// карта
typedef struct card {
	char m; // масть карты
	uint8_t n; // номинал карты
} Tcard;

// структура с информацией об картах игроков на игровом поле
typedef struct str_cards {
	Tcard deck[SIZE_DECK]; // массив общей колоды карт
	Tcard retread[SIZE_DECK]; // массив карт в отбое
	Tcard* player[6]; // массив карт игроков
} Tcards;

// структура с информацией об игровом поле для игроков
typedef struct str_game_table {
	size_t user; // игрок, за которого играет пользователь
	size_t count_players; // изначальное кол-во игроков
	size_t cur_count_players; // текущее кол-во игроков
	size_t mode; // режим игровой сессии
	size_t event_effect; // событийный эффект игровой сессии
	size_t special_card; // спец. карт игровой сессии включены
	size_t player_state[6]; // игровое состояние игроков
	size_t move; // какому игроку принадлежит текущий ход
	size_t defend_player; // игрок, под которого ходят
	size_t priority; // от какого игрока ждать ответ
	size_t game_start; // игра началась

	size_t c_deck; // кол-во карт в общей колоде
	size_t c_batt; // кол-во карт на поле боя
	Tcard battle[SIZE_DECK]; // массив карт поле боя
	size_t c_retr; // кол-во карт в отбое
	size_t c_player[6]; // кол-во карт игроков
	
	char trump; // козырная масть
	Tcard bottom_card; // нижняя карта в общей колоде карт, которя была в начале игрового сеанса
	size_t count_can_throw; // сколько карт еще можно подкинуть на поле боя
	size_t end_move; // конец хода
	size_t end_game; // конец игровой сессии
	size_t move_number; // номер хода игровой сессии
	size_t count_priority; // кол-во ответов в игровой сессии
	size_t pos_out_player[6]; // позиции выхода игроков из игры

	clock_t time_start; // время начала игры
	clock_t time_sec; // текущее время игры в секундах

	char (*chat)[SIZE]; // чат
	size_t command; // команда, которую ввел пользователь в чате
	char args[200]; // аргументы введенной пользователем команды
	size_t cond_battle[SIZE_DECK]; // состояние карт на поле боя
	char name_player[6][MAX_LEN_NICKNAME + 1]; // имена игроков
	size_t count_wait_ms_AI; // сколько миллисекунд ждать ответа ИИ
} TgameTable;

// структура с информацией, которую собрал ИИ по ходу игры
typedef struct str_ai {
	// матрица, содержащая информацию о картах в игре, собранная ИИ
	uint8_t matr_cards[SIZE_LINE_AI][SIZE_COLUMN_AI];
	size_t sum_rank_ai; // сумма рангов карт ИИ
	size_t rank_ai; // средний ранг карт ИИ

	size_t sum_rank_unknown; // сумма рангов неизвестных карт
	size_t rank_unknown; // средний ранг неизвестных карт

	size_t sum_rank_enemy[6]; // сумма рангов известных карт противников
	size_t rank_enemy[6]; // средний ранг известных карт противников

	// предполагаемый минимальный номинал карт каждой масти противника
	uint8_t min_nom_enemy[6][4];
	Tcard card_cause[6]; // карта, по причине которой противник затянул
	size_t prev_cause[6]; // карта-причина была затянута на прошлом ходу у противника
	size_t prev_c_batt; // предыдущее кол-во карт на поле боя
	size_t prev_move_number; // номер хода на предыдущем ответе

	size_t evaluation[SIZE_DECK]; // массив оценок карт на руках ИИ
} TAI;

// структура с настройками ИИ
typedef struct str_settings_ai {
	size_t difficulty; // уровень сложности игры ИИ
	size_t init_ai; // была ли инициализация памяти ИИ
	struct str_ai info; // структура с информацией, которую собрал ИИ по ходу игры
} TsettingsAI;

// структура с информацией о настройках игры
typedef struct str_theme {
	char* colorBgBase; // цвет основного фона
	char* colorBgMsg; // цвет фона сообщений
	char* colorBgTarget; // цвет фона выбранного объекта
	char* colorTextBase; // цвет основного текста
	char* colorTextMsg; // цвет текста сообщений
	char* colorTextTarget; // цвет специального текста
	char* colorSuit1; // цвет червовой и бубновой масти
	char* colorSuit2; // цвет пиковой и крестовой масти

	char userName[MAX_LEN_NICKNAME + 1]; // имя пользователя

	size_t musicTheme; // музыкальная тема
	size_t onMusicBg; // включена ли фоновая музыка
	size_t onSoundsWeather; // включены ли звуки погоды
	size_t onSounds; // включены ли прочие звуки

	size_t designTheme; // тема оформления интерфейса
	size_t typeWeather; // тип погоды
	size_t printChat; // выводить ли чат игры
	size_t messagesChat; // режим показа сообщений в чате игры
	size_t specialEffects; // выводить ли спецэффекты игры
	// улучшенный алгоритм интерактивности интерфейса игры
	size_t improvedAlgGameInterface; 

	size_t raiting; // рейтинг пользователя
	size_t levelUser; // уровень пользователя
	size_t countGames; // количество сыгранных игр
	size_t countWins; // количество побед
	size_t countLose; // количество поражений
	size_t minutsInGame; // количество минут в игре

	size_t resultsGames[4][6][2]; // матрица результатов игр
	size_t version; // версия игры
	size_t launch; // версия игры
} Ttheme;

// структура хрянящая точку вывода строки и ее длину
typedef struct str_rows {
	COORD pos; // координаты начала вывода строки
	size_t lenX; // длина строки
} Trows;

// массив двумерных строкодержащий название событийных эффектов и их описание
extern char optionsEffects[][2][300];
extern size_t countEffects; // кол-во событийных эффектов

// массив доступных для вызова команд 
extern char commandList[][50];
extern char commandListArgs[][50];
extern size_t countCommand;

#endif 