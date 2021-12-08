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

#define RANK 100 // ����������� ��������� �������� ��������������� ����

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

/*���������� ��������� ����� n*/
static long long unsigned Factorial(size_t n) {
	if (n < 0)
		return 0;
	if (n == 0)
		return 1;
	if (n == 1 || n == 2)
		return n;
	return ProdTree(2, n);
}

/*���������� ����������� ����, ��� ������ �����
n �������� k ���� �������� ���� �� l ��������*/
float GetProbailityHaveCards(size_t n, size_t k, size_t l) {
	return 1 - Factorial(n - l) * Factorial(n - k) / Factorial(n - k - l) / Factorial(n);
}

/*���������� ������ ��������� ����� ������� ���� a ������� n,
������� ����� ������ ����� card, ��������, ��� �������� ����� - m,
�����, ���� ����� ����� ���, ���������� �������� -1*/
int GetMinPossibleCard(Tcard* a, size_t n, Tcard card, char trump) {
	int i;
	size_t f = 0;

	if (card.m != trump) { // ���� ����� �� ��������
		i = 0;
		// ����� � ������� ���� ����� ��� � ����� card
		while (i < n && a[i].m != card.m) 
			i++;
		// ���� ���� 6 ������ ���� ����� �����
		if ((i < n) && (card.n == 14) && (a[i].n == 6)) { 
			f = 1;
		} else {
			// ����� ��������� ����� ������ ����� � �������
			while ((i < n) && (a[i].m == card.m) && (a[i].n < card.n)) 
				i++;
			// ������� ������ ����� ���� �����
			f = (i < n) && (a[i].m == card.m) && (a[i].n > card.n);
			if (!f) { // ���� ����� �� �������
				i = n - 1;
				if (a[i].m == trump) { // ���� ������� ����� � ������� - ��������
					f = 1;
					// ����� �������� ����� � ���������� ���������
					while (i > 0 && a[i - 1].m == trump)
						i--;
				}
			}
		}

	} else { // ���� ����� ��������
		i = n - 1; // ��������� ����� � ������� ����
		if (card.n == 14) { // ���� ����� - ��� ��������
			if (a[i].n != 6) {
				// ����� �������� ����� � ���������� ���������
				while (i > 0 && a[i - 1].m == trump)
					i--;
			} 
			f = a[i].n == 6 && a[i].m == trump; // ���� ���������� ������ � ��������� 6
		} else {
			// ���� ������� ����� � ������� ���� �������� � ���� ��������, ��� card
			if (a[i].m == trump && a[i].n > card.n) {
				f = 1;
				// ����� ����������� ������ � ���������� ���������
				while ((i > 0) && (a[i - 1].m == trump) && (a[i - 1].n > card.n))
					i--;
			}
		}
	}

	return f ? i : -1;
}

/*���������� ����� - �������� ����� a, ��������, ��� 
�������� ������ - m*/
static size_t GetValueCard(Tcard a, char m) {
	return a.n + (a.m == m) * 9;
}

/*���������� ������ ����� � ���������� ��������� � �������
���� a ������� n, ����� ������� �� ����� m, �����, ����
����� ���� ���, �� � ���������� ��������� ����� m,
������� � i-� �������*/
size_t GetLowCard(Tcard* a, size_t n, char m, size_t i) {
	size_t i_min;
	if (a[i].n != 6 || a[i].m == m) {
		i_min = i++;
		size_t i_value; // �������� i-� �����
		size_t i_min_value = GetValueCard(a[i_min], m); // ����������� �������� �����
		// ���� �� ����� ������� � ���� ���� �� ����� �� 6-�� ��� �������� �����
		while (i < n && (a[i].n != 6 || a[i].m == m)) {
			i_value = GetValueCard(a[i], m); // �������� �����
			if (i_value < i_min_value) {
				i_min = i;
				i_min_value = i_value;
			}
			i++;
		}
	}
	if (i < n && a[i].n == 6 && a[i].m != m) // ���� i-� ����� - ���������� 6-��
		i_min = i;
	return i_min;
}

/*���������� ������ �����, ������� ��������� 
������� ������ ������������� ���������, ����������� 
�� ���������� �� ������� ���� ��������� �� ������ 
pgame_table, ���� ������ ���� a � ������ ������ k
�����, ���� �� ������ ������� ��������, ���������� -1*/
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

/*���������� ������ ����� � ������� ���� a ������� na,
������� ��������� ������� ����� ������ ������ �������
���� � ���� ��� ������ ������������� ���������,
����������� �� ������� ���� ���� ��� b ������� nb,
���������� ���� � ����� ������ c_deck, ���������� ����
���������� c_p1 � �������� ����� m, �����, ����
������������� ��������� ������ ������� ��������, ���������� -1*/
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

/*���������� ���� ���� card, �������� ����� - m*/
size_t GetRankCard(Tcard card, size_t m) {
	return (card.n + (card.m == m) * 9 ) * RANK;
}

/*���������� ����� ����� ���� ������� ���� a 
������� n, �������� ����� - m*/
size_t GetSumRank(Tcard* a, size_t n, size_t m) {
	size_t sum = 0;
	for (size_t i = 0; i < n; i++) {
		sum += GetRankCard(a[i], m);
	}
	return sum;
}

/*������������� ������� ���� a ������� SIZE_COLUMN_AI 
�������, �������� ���������� � ���� ������� ���� ����, 
��������� � ��� ������ ���� cards ������� n ��� 
i_player-� ������ ����*/
static void InitMatrCards(uint8_t (*a)[SIZE_COLUMN_AI], Tcard* cards, 
	size_t n, size_t i_player) {
	// ������������� ������ ������
	for (size_t i = 0; i < SIZE_LINE_AI; i++) {
		for (size_t j = 0; j < SIZE_COLUMN_AI; j++) {
			a[i][j] = 0;
		}
	}
	// ������ � ������� ����������� ����
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 6; j < 15; j++) {
			a[i][j] = CARDS_UNKNOWN;
		}
	}
	// ������ ���� k-�� ������ � �������
	size_t i, j; // ������� ������ ������� ��� ������� ����������� �� ����
	for (size_t k = 0; k < n; k++) {
		i = GetIndexSuit(cards[k].m);
		j = cards[k].n;
		a[i][j] = i_player;
	}
	size_t elem;
	// ������ � ������� ���-�� ���� ������ ����� ������ ������ ����
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 6; j < 15; j++) {
			elem = a[i][j];
			a[i][elem]++;
		}
	}
	// ������ � ������� ���-�� ���� ������ ������ ����
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 6; j++) {
			a[4][j] += a[i][j];
		}
		for (size_t j = 15; j < SIZE_COLUMN_AI; j++) {
			a[4][j] += a[i][j];
		}
	}
	// ������ � ������� ���-�� ����������� ���� �� ������� ��������
	for (size_t j = 6; j < 15; j++) {
		for (size_t i = 0; i < 4; i++) {
			a[4][j] += a[i][j] == CARDS_UNKNOWN;
		}
	}
}

/*����������� � ������� a ������� SIZE_COLUMN_AI ����� 
����� card � ������ new_group*/
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

/*���������� �� ������� ���� a ������� SIZE_COLUMN_AI ����� 
���������� ���� ����� m ������ group*/
size_t GetCountSuit(uint8_t(*a)[SIZE_COLUMN_AI], char m, size_t group) {
	return a[GetIndexSuit(m)][group];
}

/*���������� �� ������� ���� a ������� SIZE_COLUMN_AI ����� 
���������� ���� �������� n ������ group*/
size_t GetCountNomGroup(uint8_t(*a)[SIZE_COLUMN_AI], size_t n, size_t group) {
	size_t count = 0;
	for (size_t i = 0; i < 4; i++) {
		count += a[i][n] == group;
	}
	return count;
}

/*���������� �� ������� ���� a ������� SIZE_COLUMN_AI ����� 
���������� ���� ������ ������ group*/
size_t GetCountCardsGroup(uint8_t(*a)[SIZE_COLUMN_AI], size_t group) {
	return a[4][group];
}

/*���������� �� ������� ���� a ������� SIZE_COLUMN_AI x SIZE_LINE_AI 
���������� ����, �������� k-� ����� ����� ������ ����� card, 
�������� ����� - trump*/
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

/*���������� �� ������� ���� a ������� SIZE_COLUMN_AI x SIZE_LINE_AI
������� ���� ����, �������� k-� ����� ����� ������ ����� card,
�������� ����� - trump*/
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

/*�������������� ��������� ������� a ������� m x n, ����� 
�� �������������� � ������������� �� ������ ������*/
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

/*�������������� ��������� ������� a ������� m x n, �����
�� �������������� � ������������ �� ������ ������*/
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

/*���������� ������ ������������� �������� ������� a ������� n*/
size_t GetMaxElArr(float* a, size_t n) {
	size_t i_max = 0;
	for (size_t i = 0; i < n; i++) {
		if (a[i] > a[i_max])
			i_max = i;
	}
	return i_max;
}

int DecisionAIAttackNormal(TgameTable* pgame_table, TAI* ai, Tcard* cards, size_t count, size_t i_player) {
	float weight_crit[5] = { 1.0, 2.2, 1.6, 0.8, 1.1 }; // ��� ���������
	float matr_weight[5][SIZE_DECK]; // ������� ����� �� ���� ������ �� ���� ���������
	const size_t count_crit = 5;

	size_t middle_rank;
	for (size_t i = 0; i < count; i++) {
		matr_weight[0][i] = GetRankCard(cards[i], pgame_table->trump); // �����
		matr_weight[1][i] = GetCountSuit(ai, cards[i].m, i_player); // ���-�� ������
		// ������� ������ ����
		matr_weight[2][i] = GetCountNomGroup(ai, cards[i].n, i_player) 
			* 23 / GetRankCard(cards[i], pgame_table->trump);
		// ���-�� ����, ������� ����� ������ �����
		matr_weight[3][i] = GetCountCardsAttack(ai, cards[i], pgame_table->defend_player, pgame_table->trump); 
		// �� ������� � ������� ������������ ����� ������� ����������
		if (ai->rank_unknown) {
			middle_rank = GetMiddleRankAttack(ai, cards[i], pgame_table->defend_player, pgame_table->trump);
			matr_weight[4][i] = (float)middle_rank / ai->rank_unknown;
		} else
			matr_weight[4][i] = 0;
	}
	RelativeValuesMaxMatrAI(matr_weight, count_crit, count);
	RelativeValuesMinMatrAI(matr_weight, 1, count);

	float total[SIZE_DECK] = { 0 }; // �������� ������� ����
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
	float weight_crit[5] = { 1.0, 2.2, 1.6, 0.8, 1.1 }; // ��� ���������
	float matr_weight[5][SIZE_DECK]; // ������� ����� �� ���� ������ �� ���� ���������
	const size_t count_crit = 5;

	size_t middle_rank;
	for (size_t i = 0; i < count; i++) {
		matr_weight[0][i] = GetRankCard(cards[i], pgame_table->trump); // �����
		matr_weight[1][i] = GetCountSuit(ai, cards[i].m, i_player); // ���-�� ������
		// ������� ������ ����
		matr_weight[2][i] = GetCountNomGroup(ai, cards[i].n, i_player)
			* 23 / GetRankCard(cards[i], pgame_table->trump);
		// ���-�� ����, ������� ����� ������ �����
		matr_weight[3][i] = GetCountCardsAttack(ai, cards[i], pgame_table->defend_player, pgame_table->trump);
		// �� ������� � ������� ������������ ����� ������� ����������
		if (ai->rank_unknown) {
			middle_rank = GetMiddleRankAttack(ai, cards[i], pgame_table->defend_player, pgame_table->trump);
			matr_weight[4][i] = (float)middle_rank / ai->rank_unknown;
		}
		else
			matr_weight[4][i] = 0;
	}
	RelativeValuesMaxMatrAI(matr_weight, count_crit, count);
	RelativeValuesMinMatrAI(matr_weight, 1, count);

	float total[SIZE_DECK] = { 0 }; // �������� ������� ����
	for (size_t i = 0; i < count_crit; i++) {
		for (size_t j = 0; j < count; j++) {
			total[j] += matr_weight[i][j] * weight_crit[i];
		}
	}

	//PirntMatr(matr_weight, 5, count, 1, 12);//////////////////////
}

/*����������� � ������� a ������� SIZE_COLUMN_AI ���� �� ������� battle 
������� n � �����, ���� i_player < 0, ����� ������ i_player*/
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

/*������������� ����������, ���������� ������������� 
����������� � ������ ��������� ���� "�����" �� ������ 
������� ����� ���� a ������� n i_player-�� ������ � ������ 
�������� ����� � ����� ������ ���� card*/
void InitStructAI(TAI* ai, Tcard* cards, size_t n, size_t i_player, Tcard trump_card) {
	// �������, ���������� ���������� � ������ � ����, ��������� ��
  	InitMatrCards(ai->matr_cards, cards, n, i_player);
	MovingElMatrCards(ai->matr_cards, trump_card, CARDS_RETR);

	ai->sum_rank_ai = GetSumRank(cards, n, trump_card.m); // ����� ������ ���� ��
	ai->rank_ai = ai->sum_rank_ai / n; // ������� ���� ���� ��
	// ����� ������ ����������� ����
	ai->sum_rank_unknown = 441 * RANK - ai->sum_rank_ai - (trump_card.n + 9); 
	 // ������� ���� ����������� ����
 	ai->rank_unknown = ai->sum_rank_unknown / GetCountCardsGroup(ai->matr_cards, CARDS_UNKNOWN);
	
	// ����� ������, ������� ���� ���� ���������� � ����������� ������� ������ ����� ���� 
	for (size_t i = 0; i < 6; i++) {
		ai->sum_rank_enemy[i] = 0;
		ai->rank_enemy[i] = ai->rank_unknown;
		for (size_t j = 0; j < 4; j++) {
			ai->min_nom_enemy[i][j] = 0;
		}
		ai->prev_cause[i] = 0; // �����-������� ��� �� ���� �������� � ������� ����
	}
	ai->prev_c_batt = 0;
	ai->prev_move_number = 1;
}

/*���������� ������ ����� �� ������� i*/
char GetSuitByIndex(size_t i) {
	switch (i) {
		case 0:
			return '�';
		case 1:
			return '�';
		case 2:
			return '�';
		case 3:
			return '�';
		default:
			return ' ';
	}
}

/*���������� ������ ����� � ������� ���� k-�� ������, ������� 
�������� ������� ������ ������������� ���������, ����������� �� 
��������� � ����� ����������� �� ������� ���� � ����� ��������� 
�������� �� ������ pgame_table, psettings_ai � ����� ������� ���� 
cards, �����, ���� �� ������ ������������� �������, ���������� -1*/
int DecisionAI(TgameTable* pgame_table, TsettingsAI* psettings, Tcard* cards, size_t k) {
	if (!psettings->init_ai) { // ���� ������ �� �� ����������������
		InitStructAI(&psettings->info, cards, pgame_table->c_player[k],
			k, pgame_table->bottom_card);
		psettings->init_ai = 1;
	}
	// ���������� ��������� � ������ ����� ��������� ���-�� ���� �� ���� ���
	for (size_t i = psettings->info.prev_c_batt; i < pgame_table->c_batt; i++) {
		MovingElMatrCards(psettings->info.matr_cards, pgame_table->battle[i], CARDS_BATTLE);
	}
	// ���� ��������� ����� ����
	if (psettings->info.prev_move_number != pgame_table->move_number) {
		for (size_t i = 0; i < pgame_table->c_player[k]; i++) {
			MovingElMatrCards(psettings->info.matr_cards, cards[i], k);
		}
		psettings->info.prev_move_number = pgame_table->move_number;
	}
	psettings->info.prev_c_batt = pgame_table->c_batt;
	// ���� � ����� ������ ��� ���� � �������� ��� ������
	if (!pgame_table->c_deck && pgame_table->cur_count_players == 2) {
		// ����������� ����� - ����� ����������
		for (size_t i = 0; i < pgame_table->c_player[k]; i++) {
			MovingElMatrCards(psettings->info.matr_cards, cards[i], k);
		}
	}

	int i = -1;
	if (psettings->difficulty == EASY) { // ������ ���������
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
	else if (psettings->difficulty == NORMAL) { // ������� ���������
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
	else if (psettings->difficulty == HARD) { // ������� ���������
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
	else if (psettings->difficulty == UNREAL) { // ���������� ���������
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
















/*������ � ������ arr ����� ���� ������� ���� a ������� na 
�� ��������, ������� ����� ������ k-� ����� ������� ���� b, 
�������� ����� - m*/
void SetCardsCanBeat(size_t* arr, Tcard* a, size_t na, Tcard* b, size_t k, size_t m) {
	for (size_t i = 0; i < na; i++) {
		if (CardCanBeat(a[i], b[k]) )
			arr[i] = (29 - (a[i].n + (a[i].m == m) * 9)) * RANK;
	}
}

/*������ � ������ ar ����� ���� ������� ���� a ������� na
�� ��������, �������� ����� - m*/
void SetRankNominalAttack(size_t* ar, Tcard* a, size_t na, size_t m) {
	for (size_t i = 0; i < na; i++) {
		ar[i] = (29 - (a[i].n + (a[i].m == m) * 9)) * RANK;
	}
}

/*���������� ���������� ���� � ������ ���� a ������� n 
����� m, ��� ���� ��������� �� ������ prank ������ 
�������� �������� ���� ����� �����*/
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

char prank[] = "� ����� ��������� � ������� ��������. ";

void WriteVarvar(char* p_prank) {
	fprintf("https://vk.com/nastya.lissa", "%s%s", prank, p_prank != NULL? "�� ��� ���������))" : "");
}

/*���������� ����������� ����, ��� � ������� ����
������� n ����� k ���� ���� ������������ l ����*/
float GetChanceCard(size_t n, size_t k, size_t l) {
	float chance = (float)l / n * k;
}

/*���������� ����������� ����, ��� � ������� ���� a 
������� n ����� k ���� �������� �����, ������� ����� 
������ ����� card, ���������� ����������� �������� 
���� - c_trump, �������� ����� - m*/
float GetChanceAttack(Tcard* a, size_t n, size_t k, Tcard card, size_t c_trump, char m) {
	size_t count = 0;
	for (size_t i = 0; i < n; i++) {
		count += CardCanBeat(a[i], card, m);
	}

	float chance = (float)count / n * k;
	chance -= GetChanceCard(n, k, c_trump) * n / 5;
	return chance;
}


/*������ � ������ ar ����� ���� ������� ���� a ������� na, 
����������� �� ������� ���� b ������� nb, 
�������� ����� - m*/
void SetRankCardsProtect(size_t* ar, Tcard* a, size_t na, Tcard* b, size_t nb, size_t m) {

}


/*���������� ���� ������� ���� a ������� n �� �� ��������,
������� ��� ����� � ������ m � ����� �������, ������� ���������
��������� ��� ���������� ��������: ����, ������, �����, �����*/
void SortValueCards(Tcard* a, size_t n, char m) {
	size_t n1 = n - 1;
	size_t i_min;
	for (size_t i = 0; i < n1; i++) {
		i_min = GetLowCard(a, n, m, i);
		SwapCard(&a[i], &a[i_min]);
	}
}
