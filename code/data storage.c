#include "header.h"

// ���������, �������� ����, �������� �� �����
typedef struct str_data_file {
	char key[50];
	char* value;
} TdataFile;

// ���������, �������� ����, �������� �� �����
typedef struct str_data_save_file {
	char key[50];
	char* value;
	size_t size;
} TdataSaveFile;

/*����������� ������ � �������� �����, ��������� ��� 
������ � ��������� �� count ������, ������� � 
������� pos*/
static void MoveDataInBinaryFile(FILE* f, long count, long pos) {
	long i, j;
	char data;
	
	if (count > 0) {
		fseek(f, count, SEEK_END);
		i = ftell(f);
		fseek(f, 0, SEEK_END);
		j = ftell(f);
		while (i >= pos) {
			fseek(f, j, SEEK_SET);
			fread(&data, sizeof(char), 1, f);
			fseek(f, i, SEEK_SET);
			fwrite(&data, sizeof(char), 1, f);
			i--;
			j--;
		}

	} else {
		fseek(f, pos + count, SEEK_SET);
		i = ftell(f);
		fseek(f, pos, SEEK_SET);
		j = ftell(f);
		fseek(f, 0, SEEK_END);
		long fend = ftell(f);
		while (j <= fend) {
			fseek(f, j, SEEK_SET);
			fread(&data, sizeof(char), 1, f);
			fseek(f, i, SEEK_SET);
			fwrite(&data, sizeof(char), 1, f);
			i++;
			j++;
		}
	}
}

/*������ � �������� ���� � ������ fname, ���� 
"����: ��������" � ������ ����� key � ��������� �� 
������ pvalue ������� size ����, ���� �� ��� ���, 
����� ���������� �������� ��������� �����, �����, 
���� ���������� ����� ���, �� ��� �������� � ������ fname*/
void SaveKeyValueInFile(char* fname, char* key, void* pvalue, size_t size) {
	FILE* f = fopen(fname, "r+b");
	int equal = 0; // ����� �� ��������
	char* p_pvalue = (char*)pvalue;

	if (f != NULL) {
		char file_key[1000];
		char file_value[1000];
		uint16_t n_key, n_value; // ����� ���������� � ������

		do { // ����� ������� ��� ������ ���� "����: ��������"
			fread(&n_key, sizeof(uint16_t), 1, f);
			fread(&file_key, sizeof(char), n_key, f);
			fread(&n_value, sizeof(uint16_t), 1, f);
			fread(&file_value, sizeof(char), n_value, f);
			equal = !strcmp(file_key, key);
		} while (!equal && !feof(f));

		if (equal) { // ���� ���� ������, �� ���������� ��������
			long pos_write = ftell(f) - n_value;
			// ���� �������������� �������� ����� ������� �������
			if (size != n_value) {
				int d = size - n_value;
				MoveDataInBinaryFile(f, d, ftell(f) + d);
				fseek(f, pos_write - sizeof(uint16_t), SEEK_SET);
				fwrite(&size, sizeof(uint16_t), 1, f);
				if (d < 0) {
					// �������� ����� ����� �� d ������
					fseek(f, d, SEEK_END);
					chsize(fileno(f), ftell(f));
				}
			} 
			fseek(f, pos_write, SEEK_SET);
			fwrite(p_pvalue, sizeof(char), size, f);
		}

	} else {
		f = fopen(fname, "wb");
	}

	if (!equal) {
		size_t len_key = strlen(key) + 1;
		fwrite(&len_key, sizeof(uint16_t), 1, f);
		fwrite(key, sizeof(char), len_key, f);
		fwrite(&size, sizeof(uint16_t), 1, f);
		fwrite(p_pvalue, sizeof(char), size, f);
		chsize(fileno(f), ftell(f));
	}
	fclose(f);
}

/*����������� � ���������� �� ������ pa ����������
�� ������ pb ������� size*/
static void CopyData(void* pa, void* pb, size_t size) {
	char* a = (char*)pa;
	char* b = (char*)pb;
	while (size--) {
		a[size] = b[size];
	}
}

/*������ �� ��������� ����� f, ��������� ��� ������ �������� 
�� ����� key, ��������� ��� �� ������ pvalue, ��������� 
������������� ��������, �����, ���� ���� �� ������, 
���������� 0, �����, ���� ���������� ����� � ����� ������ 
���, ���������� ������������� ��������*/
int LoadKeyValueInFile(FILE* f, char* key, void* pvalue) {
	size_t found = 0;
	if (f == NULL) {
		return -1;
	} else {
		char file_key[1000];
		char file_value[1000];
		uint16_t n_key = 0, n_value = 0; // ����� ���������� � ������
		int equal; // ����� �� ��������
		char* p_pvalue = (char*)pvalue;

		do { // ����� ���� "����: ��������"
			fread(&n_key, sizeof(uint16_t), 1, f);
			fread(&file_key, sizeof(char), n_key, f);
			fread(&n_value, sizeof(uint16_t), 1, f);
			fread(&file_value, sizeof(char), n_value, f);
			equal = !strcmp(file_key, key);
		} while (!equal && !feof(f));

		if (equal) {
			CopyData(p_pvalue, file_value, n_value);
			found = 1;
		}
	}
	return found;
}

/*������ �� ���������� ����� fname � ��������� �� ������ 
ptheme ����������� ������ ������������, �����, 
���� ���� �� ������ ��� �� ������� �����-���� ���� 
"����: ��������", �� ������������� ���� ������ �� 
��������� � ������ �� � ��������� ����*/
void LoadDataInGame(char* fname, Ttheme* ptheme) {
	TdataFile loadData[] = {
		{"userName", &ptheme->userName},
		{"musicTheme", &ptheme->musicTheme},
		{"onMusicBg", &ptheme->onMusicBg},
		{"onSoundsWeather", &ptheme->onSoundsWeather},
		{"onSounds", &ptheme->onSounds},

		{"designTheme", &ptheme->designTheme},
		{"typeWeather", &ptheme->typeWeather},
		{"printChat", &ptheme->printChat},
		{"messagesChat", &ptheme->messagesChat},
		{"specialEffects", &ptheme->specialEffects},
		{"improvedAlgGameInterface", &ptheme->improvedAlgGameInterface},
		
		{"raiting", &ptheme->raiting},
		{"levelUser", &ptheme->levelUser},
		{"countGames", &ptheme->countGames},
		{"countWins", &ptheme->countWins},
		{"countLose", &ptheme->countLose},
		{"minutsInGame", &ptheme->minutsInGame},

		{"resultsGames", &ptheme->resultsGames},
		{"version", &ptheme->version},
		{"launch", &ptheme->launch}
	};

	char s_name[MAX_LEN_NICKNAME + 1] = "\0";
	size_t value0 = 0;
	size_t value1 = 1;
	size_t value_version = 30;
	size_t value_raiting = 1000;
	size_t resultsGames[4][6][2] = { 0 };

	TdataSaveFile saveData[] = {
		{"userName", s_name, sizeof(char) * (MAX_LEN_NICKNAME + 1)},
		{"musicTheme", &value0, sizeof(size_t)},
		{"onMusicBg", &value1, sizeof(size_t)},
		{"onSoundsWeather", &value1, sizeof(size_t)},
		{"onSounds", &value1, sizeof(size_t)},

		{"designTheme", &value0, sizeof(size_t)},
		{"typeWeather", &value1, sizeof(size_t)},
		{"printChat", &value1, sizeof(size_t)},
		{"messagesChat", &value1, sizeof(size_t)},
		{"specialEffects", &value1, sizeof(size_t)},
		{"improvedAlgGameInterface", &value1, sizeof(size_t)},

		{"raiting", &value_raiting, sizeof(size_t)},
		{"levelUser", &value1, sizeof(size_t)},
		{"countGames", &value0, sizeof(size_t)},
		{"countWins", &value0, sizeof(size_t)},
		{"countLose", &value0, sizeof(size_t)},
		{"minutsInGame", &value0, sizeof(size_t)},
		
		{"minutsInGame", resultsGames, sizeof(size_t) * 4 * 6 * 2},
		{"version", &value_version, sizeof(size_t)},
		{"launch", &value0, sizeof(size_t)}
	};
	size_t initData[20] = { 0 }; // ������� ������, ������� ��� � �����
	const size_t count_data = 20;

	FILE* f = fopen(fname, "rb");
	if (f != NULL) {
		// �������� ������ �� ����� � ����������
		for (size_t i = 0; i < count_data; i++) {
			if (!LoadKeyValueInFile(f, loadData[i].key, loadData[i].value)) {
				initData[i] = 1;
			}
		}
		fclose(f);
	} else {
		for (size_t i = 0; i < count_data; i++) {
			initData[i] = 1;
		}
	}

	// ������������� ��� ������, ������� ��� � �����
	for (size_t i = 0; i < count_data; i++) {
		if (initData[i]) {
			CopyData(loadData[i].value, saveData[i].value, saveData[i].size);
			SaveKeyValueInFile(fname, loadData[i].key, loadData[i].value, saveData[i].size);
		}
	}
}

/*�������������� � �������� ����� fname ������������ 
�������� ����� key ������� ��������� �����, �������� � ���� 
�������� �� ������ pvalue, �����, ���� ���� ��� ���� �� 
������, ����������� �������� �������� 0, ��������� ����� ��������*/
size_t ChangeValueData(char* fname, char* key, int value_diff) {
	FILE* f = fopen(fname, "rb");
	int prev_value = 0;
	// ���� ���� ��� ���� �� ������, �� �������� ��������
	if (LoadKeyValueInFile(f, key, &prev_value) <= 0)
		prev_value = 0;

	size_t new_value = prev_value + value_diff;
	SaveKeyValueInFile(fname, key, &new_value, sizeof(size_t));
	fclose(f);
	return new_value;
}

/*����� � ����� f ��������� ������������� ������������ ����� n*/
static void printByte(FILE* f, unsigned char n) {
	unsigned char m = ~((unsigned char)~0 >> 1);
	while (m) {
		(m & n) == 0 ? fputc('0', f) : fputc('1', f);
		m >>= 1;
	}
	fputc(' ', f);
}

/*����� � ����� f ��������� ������������� ���������� 
�� ������ pa ������������� ���� �������� size ����*/
static void printVar(FILE* f, void* pa, size_t size) {
	unsigned char* a = (unsigned char*)pa;
	char t;
	while (size--) {
		printByte(f, a[size]);
	}
	fputc('\n', f);
}

/*������ � ��������� ���� � ������ fnameTxt ���� 
��� "����: ��������" �� ��������� ����� � ������ 
fnameBin, ��������� �������� "������", ���� 
������� ���� ���������, ����� "����"*/
int WriteToTextFileSettings(char* fnameTxt, char* fnameBin) {
	FILE* fbin = fopen(fnameBin, "rb");
	if (fbin != NULL) {
		FILE* ftxt = fopen(fnameTxt, "wt");
		char file_key[1000];
		char file_value[1000];
		uint16_t n_key, n_value; // ����� ���������� � ������
		char* pfile_value = file_value;
		char p;

		fprintf(ftxt, "� ���� ����� ��������� ����������� � ��� ��������� ������� ����������.\n");
		fprintf(ftxt, "��������� ����� ����� ������� ������� �� �������� �� ������ ���������� �� ������� ����,\n");
		fprintf(ftxt, "��� ���� ���� ����� ���� ����������, ��� �������� ������ �������� � �������� �����.\n\n");

		fread(&n_key, sizeof(uint16_t), 1, fbin);
		fread(&file_key, sizeof(char), n_key, fbin);
		fread(&n_value, sizeof(uint16_t), 1, fbin);
		fread(&file_value, sizeof(char), n_value, fbin);
		while (!feof(fbin)) { // ������ ���� ��� "����: ��������"
			fprintf(ftxt, "%s:\n", file_key);
			printVar(ftxt, file_value, n_value);
			fputc('\n', ftxt);

			fread(&n_key, sizeof(uint16_t), 1, fbin);
			fread(&file_key, sizeof(char), n_key, fbin);
			fread(&n_value, sizeof(uint16_t), 1, fbin);
			fread(&file_value, sizeof(char), n_value, fbin);
		}
		fclose(fbin);
		fclose(ftxt);
		return 1;
	} else
		return 0;
}
