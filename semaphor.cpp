#include "semaphor.h"
#include "define.h"
#include "kersem.h"

Semaphore::Semaphore (int init){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	myImpl = new KernelSem(init);
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

Semaphore::~Semaphore (){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

int Semaphore::wait (Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

void Semaphore::signal(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	myImpl->signal();
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

int Semaphore::val () const {
	return myImpl->value;
}

