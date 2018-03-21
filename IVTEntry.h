#ifndef IVTENTRY_H_
#define IVTENTRY_H_

typedef unsigned char IVTNo;
typedef void interrupt (*entryInterrupt)(...);

class IVTEntry {
	friend class KernelEv;

	KernelEv* kernelEvent;
	int ivtNumber;
	entryInterrupt oldRoutine;
public:
	IVTEntry(IVTNo ivtNo, entryInterrupt newRout);
	~IVTEntry();
	void signal();
	void callOldR();
};

#endif
