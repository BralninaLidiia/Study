// ЛР4 защита Бральнина 221-324.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>>
#include <ctime> 
using namespace std;
int main()
{
	int N, max_counter=0, counter=0, num=0;
	cin >> N;
	int* mass = new int[N];
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		mass[i] = -5 + rand() % 11;
		cout << mass[i]<<" ";
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (mass[i] == mass[j])
			{
				counter += 1;
			}
		}
		if (counter > max_counter)
		{
			max_counter = counter;
			num = mass[i];
		}
		counter = 0;
	}
	if (max_counter == 1)
	{
		cout << "Net povtoreniy";
	}
	else
	{
		cout << "\n" << num;
	}
	delete[] mass;
}


