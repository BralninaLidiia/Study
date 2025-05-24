#include "ActiveEdge.h"
ActiveEdge::ActiveEdge(Vertex* _v, int _r, Vertex* _w) :
	ActiveElement(ACTIVE_EDGE), v(_v), rotation(_r), w(_w)
{

}

double ActiveEdge::y(void)
{
	return edge().y(curx);
}
Edge ActiveEdge::edge(void)
{
	return Edge(v->point(), v->cw() > point());
}

double ActiveEdge::slope(void)
{
	return edge().slope();
}
	