#include "sched_no_mistery.h"
#include <iostream>

using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	this->pid = IDLE_TASK;
	this->ticks = 0;

	this->quantums.push_back(1);

	for (int i = 1; i < argn.size(); ++i) {
		this->quantums.push_back(argn[i]);
	}
}

void SchedNoMistery::load(int p) {
	this->ready.push_back(p);
	this->pending[p] = 0;
}

void SchedNoMistery::unblock(int pid) {
	// TODO: confirm
	ready.push_front(pid);
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {  
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

					if (!this->ready.empty()) {
						this->ready.push_back(this->pid);
						this->pid = this->ready.front();
						this->ready.pop_front();
					}

					this->ticks = 0;
				}
			} else {
				if (!this->ready.empty()) {
					// cambio de contexto
					this->pid = this->ready.front();
					this->ready.pop_front();
					this->ticks = 0;
				}
			}


			break;
		case BLOCK:
			if (this->pending[this->pid] < this->quantums.size() - 1) {
				++this->pending[this->pid];
			}

			this->ticks = 0;

			if (this->ready.empty()) {
				this->pid = IDLE_TASK;
			} else {
				this->pid = this->ready.front();
				this->ready.pop_front();
			}

			break;
		case EXIT:
			pending.erase(pid);
			this->ticks = 0;

			if (this->ready.empty()) {
				this->pid = IDLE_TASK;
			} else {
				this->pid = this->ready.front();
				this->ready.pop_front();
			}

			break;
	}

	return this->pid;
}
