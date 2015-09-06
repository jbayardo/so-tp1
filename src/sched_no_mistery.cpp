#include "sched_no_mistery.h"
#include <iostream>

using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	this->pid = IDLE_TASK;
	this->ticks = 0;

	this->quantums.push_back(1);
	this->ready.push_back(std::list<int>());

	for (int i = 1; i < argn.size(); ++i) {
		this->quantums.push_back(argn[i]);
		this->ready.push_back(std::list<int>());
	}
}

void SchedNoMistery::load(int p) {
	this->pending[p] = 0;
	this->ready[0].push_back(p);
}

void SchedNoMistery::unblock(int pid) {
	this->ready[this->pending[this->pid]].push_back(pid);
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	bool context = false;

	switch (m) {
		case TICK:
			++this->ticks;

			if (this->pid != IDLE_TASK) {
				int pending = this->pending[this->pid];
				int quantum = this->quantums[pending];

				if (this->ticks >= quantum) {
					if (this->pending[this->pid] < this->quantums.size() - 1) {
						++this->pending[this->pid];
					}

					this->ready[this->pending[this->pid]].push_back(this->pid);
					context = true;
				}
			} else {
				context = true;
			}

			break;
		case BLOCK:
			if (this->pending[this->pid] > 0) {
				--this->pending[this->pid];
			}

			context = true;
			break;
		case EXIT:
			pending.erase(pid);
			context = true;
			break;
	}

	if (context) {
		this->pid = IDLE_TASK;
		this->ticks = 0;

		for (std::size_t i = 0; i < this->ready.size(); ++i) {
			if (!this->ready[i].empty()) {
				this->pid = this->ready[i].front();
				this->ready[i].pop_front();
				break;
			}
		}
	}

	return this->pid;
}
