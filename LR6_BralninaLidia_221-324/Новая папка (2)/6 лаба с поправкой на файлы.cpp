// ConsoleApplication10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>
#include <fstream>
#include <ctime> 
#include <string>
#include <algorithm>
using namespace std;
void result(int mass[10][10])
{
	if (mass[9][0] > 0)
	{
		sort(mass[9], mass[9] + 10, greater<int>());
	}
	else
	{
		sort(mass[9], mass[9] + 10);
	}
}
int main()
{
	setlocale(LC_ALL, "RUS");
	int mass1[10][10], mass2[10][10];
	srand(time(NULL));
	//С++:
	//C++ текстовый файл:
	ofstream data;
	data.open("D:\\Основы программирования\\data.dat");
	for (int i = 0; i < 10; i++)
	{
		for (int counter = 0; counter < 2; counter++)
		{
			for (int j = 0; j < 10; j++)
			{
				mass1[i][j] = -5 + rand() % 10;
				if (counter == 0)
				{
					data << "A" << i + 1 << j + 1 << " ";
				}
				else
				{
					data << mass1[i][j] << "*";
				}
			}
			data << endl;
		}
	}
	data.close();
	ifstream data2;
	data2.open("D:\\Основы программирования\\data.dat");
	cout << "Считывание текстового файла" << endl;
	int counter1 = 0;
	for (int i = 0; i < 20; i++)
	{
		string line;
		getline(data2, line);
		int counter2 = 0;
		for (int j = 1; j < line.length(); j++)
		{
			if (line[j] == '*')
			{
				string a;
				if (j != 1 && line[j - 2] != '*')
				{
					a = line[j - 2];
					a += line[j - 1];
				}
				else
				{
					a = line[j - 1];
				}
				int b = stoi(a);
				mass2[counter1][counter2] = b;
				cout << mass2[counter1][counter2] << " ";
				counter2 += 1;
			}
		}
		if (i % 2 != 0)
		{
			counter1 += 1;
		}
		cout << endl;
	}

	cout << endl << "Результирующий массив" << endl;
	result(mass2);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << mass2[i][j] << " ";
		}
		cout << endl;
	}
	data.close();
	ofstream data_binary;
	data_binary.open("D:\\Основы программирования\\result.res", ios_base::binary);
	for (int i = 0; i < 10; i++)
	{
		string str = "*";
		for (int j = 0; j < 10; j++)
			if (j == 0)
			{
				str += to_string(mass2[i][j]) + "(a" + to_string(i + 1) + to_string(j + 1) + ")";
			}
			else
			{
				str += "!" + to_string(mass2[i][j]) + "(a" + to_string(i + 1) + to_string(j + 1) + ")";
			}
		str += "\n";
		for (int i = 0; i < str.length(); i++)
		{
			char ch;
			ch = str[i];
			data_binary.write((char*)&ch, sizeof(char));
		}
	}
	data_binary.close();

}