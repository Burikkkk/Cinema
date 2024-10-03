#include "Improcom.h"

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Ru");
	SetConsoleTitle(L"Improcom Cinema");
	ConsoleCursorVisible(false, 100);
	short x = 55, y = 12, k=5;
	cout << fixed << setprecision(2);
	SetColor(LightMagenta, Black);
	GoToXY(x-2, y);
	cout << "Improcom Cinema"; GoToXY(x, y + k);
	SetColor(LightCyan, Black);
	cout << "Загрузка."; GoToXY(x, y + k);
	Sleep(500);
	cout << "Загрузка.."; GoToXY(x, y + k);
	Sleep(500);
	cout << "Загрузка..."; GoToXY(x - 13, y + 2 + k);
	Sleep(1000);
	cout << "Нажмите любую клавишу для продолжения"; GoToXY(x, y);
	_getch();
	system("CLS");
	while (TRUE) {
		string m[] = { "Войти как пользователь", "Войти как администратор", "Регистрация", "Выход" };
		int a = DrawMenu("Добро пожаловать в Improcom Cinema!!", m, size(m), 48, 10);
		system("CLS");
		switch (a)
		{
		case 0:
			UserLoginMenu();
			break;
		case 1:
			AdminLoginMenu();
			break;
		case 2:
			LoginMenu(0, 48, 12);
			_getch();
			system("CLS");
			break;
		case 3:
			GoToXY(48, 13);
			SetColor(LightCyan, Black);
			cout << "Выход из программы...";
			_getch();
			system("CLS");
			GoToXY(0, 0);
			exit(0);
			break;
		case ESC:
			GoToXY(48, 13);
			SetColor(LightCyan, Black);
			cout << "Выход из программы...";
			_getch();
			system("CLS");
			GoToXY(0, 0);
			exit(0);
			break;
		}
	}
}

void UserLoginMenu()
{
	ConsoleCursorVisible(false, 100);
	User temp;
	string log;
	bool st = 0, l = 0, p = 0;
	short y = 12, x = 48;
		int k = 0;
	temp.SetStatus(0);
	GoToXY(x, y);
	SetColor(LightCyan, Black);
	cout << "Введите логин: ";
	SetColor(LightMagenta, Black);
	y++;
	log = CinStringSymAngErrorCheck(x, y);
	temp.SetLogin(log);
	int size = LengthFile("user.txt");
	vector<User> vec_users;
	ifstream f;
	try
	{
		f.open("user.txt");
		if (f.is_open())
		{
			User temp1;
			for (int i = 0; i < size; i++)
			{
				f >> temp1;
				vec_users.push_back(temp1);
			}
			f.close();
		}
		else
			throw("Файл не найден");
	}
	catch (const char* message) {
		cout << "Вызвано исключение." << message << endl;
		exit(0);
	}
	for (int i = 0; i < vec_users.size(); i++)
	{
		if (vec_users[i].GetStatus() == temp.GetStatus())
		{
			st = 1;
			if (vec_users[i].GetLogin() == temp.GetLogin())
			{
				l = 1;
				GoToXY(x, y++);
				SetColor(LightMagenta, Black);
				cout << "Учетная запись найдена.";
				GoToXY(x, y++);
				SetColor(LightCyan, Black);
				cout << "Введите пароль: ";
				SetColor(LightMagenta, Black);
				while (k != 5)
				{
					GoToXY(x, y++);
					temp.Password();
					//SetColor(LightMagenta, Black);
					while (temp.GetPassword() ==
						"NOOOOOOOPASSWORDERRORERRORERROR")
					{
						cout << "Вы не ввели пароль, попробуйте еще раз" << endl;
						GoToXY(x, y++);
						temp.Password();
					}
					if (vec_users[i].GetPassword() == temp.GetPassword())
					{
						temp.SetName(vec_users[i].GetName());
						temp.SetSurname(vec_users[i].GetSurname());
						p = 1;
						GoToXY(x, y++);
						SetColor(LightCyan, Black);
						cout << "Вход выполнен.";
						SetColor(LightMagenta, Black);
						_getch();
						system("CLS");
						UserMenu(temp);
						return;
					}
					else if (k == 3)
					{
						GoToXY(x, y++);
						cout << "Это последняя попытка ввода пароля.";
						GoToXY(x, y++);
						cout << "Хорошо подумайте и попробуйте еще раз";
						k++;
					}
					else if (k == 4)
					{
						GoToXY(x, y++);
						cout << "Неверный пароль.";
						k++;
						break;
					}
					else
					{
						GoToXY(x, y++);
						cout << "Неверный пароль. Попробуйте еще раз";
						k++;
					}

				}
			}
		}
	}
	if (st == 0 || l == 0)
	{
		GoToXY(x, y++);
		cout << "Учетной записи с таким именем не найдено";
		_getch();
		system("CLS");
	}
	else if (p == 0)
	{
		y++;
		GoToXY(x, y++);
		cout << ".............................................";
		GoToXY(x, y++);
		cout << "Вы 5 раз ввели неправильный пароль.";
		GoToXY(x, y++);
		cout << "Подождите 3 минуты перед следующей попыткой...";
		Sleep(7000);
		_getch();
		system("CLS");
	}
	return;

}

void LoginMenu(int status, short x, short y)
{
	ConsoleCursorVisible(false, 100);
	User temp, temp_pass;
	string log, name, surname;
	bool st = 1, p = 0;
	int k = 0;
	temp.SetStatus(status);
	GoToXY(x, y++);
	SetColor(LightCyan, Black);
	cout << "Введите логин: ";
	SetColor(LightMagenta, Black);
	rewind(stdin);
	log = CinStringSymAngErrorCheck(x, y);
	int size = LengthFile("user.txt");
	vector<User> vec_users;
	ifstream f;
	try
	{
		f.open("user.txt");
		if (f.is_open())
		{
			User temp1;
			for (int i = 0; i < size; i++)
			{
				f >> temp1;
				vec_users.push_back(temp1);
			}
			f.close();
		}
		else
			throw("Файл не найден");
	}
	catch (const char* message) {
		cout << "Вызвано исключение." << message << endl;
		exit(0);
	}
	for (int i = 0; i < size; i++)
	{
		if (vec_users[i].GetLogin() == log)
			st = 0;
	}
	if (st == 1)
	{
		st = 1;
		temp.SetLogin(log);
		GoToXY(x, y++);
		SetColor(LightCyan, Black);
		cout << "Введите ваше имя: ";
		SetColor(LightMagenta, Black);
		name = CinStringSymRusErrorCheck(x, y);
		name[0] = toupper(name[0]);
		SetColor(LightCyan, Black);
		GoToXY(x, y++);
		cout << "Введите вашу фамилию: ";
		SetColor(LightMagenta, Black);
		surname = CinStringSymRusErrorCheck(x, y);
		surname[0] = toupper(surname[0]);
		SetColor(LightCyan, Black);
		GoToXY(x, y++);
		cout << "Введите пароль: ";
		SetColor(LightMagenta, Black);
		GoToXY(x, y++);
		temp.SetName(name);
		temp.SetSurname(surname);
		temp.Password();
		while (temp.GetPassword() ==
			"NOOOOOOOPASSWORDERRORERRORERROR")
		{
			cout << "Вы не ввели пароль, попробуйте еще раз" << endl;
			GoToXY(x, y++);
			temp.Password();
		}
		GoToXY(x, y++);
		SetColor(LightCyan, Black);
		cout << "Подтвердите пароль: ";
		SetColor(LightMagenta, Black);
		while (k != 3)
		{
			GoToXY(x, y++);
			temp_pass.Password();
			while (temp_pass.GetPassword() ==
				"NOOOOOOOPASSWORDERRORERRORERROR")
			{
				cout << "Вы не ввели пароль, попробуйте еще раз" << endl;
				GoToXY(x, y++);
				temp_pass.Password();
			}
			if (temp.GetPassword() == temp_pass.GetPassword())
			{
				p = 1;
				GoToXY(x, y++);
				SetColor(LightCyan, Black);
				cout << "Учетная запись создана";
				SetColor(LightMagenta, Black);
				GoToXY(x, y++);
				ofstream f2;
				f2.open("user.txt", ios::app);
				if (!f2.is_open())
				{
					cout << "Ошибка открытия файла" << endl;
					return;
				}
				else
				{
					f2 << temp;
				}
				f2.close();
				return;
			}
			else if (k == 1)
			{
				GoToXY(x, y++);
				cout << "Это последняя попытка ввода пароля.";
				k++;
			}
			else if (k == 2)
			{
				GoToXY(x, y++);
				cout << "Неверный пароль.";
				k++;
			}
			else
			{
				GoToXY(x, y++);
				cout << "Неверный пароль. Попробуйте еще раз";
				k++;
			}
		}
	}
	else
	{
		if(x!=0&&y!=0)
			GoToXY(x, y++);
		cout << "Учетная запись с таким именем уже существует";
		p = 1;
	}
	if (p == 0)
	{
		y++;
		GoToXY(x, y++);
		cout << ".............................................";
		GoToXY(x, y++);
		cout << "Вы 3 раза ввели неправильный пароль.";
		GoToXY(x, y++);
		cout << "Начните регистрацию заново.";
		_getch;
	}
	return;
}

void AdminLoginMenu()
{
	ConsoleCursorVisible(false, 100);
	User temp;
	string log;
	bool st = 0, l = 0, p = 0;
	short y = 12, x = 48;
	int k = 0;
	temp.SetStatus(1);
	GoToXY(x, y++);
	SetColor(LightCyan, Black);
	cout << "Введите логин: ";
	SetColor(LightMagenta, Black);
	log = CinStringSymAngErrorCheck(x, y);
	temp.SetLogin(log);
	int size = LengthFile("user.txt");
	vector<User> vec_users;
	ifstream f;
	try
	{
		f.open("user.txt");
		if (f.is_open())
		{
			User temp1;
			for (int i = 0; i < size; i++)
			{
				f >> temp1;
				vec_users.push_back(temp1);
			}
			f.close();
		}
		else
			throw("Файл не найден");
	}
	catch (const char* message) {
		cout << "Вызвано исключение." << message << endl;
		exit(0);
	}
	for (int i = 0; i < size; i++)
	{
		if (vec_users[i].GetStatus() == temp.GetStatus())
		{
			st = 1;
			if (vec_users[i].GetLogin() == temp.GetLogin())
			{
				l = 1;
				GoToXY(x, y++);
				cout << "Учетная запись найдена.";
				GoToXY(x, y++);
				SetColor(LightCyan, Black);
				cout << "Введите пароль: ";
				SetColor(LightMagenta, Black);
				while (k != 3)
				{
					GoToXY(x, y++);
					temp.Password();
					while (temp.GetPassword() ==
						"NOOOOOOOPASSWORDERRORERRORERROR")
					{
						cout << "Вы не ввели пароль, попробуйте еще раз" << endl;
						GoToXY(x, y++);
						temp.Password();
					}
					if (vec_users[i].GetPassword() == temp.GetPassword())
					{
						temp.SetName(vec_users[i].GetName());
						temp.SetSurname(vec_users[i].GetSurname());
						p = 1;
						GoToXY(x, y++);
						SetColor(LightCyan, Black);
						cout << "Вход выполнен.";
						SetColor(LightMagenta, Black);
						_getch();
						system("CLS");
						AdminMenu(temp);
						return;
					}
					else if (k == 1)
					{
						GoToXY(x, y++);
						cout << "Это последняя попытка ввода пароля.";
						k++;
					}
					else if (k == 2)
					{
						GoToXY(x, y++);
						cout << "Неверный пароль.";
						k++;
					}
					else
					{
						GoToXY(x, y++);
						cout << "Неверный пароль. Попробуйте еще раз";
						k++;
					}
				}
			}
		}
	}
	if (st == 0 || l == 0)
	{
		GoToXY(x, y++);
		cout << "Учетной записи с таким именем не найдено";
		_getch();
		system("CLS");

	}
	else if (p == 0)
	{
		y++;
		GoToXY(x, y++);
		cout << ".............................................";
		GoToXY(x, y++);
		cout << "Вы 3 раза ввели неправильный пароль.";
		GoToXY(x, y++);
		cout << "Подождите 3 минуты перед следующей попыткой...";
		Sleep(7000);
		_getch();
		system("CLS");

	}
	return;
}

void AdminMenu(User account)
{
	while (TRUE) {
		string m[] = {
		"Личный кабинет",
		"Просмотреть афишу",
		"Редактировать афишу",
		"Просмотреть данные пользователей",
		"Регистрация нового администратора",
		"Изменение статуса пользователя",
		"Выход" };
		string start = "Добро пожаловать, " + account.GetName();
		int a = DrawMenu(start, m, size(m), 48, 10);
		system("CLS");
		set<Film> set_films;
		ifstream f;
		cout << fixed << setprecision(2);
		switch (a)
		{
		case 0:
			PersonalAccountAdmin(account);
			break;
		case 1:
			ViewFilms();
			_getch();
			break;
		case 2:
			EditFilms();
			break;
		case 3:
			ViewUsers();
			_getch();
			break;
		case 4:
			LoginMenu(0,0,0);
			_getch();
			break;
		case 5:
			ChangeStatus();
			_getch();
			break;
		case 6:
			GoToXY(48, 13);
			SetColor(LightCyan, Black);
			cout << "Выход из программы...";
			_getch();
			system("CLS");
			GoToXY(0, 0);
			exit(0);
			break;
		case ESC:
			system("CLS");
			return;
		}
	}
}

void UserMenu(User account)
{
	
	vector<Film> vec_films;
	ifstream f;

	while (TRUE) {
		string m[] = {
			"Личный кабинет",
			"Купить билет",
			"Просмотреть афишу",
			"Фильмы по жанрам",
			"Поиск фильма",
			"Выход" };
		string start = "Добро пожаловать, " + account.GetName();
		int a = DrawMenu(start, m, size(m), 48, 10);
		system("CLS");
		int size;
		switch (a)
		{
		case 0:
			PersonalAccount(account);
			break;
		case 1:
			ChoiceFilm(account.GetLogin());
			break;
		case 2:
			ViewFilms();
			_getch();
			break;
		case 3:
			GenreSorte();
			_getch();
			break;
		case 4:
			size = FilmFileLength("cinema.txt");
			
			f.open("cinema.txt");
			if (!f.is_open())
			{
				cout << "Ошибка открытия файла" << endl;
				return;
			}
			else
			{
				Film temp1;
				for (int i = 0; i < size; i++)
				{
					f >> temp1;
					vec_films.push_back(temp1);
				}
			}
			f.close();
			Find(vec_films);
			_getch();
			break;
		
		case 5:
			GoToXY(48, 13);
			SetColor(LightCyan, Black);
			cout << "Выход из программы...";
			_getch();
			system("CLS");
			GoToXY(0, 0);
			exit(0);
			break;
		case ESC:
			system("CLS");
			return;
		}
	}
}

void PersonalAccount(User &account)
{
	while (TRUE) {
		string m[] = {
			"Доступные билеты",
			"Просмотреть личные данные",
			"Изменить личные данные",
			"Выход" };
		string start = "Добро пожаловать, " + account.GetName();
		int a = DrawMenu(start, m, size(m), 48, 10);
		system("CLS");
		switch (a)
		{
		case 0:
			ViewTickets(account.GetLogin());
			_getch();
			break;
		case 1:
			ViewUser(account);
			_getch();
			break;
		case 2:
			ChangeUser(account);
			_getch();
			break;
		case 3:
			GoToXY(48, 13);
			SetColor(LightCyan, Black);
			cout << "Выход из программы...";
			_getch();
			system("CLS");
			GoToXY(0, 0);
			exit(0);
			break;
		case ESC:
			system("CLS");
			return;
		}
	}
}

void PersonalAccountAdmin(User& account)
{
	while (TRUE) {
		string m[] = {
			"Просмотреть личные данные",
			"Изменить личные данные",
			"Выход" };
		string start = "Добро пожаловать, " + account.GetName();
		int a = DrawMenu(start, m, size(m), 48, 10);
		system("CLS");
		switch (a)
		{
		case 0:
			ViewUser(account);
			_getch();
			break;
		case 1:
			ChangeUser(account);
			_getch();
			break;
		case 2:
			GoToXY(48, 13);
			SetColor(LightCyan, Black);
			cout << "Выход из программы...";
			_getch();
			system("CLS");
			GoToXY(0, 0);
			exit(0);
			break;
		case ESC:
			system("CLS");
			return;
		}
	}
}