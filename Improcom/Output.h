#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <algorithm>
#include "Cinema.h"
using namespace std;

const char ESC = 27;
const char UP = 72;
const char DOWN = 80;
const char LEFT = 75;
const char RIGHT = 77;
const char ENTER = 13;

extern const type_info& OF;
extern const type_info& IF;

enum ConsoleColor // Цвет текста
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};


void ConsoleCursorVisible(bool show, short size); // Видимость и размеры курсора
void GoToXY(short x, short y); // Курсор в точку x,y
void SetColor(ConsoleColor text, ConsoleColor background); // Установка цвета текста

int DrawMenu(string start, string menu[], int size, int X, int Y);

template <typename T>
T DrawMenuChoice(string start, const vector <T>& films);

template string DrawMenuChoice(string start, const vector <string>& films);
template double DrawMenuChoice(string start, const vector <double>& films);
void DrawHall(string start, int hall_rows, int hall_seats, int &row, int &seat, vector<pair<int, int>> ordered_seats);

template <typename T>
class VectorSorte {
public:
	static void Sort(vector<T>& vec, string(T::* GetFun)()) {
		T temp;
		int size = vec.size(), min;
		for (int i = 0; i < size - 1; i++) {
			min = i;
			for (int j = i + 1; j < size; j++) {
				if ((vec[j].*GetFun)() < (vec[min].*GetFun)())
					min = j;
			}
			temp.Copy(vec[i]);
			vec[i].Copy(vec[min]);
			vec[min].Copy(temp);
		}
	}
};

int CinIntErrorCheck(int min, int max);
double CinDoubleErrorCheck(double min, double max);
int CinIntErrorCheck();
string CinStringSymRusErrorCheck();
string CinStringSymAngErrorCheck(short& x, short& y);
string CinStringSymRusErrorCheck(short& x, short& y);
string GetlineErrorCheck();
void RemoveSpace(string& a);