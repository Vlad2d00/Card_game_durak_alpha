#include "header.h"

/*���������� ������� ��������� � ������������ ������
(x, y), �������� dx �� dy � ��������� ���������� cond*/
Tblock GetBlock(int x, int y, size_t dx, size_t dy, size_t cond) {
	Tblock block;
	block.pos.X = x;
	block.pos.Y = y;
	block.lenX = dx;
	block.lenY = dy;
	block.cond = cond;
	return block;
}

/*���������� ����� ������������ (x, y)*/
COORD GetPoint(int x, int y) {
	COORD point;
	point.X = x;
	point.Y = y;
	return point;
}

/*������������� � ��������� �� ������ pblocks
��������� ����� ������ ������ � ������� ����������
� ������� ���� ����, ��������� ��������� �������
��������� �� ������ p_allblock*/
void InitblocksMainMenu(TblocksMainMenu* pblocks, TblocksMenu* p_allblocks) {
	pblocks->header = GetBlock( // ����� ����
		WIN_X0 + WIDTH / 2 - 81 / 2,
		WIN_Y0 + 1,
		81,
		6,
		BUTTON_INIT
	);

	pblocks->buttons = GetBlock( // ������ �������� ����
		WIN_X0 + (WIDTH - WIDTH_BUTTON_MENU) / 2,
		WIN_Y0 + 8,
		WIDTH_BUTTON_MENU,
		(5 + DISTANCE_BUTTON) * 5,
		BUTTON_INIT
	);

	pblocks->story = GetBlock( // ������ �������� ����
		pblocks->buttons.pos.X,
		pblocks->buttons.pos.Y,
		WIDTH_BUTTON_MENU,
		5,
		BUTTON_INIT
	);

	pblocks->custom_game = GetBlock( // ������ ������ ����
		pblocks->buttons.pos.X,
		pblocks->story.pos.Y + 5 + DISTANCE_BUTTON,
		WIDTH_BUTTON_MENU,
		5,
		BUTTON_INIT
	);

	pblocks->simulation = GetBlock( // ������ ���������
		pblocks->buttons.pos.X,
		pblocks->custom_game.pos.Y + 5 + DISTANCE_BUTTON,
		WIDTH_BUTTON_MENU,
		5,
		BUTTON_INIT
	);

	pblocks->settings = GetBlock( // ������ ���������
		pblocks->buttons.pos.X,
		pblocks->simulation.pos.Y + 5 + DISTANCE_BUTTON,
		WIDTH_BUTTON_MENU,
		5,
		BUTTON_INIT
	);

	pblocks->exit = GetBlock( // ������ �����
		pblocks->buttons.pos.X,
		pblocks->settings.pos.Y + 5 + DISTANCE_BUTTON,
		WIDTH_BUTTON_MENU,
		5,
		BUTTON_INIT
	);

	pblocks->book_rule = GetBlock( // ������ �������� �� ����� ������
		WIN_X0 + WIDTH - 35,
		WIN_Y0 + HEIGHT - 5,
		13,
		3,
		BUTTON_INIT
	);

	pblocks->achievement_table = GetBlock( // ������� ����������
		WIN_X0 + 3,
		WIN_Y0 + HEIGHT - 20,
		39,
		14,
		BUTTON_INIT
	);

	// ����� �������� ��� ������� ����
	pblocks->pwindow = p_allblocks->pwindow;
	pblocks->pversion = p_allblocks->pversion;
	pblocks->pfooter = p_allblocks->pfooter;
	pblocks->pcat = p_allblocks->pcat;
	pblocks->pcursore = p_allblocks->pcursore;
}

/*������������� � ��������� �� ������ pblocks
��������� ����� ������ ������ � ������� ����������
� ������� ���� �������� ����� ����, ���������
��������� ������� ��������� �� ������ p_allblock*/
void InitblocksCustomGame(TblocksCustomGame* pblocks, TblocksMenu* p_allblocks) {
	pblocks->header = GetBlock( // ����� ����
		WIN_X0 + (WIDTH - GetSizeLargeWord("���������������� ����")) / 2,
		WIN_Y0 + 1,
		GetSizeLargeWord("���������������� ����") + 1,
		5,
		BUTTON_INIT
	);

	pblocks->info = GetBlock( // ������� ��������
		WIN_X0 + WIDTH / 8,
		WIN_Y0 + 6,
		WIDTH * 3 / 4,
		23,
		BUTTON_INIT
	);

	pblocks->table = GetBlock( // ������� �������� �������
		pblocks->info.pos.X + 3,
		pblocks->info.pos.Y + 1,
		65,
		15,
		BUTTON_INIT
	);

	pblocks->players[0] = GetBlock( // ������ �������� �������
		pblocks->table.pos.X + 1,
		pblocks->table.pos.Y + 3,
		63,
		1,
		BUTTON_INIT
	);
	for (size_t i = 1; i < 6; i++) {
		pblocks->players[i] = pblocks->players[i - 1];
		pblocks->players[i].pos.Y += 2;
	}

	pblocks->see_mode = GetBlock( // �������� ����� �����������
		pblocks->table.pos.X,
		pblocks->table.pos.Y + pblocks->table.lenY + 2,
		GetSizeButtonMark("���. ����� ����������� (���-�����)"),
		1,
		BUTTON_INIT
	);

	pblocks->only_ai = GetBlock( // �������� ����� ������ ��
		pblocks->see_mode.pos.X,
		pblocks->see_mode.pos.Y + 2,
		GetSizeButtonMark("���. ����� \"������ ��\" (��� ������������)"),
		1,
		BUTTON_INIT
	);

	pblocks->effect = GetBlock( // ���������� �������
		pblocks->info.pos.X + pblocks->info.lenX - 43,
		pblocks->info.pos.Y + 1,
		40,
		15,
		BUTTON_INIT
	);

	pblocks->special_card = GetBlock( // �������� ����������� �����
		pblocks->table.pos.X + pblocks->table.lenX - 4,
		pblocks->table.pos.Y + pblocks->table.lenY + 2,
		GetSizeButtonMark("���. ������������� ����������� ���� (�� ��������, ������)"),
		1,
		BUTTON_INIT
	);

	pblocks->multiplayer = GetBlock( // �������� �����������
		pblocks->special_card.pos.X,
		pblocks->special_card.pos.Y + 2,
		GetSizeButtonMark("���. ���� �� ��������� ���� (������� �� ��������)"),
		1,
		BUTTON_INIT
	);

	pblocks->chat = GetBlock( // ��� 
		WIN_X0 + 2,
		pblocks->info.pos.Y + pblocks->info.lenY + 1,
		50,
		18,
		BUTTON_INIT
	);

	pblocks->button_chat = GetBlock( // ������ ����
		pblocks->chat.pos.X,
		pblocks->chat.pos.Y + pblocks->chat.lenY - 1,
		pblocks->chat.lenX,
		1,
		BUTTON_INIT
	);

	pblocks->input_chat = GetBlock( // ����������� ���� ����� ������ ����
		pblocks->button_chat.pos.X,
		pblocks->button_chat.pos.Y,
		WIDTH / 2,
		1,
		BUTTON_INIT
	);

	pblocks->start = GetBlock( // ������ ������� ������� ������
		WIN_X0 + (WIDTH - GetSizeButtonStandart("������ ����")) / 2,
		pblocks->info.pos.Y + pblocks->info.lenY + 1,
		GetSizeButtonStandart("������ ����"),
		5,
		BUTTON_INIT
	);

	pblocks->goto_menu = GetBlock( // ������ ������ � ������� ����
		WIN_X0 + (WIDTH - GetSizeButtonStandart("� ������� ����")) / 2,
		pblocks->start.pos.Y + pblocks->start.lenY + DISTANCE_BUTTON,
		GetSizeButtonStandart("� ������� ����"),
		5,
		BUTTON_INIT
	);

	// ����� �������� ��� ������� ����
	pblocks->pwindow = p_allblocks->pwindow;
	pblocks->pversion = p_allblocks->pversion;
	pblocks->pfooter = p_allblocks->pfooter;
	pblocks->pcat = p_allblocks->pcat;
	pblocks->pcursore = p_allblocks->pcursore;
}

/*������������� � ��������� �� ������ pblocks
��������� ����� ������ ������ � ������� ����������
� ������� ���� ��������� ���, ��������� ���������
������� ��������� �� ������ p_allblock*/
void InitblocksSimulation(TblocksSimulation* pblocks, TblocksMenu* p_allblocks) {
	pblocks->header = GetBlock( // ����� ����
		WIN_X0 + (WIDTH - GetSizeLargeWord("���� ��������� ���")) / 2,
		WIN_Y0 + 1,
		GetSizeLargeWord("���� ��������� ���") + 1,
		3,
		BUTTON_INIT
	);

	pblocks->info = GetBlock( // ������� �������� � �������� ���������
		WIN_X0 + (WIDTH - WIDTH_SIMULATION_INFO) / 2,
		WIN_Y0 + 6,
		WIDTH_SIMULATION_INFO,
		23,
		BUTTON_INIT
	);

	pblocks->table = GetBlock( // ������� �������� �������
		pblocks->info.pos.X + (pblocks->info.lenX - 65) / 2 - 1,
		pblocks->info.pos.Y + 1,
		65,
		15,
		BUTTON_INIT
	);

	pblocks->players[0] = GetBlock( // ������ �������� �������
		pblocks->table.pos.X + 1,
		pblocks->table.pos.Y + 3,
		63,
		1,
		BUTTON_INIT
	);
	for (size_t i = 1; i < 6; i++) {
		pblocks->players[i] = pblocks->players[i - 1];
		pblocks->players[i].pos.Y += 2;
	}

	pblocks->count_sim = GetBlock( // ������ �������� ���-�� ��������� ���
		WIN_X0 + (WIDTH - GetSizeButtonInputNumber("���������� ��������� ���") - 10) / 2,
		pblocks->table.pos.Y + pblocks->table.lenY + 2,
		GetSizeButtonInputNumber("���������� ��������� ���") + 10,
		1,
		BUTTON_INIT
	);

	pblocks->start = GetBlock( // ������ ������� ���������
		WIN_X0 + (WIDTH - GetSizeButtonStandart("������")) / 2,
		pblocks->info.pos.Y + pblocks->info.lenY + 1,
		GetSizeButtonStandart("������"),
		5,
		BUTTON_INIT
	);

	pblocks->goto_menu = GetBlock( // ������ ������ � ������� ����
		WIN_X0 + (WIDTH - GetSizeButtonStandart("� ������� ����")) / 2,
		pblocks->start.pos.Y + pblocks->start.lenY + DISTANCE_BUTTON,
		GetSizeButtonStandart("� ������� ����"),
		5,
		BUTTON_INIT
	);

	pblocks->stop = GetBlock( // ������ ��������� ���������
		WIN_X0 + (WIDTH - GetSizeButtonStandart("����������")) / 2,
		pblocks->start.pos.Y,
		GetSizeButtonStandart("����������"),
		pblocks->start.lenY,
		BUTTON_INIT
	);

	pblocks->anew = GetBlock( // ������ ������ ��������� ���������
		WIN_X0 + (WIDTH - GetSizeButtonStandart("����� ���������")) / 2,
		pblocks->start.pos.Y,
		GetSizeButtonStandart("����� ���������"),
		pblocks->start.lenY,
		BUTTON_INIT
	);

	// ����� �������� ��� ������� ����
	pblocks->pwindow = p_allblocks->pwindow;
	pblocks->pversion = p_allblocks->pversion;
	pblocks->pfooter = p_allblocks->pfooter;
	pblocks->pcat = p_allblocks->pcat;
	pblocks->pcursore = p_allblocks->pcursore;
}

/*������������� � ��������� �� ������ pblocks
��������� ����� ������ ������ � ������� ����������
� ������� ���� ��������, ��������� ��������� �������
��������� �� ������ p_allblock*/
void InitblocksSettings(TblocksSettings* pblocks, TblocksMenu* p_allblocks) {
	pblocks->header = GetBlock( // ����� ����
		WIN_X0 + (WIDTH - GetSizeButtonStandart("���� ��������")) / 2,
		WIN_Y0 + 1,
		GetSizeLargeWord("���� ��������") + 1,
		3,
		BUTTON_INIT
	);

	pblocks->table = GetBlock( // ������� �������
		WIN_X0 + 3,
		WIN_Y0 + 5,
		WIDTH - 6,
		17,
		BUTTON_INIT
	);

	pblocks->table_control_keys = GetBlock( // ������� ����������� ������
		WIN_X0 + 2,
		WIN_Y0 + HEIGHT - 16,
		54,
		12,
		BUTTON_INIT
	);

	pblocks->theme = GetBlock( // ��������� ���� ���������� 
		pblocks->table.pos.X + pblocks->table.lenX - 34,
		pblocks->table.pos.Y,
		GetSizeLargeWord("����"),
		3,
		BUTTON_INIT
	);
	
	pblocks->theme_day = GetBlock( // ������� ���� ����������
		pblocks->theme.pos.X - 12,
		pblocks->theme.pos.Y + 6,
		GetSizeButtonMark("���� (������� ���)"),
		1,
		BUTTON_INIT
	);

	pblocks->theme_night = GetBlock( // ������ ���� ����������
		pblocks->theme_day.pos.X,
		pblocks->theme_day.pos.Y + 2,
		GetSizeButtonMark("���� (������ ���)"),
		1,
		BUTTON_INIT
	);

	pblocks->theme_east = GetBlock( // ��������� ���� ���������� 
		pblocks->theme_night.pos.X,
		pblocks->theme_night.pos.Y + 2,
		GetSizeButtonMark("������ (�������, ������, ������)"),
		1,
		BUTTON_INIT
	);

	pblocks->theme_black_blue = GetBlock( // �����-����� ���� ���������� 
		pblocks->theme_east.pos.X,
		pblocks->theme_east.pos.Y + 2,
		GetSizeButtonMark("�����-����� (����� � ������)"),
		1,
		BUTTON_INIT
	);

	pblocks->theme_new_year = GetBlock( // ���������� ���� ���������� 
		pblocks->theme_black_blue.pos.X,
		pblocks->theme_black_blue.pos.Y + 2,
		GetSizeButtonMark("����� ��� (����� � �������)"),
		1,
		BUTTON_INIT
	);


	pblocks->table_weather = GetBlock( // ������� ������� ��� �������� ��������
		WIN_X0 + WIDTH * 3 / 4 - 7,
		pblocks->table.pos.Y + pblocks->table.lenY + 2,
		47,
		13,
		BUTTON_INIT
	);

	pblocks->weather = GetBlock( // ��������� �������� ��������
		pblocks->table_weather.pos.X + (pblocks->table_weather.lenX 
			- GetSizeButtonStandart("������")) / 2 + 1,
		pblocks->table_weather.pos.Y,
		GetSizeButtonStandart("������"),
		3,
		BUTTON_INIT
	);

	pblocks->weather_snow = GetBlock( //  ������: ����
		pblocks->weather.pos.X + (pblocks->weather.lenX - 14) / 2,
		pblocks->weather.pos.Y + 5,
		13,
		6,
		BUTTON_INIT
	);

	pblocks->weather_clear = GetBlock( // ������: ����
		pblocks->weather_snow.pos.X - 14,
		pblocks->weather_snow.pos.Y,
		13,
		6,
		BUTTON_INIT
	);

	pblocks->weather_rain = GetBlock( // ������: �����
		pblocks->weather_snow.pos.X + 14,
		pblocks->weather_snow.pos.Y,
		13,
		6,
		BUTTON_INIT
	);


	pblocks->volume = GetBlock( // ��������� ��������� ������ � ������
		pblocks->table.pos.X + (pblocks->table.lenX - GetSizeLargeWord("����� � ������")) / 2 + 4,
		pblocks->table.pos.Y,
		GetSizeLargeWord("����� � ������"),
		3,
		BUTTON_INIT
	);

	pblocks->music_bg = GetBlock( // ������� ������
		pblocks->volume.pos.X + 10,
		pblocks->volume.pos.Y + 4,
		GetSizeButtonMark("���. ������� ������"),
		1,
		BUTTON_INIT
	);

	pblocks->sounds_weather = GetBlock( // ����� ������
		pblocks->music_bg.pos.X,
		pblocks->music_bg.pos.Y + 2,
		GetSizeButtonMark("���. ���� ������"),
		1,
		BUTTON_INIT
	);

	pblocks->sounds = GetBlock( // ������ �����
		pblocks->sounds_weather.pos.X,
		pblocks->sounds_weather.pos.Y + 2,
		GetSizeButtonMark("���. ������ �����"),
		1,
		BUTTON_INIT
	);


	pblocks->game = GetBlock( // ��������� ������� ��������
		pblocks->table.pos.X + 20,
		pblocks->table.pos.Y,
		GetSizeLargeWord("����"),
		3,
		BUTTON_INIT
	);

	pblocks->chat = GetBlock( // ���
		pblocks->game.pos.X - 16,
		pblocks->game.pos.Y + 4,
		GetSizeButtonMark("�������� ��� �� ������� �����"),
		1,
		BUTTON_INIT
	);

	pblocks->messages_chat = GetBlock( // ��������� � ��������� � ����
		pblocks->chat.pos.X,
		pblocks->chat.pos.Y + 2,
		GetSizeButtonMark("���. ��������� � ��������� ������� � ����"),
		1,
		BUTTON_INIT
	);

	pblocks->effects = GetBlock( // ������� �����������
		pblocks->messages_chat.pos.X,
		pblocks->messages_chat.pos.Y + 2,
		GetSizeButtonMark("���. ������� �����������"),
		1,
		BUTTON_INIT
	);

	pblocks->improved_alg = GetBlock( // ���������������� ��������� ������ ��������� ����
		pblocks->effects.pos.X,
		pblocks->effects.pos.Y + 2,
		GetSizeButtonMark("�������������� ��������� ������ ��������� �������� �����"),
		1,
		BUTTON_INIT
	);

	pblocks->full_screen_mode = GetBlock( // ������������� �����
		pblocks->improved_alg.pos.X,
		pblocks->improved_alg.pos.Y + 3,
		GetSizeButtonMark("���. ������������� ����� (�� ��������: �� �������, ����������)"),
		1,
		BUTTON_INIT
	);


	pblocks->nickname = GetBlock( // �������� �������
		WIN_X0 + (WIDTH - GetSizeButtonStandart("�������� �������")) / 2,
		pblocks->table.pos.Y + pblocks->table.lenY + DISTANCE_BUTTON - 1,
		GetSizeButtonStandart("�������� �������"),
		5,
		BUTTON_INIT
	);

	pblocks->reset_progress = GetBlock( // ����� ��������
		WIN_X0 + (WIDTH - GetSizeButtonStandart("����� ��������")) / 2 - 2,
		pblocks->nickname.pos.Y + pblocks->nickname.lenY + DISTANCE_BUTTON,
		GetSizeButtonStandart("����� ���������"),
		5,
		BUTTON_INIT
	);

	pblocks->goto_menu = GetBlock( // ������ ������
		WIN_X0 + (WIDTH - GetSizeButtonStandart("� ������� ����")) / 2,
		pblocks->reset_progress.pos.Y + pblocks->reset_progress.lenY + DISTANCE_BUTTON,
		GetSizeButtonStandart("� ������� ����"),
		5,
		BUTTON_INIT
	);


	pblocks->table_input_name = GetBlock( // ������� ����� �����
		WIDTH / 6,
		HEIGHT / 6 - 2,
		WIDTH * 2 / 3,
		HEIGHT * 2 / 3,
		BUTTON_INIT
	);

	// ����� �������� ��� ������� ����
	pblocks->pwindow = p_allblocks->pwindow;
	pblocks->pversion = p_allblocks->pversion;
	pblocks->pfooter = p_allblocks->pfooter;
	pblocks->pcat = p_allblocks->pcat;
	pblocks->pcursore = p_allblocks->pcursore;
}

/*������������� � ��������� �� ������ pblocks
��������� ����� ������ ������ � ������� ����������
� ������� ���� ������ ����, ��������� ���������
������� ��������� �� ������ p_allblock*/
void InitblocksGameRule(TblocksGameRule* pblocks, TblocksMenu* p_allblocks) {
	pblocks->header = GetBlock( // ����� ����
		WIN_X0 + (WIDTH - GetSizeLargeWord("������� ����")) / 2,
		WIN_Y0 + 5,
		GetSizeLargeWord("������� ����"),
		5,
		BUTTON_INIT
	);

	pblocks->book = GetBlock( // �����
		WIN_X0 + (WIDTH - 141) / 2,
		WIN_Y0 + 3,
		141,
		40,
		BUTTON_INIT
	);

	pblocks->voice_acting = GetBlock( // ������� ������
		pblocks->book.pos.X - 10,
		pblocks->book.pos.Y,
		8,
		5,
		BUTTON_INIT
	);

	pblocks->invert_lighting = GetBlock( // ������������� ���������
		pblocks->book.pos.X + pblocks->book.lenX + 2,
		pblocks->book.pos.Y,
		9,
		6,
		BUTTON_INIT
	);

	pblocks->page_left = GetBlock( // ������ ������������ �������� �����
		pblocks->book.pos.X - 10,
		pblocks->book.pos.Y + pblocks->book.lenY - 4,
		8,
		3,
		BUTTON_INIT
	);

	pblocks->page_right = GetBlock( // ������ ������������ �������� ������
		pblocks->book.pos.X + pblocks->book.lenX + 2,
		pblocks->page_left.pos.Y,
		8,
		3,
		BUTTON_INIT
	);

	pblocks->goto_menu = GetBlock( // ������ ������ � ������� ����
		WIN_X0 + (WIDTH - GetSizeButtonStandart("� ������� ����")) / 2,
		WIN_Y0 + HEIGHT - 7,
		GetSizeButtonStandart("� ������� ����"),
		5,
		BUTTON_INIT
	);

	// ����� �������� ��� ������� ����
	pblocks->pwindow = p_allblocks->pwindow;
	pblocks->pversion = p_allblocks->pversion;
	pblocks->pfooter = p_allblocks->pfooter;
	pblocks->pcat = p_allblocks->pcat;
	pblocks->pcursore = p_allblocks->pcursore;
}

/*������������� � ��������� �� ������ pblocks
��������� ����� ������ ������ � ������� ����������
� ���� ����� ���� ����, ������� � �����
������� (baseX, baseY)*/
void InitblocksMenu(TblocksMenu* pblocks, size_t baseX, size_t baseY) {
	pblocks->window = GetBlock( // ������� ����
		baseX,
		baseY,
		WIDTH,
		HEIGHT,
		BUTTON_INIT
	);

	pblocks->version = GetBlock( // ������� ������ ����
		baseX + WIDTH - strlen(VERSION) - 9,
		baseY + HEIGHT - 2,
		strlen(VERSION),
		1,
		BUTTON_INIT
	);

	pblocks->footer = GetBlock( // ������ ����
		baseX,
		baseY + HEIGHT - 4,
		WIDTH,
		4,
		BUTTON_INIT
	);

	pblocks->cat = GetBlock( // ����������� ����
		baseX + WIDTH - 52,
		baseY + HEIGHT - 9,
		16,
		8,
		BUTTON_INIT
	);

	pblocks->cursore = GetPoint( // ������� �������
		pblocks->version.pos.X + pblocks->version.lenX,
		pblocks->version.pos.Y
	);

	pblocks->pwindow = &pblocks->window;
	pblocks->pversion = &pblocks->version;
	pblocks->pfooter = &pblocks->footer;
	pblocks->pcat = &pblocks->cat;
	pblocks->pcursore = &pblocks->cursore;

	InitblocksMainMenu(&pblocks->mainMenu, pblocks, baseX, baseY);
	InitblocksCustomGame(&pblocks->customGame, pblocks, baseX, baseY);
	InitblocksSimulation(&pblocks->simulation, pblocks, baseX, baseY);
	InitblocksSettings(&pblocks->settings, pblocks, baseX, baseY);
	InitblocksGameRule(&pblocks->gameRule, pblocks, baseX, baseY);
}

/*������������� � ��������� �� ������ pblocks
��������� ����� ������ ������ � ������� ����������
�� ������� ����, ������� � ����� ������� (baseX, baseY)*/
void InitBlockGame(TblocksGame* pblocks, size_t baseX, size_t baseY) {
	pblocks->window = GetBlock( // ������� ����
		baseX,
		baseY,
		WIDTH,
		HEIGHT,
		BUTTON_INIT
	);

	pblocks->target_card = 0; // ��������� ����� ������

	pblocks->matr_cards_ai = GetBlock( // ������� ���� ������������� ��
		baseX,
		baseY,
		60,
		8,
		BUTTON_OFF
	);


	pblocks->header = GetBlock( // ����� �������� ����
		baseX,
		baseY,
		WIDTH,
		3,
		BUTTON_INIT
	);

	strcpy(pblocks->s_effect, "���������� ������: �����������");
	pblocks->effect = GetBlock( // ���������� ������
		WIDTH * 0.67,
		pblocks->header.pos.Y + 1,
		strlen(pblocks->s_effect),
		2,
		BUTTON_INIT
	);

	pblocks->esc = GetBlock( // ����� ���� �����
		pblocks->header.pos.X + 2,
		pblocks->header.pos.Y + 1,
		7,
		1,
		BUTTON_INIT
	);

	pblocks->menu_block = GetBlock( // ���� �����
		baseX + WIDTH / 8,
		baseY + HEIGHT / 8,
		WIDTH * 3 / 4,
		HEIGHT * 3 / 4,
		BUTTON_INIT
	);

	pblocks->menu_header = GetBlock( // ����� ���� �����
		pblocks->menu_block.pos.X + (pblocks->menu_block.lenX
			- GetSizeButtonStandart("���� ��������������")) / 2,
		pblocks->menu_block.pos.Y + 2,
		GetSizeButtonStandart("���� ��������������"),
		5,
		BUTTON_INIT
	);

	pblocks->menu_continue = GetBlock( // ���������� ����
		pblocks->menu_block.pos.X + (pblocks->menu_block.lenX
			- GetSizeButtonStandart("����������")) / 2,
		pblocks->menu_block.pos.Y + 10,
		GetSizeButtonStandart("����������"),
		5,
		BUTTON_INIT
	);

	pblocks->menu_exit = GetBlock( // ����� � ������� ����
		pblocks->menu_block.pos.X + (pblocks->menu_block.lenX
			- GetSizeButtonStandart("� ������� ����")) / 2,
		pblocks->menu_continue.pos.Y + 5 + DISTANCE_BUTTON,
		GetSizeButtonStandart("� ������� ����"),
		5,
		BUTTON_INIT
	);

	pblocks->cards_p2_2 = GetBlock( // ����� 2-�� ������ ��� ���� ������
		baseX + (WIDTH - WIDTH_CRADS_BASE) / 2,
		baseY + 5,
		WIDTH_CRADS_BASE,
		8,
		BUTTON_INIT
	);

	pblocks->cards_battle = GetBlock( // ���� ���
		baseX + (WIDTH - WIDTH_CRADS_MEDIUM) / 2,
		pblocks->cards_p2_2.pos.Y + 10,
		WIDTH_CRADS_MEDIUM,
		18,
		BUTTON_INIT
	);

	pblocks->cards_user = GetBlock( // ����� ������������
		pblocks->cards_p2_2.pos.X,
		pblocks->cards_battle.pos.Y + 20,
		WIDTH_CRADS_BASE,
		8,
		BUTTON_INIT
	);

	pblocks->chat = GetBlock( // ���
		baseX + 2,
		pblocks->cards_user.pos.Y + 10 - 22,
		(WIDTH - WIDTH_CRADS_BASE) / 2 - 3,
		22,
		BUTTON_INIT
	);

	pblocks->button_chat = GetBlock( // ������ ����
		pblocks->chat.pos.X,
		pblocks->chat.pos.Y + pblocks->chat.lenY - 1,
		pblocks->chat.lenX,
		1,
		BUTTON_INIT
	);

	pblocks->input_chat = GetBlock( // ����������� ���� ����� ������ ����
		pblocks->button_chat.pos.X,
		pblocks->button_chat.pos.Y,
		WIDTH / 2,
		1,
		BUTTON_INIT
	);

	pblocks->cards_deck = GetBlock( // ����� ������ ����
		pblocks->cards_user.pos.X + WIDTH_CRADS_BASE + 3,
		pblocks->chat.pos.Y,
		32,
		16,
		BUTTON_INIT
	);

	pblocks->time = GetPoint( // �����
		pblocks->cards_deck.pos.X + pblocks->cards_deck.lenX - 17,
		pblocks->cards_deck.pos.Y + pblocks->cards_deck.lenY - 1
	);

	pblocks->card_special = GetBlock( // ����������� �����
		baseX + WIDTH - 16,
		pblocks->cards_user.pos.Y,
		11,
		8,
		BUTTON_INIT
	);

	pblocks->button_pass = GetBlock( // ������ ����
		pblocks->cards_deck.pos.X,
		pblocks->cards_deck.pos.Y + pblocks->cards_deck.lenY,
		GetSizeLargeWord("����") + 5 + 6,
		5,
		BUTTON_INIT
	);

	// ����� 2-�� ������ ��� ���� ������
	pblocks->cards_p2_3 = GetBlock(
		baseX + WIDTH / 4 - (WIDTH_CRADS_BASE / 2),
		baseY + pblocks->cards_p2_2.pos.Y,
		WIDTH_CRADS_BASE,
		8,
		BUTTON_INIT
	);

	// ����� 3-�� ������ ��� ���� ������
	pblocks->cards_p3_3 = GetBlock(
		baseX + (WIDTH * 3) / 4 - (WIDTH_CRADS_BASE / 2),
		baseY + pblocks->cards_p2_2.pos.Y,
		WIDTH_CRADS_BASE,
		8,
		BUTTON_INIT
	);

	// ����� 2-�� ������ ��� ���� ���������
	pblocks->cards_p2_4 = GetBlock(
		baseX + WIDTH / 6 - (WIDTH_CRADS_SMALL / 2) + 1,
		baseY + pblocks->cards_p2_2.pos.Y,
		WIDTH_CRADS_SMALL,
		8,
		BUTTON_INIT
	);

	// ����� 3-�� ������ ��� ���� ���������
	pblocks->cards_p3_4 = GetBlock(
		baseX + (WIDTH) / 2 - (WIDTH_CRADS_SMALL / 2),
		baseY + pblocks->cards_p2_2.pos.Y,
		WIDTH_CRADS_SMALL,
		8,
		BUTTON_INIT
	);

	// ����� 4-�� ������ ��� ���� ���������
	pblocks->cards_p4_4 = GetBlock(
		baseX + (WIDTH * 5) / 6 - (WIDTH_CRADS_SMALL / 2) - 1,
		baseY + pblocks->cards_p2_2.pos.Y,
		WIDTH_CRADS_SMALL,
		8,
		BUTTON_INIT
	);

	// ����� 5-�� ������ ��� ���� ��������
	pblocks->cards_p5_5 = GetBlock(
		baseX + pblocks->cards_p2_4.pos.X,
		baseY + pblocks->cards_p2_2.pos.Y + 10,
		WIDTH_CRADS_SMALL,
		8,
		BUTTON_INIT
	);

	// ����� 6-�� ������ ��� ���� ��������
	pblocks->cards_p6_6 = GetBlock(
		baseX + pblocks->cards_p4_4.pos.X,
		baseY + pblocks->cards_p5_5.pos.Y,
		WIDTH_CRADS_SMALL,
		8,
		BUTTON_INIT
	);

	// // ������� �������
	pblocks->cursore = GetPoint(
		pblocks->cards_deck.pos.X + pblocks->cards_deck.lenX - 12,
		pblocks->cards_deck.pos.Y + pblocks->cards_deck.lenY - 1
	);
}
