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
	this->pending[p] = 0;
	// for (auto it = this->ready.end(); it != this->ready.begin(); it--){
	// 	if (this->pending[*it] > this->pending[p]){
	// 		this->ready.insert(it,p);
	// 		this->pending[p] = 0;
	// 		return;
	// 	}
	// }
	this->readyB.push_back(p);
	this->blocked[p] = false;
}

void SchedNoMistery::unblock(int pid) {
	this->readyB.push_back(pid);
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

					this->ready.push_back(this->pid);

					if (!this->readyN.empty()) {
						this->pid = this->readyN.front();
						this->readyN.pop_front();
					} else if (!this->readyB.empty()) {
						this->pid = this->readyB.front();
						this->readyB.pop_front();
					} else if (!this->ready.empty()) {
						this->pid = this->ready.front();
						this->ready.pop_front();
					}

					this->ticks = 0;
				}
			} else {
				if (!this->readyN.empty()) {
					this->pid = this->readyN.front();
					this->readyN.pop_front();
				} else if (!this->readyB.empty()) {
					this->pid = this->readyB.front();
					this->readyB.pop_front();
				} else if (!this->ready.empty()) {
					this->pid = this->ready.front();
					this->ready.pop_front();
				}
				this->ticks = 0;
			}


			break;
		case BLOCK:
			// if (this->pending[this->pid] < this->quantums.size() - 1) {
			// 	++this->pending[this->pid];
			// }

			this->ticks = 0;
			this->blocked[this->pid] = true;

			if (!this->readyN.empty()) {
				this->pid = this->readyN.front();
				this->readyN.pop_front();
			} else if (!this->readyB.empty()) {
				this->pid = this->readyB.front();
				this->readyB.pop_front();
			} else if (!this->ready.empty()) {
				this->pid = this->ready.front();
				this->ready.pop_front();
			} else {
				this->pid = IDLE_TASK;				
			}

			break;
		case EXIT:
			pending.erase(pid);
			blocked.erase(pid);
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
