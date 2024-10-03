#include "Cinema.h"

int FilmFileLength(string name) {
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
		i /= 4;
	}
	f.close();
	return i;
}

void Calendar(int month)
{
	string months_list[12] = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь" };
	int mdays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	string weekdays[7] = { "Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс" };
	static int t[] = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	int days, current;
	int year;
	if (month == 12)
	{
		year = 2023;
		//определение дня недели
		static int t[] = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
		int y = year % 100;
		current = y / 12 + y % 12 + y % 12 / 4 + t[month - 1] + (20 - year / 100);
		if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) && month <= 2) current--;
		current = current % 7;
	}
	else if (month == 1)
	{
		year = 2024;
		//определение дня недели
		int y = year % 100;
		current = y / 12 + y % 12 + y % 12 / 4 + t[month - 1] + (20 - year / 100);
		if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) && month <= 2) current--;
		current = current % 7;

	}
	//Проверка на високосность начиная с нулевого месяца:
	if (month == 2)
		if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			days = 29; //Если високосный
		else
			days = mdays[month - 1];
	else
		days = mdays[month - 1];
	int i = month - 1;
	SetColor(LightMagenta, Black);
	if(month==12)
		cout << endl<<endl << "--------------" << months_list[i] << "--------------" << endl;
	else
		cout << endl << endl << "---------------" << months_list[i] << "--------------" << endl;
	SetColor(LightCyan, Black);
	for (int j = 0; j < 7; j++)
	{
		cout << setw(5) << weekdays[j];
	}
	cout << endl;
	/*	доп. переменные k и j:
		k - количество дней в неделе от 0 до 6 (0 - ПН; 6 - ВС)
		j - количество дней в месяце (от 1 до общего в месяце)
		*/
	int k;
	for (k = 0; k < current; k++)
		cout << "     ";
	cout << setw(5 * current);
	for (int j = 1; j <= days; j++)
	{
		k++;
		cout << setw(5) << j;
		if (k > 6)
		{
			k = 0;
			cout << endl;
		}
	}
	if (k)
		cout << endl;
	SetColor(LightMagenta, Black);
	if (month == 12)
		cout << "-----------------------------------" << endl << endl;
	else
		cout << "-----------------------------------" << endl << endl;
	SetColor(LightCyan, Black);
}

void Film::AddFilmData()
{
	set<double> dates;
	double temp, interval, first_time, *time;
	int n, count_dates, month;
	//выбрать дни
	while (true) {
		cout << "Введите номер месяца (12-Декабрь, 1-Январь): ";
		month = CinIntErrorCheck();
		if (month == 1 || month == 12)
			break;
		else
			cout << "Неверный ввод" << endl;
	}
	Calendar(month);
	// Получаем текущее время
	time_t currentTime = std::time(0);
	// Конвертируем текущее время в структуру tm для локального времени
	tm* localTime = localtime(&currentTime);
	int today = localTime->tm_mday;
	bool first = 0;
	while (true) {
		cout << "Введите номер дня (0-для выхода)" << endl;
		if (month == 12) 
		{
			temp = CinIntErrorCheck(0, 31);
			if (first!=0&&temp==0) 
			{
					break;
			}
			else if(temp==0)
			{
				cout << "Вы не выбрали ни одного дня" << endl;
				continue;
			}
				if (temp < today + 1)
				{
					cout << "Сегодня уже " << today << " декабря. Введите будущую дату" << endl;
					continue;
				}
				temp += 0.12;
				first = 1;
			
		}
		else if (month == 1) 
		{
			temp = CinIntErrorCheck(0, 31);
			if (first != 0 && temp == 0)
			{
				break;
			}
			else if (temp == 0)
			{
				cout << "Вы не выбрали ни одного дня" << endl;
				continue;
			}
			temp += 0.01;
			first = 1;
		}
		
		dates.insert(temp);
	}
	bool a = 1;
	int film_length_m;
	int time_h, time_m;
	//длина фильма в минутах
	time_h = round((int)length);
	time_m = round((length - (int)length) * 100);
	film_length_m = time_h * 60 + time_m;
	while (a) {
		//определить время начала сеансов
		cout << "Введите время начала сеансов (9-23)" << endl;
		first_time = CinDoubleErrorCheck(9, 23);

		//количество показов
		int max = (24 - first_time)*60/film_length_m;
		cout << "Введите количество сеансов" << endl;
		n = CinIntErrorCheck(1, max);

		//интервал между показами

		//начало в минутах
		time_h = round((int)first_time);
		time_m = round((first_time - (int)first_time) * 100);
		first_time = time_h * 60 + time_m;

		
		if (n != 1) {
			int max_interval = (24 * 60 - first_time - (n - 1) * film_length_m);
			if (max_interval < 20) {
				cout << "Вы ввели некорректные данные для сеансов. Начните заново" << endl;
				continue;
			}
			else {
				cout << "Введите интервал между показами в минутах (>20 мин)" << endl;
				interval = CinIntErrorCheck(20, max_interval);
				a = 0;
			}
		}
		else
			interval = 0;

	}

	time = new double[n];
	for (int i = 0, k = first_time; i < n; i++, k += (interval+ film_length_m))
	{
		int h = k / 60 % 24;
		int m = k % 60;
		time[i] = h + m / 100.;
		
	}
	count_days = dates.size();
	int i = 0;
	
	day = unique_ptr<Day[]>(new Day[count_days]);
	for (auto it = dates.begin(); it!=dates.end(); it++)
	{
		day[i].SetData(*it);
		day[i].SetCountTimes(n);
		day[i].SetTime(time);
		i++;
	}
	delete[]time;
}

void Film::AddFilm()
{
	string name, genre;
	double length, price;
	int age, rows, seats, format;
	cout << "Введите название фильма: " << endl;
	name= GetlineErrorCheck();
	name[0] = toupper(name[0]);
	if (!UniqueFilm(name))
	{
		cout << "Такой фильм уже добавлен в афишу" << endl;
		_getch();
		return;
	}
	
	cout << "Введите жанр фильма: " << endl;
	genre = CinStringSymRusErrorCheck();
	cout << "Введите длину фильма в минутах (>15):  " << endl;
	length = CinDoubleErrorCheck(15, 7 * 60);
	double time_h, time_m;
	time_h = (int)length / 60;
	time_m = (length - time_h * 60) / 100;
	length = time_h + time_m;
	this->length = length;
	cout << "Введите формат фильма (2: 2D, 3: 3D)" << endl;
	format = CinIntErrorCheck(2, 3);
	while (true) {
		cout << "Введите возрастное ограничение " << endl;
		age = CinIntErrorCheck(0, 21);
		if (age == 0 || age == 3 || age == 6 || age == 12 || age == 15 || age == 16 || age == 18 || age == 21)
			break;
		else
			cout << "Такого возрастного ограничения не существует" << endl;
	}
	cout << "Введите цену за просмотр: " << endl;
	price = CinDoubleErrorCheck(1, 100);
	AddFilmData();
	cout << "Введите параметры кинозала\nВведите количество рядов (<20):" << endl;
	rows = CinIntErrorCheck(1, 20);
	cout << "Введите количество мест в ряду (<20):" << endl;
	seats = CinIntErrorCheck(1, 20);
	this->name = name;
	age_limit = age;
	this->genre = genre;
	this->format = format;
	this->length = length;
	this->price = price;
	hall.SetRows(rows);
	hall.SetSeats(seats);
}

void Film::ViewFilmData() const{
	cout << "Количество дней " << count_days << endl;
	for (int i = 0; i < count_days; i++)
	{
		cout << "День " << day[i].GetData() << endl;
		cout << "Количество сеансов " << day[i].GetCountTimes() << endl;
		cout << "Время " << endl;
		for (int j = 0; j < day[i].GetCountTimes(); j++)
			cout << day[i].GetTime()[j] << "\t";
		cout << endl;
	}
}

void Film::ViewFilm() const
{
	table::ColoredTable t;
	Film temp;
	vector<pair<string, int>> collums;
	vector<string> data;
	int size_name = name.size(),
		size_genre = genre.size();
	if (size_name < 10)
		size_name = 10;
	if (size_genre < 6)
		size_genre = 6;

	collums.push_back(pair<string, int>("Название", size_name + 2));
	collums.push_back(pair<string, int>("Жанр", size_genre + 2));
	collums.push_back(pair<string, int>("Время, ч", 10));
	collums.push_back(pair<string, int>("Возраст", 10));
	collums.push_back(pair<string, int>("Формат", 10));
	collums.push_back(pair<string, int>("Цена, р", 10));
	collums.push_back(pair<string, int>("Зал", 10));
	collums.push_back(pair<string, int>("Кол. дней", 12));
	collums.push_back(pair<string, int>("Дата", 10));
	int size_time = day.get()->GetCountTimes();
	size_time *= 6;
	collums.push_back(pair<string, int>("Время", size_time));

	data.push_back(name);
	data.push_back(genre);

	string length_f;
	int time_h = round((int)length);
	int time_m = round((length - (int)length) * 100);
	length_f = '0' + to_string(time_h) + ':';
	if (time_m <10)
		length_f += '0';
	length_f += to_string(time_m);
	data.push_back(length_f);

	string age = to_string(age_limit);
	age += '+';
	data.push_back(age);
	string format = to_string(this->format);
	format += 'D';
	data.push_back(format);

	string pr;
	int pr1 = (int)price;
	int pr2 = (price - (int)price) * 100;
	pr = to_string(pr1) + '.' + to_string(pr2);
	if (pr2 == 0)
		pr += '0';
	data.push_back(pr);

	string h = to_string(hall.GetRows());
	h += 'x';
	h += to_string(hall.GetSeats());
	data.push_back(h);
	data.push_back(to_string(count_days));

	string time;
	int n = day[0].GetCountTimes();
	string d;
	int d1 = (int)round(day[0].GetData());
	int d2 = round((day[0].GetData() - (int)day[0].GetData()) * 100);
	d = to_string(d1) + '.' + to_string(d2);
	data.push_back(d);
	for (int j = 0; j < n; j++) 
	{
		int t1 = round((int)day[0].GetTime()[j]);
		int t2 = round((day[0].GetTime()[j] - (int)day[0].GetTime()[j])*100);
		time += to_string(t1) + ':' + to_string(t2);
		if (t2 == 0)
			time += '0';
		time += ' ';
	}

	data.push_back(time);

	for (int i = 1; i < count_days; i++)
	{
		for (int j = 0; j < 8; j++)
			data.push_back(" ");

		n = day[i].GetCountTimes();
		time.clear();

		int d1 = round((int)day[i].GetData());
		int d2 = round((day[i].GetData() - (int)day[i].GetData()) * 100);
		d = to_string(d1) + '.' + to_string(d2);
		data.push_back(d);

		for (int j = 0; j < n; j++) 
		{
			int t1 = round((int)day[i].GetTime()[j]);
			int t2 = round((day[i].GetTime()[j] - (int)day[i].GetTime()[j]) * 100);
			time += to_string(t1) + ':' + to_string(t2);
			if (t2 == 0)
				time += '0';
			time += ' ';
		}
		data.push_back(time);
	}
	t.OutputTable(collums, data);
}

void ViewFilms()
{
	cout << fixed << setprecision(2);
	table::ColoredTable t;
	int size = FilmFileLength("cinema.txt");
	set<Film> set_films;
	ifstream f;
	f.open("cinema.txt");
	if (!f.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}
	else
	{

		Film temp;
		vector<pair<string, int>> collums;
		vector<string> data;
		set<Film> set_films;
		f >> temp;
		set_films.insert(temp);
		auto it = set_films.begin();
		int size_name = (*it).name.size(),
			size_genre = (*it).genre.size();

		for (int i = 1; i < size; i++)
		{
			f >> temp;
			set_films.insert(temp);
		}

		it = set_films.begin();
		while (it != set_films.end())
		{
			if (size_name < (*it).name.size())
				size_name = (*it).name.size();
			if (size_genre < (*it).genre.size())
				size_genre = (*it).genre.size();
			it++;
		}

		if (size_name < 10)
			size_name = 10;
		if (size_genre < 6)
			size_genre = 6;

		collums.push_back(pair<string, int>("Название", size_name + 2));
		collums.push_back(pair<string, int>("Жанр", size_genre + 2));
		collums.push_back(pair<string, int>("Время, ч", 10));
		collums.push_back(pair<string, int>("Возраст", 10));
		collums.push_back(pair<string, int>("Формат", 10));
		collums.push_back(pair<string, int>("Цена, р", 10));

		for (auto it = set_films.begin(); it != set_films.end(); ++it)
		{
			data.push_back((*it).name);
			data.push_back((*it).genre);

			string length_f;
			int time_h = round((int)((*it).length));
			int time_m = round(((*it).length - (int)((*it).length)) * 100);
			length_f = '0' + to_string(time_h) + ':';
			if (time_m < 10)
				length_f += '0';
			length_f += to_string(time_m);
			data.push_back(length_f);

			string age = to_string((*it).age_limit);
			age += '+';
			data.push_back(age);
			string format = to_string((*it).format);
			format += 'D';
			data.push_back(format);

			string pr;
			int pr1 = (int)((*it).price);
			int pr2 = ((*it).price - (int)((*it).price)) * 100;
			pr = to_string(pr1) + '.' + to_string(pr2);
			if (pr2 == 0)
				pr += '0';
			data.push_back(pr);
		}
		t.OutputTable(collums, data);
	}
	f.close();
}

void ViewFilms(vector<Film> vec_films)
{

	table::ColoredTable t;
	int size = vec_films.size();
	vector<pair<string, int>> collums;
	vector<string> data;

	int size_name = vec_films[0].name.size(),
		size_genre = vec_films[0].genre.size();

	for (int i = 1; i < size; i++)
	{
		if (size_name < vec_films[i].name.size())
			size_name = vec_films[i].name.size();
		if (size_genre < vec_films[i].genre.size())
			size_genre = vec_films[i].genre.size();
	}

	if (size_name < 10)
		size_name = 10;
	if (size_genre < 6)
		size_genre = 6;

	collums.push_back(pair<string, int>("Жанр", size_genre + 2));
	collums.push_back(pair<string, int>("Название", size_name + 2));
	collums.push_back(pair<string, int>("Время, ч", 10));
	collums.push_back(pair<string, int>("Возраст", 10));
	collums.push_back(pair<string, int>("Формат", 10));
	collums.push_back(pair<string, int>("Цена, р", 10));

	for (int i = 0; i < size; i++)
	{
		data.push_back(vec_films[i].genre);
		data.push_back(vec_films[i].name);

		string length_f;
		int time_h = round((int)(vec_films[i].length));
		int time_m = round((vec_films[i].length - (int)(vec_films[i].length)) * 100);
		length_f = '0' + to_string(time_h) + ':';
		if (time_m < 10)
			length_f += '0';
		length_f += to_string(time_m);
		data.push_back(length_f);

		string age = to_string(vec_films[i].age_limit);
		age += '+';
		data.push_back(age);
		string format = to_string(vec_films[i].format);
		format += 'D';
		data.push_back(format);

		string pr;
		int pr1 = (int)(vec_films[i].price);
		int pr2 = (vec_films[i].price - (int)(vec_films[i].price)) * 100;
		pr = to_string(pr1) + '.' + to_string(pr2);
		if (pr2 == 0)
			pr += '0';
		data.push_back(pr);
	}
	t.OutputTable(collums, data);
	
}

void ViewFilms(vector<Film> vec_films, vector<int> vec)
{

	table::ColoredTable t;
	int size = vec_films.size();
	vector<pair<string, int>> collums;
	vector<string> data;

	int size_name = vec_films[0].name.size(),
		size_genre = vec_films[0].genre.size();

	for (int i = 1; i < size; i++)
	{
		if (size_name < vec_films[i].name.size())
			size_name = vec_films[i].name.size();
		if (size_genre < vec_films[i].genre.size())
			size_genre = vec_films[i].genre.size();
	}

	if (size_name < 10)
		size_name = 10;
	if (size_genre < 6)
		size_genre = 6;

	collums.push_back(pair<string, int>("Название", size_name + 2));
	collums.push_back(pair<string, int>("Время, ч", 10));
	collums.push_back(pair<string, int>("Возраст", 10));
	collums.push_back(pair<string, int>("Формат", 10));
	collums.push_back(pair<string, int>("Цена, р", 10));

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < vec.size(); j++)
		{
			if (i == vec[j]) {

				data.push_back(vec_films[i].name);

				string length_f;
				int time_h = round((int)(vec_films[i].length));
				int time_m = round((vec_films[i].length - (int)(vec_films[i].length)) * 100);
				length_f = '0' + to_string(time_h) + ':';
				if (time_m < 10)
					length_f += '0';
				length_f += to_string(time_m);
				data.push_back(length_f);

				string age = to_string(vec_films[i].age_limit);
				age += '+';
				data.push_back(age);
				string format = to_string(vec_films[i].format);
				format += 'D';
				data.push_back(format);

				string pr;
				int pr1 = (int)(vec_films[i].price);
				int pr2 = (vec_films[i].price - (int)(vec_films[i].price)) * 100;
				pr = to_string(pr1) + '.' + to_string(pr2);
				if (pr2 == 0)
					pr += '0';
				data.push_back(pr);
			}
		}
	}
	t.OutputTable(collums, data);

}

istream& operator >>(istream& is, Film& film)
{
	const type_info& t = typeid(is);
	if (IF == t) //из файла
	{
		char a=' ';
		string title;
		is.get(a);
		if(a=='\n')
			rewind(stdin); //моя любимая функция!!!
		else
			title += a;
		while (is.get(a) && a != '\n') {
			title += a;
		}
		film.name = title;
		is>> film.genre >> film.length >> film.age_limit >> film.format >> film.price >> film.count_days;
		film.day = unique_ptr<Day[]>(new Day[film.count_days]);
		for (int i = 0; i < film.count_days; i++)
		{
			double data; int count; 
			is >> data >> count;
			double* mas =new double[count];
			film.day[i].SetData(data);
			film.day[i].SetCountTimes(count);
			for (int j = 0; j < count; j++)
			{
				is >> mas[j];
			}
			film.day[i].SetTime(mas);
			delete[]mas;
		}
		int row, seat;
		is >> row >> seat;
		film.hall.SetRows(row);
		film.hall.SetSeats(seat);
	}
	else //ввод
	{
		film.AddFilm();
	}
	return is;
}

ostream& operator <<(ostream& os, const Film& film)
{
	const type_info& t = typeid(os);
	if (OF == t) //в файл
	{
		os << film.name << endl << film.genre << " " << film.length << " " << film.age_limit 
			<< " " << film.format << " " << film.price << " " << film.count_days<<endl;
		for (int i = 0; i < film.count_days; i++)
		{
			int count = film.day[i].GetCountTimes();
			os << film.day[i].GetData() << " " << count <<" ";
			for (int j = 0; j < count; j++)
				os << film.day.get()[i].GetTime()[j] << " ";
		}
		os <<endl<< film.hall.GetRows() <<" "<< film.hall.GetSeats()<<endl;
	}
	else //вывод
	{
		os<< fixed << setprecision(2);
		film.ViewFilm();
	}
	return os;
}

void EditFilms()
{
	string title;
	char ch;
	Film temp;
	int size = FilmFileLength("cinema.txt");
	set<Film> set_films;
	ifstream f;
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
			set_films.insert(temp1);
		}
	}
	f.close();
	auto it = set_films.begin();
	ofstream file;
	while (TRUE) {
		string s[] = {
			"Добавить новый фильм",
			"Изменить фильм",
			"Удалить фильм",
			"Выход" };
		int a = DrawMenu("Редактирование афиши", s, sizeof(s) / sizeof(s[0]), 3, 0);
		
		switch (a)
		{
		case 0:
			system("CLS");
			cin >> temp;
			set_films.insert(temp);
			
			file.open("cinema.txt", ios::app);
			if (!file.is_open())
			{
				cout << "Ошибка открытия файла" << endl;
				return;
			}
			else
			{
				file << temp;
			}
			file.close();
			_getch();
			break;
		case 1:
			system("CLS");
			ChangeFilm();
			break;
		case 2:
			system("CLS");
			cout << "Просмотреть текущие данные?(1-Да, 2-Нет)" << endl;
			
			ch = _getch();
			if (ch == 49) {
				ViewFilms();
			}

			cout << "Введите название фильма" << endl;
			title = GetlineErrorCheck();
			title[0] = toupper(title[0]);
			temp.SetName(title);
			it = set_films.find(temp);
			if (it != set_films.end())
			{
				set_films.erase(it);
				cout << "Фильм удален" << endl;
				it = set_films.begin();
				file.open("cinema.txt");
				if (!file.is_open())
				{
					cout << "Ошибка открытия файла" << endl;
					return;
				}
				else
				{
					while (it != set_films.end())
					{
						file << *it;
						it++;
					}
				}
				file.close();
				_getch();
				break;
			}
			else
				cout << "Фильм не найден" << endl;
			_getch();
			break;
		case 3:
			system("CLS");
			GoToXY(48, 13);
			SetColor(LightCyan, Black);
			cout << "Выход из программы...";
			_getch();
			system("CLS");
			GoToXY(0, 0);
			exit(0);
			break;
		case ESC:
			//system("CLS");
			return;
		}
	}
}

void ChangeFilm()
{
	int size = FilmFileLength("cinema.txt");
	set<Film> set_films;
	ifstream f;
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
			set_films.insert(temp1);
		}
	}
	f.close();
	string title;
	Film temp;
	auto it = set_films.begin();
	cout << "Введите название фильма" << endl;
	title= GetlineErrorCheck();
	title[0] = toupper(title[0]);
	temp.SetName(title);
	it = set_films.find(temp);
	if (OrderedFilms(title))
	{
		cout << "Билеты на этот фильм уже проданы. Выберите другой фильм" << endl;
		_getch();
		return;
	}
	if (it != set_films.end())
	{	
		cout << "Просмотреть текущие данные?(1-Да, 2-Нет)" << endl;
		char ch;
		ch = _getch();
		if (ch == 49) {
			cout << endl;
			(*it).ViewFilm();
			cout << endl;
			_getch();
		}
		bool c = 1;
		double length;
		int rows, seats, age;
		double time_h, time_m;
		ofstream file;
		temp.Copy(*it);
		
		while (c) 
		{
			string s[] = {
				"Название",
				"Жанр",
				"Возрастное ограничение",
				"Формат",
				"Цену проката",
				"Длину фильма и дни сеансов",
				"Зал" };
			int a = DrawMenu("Изменить:", s, sizeof(s) / sizeof(s[0]), 3, 0);
			system("CLS");
			switch (a)
			{
			case 0:
				
				while (true)
				{
					cout << "Введите название фильма: " << endl;
					temp.name= GetlineErrorCheck();
					if (!temp.name.empty())
						break;
					else
						cout << "Вы ничего не ввели" << endl;
				}
				temp.name[0] = toupper(temp.name[0]);
				break;
			case 1:
				
				cout << "Введите жанр фильма: " << endl;
				temp.genre = CinStringSymRusErrorCheck();
				break;
			case 2:
				
				while (true) {
					cout << "Введите возрастное ограничение " << endl;
					age = CinIntErrorCheck(0, 21);
					if (age == 0 || age == 3 || age == 6 || age == 12 || age == 15 || age == 16 || age == 18 || age == 21)
						break;
					else
						cout << "Такого возрастного ограничения не существует" << endl;
				}
				temp.age_limit = age;
				break;
			case 3:
				
				cout << "Введите формат фильма (2: 2D, 3: 3D)" << endl;
				temp.format = CinIntErrorCheck(2, 3);
				break;
			case 4:
				
				cout << "Введите цену за просмотр: " << endl;
				temp.price = CinDoubleErrorCheck(1, 100);
				break;
			case 5:
				
				cout << "Введите длину фильма в минутах:  " << endl;
				length = CinDoubleErrorCheck(10, 7 * 60);
				time_h = (int)length / 60;
				time_m = (length - time_h * 60) / 100;
				length = time_h + time_m;
				temp.length = length;
				temp.AddFilmData();
				break;
			case 6:
				
				cout << "Введите параметры кинозала\nВведите количество рядов (<30):" << endl;
				rows = CinIntErrorCheck(1, 30);
				temp.hall.SetRows(rows);
				cout << "Введите количество мест в ряду (<30):" << endl;
				seats = CinIntErrorCheck(1, 30);
				temp.hall.SetSeats(seats);
				break;
			case ESC:
				c = 0;
				break;
			}
		}
		set_films.erase(it);
		set_films.insert(temp);
		it = set_films.begin();
		file.open("cinema.txt");
		if (!file.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
			return;
		}
		else
		{
			while (it != set_films.end())
			{
				file << *it;
				it++;
			}
		}
		file.close();
	}
	else
	{
		cout << "Фильм не найден" << endl;
		_getch();
	}
}

void Film:: Copy(const Film& other)
{
	name = other.name;
	genre = other.genre;
	format = other.format;
	age_limit = other.age_limit;
	length = other.length;
	price = other.price;
	day = unique_ptr<Day[]>(new Day[other.count_days]);
	count_days = other.count_days;
	for (int i = 0; i < other.count_days; i++)
	{
		int count = other.day[i].GetCountTimes();
		day[i].SetCountTimes(count);
		day[i].SetData(other.day[i].GetData());
		day[i].SetTime(other.day[i].GetTime());
	}
	hall.SetRows(other.hall.GetRows());
	hall.SetSeats(other.hall.GetSeats());
}

void GenreSorte()
{
	int size = FilmFileLength("cinema.txt");
	vector<Film> vec_films;
	ifstream f;
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
	VectorSorte<Film>::Sort(vec_films, &Film::GetGenre);
	cout << "Просмотреть афишу?(1-Да, 2-Нет)" << endl;
	char ch;
	ch = _getch();
	if (ch == 49) {
		cout << endl;
		ViewFilms(vec_films);
		cout << endl;
	}
	cout << "Введите жанр" << endl;
	string g = CinStringSymRusErrorCheck();
	bool a = 0;
	vector<int>vec;
	for (int i = 0; i < vec_films.size(); i++)
	{
		if (g == vec_films[i].GetGenre())
		{
			a = 1;
			vec.push_back(i);
		}
	}
	if (a == 0)
		cout << "Фильмов этого жанра не найдено" << endl;
	else
	{
		cout << "Жанр: " << g << endl;
		ViewFilms(vec_films, vec);
	}
	f.close();
}

template <typename T>
void Find(vector<T> vec)
{
	string title;
	cout << "Введите название фильма" << endl;
	title= GetlineErrorCheck();
	title[0] = toupper(title[0]);
	bool a = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == title)
		{
			a = 1;
			cout << "Фильм найден" << endl;
			vec[i].ViewFilm();
			break;
		}
	}
	if(a==0)
		cout << "Фильм не найден" << endl;
}


void ChoiceFilm(string login)
{
	int size = FilmFileLength("cinema.txt");
	vector <Film> films;
	vector <string> film_titles;
	vector <double> dates;
	vector <double> time;
	vector<pair<int, int>> hall_seats;
	vector <Session> t;
	ifstream f;
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
			films.push_back(temp1);
			film_titles.push_back(temp1.name);
		}
	}
	f.close();
	ofstream file;
	string film_name = DrawMenuChoice("Выберите фильм", film_titles);
	double film_data, film_time;
	int n = 0, count_time, row, seat;
	for (int i = 0; i < size; i++)
	{
		if (films[i] == film_name)
		{
			n = films[i].count_days;
			for (int j = 0; j < n; j++)
			{
				dates.push_back(films[i].day[j].GetData());
			}


			film_data = DrawMenuChoice("Выберите дату", dates);
			for (int j = 0; j < n; j++)
			{
				if (films[i].day[j].GetData() == film_data)
				{
					count_time = films[i].day[j].GetCountTimes();
					double* mas = films[i].day[j].GetTime();
					for (int k = 0; k < count_time; k++)
					{
						time.push_back(mas[k]);
					}
					break;
				}
			}
			film_time = DrawMenuChoice("Выберите время", time);
			system("cls");
			bool first = 0;

			vector<pair<int, int>> ordered_seats;
			OrderedPlaces(ordered_seats, film_name, film_data, film_time);
			
			
			while (true) {
				DrawHall("Выбор мест в зале (ESC для выхода)", films[i].hall.GetRows(), films[i].hall.GetSeats(), row, seat, ordered_seats);
				
				if (row == 0 && seat == 0)
					if (first == 1)
						break;
					else {
						cout << endl << "Вы еще не выбрали ни одного места" << endl;
						_getch();
						continue;
					}
				if (row == -1 && seat == -1)
				{
					cout << "Выберите другой фильм" << endl;
					return;
				}
				hall_seats.push_back(make_pair(row, seat));
				first = 1;
				ordered_seats.push_back(make_pair(row, seat));
			}
			
			for (int k = 0; k < hall_seats.size(); k++)
			{
				Session ticket;
		
				ticket.SetLogin(login);
				ticket.SetDay(film_data);
				ticket.SetTime(film_time);
				ticket.SetRow(hall_seats[k].first);
				ticket.SetSeat(hall_seats[k].second);
				if (film_time > 21)
				{
					ticket.SetPrice(films[i].price * 1.2);
				}
				else
					ticket.SetPrice(films[i].price);
				ticket.name = films[i].name;
				ticket.age_limit = films[i].age_limit;
				ticket.genre = films[i].genre;
				ticket.format = films[i].format;
				ticket.length = films[i].length;
				t.push_back(ticket);
			}
			file.open("tickets.txt", ios::app);
			if (!file.is_open())
			{
				cout << "Ошибка открытия файла" << endl;
				return;
			}
			else
			{
				for (int k = 0; k < t.size(); k++)
					file << t[k];
			}
			file.close();
			cout <<endl<<endl<< "Посмотреть билеты можно в личном кабинете" << endl;
			_getch();
			return;
		}
	}

}

ostream& operator <<(ostream& os, const Session& session)
{
	const type_info& t = typeid(os);
	if (OF == t) //в файл
	{
		os << session.login << endl << session.name << endl
			<< session.genre << " " << session.length << " " << session.age_limit << " " << session.format << " " << session.final_price << endl
			<< session.session_day << " " << session.session_time <<" " << session.row << " " << session.seat << endl;
	}
	else
	{
		int n = session.name.size(), size = 0, maxSize = 0, offset = 0;
		if (n < 30) maxSize = 30;
		else maxSize = session.name.size()+2;
		cout << CROSS_SYMBOL;
		for (int i = 0; i < maxSize; i++)
			cout << HOR_SYMBOL;
		cout << CROSS_SYMBOL << endl;

		//строка 1: название
		cout << VERT_SYMBOL;
		offset = (maxSize - n) / 2;
		cout << fixed << setprecision(2);
		SetColor(LightMagenta, Black);
		cout << setw(offset + n) << session.name << setw(maxSize - n - offset + 1);
		SetColor(LightCyan, Black);
		cout <<  VERT_SYMBOL << endl;
		cout << VERT_SYMBOL << setw(maxSize + 1) << VERT_SYMBOL << endl;

		//строка 2: дата и время
		cout << VERT_SYMBOL;
		//SetColor(LightMagenta, Black);
		cout << session.session_day;
		int d1 = round((int)session.session_day);
		int d2 = round((session.session_day - d1) * 100);
		if (d2 == 12)
			cout << ".2023";
		else
			cout << ".2024";
		//SetColor(LightCyan, Black);
		int t1 = round((int)session.session_time);
		int t2 = round((session.session_time - t1) * 100);
		string time = to_string(t1) + ':' + to_string(t2);
		if (t2 == 0)
			time += '0';
		SetColor(LightMagenta, Black);
		cout << setw(maxSize - 10) << time;
		SetColor(LightCyan, Black);
		cout<< VERT_SYMBOL << endl;
		cout << VERT_SYMBOL << setw(maxSize + 1) << VERT_SYMBOL << endl;

		//строка 3: длина, формат, возраст
		string length_f;
		int time_h = (int)session.length;
		int time_m = (session.length - time_h) * 100;
		length_f = '0' + to_string(time_h) + ':' + to_string(time_m);
		if (time_m == 0)
			length_f += '0';
		string format = to_string(session.format) + 'D';
		string age = to_string(session.age_limit)+'+';
		int set = (maxSize - 7 - format.size() - age.size() - 1);
		if (set % 2 == 0) {
			set /= 2;
			cout << VERT_SYMBOL << "Длина " << length_f << setw(set + 1);
			cout << format << setw(set + 1) << age;
		}
		else
		{
			set /= 2;
			cout << VERT_SYMBOL << "Длина " << length_f << setw(set + 2);
			cout << format << setw(set + 1) << age;
		}
		cout << VERT_SYMBOL<<endl;
		cout << VERT_SYMBOL << setw(maxSize + 1) << VERT_SYMBOL << endl;

		//строка 4: ряд и место
		cout << VERT_SYMBOL << "Ряд ";
		int n_s=0, n_r=0,x1= session.row, x2= session.seat;
		while (x2 >= 1)
		{
			x2 /= 10;
			n_s++;
		}
		while (x1 >= 1)
		{
			x1 /= 10;
			n_r++;
		}
		SetColor(LightMagenta, Black);
		cout << session.row << setw(maxSize - 4 - n_s-n_r);
		SetColor(LightCyan, Black);
		cout << "Место ";
		SetColor(LightMagenta, Black);
		cout << session.seat;
		SetColor(LightCyan, Black);
		cout << VERT_SYMBOL<<endl;
		cout << VERT_SYMBOL << setw(maxSize + 1) << VERT_SYMBOL << endl;

		//строка 5: стоимость
		cout << VERT_SYMBOL;
		string pr;
		int pr1 = round((int)session.final_price);
		int pr2 = round((session.final_price - pr1) * 100);
		pr = to_string(pr1) + '.' + to_string(pr2);
		if (pr2 == 0)
			pr += '0';
		cout << "Стоимость ";
		//SetColor(LightMagenta, Black);
		cout << pr;
		//SetColor(LightCyan, Black);
		cout << " р." << setw(maxSize - pr.size() - 12);
		cout << VERT_SYMBOL<<endl;

		cout << CROSS_SYMBOL;
		for (int i = 0; i < maxSize; i++)
			cout << HOR_SYMBOL;
		cout << CROSS_SYMBOL;
	}
	return os;
}

istream& operator >>(istream& is, Session& session)
{
	const type_info& t = typeid(is);
	if (IF == t) //из файла
	{
		is >> session.login;
		char a = ' ';
		string title;
		is.get(a);
		if (a == '\n')
			rewind(stdin); 
		else
			title += a;
		while (is.get(a) && a != '\n') {
			title += a;
		}
		session.name = title;
		is >> session.genre >> session.length >> session.age_limit >> session.format >> session.final_price;
		is >> session.session_day >> session.session_time >> session.row >> session.seat;
	}
	return is;
}

void ViewTickets(string account)
{
	int size = FilmFileLength("tickets.txt");
	vector <Session> t;
	ifstream f;
	f.open("tickets.txt");
	if (!f.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}
	else
	{
		Session temp1;
		for (int i = 0; i < size; i++)
		{
			f >> temp1;
			t.push_back(temp1);

		}
	}
	f.close();
	VectorSorte<Session>::Sort(t, &Session::GetName);
	bool a = 0;
	cout << "Ваши билеты: " << endl;
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i] == account)
		{
			a = 1;
			cout << endl << t[i] << endl;
		}
	}
	if (a == 0)
		cout << "Нет доступных билетов" << endl;
	ofstream file;
	file.open("tickets.txt");
	if (!file.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}
	else
	{
		for (int i = 0; i < t.size(); i++)
		{
			file << t[i];
		}
	}
	file.close();
}

void Session::Copy(const Session& other)
{
	name = other.name;
	genre = other.genre;
	format = other.format;
	age_limit = other.age_limit;
	length = other.length;
	final_price = other.final_price;
	session_day = other.session_day;
	session_time = other.session_time;
	row = other.row;
	seat = other.seat;
	login = other.login;
	
}

void OrderedPlaces(vector<pair<int, int>>& ordered_seats, string name, double data, double time)
{
	int size = FilmFileLength("tickets.txt");
	vector <Session> t;
	ifstream f;
	f.open("tickets.txt");
	if (!f.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}
	else
	{
		Session temp1;
		for (int i = 0; i < size; i++)
		{
			f >> temp1;
			t.push_back(temp1);

		}
	}
	f.close();
	for (int i = 0; i < size; i++)
	{
		if (t[i].name == name)
		{
			if (t[i].session_day == data)
			{
				if (t[i].session_time == time)
				{
					ordered_seats.push_back(make_pair(t[i].row, t[i].seat));
				}
			}
		}
	}
}

bool OrderedFilms(string film)
{
	int size = FilmFileLength("tickets.txt");
	vector <Session> t;
	ifstream f;
	f.open("tickets.txt");
	if (!f.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
	}
	else
	{
		Session temp1;
		for (int i = 0; i < size; i++)
		{
			f >> temp1;
			t.push_back(temp1);

		}
	}
	f.close();
	for (int i = 0; i < size; i++)
	{
		if (t[i].name == film)
		{
			return true;
		}
	}
	return false;
}

bool UniqueFilm(string film)
{
	int size = FilmFileLength("cinema.txt");
	vector <Film> t;
	ifstream f;
	f.open("cinema.txt");
	if (!f.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
	}
	else
	{
		Film temp1;
		for (int i = 0; i < size; i++)
		{
			f >> temp1;
			t.push_back(temp1);

		}
	}
	f.close();
	for (int i = 0; i < size; i++)
	{
		if (t[i] == film)
		{
			return false;
		}
	}
	return true;
}