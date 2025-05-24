#pragma once
class Rectangle {
public:
	Point sw;
	Point ne;
	int id;
	// // юго-западный (нижний левый) угол
	// северо-восточный (верхний правый) угол
	// идентификатор
	Rectangle(Point& _5w, Point& _ne, int _id = -1);
	Rectangle(void) {};
};