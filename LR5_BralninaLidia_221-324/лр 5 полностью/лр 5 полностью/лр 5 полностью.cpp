// лр 5 полностью.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iostream>
#include<locale>
#include <iomanip>

using namespace std;

//float opred(float a, float b, float c, float d);
void Zone(double X, double Y, int& Z);
//double Func(double x);

////5.1
//float opred(float a, float b, float c, float d)
//{
//	float opredelitel = a * d - b * c;
//	return opredelitel;
//}
//
//int main()
//{
//	float A, B, C, D;
//	setlocale(LC_ALL, "RUS");
//	cin >> A >> B >> C >> D;
//	cout << "Первая строка матрицы:" << " " << A << " " << B << "\n" << "Вторая строка матрицы:" << " " << C << " " << D << "\n" << setprecision(3) << opred(A, B, C, D) << " " << " - определитель матрицы с элементами" << " " << A << " " << B << "\n" << "в первой строке и " << C << " " << D << " " << "во второй строке";
//
//}//end 5.1
////5.2

void Zone(double X, double Y, int& Z)
{
	if ((Y) > 0)
	{
		if ((X) >= 0) // первая четверть
		{
			if ((Y) >= 1 && (X) != 0)//y=1 не вкл (0;1)
			{
				Z = 4;
			}
			else if ((Y) > 1 && (X) == 0)//от (0;1) не вкл до +беск ось y
			{
				Z = 5;
			}
			else if ((Y) < (-1) * (X) + 1)//у=-х+1 не вкл (0;1)
			{
				Z = 15;
			}

			else if (((pow((-1) * ((X) - 1), (1.0 / 3.0)) >= (Y)) || ((Y) = (-1) * (X) + 1) || ((X) == 0 || (Y) == 1)) && (X) <= 1) //-nan(ind)! загагулистая дрянь+(0;1)+гипотенуза 15
			{
				Z = 18;
			}
			else
			{
				Z = 3;
			}



		}
		else // вторая четверть
		{
			if (Y > ((-1) * X + 1))// не вкл у==-х+1, над у==-х+1 
			{
				Z = 5;

			}
			else if (Y == ((-1) * (X) + 1) || (pow((-1) * ((X) - 1), (1.0 / 3.0)) < Y))//у==-х+1 вкл загаг не вкл то что ниже
			{
				Z = 6;

			}
			else if ((pow((-1) * ((X) - 1), (1.0 / 3.0)) >= Y) && Y > 1)//у!=1, под загагулистой дрянью не вкл то что ниже
			{
				Z = 7;
			}
			else if (Y <= 1)
			{
				Z = 8;//у=1
			}

		}
	}
	else
	{
		if ((Y) == (X) && (X) == 0)// точка 0;0
		{
			Z = 16;
		}
		else if ((X) <= 0) // третья четверть
		{
			if (Y < (-1) * pow(X, 2) && pow((pow(X, 2) + pow(Y, 2)), 0.5) <= 2 && (-1) * pow(X, 2) != pow((pow(X, 2) + pow(Y, 2)), 0.5))//под параболой не вкл ее саму т пересеч окр и пар вкл ох до-2 и кусок ок-ти 
			{
				Z = 13;
			}
			else if (Y <= (-1) * pow(X, 2) && pow((pow(X, 2) + pow(Y, 2)), 0.5) > 2 && (-1) * pow(X, 2) != pow((pow(X, 2) + pow(Y, 2)), 0.5) && X != 0)//вкл под параболой и ее саму не вкл т пересеч окр и пар ох и кусок ок-ти
			{
				Z = 10;
			}
			else if ((-1) * pow(X, 2) == pow((pow(X, 2) + pow(Y, 2)), 0.5) || (Y >= (-1) * pow(X, 2) && pow((pow(X, 2) + pow(Y, 2)), 0.5) <= 2))//вкл т пересеч окр и пар 
			{
				Z = 14;
			}
			else if ((X) != 0)
			{
				Z = 9;
			}
			else
			{
				Z = 11;
			}
		}
		else //четвертая четверть

		{
			if (Y < (-1) * pow(X, 2) && pow((pow(X, 2) + pow(Y, 2)), 0.5) <= 2 && X != 0)
			{
				Z = 12;
			}
			else if (Y <= (-1) * pow(X, 2) && pow((pow(X, 2) + pow(Y, 2)), 0.5) > 2)
			{
				Z = 11;
			}
			else if (X == 1 && Y == 0)
			{
				Z = 18;
			}
			else if (Y < (-1) * X + 1 && pow((pow(X, 2) + pow(Y, 2)), 0.5) <= 2)
			{
				Z = 16;
			}
			else if (Y < (-1) * X + 1)
			{
				Z = 1;
			}
			else if (Y >= (-1) * X + 1 && pow((pow(X, 2) + pow(Y, 2)), 0.5) <= 2)
			{
				Z = 17;
			}
			else
			{
				if (Y == 0)
				{
					Z = 3;
				}
				else
				{
					Z = 2;
				}
			}
		}
	}

}
int main()
{
	setlocale(LC_ALL, "RUS");
	double x, y;
	int z = 0;
	cout << "Ведите координаты точки через пробел:";
	cin >> x >> y;
	Zone(x, y, z);
	cout << "Зона № " << z << "\n";
}
////end 5.2
////5.3
//int main()
//{
//	double X;
//	cin >> X;
//	cout << Func(X);
//}
//double Func(double x)
//{
//	double result = 0;
//	int n = 1, num = 1;
//	while (abs(pow(x, n) / num) >= 0.0001)
//
//	{
//		if (n % 2 == 0)
//		{
//			result -= pow(x, n) / num;
//		}
//		else
//		{
//			result += pow(x, n) / num;
//		}
//		n += 1;
//		num *= n;
//	}
//	return result;
//}
////end 5.3