#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include <map>
#include "basesched.h"

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
        ~SchedRR2();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
	private:
		int ncores;
		std::vector<int> total;
		std::vector<int> quantums;
		std::vector<int> ticks;

		std::vector<int> running;
		std::map<int, int> blocked;

		std::vector<std::queue<int>> queues;

};

#endif
