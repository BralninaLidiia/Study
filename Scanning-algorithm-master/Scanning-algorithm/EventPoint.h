#pragma once
class EventPoint
{
public:
	Point p;
	virtual void handleTransition(Dictionary<Edge*>&, Dictionary<EventPoint*>&, List<EventPoint*>*) = 0;
};

