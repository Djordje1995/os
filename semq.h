#ifndef SEMQ_H_
#define SEMQ_H_

#include "pcb.h"

class PCB;

class Selem{
public:
	PCB *pcb;
	int check;
	Selem *next;
	Selem(PCB *p){ pcb = p; next = 0; check = 0;}
	~Selem(){}
};

class SemQueue{
private:
	Selem *head;
	Selem *tail;

public:
	SemQueue();
	~SemQueue();
	void put(PCB *pcb);
	PCB* get();
	Selem* getHead();
};

#endif
