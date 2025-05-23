// zashita3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>
#include <iomanip>
#include <windows.h>

using namespace std;

int main()
{
	int i = 1, n = 2, y1 = 0, y2 = y1 + 11, x1 = 7, x2 = 0/*, x=0, y=20*/;
	for (i; i <= 9; i++, y1++, y2++)
	{
		for (n; n <= 5; n++, x2 += 7, x1 += 7)
		{
			cout << i << "*" << n << "=" << setw(2) << i * n << " ";
			void gotoxy(short x2, short y2);
			{
				COORD Coor;
				Coor.X = x2; Coor.Y = y2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coor);
			}
			cout << i << "*" << n + 4 << "=" << setw(2) << i * (n + 4) << " ";
			void gotoxy(short x1, short y1);
			{
				COORD Coor;
				Coor.X = x1; Coor.Y = y1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coor);
			}
		}
		x2 = 0;
		x1 = 7;
		n = 2;
		cout << "\n";
	}
	//void gotoxy(short x, short y);
	//{
	//	COORD Coor;
	//	Coor.X = x; Coor.Y = y;
	//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coor);
	//}
	system("pause");
	return 0;

}
