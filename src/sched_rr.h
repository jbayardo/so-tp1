#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <vector>
#include <queue>
#include <unordered_map>
#include "basesched.h"

class SchedRR : public SchedBase {
	public:
		SchedRR(std::vector<int> argn);
        ~SchedRR();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
	private:
		int cores;
		std::vector<int> quantums;
		std::unordered_map<int, int> running;
		std::unordered_map<int, int> coreStates;
		std::queue<int> next;
		bool firstTick;

};

#endif
