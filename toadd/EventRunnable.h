#ifndef EVENTRUNNABLE_H
#define EVENTRUNNABLE_H

class Main;
class EventRunnable : public CThread
{
public:
	EventRunnable(Main *mainArg);
	bool run();
	Main *main;
};

#endif
