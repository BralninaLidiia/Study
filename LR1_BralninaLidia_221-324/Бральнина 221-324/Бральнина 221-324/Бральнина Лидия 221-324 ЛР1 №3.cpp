#include <iostream>
#include<locale>
#include <iomanip>
using namespace std;




int main()
{
	setlocale(LC_ALL, "RUS");
	int a, b, c, d;
	cout << "Первая строка матрицы:";
	cin >> a >> b;
	cout << "Вторая строка матрицы:";
	cin >> c >> d;
	float volume = a * d - b * c;
	cout << std::fixed;
	cout << std::setprecision(3);
	cout << volume << " - определитель матрицы с элементами " << a <<" "<< b << " в первой строке и " << c <<" "<< d << " во второй строке\n";
	system("pause");
	return 0;


 }