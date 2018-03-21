#include <iostream.h>
#include <dos.h>
#include "schedule.h"
#include "pcb.h"
#include "thread.h"
#include "nit.h"
#include "define.h"
#include "timer.h"
#include "kersem.h"
#include "semq.h"
#include "bounded.h"
#include "intLock.h"
#include "keyevent.h"
#include "user.h"
#include "idle.h"

extern int userMain(int argc, char** argv);

class UserMain: public Thread {
public:
	UserMain(int count, char **arg):argc(count),argv(arg),Thread(defaultStackSize, 50) {
		returningValue = 0;
	}

	int getRet() {
		return returningValue;
	}

	virtual void run() {
		returningValue = userMain(argc, argv);
	}
	~UserMain(){
		waitToComplete();
	}

private:
	int argc;
	int returningValue;
	char **argv;
};

PCB *startingPCB;

int main(int argc, char* argv[]){

	inic();

	Idle* idle = new Idle(defaultStackSize, 1);
	idle->start();

	UserMain* user = new UserMain(argc, argv);
	user->start();

	g = 1;
	dispatch();
	int value = user->getRet();

	//for(int i = 100; i >= 0; i--) delete p[i];
	//delete [] p;
	//for(int j = 100; j > 0; j--) delete s[j];
	//delete [] s;
	delete user;

	restore();

	return value;
}

