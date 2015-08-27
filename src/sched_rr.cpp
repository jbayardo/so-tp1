#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	this->cores = argn[0];

	for (int i = 1; i < argn.size(); ++i) {
		this->quantums.push_back(argn[i]);
		this->coreStates[i-1] = IDLE_TASK;
	}

	running[IDLE_TASK] = 1;
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	// Llega una tarea
	this->next.push(pid);
}

void SchedRR::unblock(int pid) {
	// Se desbloquea una tarea
	this->next.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	// Tick de CPU
	switch (m) {
		case TICK: {
			int pid = coreStates[cpu];
			int quantum = 1;

			if (pid != IDLE_TASK) {
				quantum = running[pid];
			}

			--quantum;

			// Si termino el quantum
			if (quantum == 0) {
				if (next.empty()) {
					running[pid] = quantums[cpu];
					return pid;
				} else {
					if (pid != IDLE_TASK) {
						next.push(pid);
					}

					int nextPid = next.front();
					next.pop();

					running.erase(pid);
					running[nextPid] = quantums[cpu];
					coreStates[cpu] = nextPid;

					return nextPid;
				}
			} else {
				running[pid] = quantum;
				return pid;
			}

			break;
		}
		case BLOCK:
		case EXIT: {
			int pid = coreStates[cpu];
			running.erase(pid);

			if (next.empty()) {
				coreStates[cpu] = IDLE_TASK;

				return IDLE_TASK;
			} else {
				int nextPid = next.front();
				next.pop();

				running[nextPid] = quantums[cpu];
				coreStates[cpu] = nextPid;

				return nextPid;
			}

			break;
		}
	}
}
