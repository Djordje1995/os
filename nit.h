#ifndef NIT_H_
#define NIT_H_

#include "thread.h"
#include "pcb.h"
#include "timer.h"
#include "queue.h"
#include <iostream.h>
#include "define.h"

class Nit: public Thread {
public:
	Nit(StackSize stackSize, Time timeSlice):Thread(stackSize,timeSlice){}
	virtual ~Nit();
	virtual void run();

};

#endif
