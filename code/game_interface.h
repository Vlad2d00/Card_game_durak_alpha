#if !defined(__GAME_INTERFACE_H) 
#define __GAME_INTERFACE_H 

#include "header.h"

// побочные функции для вывода карт
char GetchDigintyCard(size_t n);
char GetNomanalDigintyCard(char ch);
void ReadCard(char* s, Tcard* pa);
void PrintCard(Tcard a);
void PrintArrCard(Tcard* a, size_t n);
void StrPrintCardText(char* s, Tcard a);

// функции для выводла карт
void GetDistanceAndIndentCards(size_t* pdist, size_t* pindent, Tblock block, size_t n);
void PrintImgCards(HANDLE h, Tblock block, Tcard* a, size_t n, Ttheme* ptheme);
void PrintShirtCards(HANDLE h, Tblock block, size_t n, Ttheme* ptheme);
void RePrintImgRegionCards(HANDLE h, COORD point, Tcard* a,
	size_t n, size_t k, size_t distance, Ttheme* ptheme);
COORD GetPointCardBattle(size_t k, size_t* cond_battle, Tblock block);
void PrintCardsBattle(HANDLE h, Tblock block, Tcard* a,
	size_t n, size_t* cond_battle, size_t size, Ttheme* ptheme);
void GetHeaderNamePlayer(char* s, size_t k, TgameTable* pGameTable,
	Tblock block, char* cbg, char* ctext, Ttheme* ptheme);
Tblock GetBlockPlayer(size_t k, TgameTable* pGameTable, TblocksGame* pblocks);
void PrintCardsAndNamePlayer(HANDLE h, Tcards* a, size_t k, size_t face,
	TgameTable* pGameTable, TblocksGame* pblocks, Ttheme* ptheme);

// динамические эффекты
int CursoreCardGameTable(TblocksGame* pblocks, size_t n);
void PrintfChoiseCardGameTable(HANDLE h, COORD point, Tcard card, Ttheme* ptheme);
void PrintCellForCard(HANDLE h, Tblock* block, Tcard card, Ttheme* ptheme);
void GetCoordArrCards(size_t* pos_cards, size_t posX, size_t distance, size_t n);
void PrintBlinkingNamePlayer(HANDLE h, size_t k, TgameTable* pGameTable,
	TblocksGame* pblocks, Ttheme* ptheme);
void PrintEffectPlaceEl(HANDLE h, Tblock block, size_t time,
	char* cbg, char* ctext, Ttheme* ptheme);
void PrintEffectPlaceCard(HANDLE h, Tcard card, Tblock block, size_t time,
	char* cbg, char* ctext, Ttheme* ptheme);

// прочие элементы игрового стола
void PrintLargeMsg(HANDLE h, Tblock block, char(*strs)[100], size_t n,
	size_t time, size_t glow_time, char* cbg, char* ctext, char* ctarget, Ttheme* ptheme);
void UpdateTime(HANDLE h, COORD point, clock_t start);
void PrintHeaderGame(HANDLE h, TblocksGame* pblocks, TgameTable* pGameTable, Ttheme* ptheme);
void PrintInfoGame(HANDLE h, COORD point, TgameTable* pGameTable, Ttheme* ptheme);
size_t PrintMenuPause(HANDLE h, TblocksGame* pblocks, Ttheme* ptheme);
void PrintGameInterface(HANDLE h, TgameTable* pGameTable,
	Tcard** player, TblocksGame* pblocks, Ttheme* ptheme);
void IntroductionInGame(HANDLE h, TgameTable* pGameTable,
	Tcard** player, TblocksGame* pblocks, Ttheme* ptheme);
int InteractiveGameInterface(HANDLE h, TgameTable* pGameTable,
	Tcard** player, TblocksGame* pblocks, TsettingsAI* settingsAI[6], Ttheme* ptheme);

// работа с чатом
void PrintChat(HANDLE h, Tblock block, char(*chat)[SIZE], Ttheme* ptheme);
char* GetWord(char* w, char* s, size_t size);
void ChatMsgPosOffset(char(*a)[SIZE], size_t n);
void UpdateChat(char(*chat)[SIZE], Tblock block, char* s, Ttheme* ptheme);
void GetMsgForChat(char* s_out, char* s_in, char* name,
	char* color, Ttheme* ptheme);
int GetCommandFromStr(char* s, char* args);
int InputTextInChat(HANDLE h, COORD point, char* s, size_t len_input, Ttheme* ptheme);

#endif 