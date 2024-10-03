#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <iomanip>  
#include <memory>  
#include <ctime>
#include <set>
#include <cmath>
#include "Output.h"
#include "Table.h"

using namespace std;
//using namespace table;

void Calendar(int month);


class Day {
protected:
	double data;
	int count_times;
	shared_ptr<double> time;
public:
	Day() { data = 0; count_times = 0; time = nullptr; }
	Day(double data, int count_times, double *mas) { 
		this->data = data; 
		this->count_times = count_times; 
		time=shared_ptr<double>(new double[count_times], default_delete<double[]>());
		for (int i = 0; i < count_times; i++)
			time.get()[i] = mas[i];
	}
	void SetData(double data) { this->data = data; }
	void SetCountTimes(int count_times) { this->count_times = count_times; }
	void SetTime(double *mas)
	{
		time=shared_ptr<double>(new double[count_times], default_delete<double[]>());
		for(int i=0; i<count_times; i++)
			time.get()[i] = mas[i];
	}
	double GetData() { return data; }
	int GetCountTimes() {return count_times; }
	double* GetTime() { return time.get(); }
};

class Hall {
protected:
	int number_of_rows, number_of_seats;
public:
	void SetRows(int r) { number_of_rows = r; }
	void SetSeats(int s) { number_of_seats= s; }
	int GetRows() const{ return number_of_rows; }
	int GetSeats() const{ return number_of_seats; }
};


class Film {
protected:
	string name;
	int age_limit;
	string genre;
	int format; 
	double length, price;

	unique_ptr<Day[]> day;
	int count_days;

	Hall hall;
public:
	Film() { name = genre; format=age_limit = length = price = 0; day = nullptr; };
	Film(const Film& other)
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
	void SetName(string name) { this->name = name; }
	double GetPrice() { return price; }
	string GetGenre() { return genre; }
	string GetName() { return name; }
	friend ostream& operator <<(ostream& os, const Film& film);
	friend istream& operator >>(istream& is, Film& film);
	friend bool operator<(Film a, Film b){ return a.name < b.name; }
	friend bool operator==(Film a, string b){ return a.name == b; }
	friend bool operator==(Film a, Film b){ return a.name == b.name; }
	void AddFilmData();
	void AddFilm();
	void ViewFilmData() const;
	void ViewFilm() const;
	void Copy(const Film& other);
	friend void ViewFilms();
	friend void ViewFilms(vector<Film> vec_films);
	friend void ViewFilms(vector<Film> vec_films, vector<int> vec);
	friend void ChangeFilm();
	friend void ChoiceFilm(string login);
	friend bool UniqueFilm(string film);
};
void ViewFilms();
void EditFilms();
void ChangeFilm();
int FilmFileLength(string name);
bool UniqueFilm(string film);

class Session : public Film
{
private:
	double session_day, session_time, final_price;
	int row, seat;
	string login;
public:
	void SetDay(double d) { session_day = d; }
	void SetTime(double t) { session_time = t; }
	void SetPrice(double p) { final_price = p; }
	void SetRow(int r) { row = r; }
	void SetSeat(int s) { seat = s; }
	void SetLogin(string l) { login = l; }
	void Copy(const Session& other);

	friend ostream& operator <<(ostream& os, const Session& session);
	friend istream& operator >>(istream& is, Session& session);
	friend bool operator<(Session a, Session b) { return a.session_day < b.session_day; }
	friend bool operator==(Session a, Session b) { return a.session_day == b.session_day; }
	friend bool operator==(Session a, string b) { return a.login == b; }
	friend void OrderedPlaces(vector<pair<int, int>>& ordered_seats, string name, double date, double time);
	friend bool OrderedFilms(string film);
};

void ChoiceFilm(string login);
void GenreSorte();

template <typename T>
void Find(vector<T> vec);

template void Find<Film>(vector<Film> vec);

void ViewTickets(string account);

void OrderedPlaces(vector<pair<int, int>>& ordered_seats, string name, double data, double time);
bool OrderedFilms(string film);