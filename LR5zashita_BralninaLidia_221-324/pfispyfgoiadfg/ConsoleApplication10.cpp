// ConsoleApplication10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <iomanip>
#include <ctime> 

using namespace std;
double Func(int mass[], int N)
{
	double srzn = 0;
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		mass[i] = -5 + rand() % 11;
		srzn += mass[i];
		cout << mass[i] << " ";
	}
	srzn /= N;
	return srzn;
}
int main()
{
	int N1, N2;
	cin >> N1 >> N2;
	int* mass1 = new int[N1];
	int* mass2 = new int[N2];
	cout << Func(mass1, N1)<<"\n";
	cout<<Func(mass2, N2);
	delete[] mass1, mass2;
}
