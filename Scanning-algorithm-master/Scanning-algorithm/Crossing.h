#pragma once
class Crossing : public EventPoint
{
public:
	Edge e1, e2;
	Crossing(Edge*, Edge*, Point&);
	void handleTransition(Dictionary<Edge*>&, Dictionary <EventPoint*>&, List<EventPoint*>*);
};

