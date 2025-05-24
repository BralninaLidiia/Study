#pragma once
class LeftEndpoint : public EventPoint
{
public:
	Edge e;
	LeftEndpoint(Edge*);
	void handleTrasition(Dictionary<Edge*>&, Dictionary<EventPoint*>&, List<EventPoint*>*);
};

