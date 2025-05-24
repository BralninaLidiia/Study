#include "LeftEndpoint.h"

LeftEndpoint::LeftEndpoint(Edge* _e) : e(*_e)
{
	p = (e.org < e.dest) ? e.org : e.dest;
}
