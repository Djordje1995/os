#ifndef IDLE_H_
#define IDLE_H_

#include "Thread.h";

class Idle : public Thread {
public:
	Idle(StackSize stackSize, Time timeSlice):Thread(stackSize,timeSlice){}
	~Idle();
	virtual void run();

};

#endif
