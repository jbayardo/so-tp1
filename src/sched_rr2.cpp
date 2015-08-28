#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	this->ncores = argn[0];

	for (int i = 1; i < argn.size(); ++i) {
		this->total.push_back(0);
		this->quantums.push_back(argn[i]);
		this->queues.push_back(std::queue<int>());
		this->ticks.push_back(0);
		this->running.push_back(IDLE_TASK);
	}
}

SchedRR2::~SchedRR2() {

}


void SchedRR2::load(int pid) {
	int minimum = 0;

	for (int i = 1; i < this->ncores; ++i) {
		if (this->total[i] < total[minimum]) {
			minimum = i;
		}
	}

	this->total[minimum]++;
	this->queues[minimum].push(pid);
}

void SchedRR2::unblock(int pid) {
	auto it = this->blocked.find(pid);

	if (it != this->blocked.end()) {
		this->queues[it->second].push(pid);
		this->blocked.erase(pid);
	}
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	int pid = this->running[cpu];

	switch(m) {
		case TICK:
			++this->ticks[cpu];

			if (this->running[cpu] == IDLE_TASK) {
				if (!this->queues[cpu].empty()) {
					this->ticks[cpu] = 0;

					int next = this->queues[cpu].front();
					this->queues[cpu].pop();

					this->running[cpu] = next;
				}
			} else {
				if (this->ticks[cpu] >= this->quantums[cpu]) {
					this->queues[cpu].push(pid);
					this->ticks[cpu] = 0;

					int next = this->queues[cpu].front();
					this->queues[cpu].pop();

					this->running[cpu] = next;
				}
			}
			break;
		case BLOCK:
			this->blocked[pid] = cpu;
			this->ticks[cpu] = 0;

			if (this->queues[cpu].empty()) {
				this->running[cpu] = IDLE_TASK;
			} else {
				int next = this->queues[cpu].front();
				this->queues[cpu].pop();

				this->running[cpu] = next;
			}

			break;
		case EXIT:
			this->total[cpu]--;
			this->ticks[cpu] = 0;

			if (this->queues[cpu].empty()) {
				this->running[cpu] = IDLE_TASK;
			} else {
				int next = this->queues[cpu].front();
				this->queues[cpu].pop();

				this->running[cpu] = next;
			}

			break;
	}

	return this->running[cpu];
}
