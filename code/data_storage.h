#if !defined(__DATA_STORAGE_H) 
#define __DATA_STORAGE_H 

#include "header.h"

void SaveKeyValueInFile(char* fname, char* key, void* pvalue, size_t size);
int LoadKeyValueInFile(char* fname, char* key, void* pvalue);
void LoadDataInGame(char* fname, Ttheme* ptheme);
size_t ChangeValueData(char* fname, char* key, int value_diff);
int WriteToTextFileSettings(char* fnameTxt, char* fnameBin);

#endif 