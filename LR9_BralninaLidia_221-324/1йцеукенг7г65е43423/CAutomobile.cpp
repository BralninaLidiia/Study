
#include "CAutomobile.h";//включение заголовочного файла класса автомобиль
#include <iostream>

using namespace std; //подключение стандартного пространства имен
CAutomobile::CAutomobile(double shirota2, double dolgota2, double cena)
{
	rasstoyanie = rasst(shirota2, dolgota2);
	stoim = rashod_topliva * cena / 100 * rasstoyanie;
	time2 = rasstoyanie / max_scorost;
}
//конструкторы класса јвтомобиль
CAutomobile::CAutomobile()
{
}


//деструктор класса јвтомобиль
CAutomobile::~CAutomobile()
{
}

string CAutomobile::doedet_li()
{
	if (ostatok_topliva / rashod_topliva * 100 >= rasstoyanie)
	{
		return "ƒоедет";
	}
	else
	{
		return "Ќе доедет";
	}
}

string CAutomobile::stoimost_poezdki()
{
	return "—тоимость поездки до точки составит " + to_string(stoim)+ " рублей";
}

string CAutomobile::vremya_poezdky()
{
	return "¬рем€ поездки до точки составит " +to_string(time2)+" часов";
}

string CAutomobile::print()
{
	return "цвет " + colour + "\n" + "марка " + mark + "\n" + "тип привода " + tip_privoda + "\n" + "пробег " + to_string(probeg)+" километров" + "\n" + "стоимость нового " + to_string(stoimost_novogo) + " рублей"+"\n" + "стоимость на данный момент " + to_string(stoimost_now)+" рублей" + "\n" + "GPS координаты расположени€ в данный момент : " + "\n" + "широта " + to_string(shirota) + "\n" + "долгота " + to_string(dolgota) + "\n" + "максимальна€ скорость " + to_string(max_scorost) +" км/ч" + "\n" + "тип двигател€ " + tip_dvigatelya + "\n" + "расход топлива " + to_string(rashod_topliva) +"л/100км" + "\n" + "остаток топлива в баке " + to_string(ostatok_topliva) + " литров" + "\n" + "меж сервисный интервал " + megservisniy_interval;
}


double CAutomobile::rasst(double shirota1, double dolgota1)
{
	double shirrad, shirrad1, dolgrad, dolgrad1;
	shirrad = shirota * pi / 180;
	dolgrad = dolgota * pi / 180;
	shirrad1 = shirota1 * pi / 180;
	dolgrad1 = dolgota1 * pi / 180;

	return acos(sin(shirrad) * sin(shirrad1) + cos(shirrad) * cos(shirrad1) * cos(abs(dolgrad - dolgrad1))) * radiuszemli;
}

string CAutomobile::distance()
{
	return "рассто€ние до точки "+to_string(rasstoyanie)+ " км";
}

string CAutomobile::poterya_v_cene()
{
	int result;
	result = stoimost_novogo - stoimost_now;
	return "потер€ в цене составит "+to_string(result)+" рублей";
}
