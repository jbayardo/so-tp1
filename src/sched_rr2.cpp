#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Ponemos la cantidad de cores
	this->ncores = argn[0];

	// Inicializamos las estructuras
	for (int i = 1; i < argn.size(); ++i) {
		// Todos empiezan sin procesos corriendo
		this->total.push_back(0);

		// Cargamos el quantum correspondiente
		this->quantums.push_back(argn[i]);

		// Una cola vacia por procesar
		this->queues.push_back(std::queue<int>());

		// La idle empezando desde 0
		this->ticks.push_back(0);
		this->running.push_back(IDLE_TASK);
	}
}

SchedRR2::~SchedRR2() {

}


void SchedRR2::load(int pid) {
	int minimum = 0;

	// Buscamos el procesador con menor numero de procesos totales
	for (int i = 1; i < this->ncores; ++i) {
		if (this->total[i] < total[minimum]) {
			minimum = i;
		}
	}

	// Aumentamos la cantidad de procesos totales
	this->total[minimum]++;

	// Lo ponemos en la cola del procesador
	this->queues[minimum].push(pid);
}

void SchedRR2::unblock(int pid) {
	// Buscamos en que procesador estaba el pid
	auto it = this->blocked.find(pid);

	if (it != this->blocked.end()) {
		// Lo ponemos en la cola del procesador
		this->queues[it->second].push(pid);

		// Lo borramos permanentemente
		this->blocked.erase(pid);
	}
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	// Buscamos el PID corriendo en el CPU actual
	int pid = this->running[cpu];

	switch(m) {
		case TICK:
			// Aumentamos los ticks
			++this->ticks[cpu];

			if (this->running[cpu] == IDLE_TASK) {
				// Si estamos en la IDLE...
				if (!this->queues[cpu].empty()) {
					// Y tenemos otra cosa para ejecutar, cambiamos de contexto
					this->ticks[cpu] = 0;

					int next = this->queues[cpu].front();
					this->queues[cpu].pop();

					this->running[cpu] = next;
				}
			} else {
				// No estamos en la idle

				if (this->ticks[cpu] >= this->quantums[cpu]) {
					// Nos pasamos del quantum!, cambiamos de contexto
					this->queues[cpu].push(pid);
					this->ticks[cpu] = 0;

					int next = this->queues[cpu].front();
					this->queues[cpu].pop();

					this->running[cpu] = next;
				}
			}

			break;
		case BLOCK:
			// Nos bloqueamos
			this->blocked[pid] = cpu;

			// Reseteamos el quantum
			this->ticks[cpu] = 0;

			if (this->queues[cpu].empty()) {
				// No hay nada para seguir, vamos a la idle
				this->running[cpu] = IDLE_TASK;
			} else {
				// Cambio a otra tarea!
				int next = this->queues[cpu].front();
				this->queues[cpu].pop();

				this->running[cpu] = next;
			}

			break;
		case EXIT:
			// Bajamos los procesos corriendo
			this->total[cpu]--;

			// Reseteamos el quantum
			this->ticks[cpu] = 0;

			if (this->queues[cpu].empty()) {
				// No hay nada para seguir, vamos a la idle
				this->running[cpu] = IDLE_TASK;
			} else {
				// Cambio a otra tarea!
				int next = this->queues[cpu].front();
				this->queues[cpu].pop();

				this->running[cpu] = next;
			}

			break;
	}

	return this->running[cpu];
}
