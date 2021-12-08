#include "header.h"

char commandList[][50] = {
	"",
	"keyAdmin",
	"getCommandList",
	"setGameMode",
	"deleteCardPlayer",
	"giveCardPlayer",
	"deleteCardsPlayer",
	"getCardsPlayer",
	"decreaseCountCardsDeck",
	"setTrump",
	"setEventEffect",
	"a",//printMatrCardsAI
	"deleteMatrCardsAI",
	"endMove",
	"endGame",
	"turnOnSound",
	"getColorList"
};

char commandListArgs[][50] = {
	"",
	"keyAdmin string",
	"getCommandList page",
	"setGameMode name",
	"deleteCardPlayer name index",
	"giveCardPlayer name nominal suit",
	"deleteCardsPlayer name count",
	"getCardsPlayer name",
	"decreaseCountCardsDeck new_count",
	"setTrump name",
	"setEventEffect index",
	"printMatrCardsAI name x y",
	"deleteMatrCardsAI num_player",
	"endMove",
	"endGame",
	"turnOnSound name",
	"getColorList page",
	"\\\\<color_text>: string...",
	"\\\\<color_text>-<color_bg>: string..."
};
size_t countCommand = 18;

char colorList[][50] = {
	"black (������)",
	"blue (�����)",
	"green (�������)",
	"cyan (�������)",
	"red (�������)",
	"magenta (���������)",
	"brown (����������)",
	"lightgray (������-�����)",

	"darkgray (�����-�����)",
	"lightblue (������-�����)",
	"lightgreen (������-�������)",
	"lightcyan (������-�������)",
	"lightred (������-�������)",
	"lightmagenta (������-���������)",
	"yellow (������)",
	"white (�����)",

	"bgbase (������� ������� ����)",
	"bgmsg (������� ���� ���������)",
	"bgtarget (����������� ������� ����)",
	"textbase (������� ���� ������)",
	"textmsg (���� ������ ���������)",
	"texttarget (����������� ���� ������)",
	"suit1 (���� ������ 1-�� ����)",
	"suit2 (���� ������ 1-�� ����)",
};
size_t countColor = 24;

/*������ � ������ s1 ������ s2, ��� ���� ��������� ���������
�� ������ ����� ������ s1*/
char* strcpy(char* s1, const char* s2) {
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
	return s1;
}

/*������ � ����� ������ s1 ������ s2, ��� ����
��������� ��������� �� ������ ����� ���������� ������*/
char* strcat(char* s1, const char* s2) {
	while (*s1 != '\0')
		s1++;
	while (*s2 != '\0')
		*s1++ = *s2++;
	*s1 = '\0';
	return (s1);
}

/*����� ���� �������� ����� s1 � s2*/
void SwapStr(char* s1, char* s2) {
	char s3[SIZE];
	strcpy(s3, s1);
	strcpy(s1, s2);
	strcpy(s2, s3);
}

/*�������� �� ������� ���� a ������� n i-�� ��������, ��� ����
��������� ����� ������ �������*/
size_t DeleteCard(Tcard* a, size_t n, size_t i) {
	size_t m = n - 1;
	while (i < m) {
		a[i] = a[i + 1];
		i++;
	}
	return m;
}

/*������ � ������ ���� a ������� N ��������� ������������������ ����
��������� ������ ��� ���� � "������"*/
void GetArrCards(Tcard* a) {
	Tcard cards[] = {
		'�', 6, '�', 7, '�', 8, '�', 9, '�', 10, '�', 11, '�', 12, '�', 13, '�', 14,
		'�', 6, '�', 7, '�', 8, '�', 9, '�', 10, '�', 11, '�', 12, '�', 13, '�', 14,
		'�', 6, '�', 7, '�', 8, '�', 9, '�', 10, '�', 11, '�', 12, '�', 13, '�', 14,
		'�', 6, '�', 7, '�', 8, '�', 9, '�', 10, '�', 11, '�', 12, '�', 13, '�', 14,
	};

	size_t x, n = SIZE_DECK;
	for (size_t i = 0; i < SIZE_DECK; i++) {
		x = rand() % n;
		a[i] = cards[x];
		n = DeleteCard(cards, n, x);
	}
}

/*���������� ������ ����� �� ������� ���� a ������� n 
����� m � ���������� ���������, ���� ������� 
������������, ����� ���������� -1*/
int SearchSuit(Tcard* a, size_t n, char m) {
	size_t min = 15, i_min;
	for (size_t i = 0; i < n; i++) {
		if (a[i].m == m && a[i].n < min) {
			i_min = i;
			min = a[i].n;
		}
	}
	if (min > 14)
		return -1;
	else
		return i_min;
}

/*���������� ������ ������, ��� ��� ����� ������, 
����� �������� ���� a ������� k ������ K,
� �������� ������ m*/
size_t WhoseMove(Tcard* a[6], size_t count_players, char m) {
	int icard, min = 15;
	int iplayer = -1;
	for (size_t i = 0; i < count_players; i++) {
		icard = SearchSuit(a[i], K, m);
		if (icard >= 0 && a[i][icard].n < min) {
			iplayer = i;
			min = a[i][icard].n;
		}
	}
	if (iplayer < 0) {
		iplayer = rand() % count_players;
	}
	return iplayer;
}

/*����� �������� � ����� ���� a � b*/
void SwapCard(Tcard* a, Tcard* b) {
	Tcard t = *a;
	*a = *b;
	*b = t;
}

/*���������� �������� "������", ���� ������ ����� � ������� ���� a
������� n - ���, ��� ���� ����� ������� ��� ����� � ������ ��
���������� �����, ����� ���������� �������� "����"*/
size_t AceIsTrumpCard(Tcard* a, size_t n) {
	size_t f;
	if (a[0].n == 14) {
		f = 1;
		size_t i = 1;
		while (i < n && a[i].n == 14)
			i++;
		SwapCard(&a[0], &a[i]);
	}
	else
		f = 0;
	return f;
}

/*������������� � ��������� �� ������ pcards ������� ���������
������������������ �� N ����, �������� � �������� ���� count
������� �� K ���� �� ����� �������, ������ �������� ����
���� �������, ��� ���� ���, ��� ����� � ������ ������� ����*/
void InitStructCards(Tcards* pcards, TgameTable* pGameTable, size_t count) {
	pGameTable->user = 0;
	pGameTable->count_players = count;
	pGameTable->cur_count_players = count;
	GetArrCards(pcards->deck); // ������ ����
	AceIsTrumpCard(pcards->deck, SIZE_DECK); // �������� ����� ����� ������ != ���
	pGameTable->bottom_card = pcards->deck[0]; // �������� �����
	pGameTable->trump = pGameTable->bottom_card.m; // ������

	// ��������� ������ ��� �������� ���� ������� � ������� �� ����
	size_t c_deck = SIZE_DECK;
	for (size_t i = 0; i < count; i++) {
		pcards->player[i] = (Tcard*)malloc(SIZE_DECK * sizeof(Tcard));
		pGameTable->c_player[i] = AddCards(pcards->deck, c_deck, K,
			pcards->player[i], 0, pGameTable->trump);
		pGameTable->pos_out_player[i] = 0;
		pGameTable->c_player[i] = K;
		c_deck -= K;
	}
	for (size_t i = count; i < 6; i++) {
		pGameTable->c_player[i] = 0;
	}

	pGameTable->c_deck = c_deck;
	pGameTable->c_batt = 0;
	pGameTable->c_retr = 0;

	// ����������, ��� ����� ������
	pGameTable->move = WhoseMove(pcards->player, count, pGameTable->trump);

	pGameTable->priority = pGameTable->move;
	pGameTable->count_can_throw = 6;
	pGameTable->defend_player = (pGameTable->move + 1) % pGameTable->count_players;
	pGameTable->end_move = 0;
	pGameTable->end_game = 0;
	pGameTable->move_number = 1;
	pGameTable->count_priority = 0;

	pGameTable->count_wait_ms_AI = DECISION_TIME_AI;
}

/*���������� � ����������� ������ ���� a ������� n �����
� ��� ������������� ������� ��������*/
void InitChat(char (**chat)[SIZE], size_t n) {
	*chat = (char**)malloc(SIZE * n * sizeof(char));
	for (size_t i = 0; i < n; i++) {
		(*chat)[i][0] = '\0';
	}
}

/*������� ���� a ������� n �����, �������� ��� ������� ��������*/
void ChatClear(char(*chat)[SIZE], size_t n) {
	for (size_t i = 0; i < n; i++) {
		chat[i][0] = '\0';
	}
}

/*������ � ��������� �� ������ pai ��������
���� �� � ��������� difficulty*/
void InitGameSettingsAI(TsettingsAI* a, size_t difficulty) {
	a->difficulty = difficulty;
	a->init_ai = 0;
}

/*������������ ������������ ������ � ��������� ��
������ players, ���������� ��������� ���� k �������*/
void DeleteCardsPlayers(Tcard** players, size_t k) {
	for (size_t i = 0; i < k; i++) {
		free(players[i]);
	}
}



/*������ � ������ ���� a ������� n ����� card � ������� i,
�������� ������� ���������� ���� � �������, ��� ���� ���������
������ ����������� �������*/
size_t AddCard(Tcard* a, size_t n, Tcard card, size_t i) {
	size_t m = n;
	while (m > i) {
		a[m] = a[m - 1];
		m--;
	}
	a[i] = card;
	return n + 1;
}

/*������ �� ����� ������� ���� a ������� na k ��������� ���������
� ������ ���� b ������� nb, �������� ������� ���������� ���� ��
����������: ����, ������, �����, �����, ������ (��������
����� - m), ��� ���� ��������� ������ ����������� �������*/
size_t AddCards(Tcard* a, size_t na, size_t k, 
	Tcard* b, size_t nb, char m) {
	int j;
	for (size_t i = 0; i < k; i++) {
		na--;
		if (a[na].m == m) { // ���� ����� ��������
			j = nb - 1;
			// ����� ������� ��� ����� � ������ ���������
			while ((j >= 0) && (a[na].m == b[j].m) && (a[na].n < b[j].n)) 
				j--;
			AddCard(b, nb, a[na], j + 1);
		} else { // ���� ����� �� ��������
			j = 0;
			// ����� ������� ��� ����� ������ �����
			while ((j < nb) && (a[na].m < b[j].m) && (b[j].m != m)) 
				j++;
			// ����� ������� ��� ����� � ������ ���������
			while ((j < nb) && (a[na].m == b[j].m) && (a[na].n > b[j].n)) 
				j++;
			AddCard(b, nb, a[na], j);
		}
		nb++;
	}
	return nb;
}

/*������ �� ����� ������� ���� a ������� �� ������ pna �
������ ���� b ������� �� ������ pnb, ���� � ������� b �����
k ���� ��� ���� � ������� a �� ���������� �����, ��������
������� ���������� ���� �� ����������: ����, ������, �����,
�����, ������ (�������� ����� - m), ��������� �� ������� pna
� pnb ����� ������� �������� a � b, ��� ���� ���������
���������� ���������� ����*/
size_t MoveCardsToK(Tcard* a, size_t* pna, size_t k, 
	Tcard* b, size_t* pnb, char m) {
	size_t nb_old = *pnb;
	size_t count = (k - *pnb) * (*pnb < k);

	if (*pna) {
		if (*pna < count) // ���� � ������� a ���� ������, ��� ����������
			count = *pna; // ������ �� ���������� �������, ������� ��� ����
		*pnb = AddCards(a, *pna, count, b, *pnb, m);
		count = *pnb - nb_old;
		*pna -= count;
		return count;
	} else
		return 0;
}

/*����������� ���� � ��������� �� ������ pcards � 
pGameTable � ���� ��� � ����� � �� ����� ������ ������� 
������, ��� ������ ���, � ����� ��������� ������� �� 
������� �� count ���� ��� ���� � ����� ������ ���� 
�����, ��������� �� ������ ��������� ����� ������� 
�������� ����*/
void RedistribCards(Tcards* pcards, size_t count, 
	TgameTable* pGameTable) {
	// ����� � ����� � ���� ���
	AddCards(pGameTable->battle, pGameTable->c_batt, pGameTable->c_batt, 
		pcards->retread, pGameTable->c_retr, pGameTable->trump);

	// ����������� ����� ������� ������, ������� ���������� ����� ������
	MoveCardsToK(pcards->deck, &pGameTable->c_deck, count, 
		pcards->player[pGameTable->move], &pGameTable->c_player[pGameTable->move], 
		pGameTable->trump);
	// � ����� ���������
	for (size_t i = 0, i_player = pGameTable->move + 1; 
		i < pGameTable->count_players; i++, i_player++) {

		i_player %= pGameTable->count_players;
		MoveCardsToK(pcards->deck, &pGameTable->c_deck, count, 
			pcards->player[i_player], &pGameTable->c_player[i_player], pGameTable->trump);
	}
	pGameTable->c_retr += pGameTable->c_batt;
	pGameTable->c_batt = 0;
}

/*����������� ���� � ��������� �� ������ pcards �
pGameTable � ���� ��� ������, ��� �� �������� �����, 
� ����� ��������� ������� �� ����� ������ �� ������� 
�� count ���� ��� ���� � ����� ������ ���� �����, 
��������� �� ������ ��������� ����� ������� �������� ����*/
void RedistribCardsPass(Tcards* pcards, size_t count,
	TgameTable* pGameTable) {
	// ����� ������������� ������ � ���� ���
	AddCards(pGameTable->battle, pGameTable->c_batt, pGameTable->c_batt,
		pcards->player[pGameTable->defend_player], 
		pGameTable->c_player[pGameTable->defend_player], pGameTable->trump);
	pGameTable->c_player[pGameTable->defend_player] += pGameTable->c_batt;
	pGameTable->c_batt = 0;

	// � ����� ���������
	for (size_t i = 0, i_player = pGameTable->move;
		i < pGameTable->count_players; i++, i_player++) {
		if (i_player != pGameTable->defend_player) {
			i_player %= pGameTable->count_players;
			MoveCardsToK(pcards->deck, &pGameTable->c_deck, count,
				pcards->player[i_player], &pGameTable->c_player[i_player],
				pGameTable->trump);
		}
	}
}

/*����������� �� ������� ���� a ������� �� ������
na i-� ����� � ������ ���� b ������� �� ������ nb,
������� ������� ���� �������� �� -1 � +1
��������������*/
void MoveCardInArr(Tcard* a, size_t* na, size_t i,  Tcard* b, size_t* nb) {
	b[*nb] = a[i];
	(*nb)++;
	*na = DeleteCard(a, *na, i);
}

/*���������� �� ������� ���� a ������� n ������ �����
card, ���� ��� ��� ���������, ����� ���������� -1*/
int CardInArr(Tcard* a, size_t n, Tcard card) {
	size_t i = 0;
	while (i < n && (a[i].m != card.m || a[i].n != card.n))
		i++;
	if (i >= n || a[i].m != card.m || a[i].n != card.n)
		i = -1;
	return i;
}

/*���������� ���������� ��������� ��������� 
������ a ������� n*/
size_t GetCountNonZerolArr(size_t* a, size_t n) {
	size_t count = 0;
	for (size_t i = 0; i < n; i++) {
		count += a[i] > 0;
	}
	return count;
}

/*���������� �������� "������", ���� � ������� a 
������� n ������ count ��������� ����� value, ����� 
�������� "����"*/
size_t CountElArrValue(size_t* a, size_t n, size_t count,  size_t value) {
	size_t count_equal = 0;
	for (size_t i = 0; i < n; i++) {
		count_equal += a[i] == value;
	}
	return count_equal == count;
}

/*���������� �������� "������", ���� � ������� a ������� 
n ���� ������ ��������, ����� �������� "����"*/
size_t IsEqualElArr(size_t* a, size_t n) {
	size_t i = 0, j;
	while (i < n) {
		j = i + 1;
		while (j < n) {
			if (a[i] == a[j])
				goto flagIsEqualElArr;
			j++;
		}
		i++;
	}
	flagIsEqualElArr:
	if (i == n && j == n)
		return 0;
	else
		return 1;
}

/*������� ��������� �� ������ pparam � ������, 
������������ �� �������� �� k ������� ������ � 
��������� �� ������ pGameTable*/
void MoveToNextPlayer(size_t* p_param, size_t k, 
	TgameTable* pGameTable) {
	for (size_t i = 0; i < k; i++) {
		*p_param = (*p_param + 1) % pGameTable->count_players;
		// ������� ������� ��� ���� ��� ����, ��� �������
		while (!pGameTable->c_player[*p_param] 
			|| pGameTable->player_state == PASS) {
			*p_param = (*p_param + 1) % pGameTable->count_players;
		}
	}
}

/*���������� ������ ����� m*/
size_t GetIndexSuit(char m) {
	switch (m) {
		case '�':
			return 0;
		case '�':
			return 1;
		case '�':
			return 2;
		case '�':
			return 3;
		default:
			return 4;
	}
}

/*���������� 1, ���� ����� ���� ���� ������� �� 
������� pcards � pGameTable ���� ������ ���� ���������� 
���� � ����������� �������, ������ n, ��������� �� 
������� p_one � p_two ������� ���� ����� ����, �����, 
���� ����� ���� ���� ���� �����, �� ������������� 
��������� ������������ ���� ��� ������ ���� ������� 
SIZE_DECK, ���������� 2, ��������� �� ������ p_one 
������ ������ � ����� ������, ����� ���������� 0*/
size_t ChekingAllCards(Tcards* pcards, TgameTable* pGameTable, 
	size_t* p_one, size_t* p_two) {
	// ������� ����, � ������� ������ ������������� �����, � ������� - �������� �����
	uint8_t matr[4][15][2] = { 0 };
	Tcard* decks[] = {
		pcards->player[0],
		pcards->player[1],
		pcards->player[2],
		pcards->player[3],
		pcards->player[4],
		pcards->player[5],
		pcards->deck,
		pGameTable->battle,
		pcards->retread
	};
	size_t size_decks[] = {
		pGameTable->c_player[0],
		pGameTable->c_player[1],
		pGameTable->c_player[2],
		pGameTable->c_player[3],
		pGameTable->c_player[4],
		pGameTable->c_player[5],
		pGameTable->c_deck,
		pGameTable->c_batt,
		pGameTable->c_retr
	};
	const size_t count_decks = 9;

	size_t i_suit; // ������ �����
	for (size_t i = 0; i < count_decks; i++) {
		for (size_t j = 0; j < size_decks[i]; j++) {
			i_suit = GetIndexSuit(decks[i]->m);
			if (i_suit >= 4 || decks[i][j].n < 6 || decks[i][j].n > 14) {
				*p_one = i;
				return 2;
			} else {
				if (matr[i_suit][ decks[i][j].n ][0] == 1) {
					*p_one = matr[i][j][1];
					*p_two = i;
					return 1;
				} else {
					matr[i_suit][ decks[i][j].n ][0] == 1;
					// ������ ������, � ������� ������ ����� ����
					matr[i_suit][ decks[i][j].n ][1] = i;
				}
			}
		}
	}
	return 0;
}

/*���������� �������� "������", ���� ����� a ����� ������ ����� b,
��������, ��� �������� ����� - m, ����� ���������� �������� "����"*/
size_t CardCanBeat(Tcard a, Tcard b, char m) {
	size_t f;
	if (a.m == b.m) { // ���� ����� ����������
		// ���� ������� ����� ���� ��� ��� 6 ������ ����
		f = a.n > b.n || (a.n == 6 && b.n == 14);
	} else
		f = a.m == m; // ���� �����, ������� ���� - ��������
	return f;
}

/*���������� ������ ����� � ������� ���� a ������� n, ������
������� ����� k, �����, ���� ���� � ����� ��������� ���,
���������� -1*/
int ThereIsNominal(Tcard* a, size_t n, size_t k) {
	int i = 0;
	while (i < n && a[i].n != k)
		i++;
	if (i >= n)
		i = -1;
	return i;
}

/*������ � ������ s ���������, ���������� �������������, 
��������������� �������� �������� � ����� ������, 
���� �������� ������������ � ����� point, ������� �� 
����� size ��������*/
void GetMessageFromUser(char* s, COORD point, size_t size) {
	char ch;
	size_t cur_size;
	do {
		getchar();
		cur_size++;
	} while (ch != '\n' && cur_size < size);

}

/*������������� ��������� �� ��� ���, ����
�� ������ ������� Space*/
void UntilKeyIsPressedSpace() {
	while (GetKeyState(VK_SPACE) >= 0);
	mciSendString(TEXT("play sourse\\sound\\menu\\buttonClick.mp3"), NULL, 0, NULL); // ����
}

/*������ ��������� �� ������ ptheme ���������� ���� � �������� i*/
void SetTheme(Ttheme* ptheme, size_t i) {
	static char black[] = "black"; // ������
	static char blue[] = "blue"; // �����
	static char green[] = "green"; // �������
	static char cyan[] = "cyan"; // �������
	static char red[] = "red"; // �������
	static char magenta[] = "magenta"; // ���������
	static char brown[] = "brown"; // ����������
	static char lightgray[] = "lightgray"; // ������-�����
	static char darkgray[] = "darkgray"; // �����-�����
	static char lightblue[] = "lightblue"; // ������-�����
	static char lightgreen[] = "lightgreen"; // ������-�������
	static char lightcyan[] = "lightcyan"; // ������-�������
	static char lightred[] = "lightred"; // ������-�������
	static char lightmagenta[] = "lightmagenta"; // ������-���������
	static char yellow[] = "yellow"; // ������
	static char white[] = "white"; // �����

	if (i == THEME_DAY) {
		ptheme->colorBgBase = white;
		ptheme->colorBgMsg = black;
		ptheme->colorBgTarget = lightcyan;
		ptheme->colorTextBase = black;
		ptheme->colorTextMsg = white;
		ptheme->colorTextTarget = brown;
		ptheme->colorSuit1 = red;
		ptheme->colorSuit2 = darkgray;

	} else if (i == THEME_NIGHT) {
		ptheme->colorBgBase = black;
		ptheme->colorBgMsg = black;
		ptheme->colorBgTarget = cyan;
		ptheme->colorTextBase = yellow;
		ptheme->colorTextMsg = yellow;
		ptheme->colorTextTarget = lightmagenta;
		ptheme->colorSuit1 = cyan;
		ptheme->colorSuit2 = white;

	} else if (i == THEME_EAST) {
		ptheme->colorBgBase = lightred;
		ptheme->colorBgMsg = black;
		ptheme->colorBgTarget = yellow;
		ptheme->colorTextBase = black;
		ptheme->colorTextMsg = yellow;
		ptheme->colorTextTarget = white;
		ptheme->colorSuit1 = yellow;
		ptheme->colorSuit2 = black;

	} else if (i == THEME_BLACK_BLUE) {
		ptheme->colorBgBase = cyan;
		ptheme->colorBgMsg = yellow;
		ptheme->colorBgTarget = yellow;
		ptheme->colorTextBase = black;
		ptheme->colorTextMsg = black;
		ptheme->colorTextTarget = blue;
		ptheme->colorSuit1 = white;
		ptheme->colorSuit2 = blue;

	} else if (i == THEME_NEW_YEAR) {
		ptheme->colorBgBase = white;
		ptheme->colorBgMsg = lightred;
		ptheme->colorBgTarget = lightgreen;
		ptheme->colorTextBase = blue;
		ptheme->colorTextMsg = white;
		ptheme->colorTextTarget = magenta;
		ptheme->colorSuit1 = lightmagenta;
		ptheme->colorSuit2 = cyan;
	}
	SetConsoleColor(ptheme->colorBgBase, ptheme->colorTextBase);
}

/*����������� ������� ������ ����, �����������
�� ��������� context, ���� ������� �������� on_music*/
void MusicBgControl(size_t context, size_t on_music) {
	static time_start = 0; // ������ ������� ��������������� ������
	static time_start_pasue = 0; // ������ ������� ������������ ������ �� �����
	static i_music = 0; // ������ ������, ������� ������
	static previous_context = CONTEXT_MENU; // ���� �� ����� ��������� ������
	static switch_off_music = 0; // ��������� �� ������
	// ������ �� ������ ������ �������� ����
	static music_mainmenu = 0;
	// ������ �� ������ ������ �� ������� �����
	static music_gametable = 0;
	// ������ �� ������ ������ ���� �����
	static music_menupause = 0;
	// ������ �� ������ ������ ���� ��������� ���
	static music_simulation = 0;
	const clock_t len_musics_game[] = { // ������������ ������ � �������
		0,
		106 * CLOCKS_PER_SEC,
		101 * CLOCKS_PER_SEC,
		83 * CLOCKS_PER_SEC,
		163 * CLOCKS_PER_SEC,
		121 * CLOCKS_PER_SEC
	};
	const count_music_game = 5;

	if (!on_music) // ���� ������ ���������
		previous_context = CONTEXT_NONE;
	if (previous_context != context) { // ���� ��������� ����� ��������� ������
		if (music_mainmenu) {
			mciSendString(TEXT("close sourse\\music\\mainMenu.mp3"),
				NULL, 0, NULL); // ����. ������
			music_mainmenu = 0;

		} else if (music_gametable) {
			if (context == CONTEXT_PAUSE_GAME) {
				switch (i_music) {
					case 1: mciSendString(TEXT("pause sourse\\music\\game1.mp3"),
						NULL, 0, NULL); break; // ��������� ������ �� �����
					case 2: mciSendString(TEXT("pause sourse\\music\\game2.mp3"),
						NULL, 0, NULL); break; // ��������� ������ �� �����
					case 3: mciSendString(TEXT("pause sourse\\music\\game3.mp3"),
						NULL, 0, NULL); break; // ��������� ������ �� �����
					case 4: mciSendString(TEXT("pause sourse\\music\\game4.mp3"),
						NULL, 0, NULL); break; // ��������� ������ �� �����
					case 5: mciSendString(TEXT("pause sourse\\music\\game5.mp3"),
						NULL, 0, NULL); break; // ��������� ������ �� �����
				}
				time_start_pasue = clock();
			} else {
				switch (i_music) {
					case 1: mciSendString(TEXT("close sourse\\music\\game1.mp3"),
						NULL, 0, NULL); break; // ���. ������
					case 2: mciSendString(TEXT("close sourse\\music\\game2.mp3"),
						NULL, 0, NULL); break; // ���. ������
					case 3: mciSendString(TEXT("close sourse\\music\\game3.mp3"),
						NULL, 0, NULL); break; // ���. ������
					case 4: mciSendString(TEXT("close sourse\\music\\game4.mp3"),
						NULL, 0, NULL); break; // ���. ������
					case 5: mciSendString(TEXT("close sourse\\music\\game5.mp3"),
						NULL, 0, NULL); break; // ���. ������
				}
			}
			music_gametable = 0;

		} else if (music_menupause) {
			mciSendString(TEXT("close sourse\\music\\pauseMenu.mp3"),
				NULL, 0, NULL); // ����. ������
			music_menupause = 0;

		} else if (music_simulation) {
			mciSendString(TEXT("close sourse\\music\\simulation.mp3"),
				NULL, 0, NULL); // ����. ������
			music_simulation = 0;
		}
	}

	if (on_music) { // ���� ������ ��������
		if (context == CONTEXT_MENU && !music_mainmenu) {
			mciSendString(TEXT("play sourse\\music\\mainMenu.mp3 repeat"),
				NULL, 0, NULL); // ���. ��������� ������
			music_mainmenu = 1;
			previous_context = CONTEXT_MENU;

		} else if (context == CONTEXT_GAME) {
			if (previous_context == CONTEXT_PAUSE_GAME && !music_gametable) {
				switch (i_music) {
					case 1: mciSendString(TEXT("resume sourse\\music\\game1.mp3"),
						NULL, 0, NULL); break; // ����������� ������
					case 2: mciSendString(TEXT("resume sourse\\music\\game2.mp3"),
						NULL, 0, NULL); break; // ����������� ������
					case 3: mciSendString(TEXT("resume sourse\\music\\game3.mp3"),
						NULL, 0, NULL); break; // ����������� ������
					case 4: mciSendString(TEXT("resume sourse\\music\\game4.mp3"),
						NULL, 0, NULL); break; // ����������� ������
					case 5: mciSendString(TEXT("resume sourse\\music\\game5.mp3"),
						NULL, 0, NULL); break; // ����������� ������
				}
				// ��������� ����� ����� � ������ ������� ������� ��������������� ������
				time_start += clock() - time_start_pasue;
			}
			// ���� ����������� ���������� ������
			if (TIMER(time_start, len_musics_game[i_music])) {
				i_music = rand() % count_music_game + 1;
				switch (i_music) {
					case 1: mciSendString(TEXT("play sourse\\music\\game1.mp3"),
						NULL, 0, NULL); break; // ���. ������
					case 2: mciSendString(TEXT("play sourse\\music\\game2.mp3"),
						NULL, 0, NULL); break; // ���. ������
					case 3: mciSendString(TEXT("play sourse\\music\\game3.mp3"),
						NULL, 0, NULL); break; // ���. ������
					case 4: mciSendString(TEXT("play sourse\\music\\game4.mp3"),
						NULL, 0, NULL); break; // ���. ������
					case 5: mciSendString(TEXT("play sourse\\music\\game5.mp3"),
						NULL, 0, NULL); break; // ���. ������
				}
				time_start = clock();
			}
			music_gametable = 1;
			previous_context = CONTEXT_GAME;

		} else if (context == CONTEXT_PAUSE_GAME && !music_menupause) {
			mciSendString(TEXT("play sourse\\music\\pauseMenu.mp3 repeat"),
				NULL, 0, NULL); // ���. ��������� ������
			music_menupause = 1;
			previous_context = CONTEXT_PAUSE_GAME;

		} else if (context == CONTEXT_SIMULATION && !music_simulation) {
			mciSendString(TEXT("play sourse\\music\\simulation.mp3 repeat"),
				NULL, 0, NULL); // ���. ��������� ������
			music_simulation = 1;
			previous_context = CONTEXT_SIMULATION;
		}
	}
}

/*������������ ���������� ����� ������������ �����*/
void PlaySoundCard() {
	static size_t i = 0;
	switch (i) {
		case 0:
			mciSendString(TEXT("play sourse\\sound\\game_table\\card1.mp3"),
				NULL, 0, NULL); break;
		case 1:
			mciSendString(TEXT("play sourse\\sound\\game_table\\card2.mp3"),
				NULL, 0, NULL); break;
		case 2:
			mciSendString(TEXT("play sourse\\sound\\game_table\\card3.mp3"),
				NULL, 0, NULL); break;
	}
	i = (i + 1) % 3;
}

/*�������������� � �������� ����� fname �������� ����� key
�� ������ pvalue, �������� ���������� �����, ��������� 
� ������� ������� ������ �������, ���� ��� ����������*/
void CountTimeSpenInGame(char* fname, char* key, size_t* pvalue) {
	static clock_t time_start;
	static size_t old_min = 0;
	static size_t f = 0;
	if (!f) {
		time_start = clock();
		f = 1;
	}

	size_t cur_min = TIME_SEC(time_start) / 60;
	if (cur_min > old_min) {
		*pvalue = ChangeValueData(fname, key, cur_min - old_min);
		WriteToTextFileSettings(FILE_PATH_SETTINGS_TXT, fname);
		old_min = cur_min;
	}
}

/*���������� �������� ARGS_OK, ���� ��������� args 
������������ ��������-����� ������� types ������� n, ����� 
���������� ������ ��������, ��������������� ������� ������*/
int ArgsIsFit(char* args, char* types, size_t n) {
	size_t i = 0;
	while (*args && *args <= ' ') {  // ������� ������ ��������
		args++;
	}
	while (*args) {
		if (types[i] == 'n') { // ���� �������� - �����
			while (*args && *args >= '0' && *args <= '9') {
				args++;
			}
		} 
		else if (types[i] == 's') { // ���� �������� - ������
			if (*args && *args >= '0' && *args <= '9') {
				return i + 1;
			}
			while (*args && (*args >= 'a' && *args <= 'z'
				|| *args >= 'A' && *args <= 'Z' || *args >= '0' && *args <= '9')) {
				args++;
			}
		}
		// ���� �������� ������ �������
		if (!(*args && *args <= ' ' || !*args)) {
			return i + 1; // ������ ���������� i-�� ���������
		}
		while (*args && *args <= ' ') { // ������� ������ ��������
			args++;
		}
		i++;
	}
	if (i < n)
		return ARGS_FEW;
	else if (i > n)
		return ARGS_MANY;
	
	return ARGS_OK; // ���������� ����������� ���������
}

/*����� ������� �� ������� ���������� �� ����������, ����������� 
� ��������� �� ������ pGameTable, ��������� ��� ���������� � 
������������ � ��������� �������� ��������� �������� �� ������� 
pGameTable, Tcards, settingsAI, pblocks, ��������� � ������ 
s_res ��������� � ���������� ���������� �������*/
void CallCommand(TgameTable* pGameTable, Tcards* Tcards, TsettingsAI* settingsAI[6], 
	TblocksGame* pblocks, char* s_res, Ttheme* ptheme) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int res = COMMAND_NO_AVAILABLE;

	switch (pGameTable->command) {
		case COMMAND_PRINT_MATR_CARDS_AI: // ����� ������� ������ ���� ��
			res = CommandPrintMatrCardsAI(h, pGameTable, settingsAI, 
				&pblocks->matr_cards_ai, &pblocks->index_matr_ai, ptheme);
			break;
		case COMMAND_DELETE_MATR_CARDS_AI: // �������� ������� ������ ���� ��
			pblocks->matr_cards_ai.cond = BUTTON_OFF;
			res = ARGS_OK;
			break;
		case COMMAND_GET_COMMAND_LIST: // ����� ������ ��������� ������
			res = CommandGetCommandList(pGameTable, pblocks->chat, ptheme);
			break;
		case COMMAND_GET_COLOR_LIST: // ����� ������ ��������� ������
			res = CommandGetColorList(pGameTable, pblocks->chat, ptheme);
			break;
	};
	switch (res) {
		case ARGS_OK:
			sprintf(s_res, "\\green:������� %s ���������.", commandList[pGameTable->command]); break;
		case ARGS_FEW:
			sprintf(s_res, "\\lightred:������ ���������� ������� %s: ���� ���������� ��� ������ �������.", 
				commandList[pGameTable->command]); break;
		case ARGS_MANY:
			sprintf(s_res, "\\lightred:������ ���������� ������� %s: ������� ����� ���������� ��� ������ �������.", 
				commandList[pGameTable->command]); break;
		case COMMAND_NO_AVAILABLE:
			sprintf(s_res, "\\lightred:������ ���������� ������� %s: ������� ����������.",
				commandList[pGameTable->command]); break;
		case ERROR_NO_INIT_MATR_AI:
			sprintf(s_res, "\\lightred:������ ���������� ������� %s: ������� ������ ���� ������� �� �� ����������������.",
				commandList[pGameTable->command]); break;
		case ERROR_IS_INDEX_USER:
			sprintf(s_res, "\\lightred:������ ���������� ������� %s: � ������, �� �������� ������ ������������, �� ����� ���� ������� ������ ����.",
				commandList[pGameTable->command]); break;
		default:
			if (res >= 0) {
				sprintf(s_res, "\\lightred:������ ���������� ������� %s: ������������ ���� %d-�� ���������.", 
					commandList[pGameTable->command], res);
			}
	}
	if (ptheme->onSounds) {
		if (res == ARGS_OK)
			mciSendString(TEXT("play sourse\\sound\\menu\\inputSuccess.mp3"), NULL, 0, NULL); //����
		else
			mciSendString(TEXT("play sourse\\sound\\game_table\\erro.mp3"), NULL, 0, NULL); // ����
	}
		
}

/*������ � ��� ��������� �� ������ pGameTable �� ������� ���������� 
�� ���������� �� ���� ���������, � ��������� ���� block � 
�������� ����� ��������� �� ������ ptheme ������ ��������� ������, 
��������� �������� � ����������� ���������� �������*/
int CommandGetCommandList(TgameTable* pGameTable, Tblock block, Ttheme* ptheme) {
	char types[] = "n";
	const count_args = 1;
	const count_command_in_page = 9;
	int res;
	res = ArgsIsFit(pGameTable->args, types, count_args);
	if (res == ARGS_OK) {
		size_t page;
		sscanf(pGameTable->args, "%u", &page);
		size_t max_page = countCommand / count_command_in_page + (countCommand % count_command_in_page > 0);
		char s_out[MAX_LEN_MESSAGE];
		char stmp[MAX_LEN_MESSAGE];

		if (page > max_page) {
			sprintf(stmp, "\\lightred:������ �������� �� ����������. ���������� ��������: 1 ... %u", max_page);
			GetMsgForChat(s_out, stmp, "@p", "darkgray", ptheme);
			UpdateChat(pGameTable->chat, block, s_out, ptheme);
		} 
		else {
			char w[MAX_LEN_MESSAGE];
			char* pstmp = stmp;
			size_t i = (page - 1) * count_command_in_page + 1;
			size_t j = min(i + count_command_in_page, countCommand);
			sprintf(stmp, "%u/%u �������� ������ ������:", page, max_page);
			GetMsgForChat(s_out, stmp, "@p", "darkgray", ptheme);
			UpdateChat(pGameTable->chat, block, s_out, ptheme);
			while (i <= j) {
				strcpy(stmp, commandListArgs[i]);
				pstmp = GetWord(w, stmp, MAX_LEN_MESSAGE);
				sprintf(s_out, "\\textmsg-bgmsg: %u. \\texttarget-bgmsg:%s\\textmsg-bgmsg:%s", 
					i, w, pstmp);
				UpdateChat(pGameTable->chat, block, s_out, ptheme);
				i++;
			}
		}
	}
	return res;
}

/*������ � ��� ��������� �� ������ pGameTable �� ������� ����������
�� ���������� �� ���� ���������, � ��������� ���� block �
�������� ����� ��������� �� ������ ptheme ������ ��������� ������,
��������� �������� � ����������� ���������� �������*/
int CommandGetColorList(TgameTable* pGameTable, Tblock block, Ttheme* ptheme) {
	char types[] = "n";
	const count_args = 1;
	const count_command_in_page = 8;
	int res;
	res = ArgsIsFit(pGameTable->args, types, count_args);
	if (res == ARGS_OK) {
		size_t page;
		sscanf(pGameTable->args, "%u", &page);
		size_t max_page = countCommand / count_command_in_page + (countCommand % count_command_in_page > 0);
		char s_out[MAX_LEN_MESSAGE];
		char stmp[MAX_LEN_MESSAGE];

		if (page > max_page) {
			sprintf(stmp, "\\lightred:������ �������� �� ����������. ���������� ��������: 1 ... %u", max_page);
			GetMsgForChat(s_out, stmp, "@p", "darkgray", ptheme);
			UpdateChat(pGameTable->chat, block, s_out, ptheme);
		} 
		else {
			char w[MAX_LEN_MESSAGE];
			char* pstmp = stmp;
			size_t i = (page - 1) * count_command_in_page + 1;
			size_t j = min(i + count_command_in_page, countColor);
			sprintf(stmp, "%u/%u �������� ������ ������:", page, max_page);
			GetMsgForChat(s_out, stmp, "@p", "darkgray", ptheme);
			UpdateChat(pGameTable->chat, block, s_out, ptheme);
			while (i <= j) {
				strcpy(stmp, colorList[i]);
				pstmp = GetWord(w, stmp, MAX_LEN_MESSAGE);
				sprintf(s_out, "\\textmsg-bgmsg: %u. \\texttarget-bgmsg:%s\\textmsg-bgmsg:%s", 
					i, w, pstmp);
				UpdateChat(pGameTable->chat, block, s_out, ptheme);
				i++;
			}
		}
	}
	return res;
}

/*���������� ������ ������ �� ������� ����� ���� ������� name_player 
������� 6 � ������ name, �����, ���� ����� � ������ ������ �� 
������, ���������� -1*/
int GetIndexPlayerByName(char (*name_player)[MAX_LEN_NICKNAME + 1], char* name) {
	if (name[0] == 'i' && name[1] >= '0' && name[1] <= '5' && name[2] == '\0') {
		return name[1] - '0';
	} 
	else {
		size_t i = 0;
		while (strcmp(name_player[i], name) && i < 6) {
			i++;
		}
		if (i == 6)
			return -1;
		else
			return i;
	}
}

/*����� � ���� � ������������ h ������� ������ a 
�� � ����� point ������� 8 x 60*/
void PrintMatrCardsAI(HANDLE h, uint8_t a[SIZE_LINE_AI][SIZE_COLUMN_AI], COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("  |  0  1  2  3  4  5|  6  7  8  9 10  �  �  �  �| un  -  x ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" -|------------------|---------------------------|--------- ");
	for (size_t i = 0; i < SIZE_LINE_AI; i++) {
		MoveConsoleCursorPoint(h, &point, 0, 1);
		if (i < 4)
			printf(" %c|", GetSuitByIndex(i)); // ������ �����
		else {
			printf(" -|------------------|---------------------------|--------- ");
			MoveConsoleCursorPoint(h, &point, 0, 1);
			printf("  |");
		}

		for (size_t j = 0; j < 6; j++) {
			printf("%3u", a[i][j]);
		}
		putchar('|');
		for (size_t j = 6; j < 15; j++) {
			if (i < 4) {
				if (a[i][j] == CARDS_UNKNOWN)
					printf(" un");
				else if (a[i][j] == CARDS_RETR)
					printf("  -");
				else if (a[i][j] == CARDS_BATTLE)
					printf("  x");
				else
					printf("%3u", a[i][j]);
			} else
				printf("%3u", a[i][j]);
		}
		putchar('|');
		for (size_t j = 15; j < SIZE_COLUMN_AI; j++) {
			printf("%3u", a[i][j]);
		}
		putchar(' ');
	}
}

/*����� � ���� � ������������ h ������� ������ ���� �� � 
������� � ������� ����� �� ������� ���������� �� ���������� 
�� ��������� �� ������ pGameTable, �� ��������� �� ��������� 
�� ������ settingsAI, ��������� ��������� ����������� �������� � 
���� �� ������ block, ��������� �� ������ pi_player ������ ������� 
������, � �������� ����� ��������� �� ������ ptheme, 
��������� �������� � ����������� ���������� �������*/
int CommandPrintMatrCardsAI(HANDLE h, TgameTable* pGameTable, 
	TsettingsAI* settingsAI[6], Tblock* pblock, size_t* pi_player, Ttheme* ptheme) {
	char types[] = "snn";
	const count_args = 3;
	int res;
	res = ArgsIsFit(pGameTable->args, types, count_args);
	if (res == ARGS_OK) {
		char name[SIZE];
		sscanf(pGameTable->args, "%s %u %u", name, &pblock->pos.X, &pblock->pos.Y);
		int i = GetIndexPlayerByName(pGameTable->name_player, name);
		if (i >= 0) {
			if (i == pGameTable->user)
				return ERROR_IS_INDEX_USER;
			else if (!settingsAI[i]->init_ai)
				return ERROR_NO_INIT_MATR_AI;
			else if (pblock->pos.X > WIDTH - 60)
				return 1;
			else if (pblock->pos.Y > HEIGHT - 8)
					return 2;
			else { // ���� ���������� ����������
				pblock->lenX = 60;
				pblock->lenY = 8;
				pblock->cond = BUTTON_INIT;
				*pi_player = i;

				SetColor(h, "bgmsg", "textmsg", ptheme);
				PrintMatrCardsAI(h, settingsAI[i]->info.matr_cards, pblock->pos);
				SetColor(h, "bgbase", "textbase", ptheme);
			}
		} else
			return 0;
	}
	return res;
}

