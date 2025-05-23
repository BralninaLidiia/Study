// zashita6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <locale>
#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(0));
	cout<< "Введите количество чисел: ";
	int count;
	cin>> count;
	double* array = new double[count];
	FILE* fl;
	if (fopen_s(&fl, "D:\\data.dat", "wb"))
	{
		printf("Невозможно открыть файл.\n");
		exit(1);
	}
	for (int i = 0; i < count; i++)
	{
		array[i] = rand() % 100;
		fwrite(&array[i], sizeof(double), 1, fl);
		cout << array[i]  << " ";
	}
	cout<< "\n";
	fclose(fl);
	FILE* fl2;
	if (fopen_s(&fl2, "D:\\data.dat", "r+b"))
	{
		printf("Невозможно открыть файл.\n");
		exit(1);
	}
	double Min;
	double Max;
	fread(&Min, sizeof(double), 1, fl);
	Max = Min;
	int size_max = 0;
	int size_min = 0;
	for (int i = 1; i < count; i++)
	{
		double a;
		fread(&a, sizeof(double), 1, fl2);
		if (a > Max)
		{
			Max = a;
			size_max = i;
		}
		if (a < Min)
		{
			Min = a;
			size_min = i;
		}
	}
	fseek(fl2, (size_min) * sizeof(double), SEEK_SET);
	fwrite(&Max, sizeof(double), 1, fl2);
	fseek(fl2, (size_max) * sizeof(double), SEEK_SET);
	fwrite(&Min, sizeof(double), 1, fl2);
	rewind(fl2);
	for (int i = 0; i < count; i++)
	{
		double b;
		fread(&b, sizeof(double), 1, fl2);
		cout<< b << " ";
	}
	cout << "\n";
	fclose(fl2);
	system("pause");
	return 0;
}