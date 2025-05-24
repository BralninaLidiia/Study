#pragma once
class ActiveEdge : public ActiveElement{
public:
	Vertex *v;
	Vertex *w;
	int rotation;
	ActiveEdge(Vertex *_v, int _r, Vertex *_w);
	Edge2 edge(void);
	double y(void);
	double slope(void);
};

