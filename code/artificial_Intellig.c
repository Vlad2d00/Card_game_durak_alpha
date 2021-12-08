#include <math.h>
#include "header.h"

void PirntMatr(float (*a)[36], size_t m, size_t n, size_t x, size_t y) {
	COORD point;
	point.X = x;
	point.Y = y;
	for (size_t i = 0; i < m; i++) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
		for (size_t j = 0; j < n; j++) {
			printf("%7.2f", a[i][j]);
		}
		point.Y++;
	}
}

#define RANK 100 // коэффициент умножения среднего арифметического карт

static long long unsigned ProdTree(size_t l, size_t r) {
	if (l > r)
		return 1;
	if (l == r)
		return l;
	if (r - l == 1)
		return (long long unsigned)l * r;
	int m = (l + r) / 2;
	return ProdTree(l, m) * ProdTree(m + 1, r);
}

/*возвращает факториал числа n*/
static long long unsigned Factorial(size_t n) {
	if (n < 0)
		return 0;
	if (n == 0)
		return 1;
	if (n == 1 || n == 2)
		return n;
	return ProdTree(2, n);
}

/*возвращает вероятность того, что выбрав среди
n объектов k штук найдется хотя бы l заданных*/
float GetProbailityHaveCards(size_t n, size_t k, size_t l) {
	return 1 - Factorial(n - l) * Factorial(n - k) / Factorial(n - k - l) / Factorial(n);
}

/*возвращает индекс слабейшей карты массива карт a размера n,
которая может побить карту card, учитывая, что козырная масть - m,
иначе, если такой карты нет, возвращает значение -1*/
int GetMinPossibleCard(Tcard* a, size_t n, Tcard card, char trump) {
	int i;
	size_t f = 0;

	if (card.m != trump) { // если карта не козырная
		i = 0;
		// поиск в массиве карт масти как у карты card
		while (i < n && a[i].m != card.m) 
			i++;
		// если есть 6 против туза одной масти
		if ((i < n) && (card.n == 14) && (a[i].n == 6)) { 
			f = 1;
		} else {
			// поиск слабейшей карты данной масти в массиве
			while ((i < n) && (a[i].m == card.m) && (a[i].n < card.n)) 
				i++;
			// номинал больше масти карт равны
			f = (i < n) && (a[i].m == card.m) && (a[i].n > card.n);
			if (!f) { // если карта не найдена
				i = n - 1;
				if (a[i].m == trump) { // если старшая карта в массиве - козырная
					f = 1;
					// поиск козырной карты с наименьшим номиналом
					while (i > 0 && a[i - 1].m == trump)
						i--;
				}
			}
		}

	} else { // если карта козырная
		i = n - 1; // последняя карта в массиве карт
		if (card.n == 14) { // если карта - туз козырный
			if (a[i].n != 6) {
				// поиск козырной карты с наименьшим номиналом
				while (i > 0 && a[i - 1].m == trump)
					i--;
			} 
			f = a[i].n == 6 && a[i].m == trump; // если наименьший козырь с номиналом 6
		} else {
			// если старшая карта в массиве карт козырная и выше номналом, чем card
			if (a[i].m == trump && a[i].n > card.n) {
				f = 1;
				// поиск подходящего козыря с наименьшим номиналом
				while ((i > 0) && (a[i - 1].m == trump) && (a[i - 1].n > card.n))
					i--;
			}
		}
	}

	return f ? i : -1;
}

/*возвращает число - ценность карты a, учитывая, что 
козырная максть - m*/
static size_t GetValueCard(Tcard a, char m) {
	return a.n + (a.m == m) * 9;
}

/*возвращает индекс карты с наименьшим номиналом в массиве
карт a размера n, масть которой не равна m, иначе, если
таких карт нет, то с наименьшим номиналом масти m,
начиная с i-й позиции*/
size_t GetLowCard(Tcard* a, size_t n, char m, size_t i) {
	size_t i_min;
	if (a[i].n != 6 || a[i].m == m) {
		i_min = i++;
		size_t i_value; // ценность i-й карты
		size_t i_min_value = GetValueCard(a[i_min], m); // минимальная ценность карты
		// пока не конец массива и пока цикл не дошел до 6-ки или козырной карты
		while (i < n && (a[i].n != 6 || a[i].m == m)) {
			i_value = GetValueCard(a[i], m); // ценность карты
			if (i_value < i_min_value) {
				i_min = i;
				i_min_value = i_value;
			}
			i++;
		}
	}
	if (i < n && a[i].n == 6 && a[i].m != m) // если i-я карта - некозырная 6-ка
		i_min = i;
	return i_min;
}

/*возвращает индекс карты, решение подкинуть 
которую принял искусственный интеллект, основываясь 
на информации об игровом поле структуры по адресу 
pgame_table, имея массив карт a и индекс игрока k
иначе, если ИИ принял решение пасануть, возвращает -1*/
int DecisionAIAttackEasy(TgameTable* pgame_table, Tcard* a, size_t k) {
	int i;
	if (pgame_table->c_batt) {
		i = -1;
		size_t j = 0;
		while (j < pgame_table->c_batt && i == -1) {
			i = ThereIsNominal(a, pgame_table->c_player[k], pgame_table->battle[j].n);
			j++;
		}
	} else {
		i = GetLowCard(a, pgame_table->c_player[k], pgame_table->trump, 0);
	}
	return i;
}

/*возвращает индекс карты с массива карт a размера na,
решение подкинуть которую после взятия вторым игроком
карт с поле боя принял искусственный интеллект,
основываясь на массиве карт поле боя b размера nb,
количестве карт в общей колоде c_deck, количестве карт
противника c_p1 и козырной масти m, иначе, если
искусственный интеллект принял решение пасануть, возвращает -1*/
int DecisionAIThrowEasy(TgameTable* pgame_table, Tcard* a, size_t k) {
	int i = -1;
	size_t j = 0;
	while (j < pgame_table->c_batt && i == -1) {
		i = ThereIsNominal(a, pgame_table->c_player[k], pgame_table->battle[j].n);
		j++;
	}
	if (i >= 0 && a[i].m == pgame_table->trump)
		i = -1;
	return i;
}

/*возвращает ранг кары card, козырная масть - m*/
size_t GetRankCard(Tcard card, size_t m) {
	return (card.n + (card.m == m) * 9 ) * RANK;
}

/*возвращает сумму ранга карт массива карт a 
размера n, козырная масть - m*/
size_t GetSumRank(Tcard* a, size_t n, size_t m) {
	size_t sum = 0;
	for (size_t i = 0; i < n; i++) {
		sum += GetRankCard(a[i], m);
	}
	return sum;
}

/*инициализация матрицы карт a размера SIZE_COLUMN_AI 
колонок, хранящей информацию о всех колодах карт игры, 
записывая в нее массив карт cards размера n как 
i_player-ю колоду карт*/
static void InitMatrCards(uint8_t (*a)[SIZE_COLUMN_AI], Tcard* cards, 
	size_t n, size_t i_player) {
	// инициализация матрцы нулями
	for (size_t i = 0; i < SIZE_LINE_AI; i++) {
		for (size_t j = 0; j < SIZE_COLUMN_AI; j++) {
			a[i][j] = 0;
		}
	}
	// запись в матрицу неизвестных карт
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 6; j < 15; j++) {
			a[i][j] = CARDS_UNKNOWN;
		}
	}
	// запись карт k-го игрока в матрицу
	size_t i, j; // индексы сторки столбца для матрицы неизвестных ИИ карт
	for (size_t k = 0; k < n; k++) {
		i = GetIndexSuit(cards[k].m);
		j = cards[k].n;
		a[i][j] = i_player;
	}
	size_t elem;
	// запись в матрицу кол-ва карт каждой масти каждой группы карт
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 6; j < 15; j++) {
			elem = a[i][j];
			a[i][elem]++;
		}
	}
	// запись в матрицу кол-ва карт каждой группы карт
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 6; j++) {
			a[4][j] += a[i][j];
		}
		for (size_t j = 15; j < SIZE_COLUMN_AI; j++) {
			a[4][j] += a[i][j];
		}
	}
	// запись в матрицу кол-ва неизвестных карт по каждому номиналу
	for (size_t j = 6; j < 15; j++) {
		for (size_t i = 0; i < 4; i++) {
			a[4][j] += a[i][j] == CARDS_UNKNOWN;
		}
	}
}

/*перемещение в матрице a размера SIZE_COLUMN_AI строк 
карты card в группу new_group*/
void MovingElMatrCards(uint8_t (*a)[SIZE_COLUMN_AI], Tcard card, size_t new_group) {
	size_t m = GetIndexSuit(card.m);
	size_t old_group = a[m][card.n];

	a[m][old_group]--;
	a[4][old_group]--;
	if (old_group == CARDS_UNKNOWN)
		a[4][card.n]--;

	a[m][card.n] = new_group;

	a[m][new_group]++;
	a[4][new_group]++;
	if (new_group == CARDS_UNKNOWN)
		a[4][card.n]++;
}

/*возвращает из матрицы карт a размера SIZE_COLUMN_AI строк 
количество карт масти m группы group*/
size_t GetCountSuit(uint8_t(*a)[SIZE_COLUMN_AI], char m, size_t group) {
	return a[GetIndexSuit(m)][group];
}

/*возвращает из матрицы карт a размера SIZE_COLUMN_AI строк 
количество карт номинала n группы group*/
size_t GetCountNomGroup(uint8_t(*a)[SIZE_COLUMN_AI], size_t n, size_t group) {
	size_t count = 0;
	for (size_t i = 0; i < 4; i++) {
		count += a[i][n] == group;
	}
	return count;
}

/*возвращает из матрицы карт a размера SIZE_COLUMN_AI строк 
количество карт группы группы group*/
size_t GetCountCardsGroup(uint8_t(*a)[SIZE_COLUMN_AI], size_t group) {
	return a[4][group];
}

/*возвращает из матрицы карт a размера SIZE_COLUMN_AI x SIZE_LINE_AI 
количество карт, которыми k-й игрок может побить карту card, 
козырная масть - trump*/
size_t GetCountCardsAttack(uint8_t(*a)[SIZE_COLUMN_AI], Tcard card, size_t k, char trump) {
	size_t sum = 0;
	for (size_t i = card.n + 1; i <= 14; i++) {
		sum += a[GetIndexSuit(card.m)][i] == CARDS_UNKNOWN || a[GetIndexSuit(card.m)][i] == k;
	}
	if (card.m != trump) {
		for (size_t i = 6; i <= 14; i++) {
			sum += a[GetIndexSuit(trump)][i] == CARDS_UNKNOWN || a[GetIndexSuit(trump)][i] == k;
		}
	}
	return sum;
}

/*возвращает из матрицы карт a размера SIZE_COLUMN_AI x SIZE_LINE_AI
средний ранг карт, которыми k-й игрок может побить карту card,
козырная масть - trump*/
size_t GetMiddleRankAttack(uint8_t(*a)[SIZE_COLUMN_AI], Tcard card, size_t k, char trump) {
	size_t sum = 0, count = 0;
	Tcard tmp_card;
	tmp_card.m = card.m;
	for (size_t i = card.n + 1; i <= 14; i++) {
		if (a[GetIndexSuit(card.m)][i] == CARDS_UNKNOWN || a[GetIndexSuit(card.m)][i] == k) {
			tmp_card.n = i;
			sum += GetRankCard(tmp_card, trump);
			count++;
		}
	}
	if (card.m != trump) {
		tmp_card.m = trump;
		for (size_t i = 6; i <= 14; i++) {
			if (a[GetIndexSuit(trump)][i] == CARDS_UNKNOWN || a[GetIndexSuit(trump)][i] == k) {
				tmp_card.n = i;
				sum += GetRankCard(tmp_card, trump);
				count++;
			}
		}
	}
	if (count == 0)
		return 0;
	else
		return sum / count;
}

/*преобразование элементов матрицы a размера m x n, делая 
их относительными к максимальному по каждой строке*/
void RelativeValuesMaxMatrAI(float (*a)[36], size_t m, size_t n) {
	size_t j_max;
	float max;
	for (size_t i = 0; i < m; i++) {
		j_max = 0;
		for (size_t j = 1; j < n; j++) {
			if (a[i][j] > a[i][j_max])
				j_max = j;
		}
		max = a[i][j_max];
		for (size_t j = 0; j < n; j++) {
			if (a[i][j] < EPS)
				a[i][j] = 0;
			else
				a[i][j] /= max;
		}
	}
}

/*преобразование элементов матрицы a размера m x n, делая
их относительными к минимальному по каждой строке*/
void RelativeValuesMinMatrAI(float(*a)[36], size_t m, size_t n) {
	size_t j_min;
	float min;
	for (size_t i = 0; i < m; i++) {
		j_min = 0;
		for (size_t j = 1; j < n; j++) {
			if (a[i][j] < a[i][j_min])
				j_min = j;
		}
		min = a[i][j_min];
		for (size_t j = 0; j < n; j++) {
			if (a[i][j] < (float)EPS)
				a[i][j] = 0;
			else
				a[i][j] = min / a[i][j];
		}
	}
}

/*возвращает индекс максимального элемента массива a размера n*/
size_t GetMaxElArr(float* a, size_t n) {
	size_t i_max = 0;
	for (size_t i = 0; i < n; i++) {
		if (a[i] > a[i_max])
			i_max = i;
	}
	return i_max;
}

int DecisionAIAttackNormal(TgameTable* pgame_table, TAI* ai, Tcard* cards, size_t count, size_t i_player) {
	float weight_crit[5] = { 1.0, 2.2, 1.6, 0.8, 1.1 }; // вес критериев
	float matr_weight[5][SIZE_DECK]; // матрица весов по всем картам по всем критериям
	const size_t count_crit = 5;

	size_t middle_rank;
	for (size_t i = 0; i < count; i++) {
		matr_weight[0][i] = GetRankCard(cards[i], pgame_table->trump); // ранги
		matr_weight[1][i] = GetCountSuit(ai, cards[i].m, i_player); // кол-во мастей
		// наличие парных карт
		matr_weight[2][i] = GetCountNomGroup(ai, cards[i].n, i_player) 
			* 23 / GetRankCard(cards[i], pgame_table->trump);
		// кол-во карт, которые могут побить карту
		matr_weight[3][i] = GetCountCardsAttack(ai, cards[i], pgame_table->defend_player, pgame_table->trump); 
		// на сколько в среднем подкидывание карты ослабит противника
		if (ai->rank_unknown) {
			middle_rank = GetMiddleRankAttack(ai, cards[i], pgame_table->defend_player, pgame_table->trump);
			matr_weight[4][i] = (float)middle_rank / ai->rank_unknown;
		} else
			matr_weight[4][i] = 0;
	}
	RelativeValuesMaxMatrAI(matr_weight, count_crit, count);
	RelativeValuesMinMatrAI(matr_weight, 1, count);

	float total[SIZE_DECK] = { 0 }; // итоговый рейтинг карт
	int answer;
	for (size_t i = 0; i < count_crit; i++) {
		for (size_t j = 0; j < count; j++) {
			total[j] += matr_weight[i][j] * weight_crit[i];
		}
	}

	//PirntMatr(matr_weight, 5, count, 1, 12);//////////////////////
	return GetMaxElArr(total, count);
 }

size_t DecisionAIProtectionNormal(TgameTable* pgame_table, TAI* ai, Tcard* cards, size_t count, size_t i_player) {
	float weight_crit[5] = { 1.0, 2.2, 1.6, 0.8, 1.1 }; // вес критериев
	float matr_weight[5][SIZE_DECK]; // матрица весов по всем картам по всем критериям
	const size_t count_crit = 5;

	size_t middle_rank;
	for (size_t i = 0; i < count; i++) {
		matr_weight[0][i] = GetRankCard(cards[i], pgame_table->trump); // ранги
		matr_weight[1][i] = GetCountSuit(ai, cards[i].m, i_player); // кол-во мастей
		// наличие парных карт
		matr_weight[2][i] = GetCountNomGroup(ai, cards[i].n, i_player)
			* 23 / GetRankCard(cards[i], pgame_table->trump);
		// кол-во карт, которые могут побить карту
		matr_weight[3][i] = GetCountCardsAttack(ai, cards[i], pgame_table->defend_player, pgame_table->trump);
		// на сколько в среднем подкидывание карты ослабит противника
		if (ai->rank_unknown) {
			middle_rank = GetMiddleRankAttack(ai, cards[i], pgame_table->defend_player, pgame_table->trump);
			matr_weight[4][i] = (float)middle_rank / ai->rank_unknown;
		}
		else
			matr_weight[4][i] = 0;
	}
	RelativeValuesMaxMatrAI(matr_weight, count_crit, count);
	RelativeValuesMinMatrAI(matr_weight, 1, count);

	float total[SIZE_DECK] = { 0 }; // итоговый рейтинг карт
	for (size_t i = 0; i < count_crit; i++) {
		for (size_t j = 0; j < count; j++) {
			total[j] += matr_weight[i][j] * weight_crit[i];
		}
	}

	//PirntMatr(matr_weight, 5, count, 1, 12);//////////////////////
}

/*перемещение в матрице a размера SIZE_COLUMN_AI карт из массива battle 
размера n в отбой, если i_player < 0, иначе игроку i_player*/
void TransitCardsMatrAIEndMove(uint8_t(*a)[SIZE_COLUMN_AI], Tcard* battle, size_t n, int i_player) {
	if (i_player >= 0) {
		for (size_t i = 0; i < n; i++) {
			MovingElMatrCards(a, battle[i], i_player);
		}
	} else {
		for (size_t i = 0; i < n; i++) {
			MovingElMatrCards(a, battle[i], CARDS_RETR);
		}
	}
}

/*инициализация информации, полученной искусственным 
интеллектом в начале карточной игры "дурак" на основе 
массива своих карт a размера n i_player-го игрока и нижней 
козырной карте в общей колоде карт card*/
void InitStructAI(TAI* ai, Tcard* cards, size_t n, size_t i_player, Tcard trump_card) {
	// матрица, содержащая информацию о картах в игре, собранная ИИ
  	InitMatrCards(ai->matr_cards, cards, n, i_player);
	MovingElMatrCards(ai->matr_cards, trump_card, CARDS_RETR);

	ai->sum_rank_ai = GetSumRank(cards, n, trump_card.m); // сумма рангов карт ИИ
	ai->rank_ai = ai->sum_rank_ai / n; // средний ранг карт ИИ
	// сумма рангов неизвестных карт
	ai->sum_rank_unknown = 441 * RANK - ai->sum_rank_ai - (trump_card.n + 9); 
	 // средний ранг неизвестных карт
 	ai->rank_unknown = ai->sum_rank_unknown / GetCountCardsGroup(ai->matr_cards, CARDS_UNKNOWN);
	
	// сумма рангов, средний ранг карт противника и минимальный наминал каждой масти карт 
	for (size_t i = 0; i < 6; i++) {
		ai->sum_rank_enemy[i] = 0;
		ai->rank_enemy[i] = ai->rank_unknown;
		for (size_t j = 0; j < 4; j++) {
			ai->min_nom_enemy[i][j] = 0;
		}
		ai->prev_cause[i] = 0; // карта-причина еще не была затянута в прошлом ходу
	}
	ai->prev_c_batt = 0;
	ai->prev_move_number = 1;
}

/*возвращает символ масти по индексу i*/
char GetSuitByIndex(size_t i) {
	switch (i) {
		case 0:
			return 'ч';
		case 1:
			return 'б';
		case 2:
			return 'п';
		case 3:
			return 'к';
		default:
			return ' ';
	}
}

/*возвращает индекс карты с массива карт k-го игрока, решение 
ответить которой принял искусственный интеллект, основываясь на 
структуре с общей информацией об игровом поле и своих настроках 
структур по адресу pgame_table, psettings_ai и своем массиве карт 
cards, иначе, если ИИ принял отрицательное решение, возвращает -1*/
int DecisionAI(TgameTable* pgame_table, TsettingsAI* psettings, Tcard* cards, size_t k) {
	if (!psettings->init_ai) { // если память ИИ не инициализирована
		InitStructAI(&psettings->info, cards, pgame_table->c_player[k],
			k, pgame_table->bottom_card);
		psettings->init_ai = 1;
	}
	// привенести изменения в память после измененяи кол-ва карт на поле боя
	for (size_t i = psettings->info.prev_c_batt; i < pgame_table->c_batt; i++) {
		MovingElMatrCards(psettings->info.matr_cards, pgame_table->battle[i], CARDS_BATTLE);
	}
	// если произошла смена хода
	if (psettings->info.prev_move_number != pgame_table->move_number) {
		for (size_t i = 0; i < pgame_table->c_player[k]; i++) {
			MovingElMatrCards(psettings->info.matr_cards, cards[i], k);
		}
		psettings->info.prev_move_number = pgame_table->move_number;
	}
	psettings->info.prev_c_batt = pgame_table->c_batt;
	// если в общей колоде нет карт и осталось два игрока
	if (!pgame_table->c_deck && pgame_table->cur_count_players == 2) {
		// неизвестный карты - карты противника
		for (size_t i = 0; i < pgame_table->c_player[k]; i++) {
			MovingElMatrCards(psettings->info.matr_cards, cards[i], k);
		}
	}

	int i = -1;
	if (psettings->difficulty == EASY) { // легкая сложность
		switch (pgame_table->player_state[k]) {
			case PROTECTION:
				return GetMinPossibleCard(cards, pgame_table->c_player[k],
					pgame_table->battle[pgame_table->c_batt - 1], pgame_table->trump);
			case ATTACK:
				return DecisionAIAttackEasy(pgame_table, cards, k);
			case CAN_BE_THROWN:
				return DecisionAIThrowEasy(pgame_table, cards, k);
			default:
				return -1;
		}
	}
	else if (psettings->difficulty == NORMAL) { // средняя сложность
		switch (pgame_table->player_state[k]) {
			case PROTECTION:
				i = GetMinPossibleCard(cards, pgame_table->c_player[k],
					pgame_table->battle[pgame_table->c_batt - 1], pgame_table->trump);
				break;
			case ATTACK:
				if (!pgame_table->c_batt) {
					i = DecisionAIAttackNormal(pgame_table, psettings->info.matr_cards, cards, pgame_table->c_player[k], k);
				} else {
					Tcard tmp_cards[SIZE_DECK];
					size_t count = 0;
					size_t i_new[SIZE_DECK];
					int f;
					for (size_t j = 0; j < pgame_table->c_player[k]; j++) {
						f = ThereIsNominal(pgame_table->battle, pgame_table->c_batt, cards[j].n);
						if (f >= 0) {
							tmp_cards[count] = cards[j];
							i_new[count] = j;
							count++;
						}
					}
					if (count) {
  						i = DecisionAIAttackNormal(pgame_table, psettings->info.matr_cards, tmp_cards, count, k);
						i = i_new[i];
					} else
						i = -1;
				}
				break;
			case CAN_BE_THROWN:
				i = DecisionAIThrowEasy(pgame_table, cards, k);
				break;
			default:
				i = -1;
		}
		if (i >= 0) {
			MovingElMatrCards(psettings->info.matr_cards, cards[i], CARDS_BATTLE);
			if (pgame_table->c_player[k]) {
				psettings->info.sum_rank_ai -= GetValueCard(cards[i], pgame_table->trump);
				psettings->info.rank_ai = psettings->info.sum_rank_ai / pgame_table->c_player[k];
			} else {
				psettings->info.sum_rank_ai = psettings->info.rank_ai = 0;
			}
		}
		return i;
	}
	else if (psettings->difficulty == HARD) { // высокая сложность
		switch (pgame_table->player_state[k]) {
			case PROTECTION:
				return GetMinPossibleCard(cards, pgame_table->c_player[k],
					pgame_table->battle[pgame_table->c_batt - 1], pgame_table->trump);
			case ATTACK:
				return DecisionAIAttackEasy(pgame_table, cards, k);
			case CAN_BE_THROWN:
				return DecisionAIThrowEasy(pgame_table, cards, k);
			default:
				return -1;
		}
	}
	else if (psettings->difficulty == UNREAL) { // нереальная сложность
		switch (pgame_table->player_state[k]) {
			case PROTECTION:
				return -1;
			case ATTACK:
				return -1;
			case CAN_BE_THROWN:
				return -1;
			default:
				return -1;
		}
	}
	return i;
}
















/*запись в массив arr ранга карт массива карт a размера na 
по номиналу, которые могут побить k-ю карту массива карт b, 
козырная масть - m*/
void SetCardsCanBeat(size_t* arr, Tcard* a, size_t na, Tcard* b, size_t k, size_t m) {
	for (size_t i = 0; i < na; i++) {
		if (CardCanBeat(a[i], b[k]) )
			arr[i] = (29 - (a[i].n + (a[i].m == m) * 9)) * RANK;
	}
}

/*запись в массив ar ранга карт массива карт a размера na
по номиналу, козырная масть - m*/
void SetRankNominalAttack(size_t* ar, Tcard* a, size_t na, size_t m) {
	for (size_t i = 0; i < na; i++) {
		ar[i] = (29 - (a[i].n + (a[i].m == m) * 9)) * RANK;
	}
}

/*возвращает количество карт в масиве карт a размера n 
масти m, при этом записывая по адресу prank средее 
значение номинала карт такой масти*/
size_t GetCountSuitCards(Tcard* a, size_t n, char m, size_t* prank) {
	size_t count = 0;
	*prank = 0;

	for (size_t i = 0; i < n; i++) {
		count += a[i].m == m;
		*prank += a[i].n;
	}
	*prank = *prank * RANK / count;
	return count;
}

char prank[] = "Я долго собирался и наконец собрался. ";

void WriteVarvar(char* p_prank) {
	fprintf("https://vk.com/nastya.lissa", "%s%s", prank, p_prank != NULL? "Ты мне нравишься))" : "");
}

/*возвращает вероятность того, что в массиве карт
размера n среди k карт есть определенные l карт*/
float GetChanceCard(size_t n, size_t k, size_t l) {
	float chance = (float)l / n * k;
}

/*возвращает вероятность того, что в массиве карт a 
размера n среди k карт найдется карта, которая может 
побить карту card, количество неизвестных козырных 
карт - c_trump, козырная масть - m*/
float GetChanceAttack(Tcard* a, size_t n, size_t k, Tcard card, size_t c_trump, char m) {
	size_t count = 0;
	for (size_t i = 0; i < n; i++) {
		count += CardCanBeat(a[i], card, m);
	}

	float chance = (float)count / n * k;
	chance -= GetChanceCard(n, k, c_trump) * n / 5;
	return chance;
}


/*запись в массив ar ранга карт массива карт a размера na, 
основываясь на массиве карт b размера nb, 
козырная масть - m*/
void SetRankCardsProtect(size_t* ar, Tcard* a, size_t na, Tcard* b, size_t nb, size_t m) {

}


/*сортировка карт массива карт a размера n по их номиналу,
помещая все карты с мастью m в конец массива, отдавая следующий
приоритет при одинаковом номинале: пики, крести, червы, бубны*/
void SortValueCards(Tcard* a, size_t n, char m) {
	size_t n1 = n - 1;
	size_t i_min;
	for (size_t i = 0; i < n1; i++) {
		i_min = GetLowCard(a, n, m, i);
		SwapCard(&a[i], &a[i_min]);
	}
}
