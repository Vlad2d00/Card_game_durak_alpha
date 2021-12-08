#if !defined(__PRINT_ELEMENTS_H) 
#define __PRINT_ELEMENTS_H 

#include "header.h"

/*����� � ���� � ������������ h ������� ���������� � ����� point*/
void PrintAchievementTable(HANDLE h, COORD point, Ttheme* ptheme) {
	COORD point_base = point;
	MoveConsoleCursorPoint(h, &point, 4, -1);
	printf("_");
	MoveConsoleCursorPoint(h, &point, 30, 0);
	printf("_");
	MoveConsoleCursorPoint(h, &point, -34, 1);
	printf(" __|_|_______________  __________|_|_");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                    \\//             \\");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                                     |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                                     |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                                     |");
	MoveConsoleCursorPoint(h, &point, 1, -3);
	PrintWordLarge(h, point, "�������", 35);
	MoveConsoleCursorPoint(h, &point, 19, 0);
	printf("\\//");
	MoveConsoleCursorPoint(h, &point, -20, 4);
	printf("\\_____________________________________|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("/                                     |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|__,__________________________________|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|  \\                              \\   |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|___\\ _____________________________/__|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|    \\/                          /_   |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|_____________________________________|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                                     |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|_\\______________________/\\___________|");
	MoveConsoleCursorPoint(h, &point, 3, 1);
	printf("| /");
	MoveConsoleCursorPoint(h, &point, 31, 0);
	printf("\\ |");
	for (size_t i = 0; i < 3; i++) {
		MoveConsoleCursorPoint(h, &point, -31, 1);
		printf("| |");
		MoveConsoleCursorPoint(h, &point, 31, 0);
		printf("| |");
	}
	MoveConsoleCursorPoint(h, &point, -31, 1);
	printf("|_|");
	MoveConsoleCursorPoint(h, &point, 31, 0);
	printf("|_|");

	COORD point0;
	char s[100], s_space[50];
	point0.X = point_base.X + 1;
	point0.Y = point_base.Y + 4;

	sprintf(s, "������ %s", ptheme->userName);
	GetStrSingleChar(s_space, ' ', (37 - strlen(s)) / 2);
	SetConsoleCursorPosition(h, point0);
	printf("%s%s", s_space, s);

	point0.Y = point_base.Y + 6;
	if (ptheme->raiting < 1400)
		sprintf(s, "�������: %u (�������)", ptheme->raiting);
	else if (ptheme->raiting < 2100)
		sprintf(s, "�������: %u (�������)", ptheme->raiting);
	else if (ptheme->raiting < 3000)
		sprintf(s, "�������: %u (�����������)", ptheme->raiting);
	else if (ptheme->raiting < 3850)
		sprintf(s, "�������: %u (������)", ptheme->raiting);
	else if (ptheme->raiting < 4300)
		sprintf(s, "�������: %u (�����������)", ptheme->raiting);
	else
		sprintf("�������: %u (���)", ptheme->raiting);
	GetStrSingleChar(s_space, ' ', (37 - strlen(s)) / 2);
	SetConsoleCursorPosition(h, point0);
	printf("%s%s", s_space, s);

	point0.X = point_base.X + 12;
	point0.Y = point_base.Y + 8;
	SetConsoleCursorPosition(h, point0);
	printf("���-�� �����: %u", ptheme->countWins);

	point0.X = point_base.X + 10;
	point0.Y = point_base.Y + 10;
	SetConsoleCursorPosition(h, point0);
	printf("���-�� ���������: %u", ptheme->countLose);

	point0.X = point_base.X + 1;
	point0.Y = point_base.Y + 12;
	if (ptheme->minutsInGame < 60)
		sprintf(s, "� ����: %u �����", ptheme->minutsInGame);
	else if (ptheme->minutsInGame < 1440)
		sprintf(s, "� ����: %u ��� %u �����", ptheme->minutsInGame / 60,
			ptheme->minutsInGame % 60);
	else
		sprintf(s, "� ����: %u ���� %u ��� %u �����", ptheme->minutsInGame / 1440,
			ptheme->minutsInGame / 60 % 24, ptheme->minutsInGame % 60);
	GetStrSingleChar(s_space, ' ', (37 - strlen(s)) / 2);
	SetConsoleCursorPosition(h, point0);
	printf("%s%s", s_space, s);
}

/*����� � ���� � ������������ h ����������� ����� ������
������� � ����� point*/
void PrintImgBookRuleButton(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf(" _________ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("/\\ �������\\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("\\ \\________\\");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" \\/________/");
}

/*����� � ���� � ������������ h ������� � ��������
������ �� ��� ������� � ����� block*/
void PrintTableSimulation(HANDLE h, Tblock block, Ttheme* ptheme) {
	COORD point = block.pos;
	SetConsoleCursorPosition(h, point);
	SetColor(h, "bgmsg", "textmsg", ptheme);
	printf(".---------------------------------------------------------------.");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("| ? | � ������ |       ������� ����      |         ���          |");
	for (size_t i = 0; i < 6; i++) {
		MoveConsoleCursorPoint(h, &point, 0, 1);
		printf("|---|----------|-------------------------|----------------------|");
		MoveConsoleCursorPoint(h, &point, 0, 1);
		printf("|                                                               |");
	}
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("'---------------------------------------------------------------'");
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*����� � ���� � ������������ h ���������
"card game durak" � ������� point*/
void PrintImgHeaderMainMenu(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("   ___              _                                   ___                 _    \n");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  / __\\__ _ _ __ __| |   __ _  __ _ _ __ ___   ___     /   \\_   _ _ __ __ _| | __\n");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" / /  / _` | '__/ _` |  / _` |/ _` | '_ ` _ \\ / _ \\   / /\\ / | | | '__/ _` | |/ /\n");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("/ /__| (_| | | | (_| | | (_| | (_| | | | | | |  __/  / /_//| |_| | | | (_| |   < \n");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("\\____/\\__,_|_|  \\__,_|  \\__, |\\__,_|_| |_| |_|\\___| /___,'  \\__,_|_|  \\__,_|_|\\_\\\n");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("                        |___/                                                    \n");
}

/*������ � ������� a ������� 8 x 15 ����������� ����*/
void SetCatMatr(char a[8][WIDTH]) {
	char s_cat[] = "\
        />__/> \
       | _  _\\ \
      (`= _x =)\
     /       / \
 __/ `      )  \
/  _    | | |  \
| (_ \\___`_)_) \
 \\__>          \
\0";
	size_t k = 0;
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 15; j++) {
			a[i][j] = s_cat[k++];
		}
	}
}

/*����� � ���� � ������������ h ������� a ������� 
m x n � � ������� � ����� point*/
void PrintMatrPoint(HANDLE h, char (*a)[WIDTH], size_t m, size_t n, COORD point) {
	int j, k;
	size_t baseX = point.X;
	for (size_t i = 0; i < m; i++) {
		j = 0;
		while (j < n && a[i][j] == ' ') {
			j++;
		}
		k = n - 1;
		while (k >= 0 && a[i][k] == ' ') {
			k--;
		}

		point.X = baseX + j;
		SetConsoleCursorPosition(h, point);
		while (j <= k) {
			printf("%c", a[i][j++]);
		}
		point.Y++;
	}
}

/*����� � ���� � ������������ h �����������
��������� �������� ���� � ������� point*/
void PrintPointerMainMenu(HANDLE h, COORD point) {
	MoveConsoleCursorPoint(h, &point, -7, 1); // 1 ������ ������
	printf("       ");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 2 ������ ������
	printf("  /\\   ");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 3 ������ ������
	printf(" /  \\  ");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 4 ������ ������
	printf("(_  _) ");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 5 ������ ������
	printf(" /__\\  ");
}

/*����� � ���� � ������������ h ������ ������ �� ��������
������� 6 x 13 � ����� point*/
void PrintSymbolIconSun(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("      |      ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" \\ \\ ___/  / ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("_  /     \\ _ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" _|       | _");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   \\ ___ /   ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  /   |   \\  ");
}

/*����� � ���� � ������������ h ������ ����� �� ��������
������� 6 x 13 � ����� point*/
void PrintSymbolIconRain(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("\\  \\  \\    \\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     \\   \\  \\");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("\\  \\    \\    ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  \\  \\  \\  \\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  \\  \\  \\  \\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" _x %%_ __x%% x");
}

/*����� � ���� � ������������ h ������ ��������� �� ��������
������� 6 x 13 � ����� point*/
void PrintSymbolIconSnow(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf(" *    *   *  ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  *   *  *  *");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   * *    *  ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" *   *  *  * ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  **   *  *  ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  *    *     ");
}

/*����� � ���� � ������������ h ���������� ������� ������ ����� block*/
void PrintOutlineBlock(HANDLE h, Tblock block) {
	char outline[WIDTH];
	COORD point = block.pos;
	point.X--;
	point.Y--;
	GetStrSingleChar(outline, '-', block.lenX);
	SetConsoleCursorPosition(h, point);
	printf(".%s.", outline);

	for (size_t i = 0; i < block.lenY; i++) {
		MoveConsoleCursorPoint(h, &point, 0, 1);
		printf("|");
	}
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("'%s'", outline);

	MoveConsoleCursorPoint(h, &point, block.lenX + 1, 0);
	for (size_t i = 0; i < block.lenY; i++) {
		MoveConsoleCursorPoint(h, &point, 0, -1);
		printf("|");
	}
}

/*����� � ���� � ������������ h ������� ����������� ������
���� � ����� point � �������� ����� ��������� �� ������ ptheme*/
void PrintTableControlKeys(HANDLE h, COORD point, Ttheme* ptheme) {
	SetColor(h, "bgbase", "textbase", ptheme);
	SetConsoleCursorPosition(h, point);
	printf(" _______  ___________________________________________");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|       \\/                              /\\_          |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|                ����������� �������:   \\_\\      ____/");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Space]\\textbase-bgbase: - ����������� �����.                        |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Esc]\\textbase-bgbase: - �������� ����� ����� / ����� � ����.        |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[\"�������\"]\\textbase-bgbase: - ����������� ����� �������� � �������. |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Shift]\\textbase-bgbase: - ��� / ������������� ����� ����.           |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Enter]\\textbase-bgbase: - ����������� ���� ������ / �����.          |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Tab]\\textbase-bgbase: - ������� ���� ����� ���� / �������� ����.    |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Backspace]\\textbase-bgbase: - ������� ��������� ������ ���� �����.  |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	PrintColor(h, "|\\bgbase-textbase:[Ctrl]\\textbase-bgbase: + \\bgbase-textbase:[\"������ ����\"]\\textbase-bgbase: - �������� �������� ����.  |", ptheme);
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|________________________________/ \\\\________________|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("------| |------------------------------------| |------");
	MoveConsoleCursorPoint(h, &point, 6, 1);
	printf("| |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|_|");
	MoveConsoleCursorPoint(h, &point, 39, -1);
	printf("| |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|_|");
}

/*����� � ���� � ������������ h � �����
point ����������� ����� card*/
void PrintImgCardNotColor(HANDLE h, COORD point, Tcard card) {
	SetConsoleCursorPosition(h, point); // 1-� ������
	printf(" _________ ");

	MoveConsoleCursorPoint(h, &point, 0, 1); // 2-� ������
	if (card.n <= 10)
		printf("|%2u       |", card.n);
	else
		printf("| %c       |", GetCharDigintyCard(card.n));

	MoveConsoleCursorPoint(h, &point, 0, 1); // 3-� ������
	switch (card.m) {
	case '�': printf("|  _  _   |"); break;
	case '�': printf("|   /\\    |"); break;
	case '�': printf("|    _    |"); break;
	case '�': printf("|   / \\   |"); break;
	}
	MoveConsoleCursorPoint(h, &point, 0, 1); // 4-� ������
	switch (card.m) {
	case '�': printf("| ( \\/ )  |"); break;
	case '�': printf("|  /  \\   |"); break;
	case '�': printf("|  _| |_  |"); break;
	case '�': printf("|  /   \\  |"); break;
	}

	MoveConsoleCursorPoint(h, &point, 0, 1); // 5-� ������
	switch (card.m) {
	case '�': printf("|  \\  /   |"); break;
	case '�': printf("| (_  _)  |"); break;
	case '�': printf("| (_   _) |"); break;
	case '�': printf("|  \\   /  |"); break;
	}

	MoveConsoleCursorPoint(h, &point, 0, 1); // 6-� ������
	switch (card.m) {
	case '�': printf("|   \\/    |"); break;
	case '�': printf("|  /__\\   |"); break;
	case '�': printf("|   /_\\   |"); break;
	case '�': printf("|   \\ /   |"); break;
	}

	MoveConsoleCursorPoint(h, &point, 0, 1); // 7-� ������
	if (card.n <= 10)
		printf("|      %2u |", card.n);
	else
		printf("|       %c |", GetCharDigintyCard(card.n));

	MoveConsoleCursorPoint(h, &point, 0, 1); // 8-� ������
	printf("|_________|");
}

/*����� � ���� � ������������ h � �����
point ����������� ����� card � �������� �����
��������� �� ������ ptheme*/
void PrintImgCard(HANDLE h, COORD point, Tcard card, Ttheme* ptheme) {
	SetColorBySuit(h, card.m, ptheme);
	PrintImgCardNotColor(h, point, card);
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*����� � ���� � ������������ h � �����
point ����������� ����� card � ������ ���� cbg
� ������ �������� ctext � �������� ����� ���������
�� ������ ptheme*/
void PrintImgCardColor(HANDLE h, COORD point, Tcard card,
	char* cbg, char* ctext, Ttheme* ptheme) {
	SetColor(h, cbg, ctext, ptheme);
	PrintImgCardNotColor(h, point, card);
	SetColor(h, "bgbase", ctext, ptheme);
	SetConsoleCursorPosition(h, point);
	printf(" _________ ");
	SetConsoleCursorPosition(h, point);
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*����� � ���� � ������������ h � �����
point ������� ����� � �������� ����� ���������
�� ������ ptheme*/
void PrintShirtCard(HANDLE h, COORD point, Ttheme* ptheme) {
	SetConsoleCursorPosition(h, point); // 1-� ������
	SetColor(h, "bgbase", "texttarget", ptheme);
	printf(" _________ ");
	for (size_t i = 0, f = 0; i < 6; i++, f++) {
		MoveConsoleCursorPoint(h, &point, 0, 1); // (2 + i)-� ������
		if (f % 2)
			printf("|\\/\\/\\/\\/\\| ");
		else
			printf("|/\\/\\/\\/\\/| ");
	}
	MoveConsoleCursorPoint(h, &point, 0, 1); // 8-� ������
	printf("|_________|");

	SetColor(h, "bgbase", "textbase", ptheme);
}

/*����� � ���� � ������������ h � ����� point ������� 
����������� ����� card, ������� � k-�� ������� �� n ��������*/
void PrintRegionImgCardColor(HANDLE h, COORD point, Tcard card, 
	size_t k, size_t n, Ttheme* ptheme) {
	char* p_line;
	size_t k2 = k + n; // ������ ��������� ������� ��� ������ �����
	SetColorBySuit(h, card.m, ptheme);

	SetConsoleCursorPosition(h, point); // 1-� ������
	char line[12] = " _________ ";
	p_line = &line[k];
	line[k2] = '\0';
	printf("%s", p_line);

	for (size_t i = 1; i < 8; i++) {
		MoveConsoleCursorPoint(h, &point, 0, 1);
		switch (i) {
			case 1:
				if (card.n <= 10)
					sprintf(line, "|%2u       |", card.n);
				else
					sprintf(line, "| %c       |", GetCharDigintyCard(card.n));
				break;
			case 2:
				switch (card.m) {
					case '�': sprintf(line, "|  _  _   |"); break;
					case '�': sprintf(line, "|   /\\    |"); break;
					case '�': sprintf(line, "|    _    |"); break;
					case '�': sprintf(line, "|   / \\   |"); break;
				}
				break;
			case 3:
				switch (card.m) {
					case '�': sprintf(line, "| ( \\/ )  |"); break;
					case '�': sprintf(line, "|  /  \\   |"); break;
					case '�': sprintf(line, "|  _| |_  |"); break;
					case '�': sprintf(line, "|  /   \\  |"); break;
				}
				break;
			case 4:
				switch (card.m) {
					case '�': sprintf(line, "|  \\  /   |"); break;
					case '�': sprintf(line, "| (_  _)  |"); break;
					case '�': sprintf(line, "| (_   _) |"); break;
					case '�': sprintf(line, "|  \\   /  |"); break;
				}
				break;
			case 5:
				switch (card.m) {
					case '�': sprintf(line, "|   \\/    |"); break;
					case '�': sprintf(line, "|  /__\\   |"); break;
					case '�': sprintf(line, "|   /_\\   |"); break;
					case '�': sprintf(line, "|   \\ /   |"); break;
				}
				break;
			case 6:
				if (card.n <= 10)
					sprintf(line, "|      %2u |", card.n);
				else
					sprintf(line, "|       %c |", GetCharDigintyCard(card.n));
				break;
			case 7:
				sprintf(line, "|_________|");
				break;
		}
		p_line = &line[k];
		line[k2] = '\0';
		printf("%s", p_line);
	}
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*����� � ���� � ������������ h � ����� point ����������� �����*/
void PrintSpecialCard(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point); // 1-� ������
	printf(" _________ ");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 2-� ������
	printf("|\\       /|");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 3-� ������
	printf("| \\#### / |");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 4-� ������
	printf("| ##  ##  |");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 5-� ������
	printf("| ##      |");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 6-� ������
	printf("| ##  ##  |");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 7-� ������
	printf("| /#### \\ |");
	MoveConsoleCursorPoint(h, &point, 0, 1); // 8-� ������
	printf("|_________|");
}

/*����� � ���� � ������������ h � ����� block �������������� 
����� color � �������� ����� ��������� �� ������ ptheme*/
void PrintRectangle(HANDLE h, Tblock block, char* color, Ttheme* ptheme) {
	SetConsoleCursorPosition(h, block.pos);
	SetColor(h, color, color, ptheme);
	for (size_t i = 0; i < block.lenY; i++) {
		for (size_t j = 0; j < block.lenX; j++) {
			printf(" ");
		}
		MoveConsoleCursorPoint(h, &block.pos, 0, 1);
	}
	SetColor(h, "bgbase", "textbase", ptheme);
}

/*����� � ���� � ������������ h � ����� point ����� ������� 40 x 141*/
void PrintLargeBook(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("            =------------:::::::::::::::------------------*===*-             -:===========+++*****++++++==============++++**:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("          -%%=                                                   -%%+    *%%=*                                                  %%#*");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("         -=%%=                                                      -%%%%-                                                      +@%%@%%*");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("        -%%*%%+                                                       :*                                                       *#%%%%:%%@##:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("       ##@%%=*                                                       -+                                                       -#%%=*%%=%%#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("      %%##%%%%=:                                                       -+                                                        @%%%%+%%+=#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     -###%%%%%%                                                        -+                                                        %%%%=%%++%%##");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     *##@%%==                                                        -+                                                        ==%%%%*=%%@#");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     +##%%%%%%%%                                                        -=                                                        +#=%%:%%%%%%#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     %%##=%%%%=                                                         =                                                        :@%%=*%%==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     @##=%%=+                                                         =                                                         #%%+=%%+=#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     ###+@=*                                                         +                                                         =%%=%%=+%%#@");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    -###=%%=:                                                         =                                                         %%%%=%%*=%%@#-");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    *##%%%%%%=-                                                         =                                                         +%%%%%%:%%%%=#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    =##%%%%%%%%                                                          =                                                         *@%%++%%==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    %%##=%%%%=                                                          =                                                         -@%%+=%%*=#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    ###+@%%=                                                          =                                                          @%%=%%=*%%##");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("    ##@*@==                                                          =                                                          ==%%%%*=%%@#");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   :##%%*@++                                                          =                                                          =%%==*%%%%=#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   *##%%=#+*                                                          =                                                          +%%%%++%%==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   =#@%%=%%=-                                                          =                                                          :%%%%+%%%%+=#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   %%#@=%%%%%%                                                           =                                                           %%%%=%%=+%%#@");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   ##@*%%%%%%                                                           =                                                           =%%%%%%+=%%@#");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   ##@:%%=%%                                                           =                                                           %%%%%%=*%%%%%%#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  :##%%:#==                                                           =                                                           +%%%%+=%%==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  +#@%%*#++                                                           =                                                           *%%%%*%%%%+=#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  =#@%%+#+*                                                           =                                                           -%%%%=%%=+%%#@");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  %%#%%+=#=-                                                           =                                                            %%%%%%%%*=@@#-");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  ##%%*%%%%%%-                                                           =                                                            =%%%%=*%%%%=#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  ##%%:%%%%%%                                                            =                                                            ==%%*=%%==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" -##@:@==                                                            =                                                            +=%%*%%%%+=#=");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" *#%%%%:#+=                                                            +                                                            :=%%=%%=+%%#@");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" =#%%%%:#*=                                                            =                                                            -=%%%%%%+=%%@#");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" @#%%+*#**                                                            +                                                             %%%%%%=+%%@%%#:");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" ##%%*+#=:                                                            +                                                             =%%%%*=@==#+");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" ##@:=@=-                                                            =                                                             ==%%*%%%%+%%#%%");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(":#@%%:%%%%%%==%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@###########@@%%%%=++*:-                     =                  ---:::::********++++++++++++++======#######@@%%=%%=+%%#@");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("*#%%%%:@####################################################@##########################################################################@#@#");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("=#@@%%####################################################################################################################################:");
}

/*����� � ���� � ������������ h ������ ������� ����� 
������� 3 x 8 � ����� point*/
void PrintSymbolIconLeft(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf(" /|____ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("(  ____|");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" \\|     ");
}

/*����� � ���� � ������������ h ������ ��������
������� 6 x 9 � ����� point*/
void PrintSymbolIconBulb(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("  _____  ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" /     \\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("| Shift |");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" \\_ � _/ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   |_|   ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("   \"\"\"   ");
}

/*����� � ���� � ������������ h ������ ���������
������� 5 x 8 � ����� point*/
void PrintSymbolIconVoice(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf("   __   ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf(" _/  |-_");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|_Tab|-_");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("  \\__|- ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("        ");
}

/*����� � ���� � ������������ h ������ ������� ������ 
������� 3 x 8 � ����� point*/
void PrintSymbolIconRight(HANDLE h, COORD point) {
	SetConsoleCursorPosition(h, point);
	printf(" ____|\\ ");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("|____  )");
	MoveConsoleCursorPoint(h, &point, 0, 1);
	printf("     |/ ");
}

#endif 