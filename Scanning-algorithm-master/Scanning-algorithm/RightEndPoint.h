#pragma once
#include "EventPoint.h"
class RightEndPoint : public EventPoint
{
public:
	Edge e;
	RightEndPoint(Edge*);
	void handleTransition(Dictionary < Edge*>&, Dictionary < EventPoint*>&, List<EventPoint*>*);
};

