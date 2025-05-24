#include "ActivePoint.h"
ActivePoint::ActivePoint(Point& _p) :
	ActiveElement(ACTIVE_POINT), p(_p)
{

}

double ActivePoint::y(void)
{
	return p.y;
}

Dictionary<ActiveElement*>& buildSweepline()
{
	Dictionary<ActiveElement*>* sweepline = new Dictionary<ActiveElement*>(activeElementCmp);
	sweepline->insert(new ActivePoint(Point(0.0, -DBL_MAX)));
	return *sweepline;
}

int activeElementCmp(ActiveElement* a, ActiveElement* b)
{
	double ya = a->y();
	double yb = b->y();
	if (ya < yb) return -1;
	else if (ya > yb) return 1;
	if ((a->type == ACTIVE_POINT) && (b->type == ACTIVE_POINT))
		return 0;
	else if (a->type == ACTIVE_POINT) return -1;
	else if (b->type == ACTIVE_POINT) return 1;
	int rval = 1;
	if ((sweepdirection == LEFT_TO_RIGHT && curtype == START_TYPE) || (sweepdirection == RIGHT_TO_LEFT && curtype == END_TYPE))
		rval = -1;
	double ma = a->slope();
	double mb = b->slope();
	if (ma < mb) return rval;
	else if (ma > mb) return -rval;
	return 0;
}

void startTransition(Vertex* v, Dictionary<ActiveElement*>& sweepline)
{
	ActivePoint ve(v->point());
	ActiveEdge *a = (ActiveEdge*)sweepline.locate(&ve);
	Vertex* w = a->w;
	if (!isConvex(v)) {
		Vertex *wp = v->split(w);
		sweepline.insert(new ActiveEdge(wp->cw(), CLOCKWISE, wp->cw()));
		sweepline.insert(new ActiveEdge(v->ccw(), COUNTER_CLOCKWISE, v));
		a->w = (sweepdirection == LEFT_TO_RIGHT) ?wp->ccw() : v;
	}
	else {
		sweepline.insert(new ActiveEdge(v->ccw(), COUNTER_CLOCKWISE, v));
		sweepline.insert(new ActiveEdge(v, CLOCKWISE, v));
		a->w = v;
	}	
		
}
 
bool isConvex(Vertex* v)
{
	Vertex *u = v->ccw();
	Vertex *w = v->cw();
	int c = w->classify(*u, *v);
	return ((c == BEYOND) || (c == RIGHT));
}
	
void bendTransition(Vertex* v, Dictionary<ActiveElement*>& sweepline)
{
	ActivePoint ve(v->point());
	ActiveEdge *a = (ActiveEdge*) sweepline.locate(&ve);
	ActiveEdge *b = ((ActiveEdge*) sweepline.next();
	a->w = v;
	b->w = v;
	b->v = b->v->neighbor(b->rotation);
}

void endTransition(Vertex* v, Dictionary<ActiveElement*>& sweepline, List<Polygon*>* polys)
{
	ActivePoint ve(v->point());
	ActiveElement *a = sweepline.locate(&ve);
	ActiveEdge *b = (ActiveEdge*) sweepline.next();
	ActiveEdge *c = (ActiveEdge*) sweepline.next();
	if (is Convex(v))
		polys->append(new Polygon(v));
	else
		((ActiveEdge*)a)->w = v;
	sweepline.remove(b);
	sweepline.remove(c);
}
