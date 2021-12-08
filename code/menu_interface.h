#if !defined(__MENU_INTERFACE_H) 
#define __MENU_INTERFACE_H 

#include "header.h"

// вспомогательные функции
void SetDifficultyInStr(char* s, size_t k, size_t difficulty);
void PrintTableChoiseAI(HANDLE h, Tblock* blocks_player, size_t* pcount_players,
	size_t* diff, char name[6][MAX_LEN_NICKNAME + 1], Ttheme* ptheme);
int GetIndexNumberPointer(size_t* a[20], size_t n, size_t value);
COORD GetIndexNumberPointerMatr(size_t* (*a)[5], size_t m, size_t n, size_t value);
long PrintTextFromFile(char* fname, long pos, HANDLE h, Trows a[2][32], size_t n, Ttheme* ptheme);
void PrintFooterMainMenu(HANDLE h, Tblock block1, Tblock block2);
void SetBlockAchievementTableMatr(char a[HEIGHT][WIDTH], Tblock block, char ch);

// эффекты переходов между окнами
void PrintTransitionEffect(HANDLE h, COORD point, Ttheme* ptheme);
void TransitionDesignTheme(HANDLE h, COORD point, Ttheme* ptheme);

// вызовы интерактивных меню
size_t PrintWindowMainMenu(HANDLE h, TblocksMainMenu* pblocks,
	Tweather* pweather, Ttheme* ptheme);
size_t PrintWindowCustomGame(HANDLE h, TblocksCustomGame* pblocks,
	Tweather* pweather, TgameTable* pGameTable, size_t* difficulty, Ttheme* ptheme);
size_t PrintWindowSimulation(HANDLE h, TblocksSimulation* pblocks,
	Tweather* pweather, TgameTable* pGameTable, size_t* difficulty, Ttheme* ptheme);
size_t PrintWindowSettings(HANDLE h, TblocksSettings* pblocks, Tweather* pweather, Ttheme* ptheme);
void PrintWindowGameRule(HANDLE h, TblocksGameRule* pblocks, Ttheme* ptheme);
void InputNameFromUser(HANDLE h, TblocksSettings* pblocks,
	Tweather* pweather, char* name, Ttheme* ptheme);
void HelloUser(HANDLE h, TblocksSettings* pblocks, Tweather* pweather,
	char* name, size_t first_launch, Ttheme* ptheme);

#endif 