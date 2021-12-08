#if !defined(__ARTIFICAL_INTELLIG_H) 
#define __ARTIFICAL_INTELLIG_H 

// вспомогательные функции принятия решения ИИ
float GetProbailityHaveCards(size_t n, size_t k, size_t l);

// функции принятия решения ИИ
int GetMinPossibleCard(Tcard* a, size_t n, Tcard card, char m);
size_t GetLowCard(Tcard* a, size_t n, char m, size_t i);
int DecisionAIAttackEasy(TgameTable* pgame_table, Tcard* a, size_t k);
int DecisionAIThrowEasy(TgameTable* pgame_table, Tcard* a, size_t k);
int DecisionAI(Tcard* a, size_t na, size_t condition, size_t difficulty,
	Tcard* b, size_t nb, size_t c_deck, size_t c_p1, Tcard card, char m, size_t aix);

// вспомогательные функции для работы информацией ИИ
size_t GetRankCard(Tcard card, size_t m);
size_t GetSumRank(Tcard* a, size_t n, size_t m);

// получение информации со структуры ИИ
void MovingElMatrCards(uint8_t** a, Tcard card, size_t new_group);
size_t GetCountSuit(uint8_t(*a)[15], char m, size_t group);
size_t GetCountNom(uint8_t(*a)[15], size_t n, size_t group);
size_t GetCountGroup(uint8_t(*a)[15], size_t group);

// работа с ИИ
void InitStructAI(TAI* str, Tcard* a, size_t n, Tcard card);
void PrintStructAI(TAI* str);
int DecisionAI(TgameTable* pgame_table,
	TsettingsAI* psettings_ai, Tcard* a, size_t k);

#endif 