#ifndef _KERNELSEM_H_
#define _KERNELSEM_H_

#include "semaphor.h"
#include "thread.h"
#include "semq.h"

static int sid = 0;

class KernelSem {
public:
	KernelSem (int init = 1);
	virtual ~KernelSem ();
	virtual int wait (Time maxTimeToWait);
	virtual void signal();
	virtual void signalAll();
	int semid;
	SemQueue* semQueue;
	int getVal(){ return value; }
	void setVal(int val){ value = val; }
	int value;
protected:
	friend class Semaphore;
	friend class SemQueue;

};

#endif

