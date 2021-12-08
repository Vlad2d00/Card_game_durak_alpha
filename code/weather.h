#if !defined(__WEATHER_H) 
#define __WEATHER_H 

#include "header.h"

// функции для работы с погодой
void InitWeather(Tweather* pweather, size_t baseX, size_t baseY);
void ClearWeather(Tweather* pweather);
void SetWeather(Tweather* pweather, char type, size_t intensity);
void PrintWeather(HANDLE h, Tweather* pweather, char a[HEIGHT][WIDTH]);
void GetSlopesForWeather(int* a, size_t n, size_t angle);
void MoveWeather(Tweather* pweather, char a[HEIGHT][WIDTH]);
size_t WeatherDynamics(HANDLE h, Tweather* pweather, Ttheme* ptheme);

// инициализация матриц препятствий для их обхода осадков
void SetMatrInMatr(char a[HEIGHT][WIDTH], char(*b)[WIDTH],
	size_t m, size_t n, size_t x, size_t y);
void SetBlockMatr(char a[HEIGHT][WIDTH], Tblock block, char ch);
void CopyCharMatr(char a[HEIGHT][WIDTH], char b[HEIGHT][WIDTH]);
void InitMatrObstac(char a[HEIGHT][WIDTH], Tblock* blocks, size_t n, Tblock window, char ch);
void InitMatrObstacBase(char a[HEIGHT][WIDTH], TblocksMenu* pblocks, char ch);

#endif 