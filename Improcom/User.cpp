#include "User.h"


int LengthFile(string name)
{
	ifstream f;
	f.open(name, ios::in);
	int i = 0;
	if (!f.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return 0;
	}
	else
	{
		string line;
		while (getline(f, line))
			i++;
	}
	f.close();
	return i;
}

void Encrypt(string& pass)
{
	int number = pass.size(), k;
	char* temp = new char[number];
	k = 7;
	for (int i = 0; i < number; i++)
	{
		int symbol = pass[i];
		symbol += k;
		temp[i] = symbol;
	}
	for (int i = 0; i < number; i++)
	{
		pass[i] = temp[i];
	}
	delete[]temp;
}
void Decrypt(string& pass)
{
	int number = pass.size(), k;
	char* temp = new char[number];
	k = 7;
	for (int i = 0; i < number; i++)
	{
		int symbol = pass[i];
		symbol -= k;
		temp[i] = symbol;
	}
	for (int i = 0; i < number; i++)
	{
		pass[i] = temp[i];
	}
	delete[]temp;
}

void User::Password()
{
	int ch = 0;
	string pass;
	while (true)
	{
		ch = _getch();
		if (ch == 13)
		{
			break;
		}
		else if (ch == 32)
		{
			break;
		}
		else if (ch == 8) // Удаление последнего введенного символа
		{

			if (!pass.empty())
			{
				cout << (char)8 << ' ' << (char)8; // Удаление из консоли
				pass.erase(pass.length() - 1); // Удаление из памяти
			}
		}
		else
		{
			cout << '*';
			pass = pass + (char)ch;
		}
	}
	if (!pass.empty())
		password = pass;
	else
		password = "NOOOOOOOPASSWORDERRORERRORERROR";
}

ostream& operator <<(ostream& os, const User& user)
{
	const type_info& t = typeid(os);
	if (OF == t)
	{
		string pass = user.password;
		Encrypt(pass);
		os << user.login << " " << pass << " " << user.status << " " << user.name << " " << user.surname << endl;
		
	}
	else 
	{
		os << user.login << " " << user.password << " " << user.status << " " << user.name << " " << user.surname;
	}
	return os;
}

istream& operator >>(istream& is, User& user)
{
	const type_info& t = typeid(is);
	if (IF == t)
	{
		string pass;
		is >> user.login >> pass >> user.status >> user.name >> user.surname;
		Decrypt(pass);
		user.SetPassword(pass);
	}
	return is;
}

bool operator<(User a, User b)
{
	return a.GetLogin() < b.GetLogin();
}
bool operator==(User a, string b)
{
	return a.GetLogin() == b;
}

void ViewUsers()
{
	ColoredTable t;
	int size = LengthFile("user.txt");
	ifstream f;
	f.open("user.txt");
	if (!f.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}
	else
	{
		User u;
		vector<pair<string, int> > collums;
		vector<string> data;
		vector<User> temp;
		f >> u;
		temp.push_back(u);
		int size_log = temp[0].GetLogin().size(),
			size_pass = temp[0].GetPassword().size(),
			size_name = temp[0].GetName().size(),
			size_surname = temp[0].GetSurname().size();
		for (int i = 1; i < size; i++)
		{
			f >> u;
			temp.push_back(u);
			if (size_log < temp[i].GetLogin().size())
				size_log = temp[i].GetLogin().size();
			if (size_pass < temp[i].GetPassword().size())
				size_pass = temp[i].GetPassword().size();
			if (size_name < temp[i].GetName().size())
				size_name = temp[i].GetName().size();
			if(size_surname < temp[i].GetSurname().size())
				size_surname = temp[i].GetSurname().size();
		}
		if (size_log < 8)
			size_log = 8;
		if (size_pass < 7)
			size_pass = 7;
		if (size_name < 8)
			size_name = 8;
		if (size_surname < 5)
			size_surname = 5;
		collums.push_back(pair<string, int>("Статус", 8));
		collums.push_back(pair<string, int>("Логин", size_log+2));
		collums.push_back(pair<string, int>("Пароль", size_pass+2));
		collums.push_back(pair<string, int>("Имя", size_name+2));
		collums.push_back(pair<string, int>("Фамилия", size_surname+2));

		for (int i = 0; i < size; i++)
		{
			if(temp[i].GetStatus() == 0)
				data.push_back("User");
			else
				data.push_back("Admin");
			data.push_back(temp[i].GetLogin());
			//data.push_back(temp[i].GetPassword());
			string pass;
			for (int j = 0; j < temp[i].GetPassword().size(); j++)
				pass += '*';
			data.push_back(pass);
			data.push_back(temp[i].GetName());
			data.push_back(temp[i].GetSurname());
		}
		t.OutputTable(collums, data);
	}
	f.close();
}

void ViewUser(User account)
{
	ColoredTable t;
	vector<pair<string, int> > collums;
	vector<string> data;
	int size_log = account.GetLogin().size(),
		size_pass = account.GetPassword().size(),
		size_name = account.GetName().size(),
		size_surname = account.GetSurname().size();
	if (size_log < 8)
		size_log = 8;
	if (size_pass < 7)
		size_pass = 7;
	if (size_name < 8)
		size_name = 8;
	if (size_surname < 5)
		size_surname = 5;
	collums.push_back(pair<string, int>("Статус", 8));
	collums.push_back(pair<string, int>("Логин", size_log + 2));
	collums.push_back(pair<string, int>("Пароль", size_pass + 2));
	collums.push_back(pair<string, int>("Имя", size_name + 2));
	collums.push_back(pair<string, int>("Фамилия", size_surname + 2));
	if (account.GetStatus() == 0)
		data.push_back("User");
	else
		data.push_back("Admin");
	data.push_back(account.GetLogin());
	data.push_back(account.GetPassword());
	data.push_back(account.GetName());
	data.push_back(account.GetSurname());
	t.OutputTable(collums, data);
}

void ChangeStatus()
{
	short x = 0, y = 0;
	User temp;
	string log;
	bool l = 0;
	int stat;
	int size = LengthFile("user.txt");
	vector<User> vec_users;
	ifstream f;
	f.open("user.txt");
	if (!f.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}
	else
	{
		User temp1;
		for (int i = 0; i < size; i++)
		{
			f >> temp1;
			vec_users.push_back(temp1);
		}
	}
	f.close();
	cout << "Просмотреть существующие записи?(1-Да, 2-Нет)" << endl;
	char ch;
	ch = _getch();
	if (ch == 49) {
		cout << endl;
		ViewUsers();
		cout << endl;
	}
	cout << "Введите логин: " << endl;
	log = CinStringSymAngErrorCheck(x, y);
	temp.SetLogin(log);
	for (int i = 0; i < size; i++)
	{
		if (vec_users[i].GetLogin() == temp.GetLogin())
		{
			l = 1;
			cout << "Учетная запись найдена" << endl;
			cout << "Введите новый статус пользователя: 0-Пользователь, 1-Администратор" << endl;
			while (true)
			{
				ch = _getch();
				if (ch == 48) {
					stat = 0;
					break;
				}
				else if (ch == 49)
				{
					stat = 1;
					break;
				}
				else
					cout << "Введите 0 или 1" << endl;

			}
			temp.SetStatus(stat);
			if (vec_users[i].GetStatus() != temp.GetStatus())
			{
				vec_users[i].SetStatus(stat);
				cout << "Статус изменен" << endl;
				ofstream file;
				file.open("user.txt");
				if (!file.is_open())
				{
					cout << "Ошибка открытия файла" << endl;
					return;
				}
				else
				{
					VectorSorte<User>::Sort(vec_users, &User::GetLogin);
					//SorteUsers(vec_users);
					for (int j = 0; j < size; j++)
					{
						file << vec_users[j];
					}
				}
				file.close();
			}
			else
			{
				cout << "Статусы совпадают" << endl;
				break;
			}
		}
	}
	if (l == 0)
	{
		cout << "Учетной записи с таким именем не найдено" << endl;
	}

}

void ChangeUser(User& account)
{
	bool b = 0, change = 0;
	string login, pass, name, surname;
	short y = 0, x=0;
	int size = LengthFile("user.txt");
	vector<User> vec_users;
	ifstream f;
	f.open("user.txt");
	if (!f.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}
	else
	{
		User temp1;
		for (int i = 0; i < size; i++)
		{
			f >> temp1;
			vec_users.push_back(temp1);
		}
	}
	f.close();
	for (int i = 0; i < size; i++)
	{
		if (vec_users[i].GetLogin() == account.GetLogin())
		{
			b = 1;
			cout << "Просмотреть текущие данные?(1-Да, 2-Нет)" << endl;
			char ch;
			ch = _getch();
			if (ch == 49) {
				cout << endl;
				ViewUser(account);
				cout << endl;
			}
			login = account.GetLogin();
			pass = account.GetPassword();
			name = account.GetName();
			surname = account.GetSurname();
			_getch();
			int c = 1;
			while (c) {
				string s[] = { "Логин", "Пароль", "Имя", "Фамилию" };
				int a = DrawMenu("Изменить:", s, sizeof(s) / sizeof(s[0]), 3, y);
				x = 0, y = 0;
				cout << endl;
				SetColor(LightCyan, Black);
				switch (a)
				{
				case 0:
					change = 1;
					cout << "Введите логин: " << endl;
					login = CinStringSymAngErrorCheck(x, y);
					break;
				case 1:
					change = 1;
					cout << "Введите пароль: " << endl;
					account.Password();
					while (account.GetPassword() ==
						"NOOOOOOOPASSWORDERRORERRORERROR")
					{
						cout << "Вы не ввели пароль, попробуйте еще раз" << endl;
						account.Password();
					}
					break;
				case 2:
					change = 1;
					cout << "Введите имя: " << endl;
					name = CinStringSymRusErrorCheck(x, y);
					name[0] = toupper(name[0]);
					break;
				case 3:
					change = 1;
					cout << "Введите фамилию: " << endl;
					surname = CinStringSymRusErrorCheck(x, y);
					surname[0] = toupper(surname[0]);
					break;
				case ESC:
					c = 0;
					break;
				}
				if (change) 
				{
					for (int j = 0; j < i; j++)
					{
						if (vec_users[j].GetLogin() == login)
						{
							cout << "Такой логин уже существует" << endl;
							return;
						}
					}
					for (int j = i + 1; j < size; j++)
					{
						if (vec_users[j].GetLogin() == login)
						{
							cout << "Такой логин уже существует" << endl;
							return;
						}
					}
				}
			}
			if (change) {
				account.SetLogin(login);
				account.SetName(name);
				account.SetSurname(surname);
				auto it = vec_users.begin();
				vec_users.erase(it + i);
				vec_users.push_back(account);
				cout << "Данные изменены" << endl;
				ofstream file;
				file.open("user.txt");
				if (!file.is_open())
				{
					cout << "Ошибка открытия файла" << endl;
					return;
				}
				else
				{
					VectorSorte<User>::Sort(vec_users, &User::GetLogin);
					//SorteUsers(vec_users);
					for (int j = 0; j < size; j++)
					{
						file << vec_users[j];
					}
				}
				file.close();
			}
			return;
		}
		
	}
	if(b==0)
	{
		cout << "Ошибка" << endl;
		return;
	}

}

void User::Copy(const User& other)
{
	login = other.login;
	password = other.password;
	name = other.name;
	surname = other.surname;
	status = other.status;
}

void SorteUsers(vector<User>& vec_users) {
	User temp;
	int size = vec_users.size(), min;
	for (int i = 0; i < size - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (vec_users[j] < vec_users[min])
				min = j;
		}
		temp = vec_users[i];
		vec_users[i] = vec_users[min];
		vec_users[min] = temp;
	}
}

