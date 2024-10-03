#include "Table.h"

namespace table
{
	void Table::OutputLine(vector<pair<string, int>> collumNames)
	{
		int n = collumNames.size();
		cout << CROSS_SYMBOL;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < collumNames[i].second; j++)
			{
				cout << HOR_SYMBOL;
			}
			cout << CROSS_SYMBOL;
		}
		cout << endl;
	}

	void Table::OutputNames(vector<pair<string, int>> collumNames)
	{
		cout << VERT_SYMBOL;
		int n = collumNames.size(), size = 0, maxSize = 0, offset = 0;
		for (int i = 0; i < n; i++)
		{
			size = collumNames[i].first.length();
			maxSize = collumNames[i].second;
			offset = (maxSize - size) / 2;
			cout << setw(offset + size) << collumNames[i].first << setw(maxSize - size - offset + 1) << VERT_SYMBOL;
		}
		cout << endl;
	}

	void Table::OutputData(vector<string> data, vector<pair<string, int>> collumNames)
	{
		int dataSize = data.size(), collumsSize = collumNames.size(), currentCollum = 0,
			size = 0, maxSize = 0, offset = 0;
		OutputLine(collumNames);
		for (int i = 0; i < dataSize; i++)
		{
			currentCollum = i % collumsSize;
			size = data[i].size();
			maxSize = collumNames[currentCollum].second;
			offset = maxSize - size;
			cout << VERT_SYMBOL << data[i] << setw(offset + 1);
			if (currentCollum == collumsSize - 1)
			{
				cout << VERT_SYMBOL;
				cout << endl;
				OutputLine(collumNames);
			}
		}
		cout << endl;
	}

	void Table::OutputTable(vector<pair<string, int>> collumNames, vector<string> data)
	{
		int totalW = 0, collums = collumNames.size(), rows = data.size() / collums;
		for (int i = 0; i < collums; i++)
		{
			totalW += collumNames[i].second;
		}
		totalW += collums + 1;
		OutputLine(collumNames);
		OutputNames(collumNames);
		OutputData(data, collumNames);
	}


	void ColoredTable::OutputNames(vector<pair<string, int>> collumNames)
	{
		cout << VERT_SYMBOL;
		int n = collumNames.size(), size = 0, maxSize = 0, offset = 0;
		for (int i = 0; i < n; i++)
		{
			size = collumNames[i].first.length();
			maxSize = collumNames[i].second;
			offset = (maxSize - size) / 2;
			cout << fixed << setprecision(2);
			SetColor(LightMagenta, Black);
			cout << setw(offset + size) << collumNames[i].first << setw(maxSize - size - offset + 1);
			SetColor(LightCyan, Black);
			cout << VERT_SYMBOL;
		}
		cout << endl;
	}
}