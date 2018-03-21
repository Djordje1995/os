#include "IVTEntry.h"
#include "define.h"
#include <dos.h>
#include "event.h"
#include "kerev.h"

IVTEntry* IVTable[256];

IVTEntry::IVTEntry(IVTNo ivtNo, entryInterrupt newRoutine) {
	ivtNumber = ivtNo;
	IVTable[ivtNumber] = this;
	kernelEvent = 0;
	oldRoutine = 0;
#ifndef BCC_BLOCK_IGNORE
	lock;
	oldRoutine = getvect(ivtNumber);
	setvect(ivtNumber, newRoutine);
	unlock;
#endif
}

IVTEntry::~IVTEntry() {
	IVTable[ivtNumber] = 0;
#ifndef BCC_BLOCK_IGNORE
	lock;
	setvect(ivtNumber, oldRoutine);
	unlock;
#endif
}

void IVTEntry::signal() {
	if (kernelEvent != 0) {
		kernelEvent->signal();
	}
	dispatch();
}

void IVTEntry::callOldR() {
	oldRoutine();
}
