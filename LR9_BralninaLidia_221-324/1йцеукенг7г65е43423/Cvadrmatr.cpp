#include "Cvadrmatr.h"
#include <ctime> 
#include <stdlib.h>
#include <iostream>
#include<string>
using namespace std;
Cvadrmatr::Cvadrmatr()
{

}
Cvadrmatr::Cvadrmatr(int n)
{
	x = n;
	srand(time(0));
	mass = new int* [x];
	for (int i = 0; i < x; i++)
	{
		mass[i] = new int[x];
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			mass[i][j] = -5 + rand() % 10;
		}

	}
}
Cvadrmatr::~Cvadrmatr()
{

}

void Cvadrmatr::opred()
{
	setlocale(LC_ALL, "RUS");
	if (x == 2) 
	{
		result = mass[0][0] * mass[1][1] - mass[0][1] * mass[1][0];
	    cout<< result;
	}
	else
	{
		cout << "Невозможно вычислить определитель";
	}
	
}

void Cvadrmatr::printmass()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			cout << mass[i][j] << " ";
		}
		cout << "\n";
	}
}

Cvadrmatr Cvadrmatr::operator+(Cvadrmatr matr)
{
	if (x == matr.x)
	{
		matr.printmass();
		Cvadrmatr newmatr(x);
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < x; j++)
			{
				newmatr.mass[i][j]= mass[i][j]+ matr.mass[i][j];
			}
			cout << "\n";
		}
		return newmatr;

	}
	else
	{
		cout << "Невозможно сложить";
		return 0;
	}
}

Cvadrmatr Cvadrmatr::operator*(Cvadrmatr matr)
{
	if (x == matr.x)
	{
		Cvadrmatr newmatr(x);
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < x; j++)
			{
				newmatr.mass[i][j] = 0;
				for (int m = 0; m < x; m++)
				{
					newmatr.mass[i][j] += mass[i][m] * matr.mass[m][j];
				}
			}
		}
		return newmatr;

	}
	else
	{
		cout << "Невозможно умножить";
		return 0;
	}
}
Cvadrmatr Cvadrmatr::transponirovanie()
{
	Cvadrmatr newmatr(x);
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			newmatr.mass[i][j] = mass[j][i];

		}
		cout << "\n";
	}
	return newmatr;
}





