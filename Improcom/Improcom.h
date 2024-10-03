#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "User.h"
#include "Cinema.h"
using namespace std;


void UserLoginMenu();
void LoginMenu(int status, short x, short y);
void AdminLoginMenu();
void UserMenu(User account);
void AdminMenu(User account);
void PersonalAccount(User& account);
void PersonalAccountAdmin(User& account);

