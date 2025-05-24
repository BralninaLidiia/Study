#include "AxisParalleEdge.h"
AxisParallelEdge::AxisParallelEdge(Rectangle* _r, int _type) :
	r(_r), count(0), m(-DBL_MAX), type(_type)


double AxisParallelEdge::pos(void)
{
	switch (type)
	{
		case LEFT_SIDE:
			return r->sw.x; break;
		case RIGHT_SIDE:
			return r->ne.x; break;
		case TOP_SIDE:
			return r->ne.y; break;
		case BOTTOM_SIDE:
		default:
			return r->sw.y; break;
	}
}

double AxisParallelEdge::min(void)
{
	if (m > -DBL_MAX)
		return m;
	switch (type) {
		case LEFT_SIDE :
		case RIGHT_SIDE :
			return r->sw.y; break;
		case TOP_SIDE :
		case BOTTOM_SIDE :
		default:
			return r->sw.x; break;
	}
}
double AxisParallelEdge::max(void)
{
	switch (type) {
	case LEFT_SIDE:
	case RIGHT_SIDE:
		return r->ne.y; break;
	case TOP_SIDE:
	case BOTTOM_SIDE:
	default:
		return r->ne.x; break;
	}
}

void AxisParallelEdge::setMin(double f)
{
	m = f;
}

List<Edge*>* findContour(Rectangle r[], int n)
{
	AxisParallelEdge** schedule = buildSchedule(r, n);
	List<Edge*>* segments = new List<Edge*>;
	Dictionary<AxisParallelEdge*> sweepline(axisParallelEdgeCmp);
	Rectangle* sentinel = new Rectangle(Point(-DBL_MAX, -DBL_MAX),
		Point(DBL_MAX, DBL_MAX), -1);
	sweepline.insert(new AxisParallelEdge(sentinel, BOTTOM_SIDE));

	for (int i = 0; i < 2*n; i++)
		switch (schedule[i]->type) {
			case LEFT_SIDE:
				schedule[i]->handleLeftEdgeTransition(sweepline, segments);
				break;
			case RIGHT_SIDE:
				schedule(i]->handleRightEdgeTransition(sweepline, segments);
				break;
		}
	return segments;
}

AxisParallelEdge** buildSchedule(Rectangle r(], int n)
{
	AxisParallelEdge **schedule = new AxisParallelEdgePtr[2*n);
	for (int i = 0; i < n; i++) {
		schedule[2*i] = new AxisParallelEdge(&r[i], LEFT_SIDE);
		schedule[2*i+1] = new AxisParallelEdge(&r[i], RIGHT_SIDE);
	}
	insertionSort(schedule, 2*n, axisParallelEdgeCmp);
	return schedule;
}
	
int axisParallelEdgeCmp(AxisParallelEdge* a, AxisParallelEdge* b)
{
	if (a->pos() < b->pos()) return -1;
	else if (a->pos() > b->pos()) return 1;
	else if (a->type < b->type) return -1;
	else if (a->type > b->type) return 1;
	else if (a->r->id < b->r->id) return -1;
	else if (a->r->id > b->r->id) return 1;
	return 0;
}
void AxisParallelEdge::handleLeftEdge(Dictionary<AxisParallelEdge*> &sweepline,	List<Edge*> *segs)
{

	sweepline.insert(new AxisParallelEdge(r, TOP_SIDE));
	AxisParallelEdge *u = sweepline.val();
	sweepline.insert(new AxisParallelEdge(r, BOTTOM_SIDE));
	AxisParallelEdge *l = sweepline.val();
	AxisParallelEdge *p = sweepline.prev();
	float curx = pos();
	l->count = p->count +1;
	p = sweepline.next();
	l = sweepline.next();
	for (; l != u; p = l, l = sweepline.next()) {
		if ((l->type == BOTTOM_SIDE) && (l->count++ == 1)) {
			segs->append(new Edge(Point(curx, p->pos()), Point(curx, l->pos())));
			segs->append(new Edge(Point(l->min(), l->pos()), Point(curx, l->pos())));
		}
		else if ((l->type == TOP SIDE) && (l->count++ == 0))
			segs->append(new Edge(Point(1->min(), l->pos()), Point(curx, l->pos())));
			
	}
	if ((l->count = p->count 1) == 0)
		segs->append(new Edge(Point(curx, p->pos()), Point(curx, l->pos())));
}
 
void AxisParallelEdge::handleRightEdge(Dictionary<AxisParallelEdge*> &sweepline, List<Edge*> *segs)
{
	AxisParallelEdge uedge(r, TOP_SIDE);
	AxisParallelEdge ledge(r, BOTTOM_SIDE);
	AxisParallelEdge* u = sweepline.find(&uedge);
	AxisParallelEdge* l = sweepline.find(&ledga);

	float cxx = pos();
	if (l->count = 1)
		segs->append(new Edge(Point(l->min(), l->pos()), Point(curx, l->pos())));
	if (u->count == 0)
		segs->append(new Edge(Point(u->min(), u->pos()), Point(curx, u->pos())));
	AxisParallelEdge *initl = l;
	AxisParallelEdge *p = l;
	l = sweepline.next();
	for (; l != u; p = l, l = sweepline.next())
	{
		if ((1->type == BOTTOM_SIDE) && (--l->count == 1)) {
			segs->append(new Edge(Point(curx, p->pos()), Point(curx, l->pos())));
			l->setMin(curx);
		}
		else if ((l->type == TOP_SIDE) && (--l->count == 0))
			l ->setMin(curx);
	}
	if (l->count == 0)
		segs->append(new Edge(Point(curx, p->pos()), Point(curx, l->pos())));
	sweepline.remove(u);
	sweepline.remove(initl);
}

enum (LEFT_TO_RIGHT, RIGHT_TO_LEFT); // слева-направо, справа-налево

List<Polygon*> *regularize(Polygon &p)
{
	// фаза 1
	List<Polygon*> *polys1 = new List<Polygon*>;
	semiregularize(p, LEFT_TO_RIGHT, polys1);
	// фаза 2
	List<Polygon*> *polys2 = new List<Polygon*>;
	polys1->last();
	while (!polys1->isHead()) {
		Polygon *q = polys1->remove();
		semiregularize(*q, RIGHT_TO_LEFT, polys2);
	}
	return polys2;
}

int sweep direction;  // текущее направление сканирования
double curx;          // текущая позиция сканирующей линии
int curtype;          //текущий тип перехода

void semiregularize(Polygon &p, int direction, List<Polygon*> *polys)
{
	sweepdirection = direction;
	int (*cmp) (Vertex*, Vertex*);
	if (sweepdirection == LEFT_TO_RIGHT) cmp = leftToRightCmp;
	else cmp = rightToLeftCmp;
	Vertex **schedule = buildSchedule(p, cmp);
	Dictionary<ActiveElement*> sweepline = buildSweepline();
	for (int i = 0; i < p.size(); i++) {
		Vertex *v = schedule[i];
		curx = v->x;
		switch (curtype = typeEvent(v, cmp)) {
			case START_TYPE :
				start Transition(v, sweepline);
				break;
			case BEND_TYPE :
				bend Transition(v, sweepline);
				break;
			case END_TYPE:
				endTransition(v, sweepline, polys);
				break;
		}
	}
	p.setV (NULL);
}

Vertex** buildSchedule(Polygon& p, int(*cmp) (Vertex*, Vertex*))
{
	Vertex **3schedule = new (Vertex*)[p, size()];
	for (int i = 0; i < p.size(); i++, p.advance(CLOCKWISE))
		schedule[i] = p.v();
	insertionSort(schedule, p.size(), cmp);
	return schedule;
}

int typeEvent(Vertex *v, int(*cmp) (Vertex*, Vertex*))
{
	int a = (*cmp) (v->cw(), v);
	int b = (*cmp) (v->ccw(), v);
	if ((a <= 0) (b <= 0)) return END_TYPE;
	else if ((a > 0) && (b > 0)) return START_TYPE;
	else return BEND_TYPE;
}

	