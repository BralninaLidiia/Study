// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale> 
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	printf("% 3.0s * %4.0s * %3.0s * %1.0s %3.0s * %8.0s *\n");
	printf("%1.0s * % 1.0s * %2.0s * %2.0s*%1.0s* %3.0s * %1.0s * %5.0s *%1.0s*\n");
	printf(" * % 3.0s * %1.0s *%1.0s* %1.0s * %1.0s *%1.0s*%1.0s*%1.0s*%1.0s* %2.0s *%1.0s*%1.0s*\n");
	printf("*% 6.0s * %0.0s * %3.0s * %1.0s * %5.0s * %1.0s * %3.0s *\n");
	
   
}

