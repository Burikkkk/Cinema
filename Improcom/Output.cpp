#include "Output.h"

const type_info& OF = typeid(ofstream);
const type_info& IF = typeid(ifstream);

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Получает дескриптор консоли
void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}
void SetColor(ConsoleColor text, ConsoleColor background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

int CinIntErrorCheck(int min, int max) {
	int wcheck;
	cin >> wcheck;
	while (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ') || wcheck < min || wcheck > max) {
		rewind(stdin);
		cin.clear();
		cout << "Ошибка. Попробуйте ещё раз.\n";
		cin >> wcheck;
	}
	rewind(stdin);
	return wcheck;
}
double CinDoubleErrorCheck(double min, double max) {
	double wcheck;
	cin >> wcheck;
	while (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ') || wcheck < min || wcheck > max) {
		rewind(stdin);
		cin.clear();
		cout << "Ошибка. Попробуйте ещё раз.\n";
		cin >> wcheck;
	}
	rewind(stdin);
	return wcheck;
}
int CinIntErrorCheck() {
	int wcheck;
	cin >> wcheck;
	while (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ')) {
		rewind(stdin);
		cin.clear();
		cout << "Ошибка. Попробуйте ещё раз.\n";
		cin >> wcheck;
	}
	rewind(stdin);
	return wcheck;
}

string CinStringSymAngErrorCheck(short& x, short& y) {
	string wcheck;
	int n, ch;
	bool a = 0;
	if (x != 0 && y != 0)
		GoToXY(x, y++);
	cin >> wcheck;
	rewind(stdin);
	n = wcheck.size();
	do {

		for (int i = 0; i < n; i++)
		{
			if ((!(wcheck[i] >= 'a' && wcheck[i] <= 'z') && !(wcheck[i] >= 'A' && wcheck[i] <= 'Z')) && (wcheck[i] < '0' || wcheck[i] > '9'))
			{
				a = 0;
				if (x != 0 && y != 0)
					GoToXY(x, y++);
				cout << "Ошибка. Попробуйте ещё раз." << endl;
				if (x != 0 && y != 0)
					GoToXY(x, y++);
				cin >> wcheck;
				rewind(stdin);
				n = wcheck.size();
				break;
			}
			else a = 1;
		}
	} while (a == 0);
	return wcheck;
}
string CinStringSymRusErrorCheck() {
	string wcheck;
	int n;
	bool a;
	do {
		a = true;
		getline(cin, wcheck);
		n = wcheck.size();

		if (n == 0) {
			a = false;
			cout << "Ошибка: введена пустая строка. Попробуйте ещё раз." << endl;
			continue;
		}

		for (int i = 0; i < n; i++) {
			if (!(wcheck[i] >= 'а' && wcheck[i] <= 'я') && !(wcheck[i] >= 'А' && wcheck[i] <= 'Я')) {
				a = false;
				cout << "Ошибка: введены недопустимые символы. Попробуйте ещё раз." << endl;
				break;
			}
		}

		for (int i = 0; i < n - 2; i++) {
			if (wcheck[i] == wcheck[i + 1] && wcheck[i] == wcheck[i + 2]) {
				a = false;
				cout << "Ошибка: три одинаковые буквы подряд. Попробуйте ещё раз." << endl;
				break;
			}
		}

		if (wcheck[0] == 'Ъ' || wcheck[0] == 'Ь' || wcheck[0] == 'ъ' || wcheck[0] == 'ь') {
			a = false;
			cout << "Ошибка: слово начинается с ъ или ь знака. Попробуйте ещё раз." << endl;
			break;
		}

	} while (!a);

	return wcheck;
}
string CinStringSymRusErrorCheck(short& x, short& y) {
	string wcheck;
	int n;
	bool a;
	do {
		if (x != 0 && y != 0)
			GoToXY(x, y++);
		a = true;
		getline(cin, wcheck);
		n = wcheck.size();

		if (n == 0) {
			a = false;
			if (x != 0 && y != 0)
				GoToXY(x, y++);
			cout << "Ошибка: введена пустая строка. Попробуйте ещё раз." << endl;
			
			continue;
		}

		for (int i = 0; i < n; i++) {
			if (!(wcheck[i] >= 'а' && wcheck[i] <= 'я') && !(wcheck[i] >= 'А' && wcheck[i] <= 'Я')) {
				a = false;
				if (x != 0 && y != 0)
					GoToXY(x, y++);
				cout << "Ошибка: введены недопустимые символы. Попробуйте ещё раз." << endl;
				
				break;
			}
		}

		for (int i = 0; i < n - 2; i++) {
			if (wcheck[i] == wcheck[i + 1] && wcheck[i] == wcheck[i + 2]) {
				a = false;
				if (x != 0 && y != 0)
					GoToXY(x, y++);
				cout << "Ошибка: три одинаковые буквы подряд. Попробуйте ещё раз." << endl;
				
				break;
			}
		}

		if (wcheck[0] == 'Ъ' || wcheck[0] == 'Ь' || wcheck[0] == 'ъ' || wcheck[0] == 'ь') {
			a = false;
			if (x != 0 && y != 0)
				GoToXY(x, y++);
			cout << "Ошибка: слово начинается с ъ или ь знака. Попробуйте ещё раз." << endl;
			
			break;
		}

	} while (!a);

	return wcheck;
}

string GetlineErrorCheck()
{
	string wcheck;
	int n;
	bool a;
	do {
		a = true;
		getline(cin, wcheck);
		n = wcheck.size();

		if (n == 0) {
			a = false;
			cout << "Ошибка: введена пустая строка. Попробуйте ещё раз." << endl;
			continue;
		}
		RemoveSpace(wcheck);
		n = wcheck.size();
		for (int i = 0; i < n; i++) {
			if (!(wcheck[i] >= 'а' && wcheck[i] <= 'я') && !(wcheck[i] >= 'А' && wcheck[i] <= 'Я') 
				&& (wcheck[i] < '0' || wcheck[i] > '9') 
				&&wcheck[i]!='-'&& wcheck[i] != '№'&& wcheck[i] != '?' && wcheck[i] != ':' && wcheck[i] != '.' 
				&& wcheck[i] != '&' && wcheck[i] != '+'&& wcheck[i] != ' ') {
				a = false;
				cout << "Ошибка: введены недопустимые символы. Попробуйте ещё раз." << endl;
				break;
			}
		}
		for (int i = 0; i < n - 2; i++) {
			if (wcheck[i] == wcheck[i + 1] && wcheck[i] == wcheck[i + 2]) {
				a = false;
				cout << "Ошибка: три одинаковых символа подряд. Попробуйте ещё раз." << endl;
				break;
			}
		}

		if (wcheck[0] == 'Ъ' || wcheck[0] == 'Ь' || wcheck[0] == 'ъ' || wcheck[0] == 'ь') {
			a = false;
			cout << "Ошибка: слово начинается с ъ или ь знака. Попробуйте ещё раз." << endl;
			break;
		}

	} while (!a);

	return wcheck;
}

void RemoveSpace(string& a)
{
	a.erase(a.begin(), std::find_if(a.begin(), a.end(), [](int ch) {
		return !std::isspace(ch);}));
	a.erase(std::find_if(a.rbegin(), a.rend(), [](int ch) {
		return !std::isspace(ch);}).base(), a.end());
}

int DrawMenu(string start, string menu[], int size, int X, int Y)
{
	ConsoleCursorVisible(false, 100);
	cout << fixed << setprecision(2);
	int active_menu = 0;
	char ch;
	while (true)
	{
		int y = Y, x = X;
		system("cls");
		int start_size = start.size();
		if (x > 3)
			GoToXY(x - (start_size / 2) + int(23 / 2), y);
		else
			GoToXY(x - 3, y);
		SetColor(LightMagenta, Black);
		cout << start;
		SetColor(LightCyan, Black);
		y += 3;
		for (int i = 0; i < size; i++)
		{
			if (i == active_menu)
			{
				SetColor(LightMagenta, Black);
				GoToXY(x - 3, y);
				cout << "> ";
			}
			else 	SetColor(LightCyan, Black);
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case ESC:
			return ESC;

		case UP:
			if (active_menu > 0)
				active_menu--;
			else
				active_menu = size - 1;
			break;
		case DOWN:
			if (active_menu < size - 1)
				active_menu++;
			else
				active_menu = 0;
			break;
		case ENTER:
			return active_menu;

		default:
			y++;
			GoToXY(x, y);
			SetColor(LightMagenta, Black);
			cout << "Используйте стрелки" << endl;
			_getch();
			system("CLS");
		}
	}
}

template <typename T>
T DrawMenuChoice(string start, const vector <T>& films)
{
	ConsoleCursorVisible(false, 100);
	cout << fixed << setprecision(2);
	int active_menu = 0;
	char ch;
	while (true)
	{
		int size = films.size();
		system("cls");
		SetColor(LightMagenta, Black);
		cout << start << endl << endl;
		SetColor(LightCyan, Black);
		for (int i = 0; i < size; i++)
		{
			if (i == active_menu) {
				SetColor(LightMagenta, Black);
				cout << "> ";
			}
			else 	SetColor(LightCyan, Black);
			cout << "  " << films[i] << endl;
		}
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		//case ESC:
		//	return 0;

		case UP:
			if (active_menu > 0)
				active_menu--;
			else
				active_menu = size - 1;
			break;
		case DOWN:
			if (active_menu < size - 1)
				active_menu++;
			else
				active_menu = 0;
			break;
		case ENTER:
			return films[active_menu];

		default:
			SetColor(LightMagenta, Black);
			cout << "Используйте стрелки" << endl;
			_getch();
			system("CLS");
		}
	}
}

void DrawHall(string start, int hall_rows, int hall_seats, int& row, int& seat, vector<pair<int, int>> ordered_seats)
{
	ConsoleCursorVisible(false, 100);
	if (ordered_seats.size() == hall_rows * hall_seats)
	{
		cout << "Все места заняты" << endl;
		row = -1;
		seat = -1;
		_getch();
		return;
	}
	cout << fixed << setprecision(2);
	int active_row = 0, active_seat = 0;
	bool first = false;
	char ch, out;
	while (true)
	{
		system("cls");
		SetColor(LightMagenta, Black);
		cout << start << endl;
		SetColor(LightCyan, Black);

		for (int i = 0; i < hall_rows; i++) {
			cout << endl;
			for (int j = 0; j < hall_seats; j++) {
				auto seat_it = find(ordered_seats.begin(), ordered_seats.end(), make_pair(i + 1, j + 1));
				out = (seat_it != ordered_seats.end()) ? '+' : '*';
				if (out == '*' && !first)
				{
					active_row = i;
					active_seat = j;
					first = true;
					SetColor(LightMagenta, Black);
				}
				else if (out == '*' && i == active_row && j == active_seat)
				{
					SetColor(LightMagenta, Black);
				}
				else
				{
					SetColor(LightCyan, Black);
				}
				cout << setw(3) << out;
			}
		}
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case ESC:
			row = 0;
			seat = 0;
			return;
		case UP:
			if (active_row > 0) {
				active_row--;
				while (find(ordered_seats.begin(), ordered_seats.end(), make_pair(active_row + 1, active_seat + 1)) != ordered_seats.end())
				{
					if (active_row > 0)
						active_row--;
					else
						active_row = hall_rows - 1;
				}
			}
			else
				active_row = hall_rows - 1;
			while (find(ordered_seats.begin(), ordered_seats.end(), make_pair(active_row + 1, active_seat + 1)) != ordered_seats.end())
			{
				if (active_row > 0)
					active_row--;
				else
					active_row = hall_rows - 1;
			}
			break;

		case DOWN:
			if (active_row < (hall_rows - 1)) {
				active_row++;
				while (find(ordered_seats.begin(), ordered_seats.end(), make_pair(active_row + 1, active_seat + 1)) != ordered_seats.end())
				{
					if (active_row < (hall_rows - 1))
						active_row++;
					else
						active_row = 0;
				}
			}
			else
				active_row = 0;
			while (find(ordered_seats.begin(), ordered_seats.end(), make_pair(active_row + 1, active_seat + 1)) != ordered_seats.end())
			{
				if (active_row < (hall_rows - 1))
					active_row++;
				else
					active_row = 0;
			}
			break;

		case LEFT:
			if (active_seat > 0)
			{
				active_seat--;
				while (find(ordered_seats.begin(), ordered_seats.end(), make_pair(active_row + 1, active_seat + 1)) != ordered_seats.end())
				{
					if (active_seat > 0)
						active_seat--;
					else
						active_seat = hall_seats - 1;
				}
			}
			else
				active_seat = hall_seats - 1;
			while (find(ordered_seats.begin(), ordered_seats.end(), make_pair(active_row + 1, active_seat + 1)) != ordered_seats.end())
			{
				if (active_seat > 0)
					active_seat--;
				else
					active_seat = hall_seats - 1;
			}
			break;
		case RIGHT:
			if (active_seat < (hall_seats - 1)) {
				active_seat++;
				while (find(ordered_seats.begin(), ordered_seats.end(), make_pair(active_row + 1, active_seat + 1)) != ordered_seats.end())
				{
					if (active_seat < (hall_seats - 1))
						active_seat++;
					else
						active_seat = 0;
				}
			}
			else
				active_seat = 0;
			while (find(ordered_seats.begin(), ordered_seats.end(), make_pair(active_row + 1, active_seat + 1)) != ordered_seats.end())
			{
				if (active_seat < (hall_seats - 1))
					active_seat++;
				else
					active_seat = 0;
			}
			break;

		case ENTER:
			if (find(ordered_seats.begin(), ordered_seats.end(), make_pair(active_row + 1, active_seat + 1)) == ordered_seats.end()) {
				row = active_row + 1;
				seat = active_seat + 1;
				return;
			}
			break;


		default:
			cout << endl;
			SetColor(LightMagenta, Black);
			cout << "Используйте стрелки" << endl;
			_getch();
			system("CLS");
		}

	}
}