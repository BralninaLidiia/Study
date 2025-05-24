#include "Crossing.h"

Crossing::Crossing(Edge* _e1, Edge* _e2, Point& _p) : e1(*_e1), e2(*_e2)
{
	p = _p;
}
