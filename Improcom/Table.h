#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include "Output.h"

#define CROSS_SYMBOL '+'
#define VERT_SYMBOL '|'
#define HOR_SYMBOL '-'

using namespace std;
namespace table
{
	class BaseTable
	{
	public:
		virtual void OutputTable(vector<pair<string, int>> collumNames, vector<string> data) = 0;

	protected:
		virtual void OutputLine(vector<pair<string, int> > collumNames) = 0;
		virtual void OutputNames(vector<pair<string, int> > collumNames) = 0;
		virtual void OutputData(vector<string> data, vector<pair<string, int> > collumNames) = 0;
	};

	class Table :public BaseTable
	{
	public:
		void OutputTable(vector<pair<string, int>> collumNames, vector<string> data) override;

	protected:
		void OutputLine(vector<pair<string, int> > collumNames) override;
		void OutputNames(vector<pair<string, int> > collumNames) override;
		void OutputData(vector<string> data, vector<pair<string, int> > collumNames) override;
	};

	class ColoredTable :public Table
	{
	protected:
		void OutputNames(vector<pair<string, int> > collumNames) override;
	};
}
