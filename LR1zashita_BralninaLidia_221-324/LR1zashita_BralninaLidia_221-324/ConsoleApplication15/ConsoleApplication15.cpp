// ConsoleApplication15.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>

using namespace std;

int main()
{
	printf_s("%5.0s * %7.0s * %6.0s *%10.0s * %13.0s *\n");
	printf_s("%2.0s * %3.0s * %4.0s * %4.0s *%0.0s *%8.0s *%2.0s * %9.0s * %1.0s *\n");
	printf_s(" * %7.0s * %2.0s * %2.0s * %1.0s *%6.0s *%6.0s * %5.0s *%1.0s*%1.0s*%1.0s*%1.0s* \n");
	printf_s(" * %7.0s * %2.0s * %0.0s * %3.0s * %2.0s *%1.0s*%1.0s*%1.0s*%1.0s*%1.0s*%1.0s*%1.0s* %2.0s * %5.0s *\n");
	printf_s(" * %7.0s * %2.0s * %6.0s * %2.0s * %11.0s * %2.0s * %5.0s *\n");
	system("pause");
}