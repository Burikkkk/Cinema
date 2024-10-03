#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <iomanip>  
#include "Table.h"
#include "Output.h"
using namespace std;
using namespace table;

void Encrypt(string& pass); // Зашифровка
void Decrypt(string& pass); // Расшифровка

int LengthFile(string name); // Получение размера файла для "user.txt" 

class User
{
protected:
	string login, password, name, surname;
	int status; // Пользователь-0; администратор-1
public:
	void Password(); // Ввод пароля для входа

	void SetLogin(string login) { this->login = login; }
	void SetPassword(string password) { this->password = password; }
	void SetStatus(int status) { this->status = status; }
	void SetName(string name) { this->name = name; }
	void SetSurname(string surname) { this->surname = surname; }
	string GetLogin() { return login; }
	string GetPassword() { return password; }
	int GetStatus() { return status; }
	string GetName() { return name; }
	string GetSurname() { return surname; }
	void Copy(const User& other);

	friend ostream& operator <<(ostream& os, const User& user);
	friend istream& operator >>(istream& is, User& user);
	friend bool operator<(User a, User b);
	friend bool operator==(User a, string b);
};

void ViewUsers();
void ViewUser(User account);
void ChangeStatus();
void ChangeUser(User& account);
void SorteUsers(vector<User> &vec_users);

