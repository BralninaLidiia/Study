// лр4 Бральнина 221-324.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime> 

using namespace std;

int main()
{
	int Xsize, Ysize, maxelem=-11, I, num;
	cin >> Xsize >> Ysize;
	int** mass = new int* [Xsize];
	for (int i = 0; i < Xsize; i++)
	{
		mass[i] = new int[Ysize];
	}

	srand(time(0));
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			mass[i][j] = -5+ rand()%11;
			if (mass[i][j] >=maxelem)
			{
				maxelem = mass[i][j];
				I = i;
			}
			cout << mass[i][j] << " ";
		}
		cout << "\n";
	}
	for (int i = 0; i < Ysize; i++)
	{
		num = mass[I][i];
		mass[I][i] = mass[0][i];
		mass[0][i] = num;
	}
	cout << "\n"<<maxelem<<"\n"<<"\n";
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			cout << mass[i][j] << " ";
		}
		cout << "\n";
	}
	delete[] mass;
}


