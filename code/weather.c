#include "header.h"

/*инициализация в структуре по адресу pweather координат 
точек начала блоков с выводом осадков, начиная с точки
отсчета (baseX, baseY) по настройкам структуры настроек 
по адресу ptheme*/
void InitWeather(Tweather* pweather, size_t baseX, size_t baseY, Ttheme* ptheme) {
	// рабочее окно
	pweather->window.pos.X = baseX;
	pweather->window.pos.Y = baseY;
	pweather->window.lenX = WIDTH;
	pweather->window.lenY = HEIGHT;

	switch (ptheme->typeWeather) {
		case WEATHER_CLEAR:
			pweather->type = '-';
			pweather->count = 0;
			break;
		case WEATHER_SNOW:
			pweather->type = '*'; break;
		case WEATHER_RAIN:
			pweather->type = '|'; break;
	}
	pweather->change_speed = 8;
	pweather->step_change = 0.0024;
	pweather->min_coeff = 0.003;
	pweather->max_coeff = 0.11;
	pweather->coeff = pweather->min_coeff + START_COEFF_WEATHER
		/ (pweather->max_coeff - pweather->min_coeff);
	pweather->direction_wind = 1;

	pweather->ch = pweather->type;
	pweather->angle = 0;
	pweather->fall_mess = 0;
	pweather->delay = 350;
	pweather->count = pweather->window.lenX * 0.01;

	pweather->type_bg_sounds = 0;
	pweather->shower = 0;
	// заполнение матрицы пустотой
	for (size_t i = 0; i < pweather->window.lenY; i++) {
		for (size_t j = 0; j < pweather->window.lenX; j++) {
			pweather->matr[i][j] = ' ';
		}
		pweather->matr[i][pweather->window.lenX] = '\0';
	}
	pweather->matr[pweather->window.lenY - 1][pweather->window.lenX - 1] = '\0';
	pweather->time_start = clock();
}

/*очищение матрицу осадков в структуре по адресу pweather*/
void ClearWeather(Tweather* pweather) {
	for (size_t i = 0; i < pweather->window.lenY; i++) {
		for (size_t j = 0; j < pweather->window.lenX; j++) {
			pweather->matr[i][j] = ' ';
		}
		pweather->matr[i][pweather->window.lenX] = '\0';
	}
	pweather->matr[pweather->window.lenY - 1][pweather->window.lenX - 1] = '\0';
}

/*устанавливает настройки погоды структуры по адресу
pweather на тип type с интенсивностью intensity*/
void SetWeather(Tweather* pweather, char type, size_t intensity) {
	pweather->type = type;
	if (pweather->type == '*') { // снег
		switch (intensity) {
		case 0:
			pweather->ch = '\'';
			pweather->angle = 0;
			pweather->fall_mess = 30;
			pweather->delay = 380;
			pweather->count = pweather->window.lenX * 0.012;
			break;
		case 1:
			pweather->ch = '*';
			pweather->angle = 0;
			pweather->fall_mess = 20;
			pweather->delay = 220;
			pweather->count = pweather->window.lenX * 0.04;
			break;
		case 2:
			pweather->ch = '*';
			pweather->angle = 0;
			pweather->fall_mess = 10;
			pweather->delay = 150;
			pweather->count = pweather->window.lenX * 0.07;
			break;
		case 3:
			pweather->ch = '*';
			pweather->angle = 30;
			pweather->fall_mess = 7;
			pweather->delay = 100;
			pweather->count = pweather->window.lenX * 0.08;
			break;
		case 4:
			pweather->ch = '*';
			pweather->angle = 45;
			pweather->fall_mess = 5;
			pweather->delay = 50;
			pweather->count = pweather->window.lenX * 0.082;
			break;
		case 5:
			pweather->ch = '*';
			pweather->angle = 75;
			pweather->fall_mess = 10;
			pweather->delay = 35;
			pweather->count = pweather->window.lenX * 0.125;
			break;
		}
	}
	else if (pweather->type == '|') { // дождь
		switch (intensity) {
		case 0:
			pweather->ch = '\|';
			pweather->angle = 0;
			pweather->fall_mess = 0;
			pweather->delay = 70;
			pweather->count = pweather->window.lenX * 0.01;
			break;
		case 1:
			pweather->ch = '\|';
			pweather->angle = 0;
			pweather->fall_mess = 0;
			pweather->delay = 40;
			pweather->count = pweather->window.lenX * 0.025;
			break;
		case 2:
			pweather->ch = '|';
			pweather->angle = 0;
			pweather->fall_mess = 0;
			pweather->delay = 32;
			pweather->count = pweather->window.lenX * 0.040;
			break;
		case 3:
			pweather->ch = '\\';
			pweather->angle = 30;
			pweather->fall_mess = 0;
			pweather->delay = 28;
			pweather->count = pweather->window.lenX * 0.047;
			break;
		case 4:
			pweather->ch = '\\';
			pweather->angle = 45;
			pweather->fall_mess = 0;
			pweather->delay = 25;
			pweather->count = pweather->window.lenX * 0.06;
			break;
		case 5:
			pweather->ch = '\\';
			pweather->angle = 60;
			pweather->fall_mess = 0;
			pweather->delay = 20;
			pweather->count = pweather->window.lenX * 0.12;
			break;
		}
	}
	else {
		pweather->count = 0;
	}
}

/*вывод в окне с дескриптором h садков от погоды
структуры по адресу pweather, которые не пересекают
препятствия матрицы a размера HEIGHT x WIDTH со 
звуками погоды, если истинно onSounds*/
void PrintWeather(HANDLE h, Tweather* pweather, char a[HEIGHT][WIDTH], size_t onSounds) {
	static size_t clear = 0;
	if (onSounds && pweather->type_bg_sounds != pweather->type) {
		clear = 0;
		// отключить старые фоновые звуки
		if (pweather->type_bg_sounds == '*')
			mciSendString(TEXT("close sourse\\music\\snow1.mp3"),
				NULL, 0, NULL);
		else if (pweather->type_bg_sounds == '|') {
			if (pweather->shower)
				mciSendString(TEXT("close sourse\\music\\rain2Level.mp3"),
					NULL, 0, NULL);
			else
				mciSendString(TEXT("close sourse\\music\\rain1Level.mp3"),
					NULL, 0, NULL);
		} else if (pweather->type_bg_sounds == '-')
			mciSendString(TEXT("close sourse\\music\\birds.mp3"),
				NULL, 0, NULL);
		pweather->type_bg_sounds = pweather->type;

		if (pweather->type == '*') {
			mciSendString(TEXT("play sourse\\music\\snow1.mp3 repeat"),
				NULL, 0, NULL); // звуки снега

		} else if (pweather->type == '|') {
			if (pweather->angle >= 15 && !pweather->shower) {
				mciSendString(TEXT("close sourse\\music\\rain1Level.mp3"),
					NULL, 0, NULL);
				mciSendString(TEXT("play sourse\\music\\rain2Level.mp3 repeat"),
					NULL, 0, NULL); // звуки ливня
				pweather->shower = 1;
			} else if (pweather->angle < 15) {
				mciSendString(TEXT("close sourse\\music\\rain2Level.mp3"),
					NULL, 0, NULL);
				mciSendString(TEXT("play sourse\\music\\rain1Level.mp3 repeat"),
					NULL, 0, NULL); // звуки дождя
				pweather->shower = 0;
			}
		} else if (pweather->type_bg_sounds == '-') {
			ClearWeather(pweather);
			mciSendString(TEXT("play sourse\\music\\birds.mp3 repeat"),
				NULL, 0, NULL);  // звуки птиц
		}
	}
	if (clear)
		return;

	size_t j, k;
	COORD point;
	point.Y = pweather->window.pos.Y;
	char* ps;
	for (size_t i = 0; i < pweather->window.lenY; i++) {
		ps = pweather->matr[i];
		j = 0;
		k = 0;
		while (j < pweather->window.lenX) {
			do {
				j++;
			} while (j < pweather->window.lenX && a[i][j] == ' ');
			// если было встречено препятствие
			if (j < pweather->window.lenX) {
				point.X = pweather->window.pos.X + k;
				pweather->matr[i][j] = '\0';
				SetConsoleCursorPosition(h, point);
				printf("%s", ps);
				pweather->matr[i][j] = ' ';
				while (j < pweather->window.lenX && a[i][j] != ' ') {
					j++;
				}
				k = j;
				ps = pweather->matr[i] + k;
			}
		}
		point.X = pweather->window.pos.X + k;
		SetConsoleCursorPosition(h, point);
		printf("%s", ps);
		point.Y++;
	}
	if (pweather->type_bg_sounds == '-')
		clear = 1;
}

/*запись в массив a размера n смещения осадков
по каждой строке матрицы осадков при угле наклона angle*/
void GetSlopesForWeather(int* a, size_t n, size_t angle) {
	double tan_angle = tan(angle * PI / 180);
	double sum = 0;
	for (size_t i = 0; i < n; i++) {
		sum += tan_angle;
		if (sum >= 1) {
			a[i] = (int)sum;
			sum -= (int)sum;
		} else
			a[i] = 0;
	}
}

/*перемещение садков от погоды структуры по адресу
pweather, учитывая препятствия в матрице a
размера HEIGHT x WIDTH*/
void MoveWeather(Tweather* pweather, char a[HEIGHT][WIDTH]) {
	int dx; // смещение осадка по оси X
	size_t maxX = pweather->window.pos.X + pweather->window.lenX;
	size_t maxY = pweather->window.pos.Y + pweather->window.lenY;
	int slopes[HEIGHT];
	GetSlopesForWeather(slopes, pweather->window.lenY, pweather->angle);

	for (int i = pweather->window.lenY - 1; i >= 0; i--) {
		for (size_t j = 0; j < pweather->window.lenX; j++) {
			if (pweather->matr[i][j] != ' ') {
				if (pweather->matr[i][j] == '%') {
					pweather->matr[i][j] = 'x';
				} else {
					pweather->matr[i][j] = ' ';
					// угол наклона осадка
					dx = slopes[i];
					// смещение осадка в случайную сторону или его остановка
					if (rand() % 100 < pweather->fall_mess)
						dx += rand() % 2 == 1 ? 1 : -1;
					if (pweather->direction_wind < 0)
						dx = -dx;

					dx = j + dx;
					// если осадок не выходит за границы окна
					if ((dx >= pweather->window.pos.X) && (dx < maxX) && (i + 1 < maxY)) {
						// если это капля воды, то она может брызнуть при ударе о пол
						if ((i + 2 == maxY || a[i + 2][dx] != ' ') && pweather->type == '|')
							pweather->matr[i + 1][dx] = '%';
						else
							pweather->matr[i + 1][dx] = pweather->ch;
					}
				}
			}
		}
	}

	// новые осадки
	static float new_count = 0;
	new_count += pweather->count;
	for (size_t i = 0, k; i < (size_t)new_count; i++) {
		do {
			k = rand() % pweather->window.lenX;
		} while (pweather->matr[0][k] != ' ');
		pweather->matr[0][k] = pweather->ch;
	}
	if (pweather->angle > 2) {
		size_t d = new_count * pweather->window.lenY
			/ pweather->window.lenX * pweather->angle / 60;
		size_t j = pweather->direction_wind > 0 ? 0 : pweather->window.lenX - 1;
		for (size_t i = 0, k; i < d; i++) {
			do {
				k = rand() % pweather->window.lenY;
			} while (pweather->matr[k][j] != ' ');
			pweather->matr[k][j] = pweather->ch;
		}
	}
	if (new_count >= 1)
		new_count -= (size_t)new_count;
	pweather->matr[pweather->window.lenY - 1][pweather->window.lenX - 1] = '\0';
	pweather->time_start = clock();
}

/*развитие в окне с дескриптором h погоды структуры
по адресу pweather и цветовой темы структуры по
адресу ptheme, возвращая знчаение "истина", если
ударила молния, иначе "ложь"*/
size_t WeatherDynamics(HANDLE h, Tweather* pweather, Ttheme* ptheme) {
	if (ptheme->typeWeather == WEATHER_CLEAR)
		return 0;
	static size_t was_max = 0; // достигнут ли пик интенсивноси погоды
	static size_t lightning = 0; // был ли удар молнии
	// точка начала изменения угла наклона осадков
	float angle_change_point = pweather->max_coeff * 0.5;

	if (!was_max) {
		pweather->coeff += rand() % 100 < pweather->change_speed ?
			pweather->step_change / (((pweather->type == '|') * 3) + 1) : 0;
		
		if (pweather->coeff >= pweather->max_coeff) {
			was_max = 1;
			if (ptheme->onSoundsWeather)
				mciSendString(TEXT("play sourse\\sound\\menu\\wind1.mp3"),
					NULL, 0, NULL); // звук порыва ветра
		}
	} else {
		// снижение интенсивности погоды медленне ее нарастания
		if (pweather->coeff > angle_change_point)
			pweather->coeff -= rand() % 100 < pweather->change_speed ?
			pweather->step_change * powf(angle_change_point / pweather->coeff, 4)
			/ (((pweather->type == '|') * 3) + 1) : 0;
		else
			pweather->coeff -= rand() % 100 < pweather->change_speed ?
			pweather->step_change / (((pweather->type == '|') * 3) + 1) : 0;

		if (pweather->coeff <= pweather->min_coeff)
			was_max = 0;
	}

	//количество осадков и скорость их выпадения
	pweather->count = pweather->window.lenX * pweather->coeff;
	pweather->delay = exp(6.05 - 17.78 * pweather->coeff);

	// тип осадков
	if (pweather->type == '*') {
		pweather->ch = pweather->coeff >= 0.03 ? '*' : '.';
		// степень хаотичности падения снежинок
		if (pweather->min_coeff < pweather->max_coeff)
			pweather->fall_mess = (1 - pweather->coeff
				/ angle_change_point) * 40 + 5;
		else
			pweather->fall_mess = 10;

	} else if (pweather->type == '|') {
		pweather->fall_mess = 0;
		if (pweather->angle >= 15) {
			if (pweather->direction_wind > 0)
				pweather->ch = '\\';
			else
				pweather->ch = '/';
		}
		else
			pweather->ch = '|';
		pweather->delay *= 0.25;
		if (lightning) { // процесс удара молнии
			lightning++;
			if (lightning == 3) {
				if (ptheme->onSoundsWeather) {
					mciSendString(TEXT("play sourse\\sound\\menu\\thunder1.mp3"),
						NULL, 0, NULL); // звук резкого удара молнии
				}
			}
			else if (lightning == 4) {
				SwapStr(ptheme->colorBgBase, ptheme->colorTextBase);
			}
			else if (lightning == 5) {
				SwapStr(ptheme->colorBgBase, ptheme->colorTextBase);
			}
			else if (lightning == 6) {
				SwapStr(ptheme->colorBgBase, ptheme->colorTextBase);
			}
			else if (lightning == 7) {
				lightning = 0;
			}
		}
		else if (pweather->angle >= 30 && rand() % CHANCE_LIGHTNING < 1) {
			SwapStr(ptheme->colorBgBase, ptheme->colorTextBase);
			lightning = 1;

		}
		else if (pweather->angle >= 15 && !pweather->shower) {
			pweather->type_bg_sounds = 0;
		}
		else if (pweather->angle < 15 && pweather->shower) {
			pweather->type_bg_sounds = 0;
		}

		if (ptheme->onSoundsWeather && rand() % 850 < 1) {
			if (rand() % 2)
				mciSendString(TEXT("play sourse\\sound\\menu\\thunderLong1.mp3"),
					NULL, 0, NULL); // звук проддолжительного тихого грома
			else
				mciSendString(TEXT("play sourse\\sound\\menu\\thunderLong2.mp3"),
					NULL, 0, NULL); // звук проддолжительного тихого грома
		}
	}

	// угол наклона осадков
	if (pweather->coeff > angle_change_point)
		pweather->angle = (pweather->coeff - angle_change_point)
		/ pweather->max_coeff * 160 * pweather->direction_wind;
	else
		pweather->angle = 0;
	return lightning;
}

/*запись в матрицу a размера HEIGHT x WIDTH
матрицы b размера m x n в точке (x, y)*/
void SetMatrInMatr(char a[HEIGHT][WIDTH], char(*b)[WIDTH],
	size_t m, size_t n, size_t x, size_t y) {
	for (size_t ai = y, bi = 0; bi < m; ai++, bi++) {
		for (size_t aj = x, bj = 0; bj < n; aj++, bj++) {
			a[ai][aj] = b[bi][bj];
		}
	}
}

/*заполнение в матрице a размера HEIGHT x WIDTH
блока block симолами ch*/
void SetBlockMatr(char a[HEIGHT][WIDTH], Tblock block, char ch) {
	size_t i_max = block.pos.Y + block.lenY;
	size_t j_max = block.pos.X + block.lenX;

	for (size_t i = block.pos.Y; i < i_max; i++) {
		for (size_t j = block.pos.X; j < j_max; j++) {
			a[i][j] = ch;
		}
	}
}

/*запись в матрицу a симольной матрицы b размера HEIGHT x WIDTH*/
void CopyCharMatr(char a[HEIGHT][WIDTH], char b[HEIGHT][WIDTH]) {
	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			a[i][j] = b[i][j];
		}
	}
}

/*запись в матрицу a размера HEIGHT x WIDTH массива
блоков blocks размера n при блоке окна window,
заполнеными симолами ch, заполняя оставшееся
пространоство пробелами*/
void InitMatrObstac(char a[HEIGHT][WIDTH], Tblock* blocks, size_t n, Tblock window, char ch) {
	for (size_t i = 0; i < n; i++) {
		blocks[i].pos.X -= window.pos.X;
		blocks[i].pos.Y -= window.pos.Y;
		SetBlockMatr(a, blocks[i], ch);
	}
}

/*запись в матрицу a размера HEIGHT x WIDTH препятствий 
элементов подвала меню структуры по адресу pblocks, 
заполняя свтрицу символами ch*/
void InitMatrObstacBase(char a[HEIGHT][WIDTH], TblocksMenu* pblocks, char ch) {
	// инициализация матрицы без препятствий
	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			a[i][j] = ' ';
		}
	}

	char cat[8][WIDTH]; // изображение кота
	SetCatMatr(cat);
	SetMatrInMatr(a, cat, 8, 15, pblocks->cat.pos.X, pblocks->cat.pos.Y);
	Tblock blocks_general[] = { pblocks->footer };
	InitMatrObstac(a, blocks_general, 1, pblocks->window, ch);
}
