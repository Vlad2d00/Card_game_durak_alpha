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

// ����� �������
#define TRUE 1
#define FALSE 0
#define PI 3.14159265
#define EPS 0.00001

// �������� ���������
#define TITLE_PROGRAM "��������� ���� � ������ 0.3.0"
// ������ ���������
#define VERSION "Alpha 0.3.0" 
// ���� ��������� ����� ��� ������ � ������ ����������
#define FILE_PATH_SETTINGS "settings.bin" 
// ���� ���������� �����, �������������� ���������� � ��������� ����
#define FILE_PATH_SETTINGS_TXT "sourse\\settings.txt" 
// ���� ���������� ����� ��� ������ ����� ������ ����
#define FILE_PATH_GAMERULE_TXT "sourse\\gamerule.txt" 

// ������� �������� ����
#define SIZE 500 // ������ ����� ��� ���������� ����������
#define WIDTH 172 // ������ ������ ����������� ����
#define HEIGHT 50 // ������ ������ ����������� ����
// ����� ������ �������� ���� �� ��� y ��� ������������� ����
#define WIN_X0 p_allblocks->window.pos.X
 // ����� ������ �������� ���� �� ��� x ��� ������������� ����
#define WIN_Y0 p_allblocks->window.pos.Y

// ������� ���������
#define SIZE_DECK 36 // ������ ������ ����
#define K 6 // ���-�� ����, ������� �������� ������� ������ �� ������
#define SIZE_BATTLEFIELD 6 // ������ ���� ��� � ������
#define WIDTH_CRADS_BASE 72 // �������� ������ ������ ������� ����
#define WIDTH_CRADS_MEDIUM 56 // ������� ������ ������ ������� ����
#define WIDTH_CRADS_SMALL 48 // ������������ ������ ������ ������� ����
#define WIDTH_BATTLE 52 // ������ ���� ���
#define MAX_LEN_NICKNAME 20 // ������������ ����� ����� ������
#define MAX_LEN_MESSAGE 200 // ������������ ����� ��� ����� ���������
#define DISTANCE_BUTTON 2 // ���������� ����� ������������ ��������
#define WIDTH_BUTTON_MENU 55 // ������ ������ � ������� ����
#define HEIGHT_CHAT 24 // ������������ ���-�� ����� ����
// ������ ��������������� ���� � ���� ��������� ���
#define WIDTH_SIMULATION_INFO WIDTH / 2 

// ����������� ���������� ���������� ��������� ��� �� ���� ������
#define MAX_COUNT_SIMULATION 10000
// ��������� �������� ����� � ���� ����� "�������"
#define BOOK_START_PAGE 5

// ������ �� � ���� �������
#define SIZE_COLUMN_AI 18 // ���-�� ������� ������� ��
#define SIZE_LINE_AI 5 // ���-�� ����� ������� ��
#define CARDS_UNKNOWN 15 // ������� ����������� ����
#define CARDS_RETR 16 // ������� ���� � �����
#define CARDS_BATTLE 17 // ������� ���� �� ���� ���

// ������� ��������� ����� �������
#define SPEED_SWITCH_BUTTON 200 // �������� ����������� ����� �������� (��)
#define SPEED_CLICK 350 // �������� ����� (��)
#define SPEED_TRANSIT 900 // �������� �������� ����� ������ (��)
#define SPEED_ANSWER_ONLY_AI 75 // �������� ������� ������� � ������ "������ ��" (��)
#define DECISION_TIME_AI 2200 // �������� ������� �������� ������� �� (��)
#define TIME_PRESS_PASS 200 // ����� �������� ������ ���� ��� ��������� (��)
#define TIME_EFFECT_CARD 500 // ����� ������� ��������� �����
#define TIME_BLINKING_ANSWER 200 // ����� ������� ����� ������ ��� ������
#define TIME_CLEAR_BUF 150 // ����� �� ������ ������ �����

// �������� ���������
#define CHANCE_LIGHTNING 1300 // ���� ����� ������ ����� ������ �� ���-�� ���������� ������
// ��������� ����������� ������������� ������ (0...1.0)
#define START_COEFF_WEATHER 0

// ��������� ������ �� ������� ����
#define PROTECTION 0
#define ATTACK 1
#define PASS 2
#define CAN_BE_THROWN 3

// ������� ���� ������
#define EASY 0
#define NORMAL 1
#define HARD 2
#define UNREAL 3
#define USER 4
#define NONE_DIFF 5

// ������ ������ �������� ��������
#define GAME_STANDART 0
#define GAME_STANDART_SEE 1
#define GAME_AI 2
#define GAME_SIMULATION 3

// �������� ����
#define THEME_DAY 0
#define THEME_NIGHT 1
#define THEME_EAST 2
#define THEME_BLACK_BLUE 3
#define THEME_NEW_YEAR 4

// ��� ������
#define WEATHER_CLEAR 0
#define WEATHER_SNOW 1
#define WEATHER_RAIN 2

// ������ � ������� ����
#define MAIN_MENU_STORY 1
#define MAIN_MENU_CUSTOM_GAME 2
#define MAIN_MENU_SIMULATION 3
#define MAIN_MENU_SETTINGS 4
#define MAIN_MENU_EXIT 5
#define MAIN_MENU_GAME_RULE 6

// ������ � ���� ���������
#define SIMULATION_START 8
#define SIMULATION_GOTO_MENU 9
#define SIMULATION_STOP 10
#define SIMULATION_ANEW 11

// ������ � ���� ��������
#define SETTINGS_RE_NICKNAME 1
#define SETTINGS_RESET_PROGRESS 2
#define SETTINGS_GOTO_MENU 3

// ��������� ������
#define BUTTON_NONE 0 // ������ �� �������
#define BUTTON_HOVER 1 // ������� ������ ���� �� ������
#define BUTTON_CHOISE 2 // ������ ������
#define BUTTON_HOVER_KEY 3 // ������ �������: ������� � ������� ������
#define BUTTON_HOVER_CUR 4 // ������� ������ �������� (���� ��������� ������� � ������� ������)
#define BUTTON_INIT 5 // ������������� ������
#define BUTTON_OFF 6 // ��������� ������

// ������������ �������� �������� ����������
#define GAME_GOTO_MENU -2
#define GAME_EXECUTE_COMMAND -3
#define GAME_REQUEST_SOLUTION_AI -4
#define GAME_CONTINUE -5

// ������ � ���� �����
#define CONTINUE 1
#define CUSTOM_GAME_GOTO_MENU 2

// ������ � �������
#define CONTEXT_NONE 0
#define CONTEXT_MENU 1
#define CONTEXT_GAME 2
#define CONTEXT_PAUSE_GAME 3
#define CONTEXT_SIMULATION 4

// ���������� �������
#define EE_NONE 0 // ��� �������� ��������
#define EE_CHANGE_OF_TRUMP 1 // ����� ������ ������ ���
#define EE_RANDOM_CARD_EXCHANGE 2 // ��������� ������
#define EE_TRANSFERABLE 3 // ����������
#define EE_MAXIMUM_CARDS_IN_HAND 4 // ������� ����
#define EE_REVERSAL_OF_NOMINAL 5 // ����������� ���������
#define EE_BAN_ON_SUIT 6 // ���� �� �����
#define EE_MIXING_CARDS 7  // ��������� �� ������� �����
#define EE_SHORT_SUIT 8 // ������ �����
#define EE_ABOLITION_TRUMP 9 // ��������� ������
#define EE_TIME_LIMIT 10 // ����� ������� �������� ������� 
#define EE_CHANGE_COLOR_CARDS 11 // ������� �������

// �������, �������� � ���
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

// ��������� ��������� ������ ����������
#define ARGS_OK 0
#define ARGS_FEW -1
#define ARGS_MANY -2
#define COMMAND_NO_AVAILABLE -3
#define ERROR_NO_INIT_MATR_AI -4
#define ERROR_IS_INDEX_USER -5

/*���������� �������� "������", ���� � ������� 
������� start ������ ���� �� target �����������*/
#define TIMER(start, target) ((clock() - (start)) >= (target))

/*���������� ���������� ������, ������� ������ 
� ������� ������� start*/
#define TIME_SEC(start) (double)(( clock() - (start) ) / CLOCKS_PER_SEC)
/*���������� ���������� �����������, ������� ������
� ������� ������� start*/
#define TIME_MSEC(start) (clock_t)( clock() - (start) )

// ��������� � ������������ ����� ������ ������ ���� ����
typedef struct str_block {
	COORD pos; // ���������� ������ �������� (����� ������� ����)
	size_t lenX; // ����� �������� �� ��� X
	size_t lenY; // ����� �������� �� ��� Y
	size_t cond; // ��������� �����
} Tblock;

// ��������� � ����������� � ������� �������
typedef struct str_weather {
	Tblock window; // ������� ����
	char type; // ��� ������� ('*', ��� '|', ��� ' ')
	size_t change_speed; // �������� ��������� ������ (1...100)
	float step_change; // ��� ���������� ��������� (0...1.0)
	float coeff; // ����������� ��������� ��������� ������� (0...1.0)
	float max_coeff; // ������������ ����. ��������� ��������� ������� (0...1.0)
	float min_coeff; // ����������� ����. ��������� ��������� ������� (0...1.0)
	int direction_wind; // ���������� ����� (-1 ��� 1)

	char ch; // ������ ������� (*, |, ', $,)
	size_t angle; // ���� ������� (0...90)
	size_t fall_mess; // ������� ����������� ������� (1...100)
	size_t delay; // �������� ������� ������� (��)
	float count; // ���-�� ������� �� ��������

	clock_t time_start; // ����� ���������� ������ �������
	// ������� � ���������������� �������� �������
	char matr[HEIGHT][WIDTH + 1];

	// ������� �����������
	char matr_obstac[HEIGHT][WIDTH];
	// ������ ������� ����������� ��� ����
	char matr_obstac_footer[HEIGHT][WIDTH];

	char type_bg_sounds; // ��� ������� ������
	size_t shower; // ���� �� ������
} Tweather;

// ��������� � ����������� ��������� �������� ����
typedef struct str_blocks_menu {
	Tblock header; // �����
	Tblock buttons; // ������ �������� ����
	Tblock story; // ������ �������� ����
	Tblock custom_game; // ������ ������ ���� 
	Tblock simulation; // ������ ���������
	Tblock settings; // ������ ��������� 
	Tblock exit; // ������ �����
	Tblock book_rule; // ������ �������� �� ����� ������
	Tblock achievement_table; // ������� ����������

	Tblock* pwindow; // ������� ����
	Tblock* pversion; // ������� ������
	Tblock* pfooter; // ������
	Tblock* pcat; // ����������� ����
	COORD* pcursore; // ������� �������
} TblocksMainMenu;

// ��������� � ����������� ��������� ���� �������� ����� ����
typedef struct str_blocks_customgame {
	Tblock header; // ���������
	Tblock info; // ������� ��������
	Tblock table; // ������� �������� �������
	Tblock players[6]; // ������ �������� �������
	Tblock effect; // ���������� �������

	Tblock see_mode; // �������� ����� �����������
	Tblock only_ai; // �������� ����� ������ ��
	Tblock chat; // ��� 
	Tblock button_chat; // ������ ����
	Tblock input_chat; // ����������� ���� ����� ������ ����
	Tblock special_card; // �������� ����������� �����
	Tblock multiplayer; // �������� �����������

	Tblock start; // ������ ����� ����
	Tblock goto_menu; // ������ ������ � ������� ����

	Tblock* pwindow; // ������� ����
	Tblock* pversion; // ������� ������
	Tblock* pfooter; // ������
	Tblock* pcat; // ����������� ����
	COORD* pcursore; // ������� �������
} TblocksCustomGame;

// ��������� � ����������� ��������� ���� ��������� ���
typedef struct str_blocks_simulation {
	Tblock header; // ��������� ���� ���������
	Tblock info; // ������� �������� � �������� ���������
	Tblock table; // ������� �������� �������
	Tblock players[6]; // ������ �������� �������
	Tblock count_sim; // ������ �������� ���-�� ��������� ���
	Tblock start; // ������ ������� ���������
	Tblock goto_menu; // ������ ������ � ������� ����

	Tblock stop; // ������ ��������� ���������
	Tblock anew; // ������ ������ ��������� ���������

	Tblock* pwindow; // ������� ����
	Tblock* pversion; // ������� ������
	Tblock* pfooter; // ������
	Tblock* pcat; // ����������� ����
	COORD* pcursore; // ������� �������
} TblocksSimulation;

// ��������� � ����������� ��������� ���� ��������
typedef struct str_blocks_settings {
	Tblock header; // ���������
	Tblock table; // ������� �������
	Tblock table_weather; // ������� ������� ��� �������� ��������
	Tblock table_control_keys; // ������� ����������� ������

	Tblock nickname; // �������� �������
	Tblock reset_progress; // ����� ��������
	Tblock full_screen_mode; // ������������� �����

	Tblock theme; // ��������� ���� ���������� 
	Tblock theme_day; // ������� ���� ���������� 
	Tblock theme_night; // ������ ���� ���������� 
	Tblock theme_east; // ��������� ���� ���������� 
	Tblock theme_black_blue; // �����-����� ���� ���������� 
	Tblock theme_new_year; // ���������� ���� ���������� 

	Tblock weather; // ��������� �������� ��������
	Tblock weather_clear; // ������: ���
	Tblock weather_snow; // ������: ����
	Tblock weather_rain; // ������: �����

	Tblock volume; // ��������� ��������� ������
	Tblock music_bg; // ������� ������
	Tblock sounds_weather; // ����� ������
	Tblock sounds; // ������ �����

	Tblock game; // ��������� ������� ��������
	Tblock chat; // ���
	Tblock messages_chat; // ��������� � ��������� � ����
	Tblock effects; // ������� �����������
	Tblock improved_alg; // ���������������� �������� ���������� ��������� ����

	Tblock goto_menu; // ������ ������

	Tblock* pwindow; // ������� ����
	Tblock* pversion; // ������� ������
	Tblock* pfooter; // ������
	Tblock* pcat; // ����������� ����
	COORD* pcursore; // ������� �������

	Tblock table_input_name; // ������� ����� �����
} TblocksSettings;

// ��������� � ����������� ��������� ���� ������ ����
typedef struct str_blocks_gamerule {
	Tblock header; // ���������
	Tblock book; // �����
	Tblock voice_acting; // ������� ������
	Tblock invert_lighting; // ������������� ���������
	Tblock page_left; // ������ ������������ �������� �����
	Tblock page_right; // ������ ������������ �������� ������
	Tblock goto_menu; // ������ ������ � ������� ����

	Tblock* pwindow; // ������� ����
	Tblock* pversion; // ������� ������
	Tblock* pfooter; // ������
	Tblock* pcat; // ����������� ����
	COORD* pcursore; // ������� �������
} TblocksGameRule;

// ��������� � ����������� ��������� ������� ���� ����
typedef struct str_all_blocks {
	Tblock window; // ������� ����
	Tblock* pwindow;
	Tblock version; // ������� ������
	Tblock* pversion;
	Tblock footer; // ������
	Tblock* pfooter;
	Tblock cat; // ����������� ����
	Tblock* pcat;
	COORD cursore; // ������� �������
	COORD* pcursore;

	TblocksMainMenu mainMenu;
	TblocksCustomGame customGame;
	TblocksSimulation simulation;
	TblocksSettings settings;
	TblocksGameRule gameRule;
} TblocksMenu;

// ��������� � ����������� ��������� �������� �����
typedef struct str_blocks_game {
	Tblock window; // ������� ����
	/*��������� ������� ��� ��������� ��������� � ���������� 
	����� �� ���� ���*/
	size_t target_card; // ��������� ����� ������������
	// ���������� ������ ����� ������������ �� ��� X
	size_t pos_cards[SIZE_DECK]; 
	COORD time; // �����
	Tblock matr_cards_ai; // ������� ���� ������������� ��
	size_t index_matr_ai; // ������ ������ ��, ������� ���� �������� ��������

	Tblock header; // ����� ����
	char s_effect[100]; // �������� ����������� �������
	Tblock effect; // ���������� ������
	Tblock esc; // ����� ���� �����

	Tblock menu_block; // ���� �����
	Tblock menu_header; // ����� ���� �����
	Tblock menu_continue; // ���������� ����
	Tblock menu_exit; // ����� � ������� ����

	Tblock chat; // ���
	Tblock button_chat; // ������ ����
	Tblock input_chat; // ����������� ���� ����� ������ ����
	Tblock cards_deck; // ������ ���� ���� ��������
	Tblock cards_battle; // ���� ���
	Tblock card_special; // ����������� �����
	Tblock button_pass; // ������ ����

	Tblock cards_user; // ����� ������������
	Tblock cards_p2_2; // ����� 2-�� ������ ��� ���� ������

	Tblock cards_p2_3; // ����� 2-�� ������ ��� ���� ������
	Tblock cards_p3_3; // ����� 3-�� ������ ��� ���� ������

	Tblock cards_p2_4; // ����� 2-�� ������ ��� ���� ���������
	Tblock cards_p3_4; // ����� 3-�� ������ ��� ���� ���������
	Tblock cards_p4_4; // ����� 4-�� ������ ��� ���� ���������

	Tblock cards_p5_5; // ����� 5-�� ������ ��� ���� ��������
	Tblock cards_p6_6; // ����� 6-�� ������ ��� ���� ��������

	COORD cursore; // ������� �������
} TblocksGame;

// �����
typedef struct card {
	char m; // ����� �����
	uint8_t n; // ������� �����
} Tcard;

// ��������� � ����������� �� ������ ������� �� ������� ����
typedef struct str_cards {
	Tcard deck[SIZE_DECK]; // ������ ����� ������ ����
	Tcard retread[SIZE_DECK]; // ������ ���� � �����
	Tcard* player[6]; // ������ ���� �������
} Tcards;

// ��������� � ����������� �� ������� ���� ��� �������
typedef struct str_game_table {
	size_t user; // �����, �� �������� ������ ������������
	size_t count_players; // ����������� ���-�� �������
	size_t cur_count_players; // ������� ���-�� �������
	size_t mode; // ����� ������� ������
	size_t event_effect; // ���������� ������ ������� ������
	size_t special_card; // ����. ���� ������� ������ ��������
	size_t player_state[6]; // ������� ��������� �������
	size_t move; // ������ ������ ����������� ������� ���
	size_t defend_player; // �����, ��� �������� �����
	size_t priority; // �� ������ ������ ����� �����
	size_t game_start; // ���� ��������

	size_t c_deck; // ���-�� ���� � ����� ������
	size_t c_batt; // ���-�� ���� �� ���� ���
	Tcard battle[SIZE_DECK]; // ������ ���� ���� ���
	size_t c_retr; // ���-�� ���� � �����
	size_t c_player[6]; // ���-�� ���� �������
	
	char trump; // �������� �����
	Tcard bottom_card; // ������ ����� � ����� ������ ����, ������ ���� � ������ �������� ������
	size_t count_can_throw; // ������� ���� ��� ����� ��������� �� ���� ���
	size_t end_move; // ����� ����
	size_t end_game; // ����� ������� ������
	size_t move_number; // ����� ���� ������� ������
	size_t count_priority; // ���-�� ������� � ������� ������
	size_t pos_out_player[6]; // ������� ������ ������� �� ����

	clock_t time_start; // ����� ������ ����
	clock_t time_sec; // ������� ����� ���� � ��������

	char (*chat)[SIZE]; // ���
	size_t command; // �������, ������� ���� ������������ � ����
	char args[200]; // ��������� ��������� ������������� �������
	size_t cond_battle[SIZE_DECK]; // ��������� ���� �� ���� ���
	char name_player[6][MAX_LEN_NICKNAME + 1]; // ����� �������
	size_t count_wait_ms_AI; // ������� ����������� ����� ������ ��
} TgameTable;

// ��������� � �����������, ������� ������ �� �� ���� ����
typedef struct str_ai {
	// �������, ���������� ���������� � ������ � ����, ��������� ��
	uint8_t matr_cards[SIZE_LINE_AI][SIZE_COLUMN_AI];
	size_t sum_rank_ai; // ����� ������ ���� ��
	size_t rank_ai; // ������� ���� ���� ��

	size_t sum_rank_unknown; // ����� ������ ����������� ����
	size_t rank_unknown; // ������� ���� ����������� ����

	size_t sum_rank_enemy[6]; // ����� ������ ��������� ���� �����������
	size_t rank_enemy[6]; // ������� ���� ��������� ���� �����������

	// �������������� ����������� ������� ���� ������ ����� ����������
	uint8_t min_nom_enemy[6][4];
	Tcard card_cause[6]; // �����, �� ������� ������� ��������� �������
	size_t prev_cause[6]; // �����-������� ���� �������� �� ������� ���� � ����������
	size_t prev_c_batt; // ���������� ���-�� ���� �� ���� ���
	size_t prev_move_number; // ����� ���� �� ���������� ������

	size_t evaluation[SIZE_DECK]; // ������ ������ ���� �� ����� ��
} TAI;

// ��������� � ����������� ��
typedef struct str_settings_ai {
	size_t difficulty; // ������� ��������� ���� ��
	size_t init_ai; // ���� �� ������������� ������ ��
	struct str_ai info; // ��������� � �����������, ������� ������ �� �� ���� ����
} TsettingsAI;

// ��������� � ����������� � ���������� ����
typedef struct str_theme {
	char* colorBgBase; // ���� ��������� ����
	char* colorBgMsg; // ���� ���� ���������
	char* colorBgTarget; // ���� ���� ���������� �������
	char* colorTextBase; // ���� ��������� ������
	char* colorTextMsg; // ���� ������ ���������
	char* colorTextTarget; // ���� ������������ ������
	char* colorSuit1; // ���� �������� � �������� �����
	char* colorSuit2; // ���� ������� � ��������� �����

	char userName[MAX_LEN_NICKNAME + 1]; // ��� ������������

	size_t musicTheme; // ����������� ����
	size_t onMusicBg; // �������� �� ������� ������
	size_t onSoundsWeather; // �������� �� ����� ������
	size_t onSounds; // �������� �� ������ �����

	size_t designTheme; // ���� ���������� ����������
	size_t typeWeather; // ��� ������
	size_t printChat; // �������� �� ��� ����
	size_t messagesChat; // ����� ������ ��������� � ���� ����
	size_t specialEffects; // �������� �� ����������� ����
	// ���������� �������� ��������������� ���������� ����
	size_t improvedAlgGameInterface; 

	size_t raiting; // ������� ������������
	size_t levelUser; // ������� ������������
	size_t countGames; // ���������� ��������� ���
	size_t countWins; // ���������� �����
	size_t countLose; // ���������� ���������
	size_t minutsInGame; // ���������� ����� � ����

	size_t resultsGames[4][6][2]; // ������� ����������� ���
	size_t version; // ������ ����
	size_t launch; // ������ ����
} Ttheme;

// ��������� �������� ����� ������ ������ � �� �����
typedef struct str_rows {
	COORD pos; // ���������� ������ ������ ������
	size_t lenX; // ����� ������
} Trows;

// ������ ��������� �������������� �������� ���������� �������� � �� ��������
extern char optionsEffects[][2][300];
extern size_t countEffects; // ���-�� ���������� ��������

// ������ ��������� ��� ������ ������ 
extern char commandList[][50];
extern char commandListArgs[][50];
extern size_t countCommand;

#endif 