#ifndef KEREV_H_
#define KEREV_H_

#include "event.h"

class KernelEv {
protected:
	friend class Event;
public:
	KernelEv (IVTNo ivtNo);
	~KernelEv ();
	void wait ();
	void signal();

	IVTNo ivtEntry;
	Event* myEvent;
	int value;
	PCB* myPCB;
};


#endif
