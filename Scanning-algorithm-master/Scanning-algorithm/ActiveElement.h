#pragma once
class ActiveElement
{
public:
	int type; // ACTIVE_EDGE (ребро) или ACTIVE_POINT (точка)
	ActiveElement(int type);
	virtual double y(void) = 0;
	virtual Edge edge(void) {return Edge(); };
	virtual double slope(void) { return 0.0; };
};

