// zashita2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream> 
#include <math.h> 

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int x, y, z;
	cout << "Введите значения (x, y, z): ";
	cin >> x >> y >> z;



	if ((x > (z - 0.5)) && (x < (z + 0.5)) && (y > (z - 0.5)) && (y < (z + 0.5)))
	{
		cout << "Зона 3";
	}

	else
	{
		if (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) <= 2)
		{
			cout << "Зона 2";
		}

		else
		{
			cout << "Зона 1";
		}

	}
	return 0;
}
