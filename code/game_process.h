#if !defined(__GAME_PROCESS_H) 
#define __GAME_PROCESS_H 

// работа со структурой информации игрового поля
size_t DeleteCard(Tcard* a, size_t n, size_t i);
void GetArrCards(Tcard* a);
int SearchSuit(Tcard* a, size_t n, char m);
size_t WhoseMove(Tcard** a, size_t count_players, char m);
void SwapCard(Tcard* a, Tcard* b);
size_t AceIsTrumpCard(Tcard* a, size_t n);
void InitNamePlayers(char(*a)[MAX_LEN_NICKNAME + 1], size_t n);
void InitStructCards(Tcards* pcards,
	TgameTable* pgame_table, size_t count);
void InitChat(char(**chat)[SIZE], size_t n);
void ChatClear(char(*chat)[SIZE], size_t n);
void InitGameSettingsAI(TsettingsAI* a, size_t difficulty);
void DeleteStructCards(Tcards* pcards, size_t k);

// процессы игры
size_t AddCard(Tcard* a, size_t n, Tcard card, size_t i);
size_t AddCards(Tcard* a, size_t na, size_t k, Tcard* b, size_t nb, char m);
size_t MoveCardsToK(Tcard* a, size_t* pna, size_t k, Tcard* b, size_t* pnb, char m);
void RedistribCards(Tcards* pcards, size_t count, TgameTable* pgame_table);
void RedistribCardsPass(Tcards* pcards, size_t count, TgameTable* pgame_table);
void MoveCardInArr(Tcard* a, size_t* na, size_t i, Tcard* b, size_t* nb);
int CardInArr(Tcard* a, size_t n, Tcard card);
size_t GetCountNonZerolArr(size_t* a, size_t n);
size_t CountElArrValue(size_t* a, size_t n, size_t count, size_t value);
size_t IsEqualElArr(size_t* a, size_t n);
void MoveToNextPlayer(size_t* p_param, size_t k, TgameTable* pgame_table);

// проверки на ошибки
size_t GetIndexSuit(char m);
size_t ChekingAllCards(Tcards* pcards, TgameTable* pGameTable,
	size_t* p_one, size_t* p_two);
size_t CardCanBeat(Tcard a, Tcard b, char m);
int ThereIsNominal(Tcard* a, size_t n, size_t k);

// вспомогательные функции
void GetMessageFromUser(char* s, COORD point, size_t size);
void UntilKeyIsPressedSpace();
void PlaySoundCard();

// работа с настройками игры
void SetTheme(Ttheme* ptheme, size_t i);
void MusicBgControl(size_t context, size_t on_music);
void CountTimeSpenInGame(char* fname, char* key, size_t* pvalue);

// работа с командами
int ArgsIsFit(char* args, char* types, size_t n);
void CallCommand(TgameTable* pGameTable, Tcards* Tcards, TsettingsAI* settingsAI[6],
	TblocksGame* pblocks, char* s_res, Ttheme* ptheme);
int CommandGetCommandList(TgameTable* pGameTable, Tblock block, Ttheme* ptheme);
int CommandGetColorList(TgameTable* pGameTable, Tblock block, Ttheme* ptheme);
int GetIndexPlayerByName(char(*name_player)[MAX_LEN_NICKNAME + 1], char* name);
void PrintMatrCardsAI(HANDLE h, uint8_t a[SIZE_LINE_AI][SIZE_COLUMN_AI], COORD point);
int CommandPrintMatrCardsAI(HANDLE h, TgameTable* pGameTable,
	TsettingsAI* settingsAI[6], Tblock* pblock, size_t* pi_player, Ttheme* ptheme);


#endif 