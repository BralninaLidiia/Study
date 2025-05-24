#pragma once
enum ( LEFT_SIDE, RIGHT_SIDE, BOTTOM_SIDE, TOP_SIDE);
// лева€ , права€ , нижн€€ , верхн€€ стороны
class AxisParallelEdge {
public:
	Rectangle* r; //пр€моугольник, обладающий ребром
	int count;
	double m;
	int type; // тип стороны пр€моугольника
	AxisParallelEdge(Rectangle*, int);
	double pos(void);
	double min(void);
	double max(void);
	void setMin(double);
	void handleLeftEdge(Dictionary<AxisParallelEdge*>&, List<Edge*>*);
	void handleRightEdge(Dictionary<AxisParallelEdge*>&, List<Edge*>*);
};

