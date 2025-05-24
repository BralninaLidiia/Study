#include "RightEndPoint.h"

RightEndPoint::RightEndPoint(Edge* _e) : e(* _e)
{
	p = (e.org < e.dest) ? e.dest : e.org;
}
