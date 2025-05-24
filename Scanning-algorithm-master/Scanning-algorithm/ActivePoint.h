#pragma once
class ActivePoint : public ActiveElement{
public:
	Point p;
	ActivePoint(Point&);
	double y(void);
};

