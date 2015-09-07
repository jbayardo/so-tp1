#include "sched_no_mistery.h"
#include <iostream>

using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	// Inicializamos corriendo la IDLE
	this->pid = IDLE_TASK;
	this->ticks = 0;

	// Agregamos el 1 como primer quantum para todas las tareas
	this->quantums.push_back(1);
	this->ready.push_back(std::list<int>());

	// Agregamos los quantums que nos pasen por parametro, y generamos las listas correspondientes
	for (int i = 1; i < argn.size(); ++i) {
		this->quantums.push_back(argn[i]);
		this->ready.push_back(std::list<int>());
	}
}

void SchedNoMistery::load(int p) {
	// Si estamos cargando, simplemente decimos que inicializa con el primer quantum, y que esta listo
	this->pending[p] = 0;
	this->ready[0].push_back(p);
}

void SchedNoMistery::unblock(int pid) {
	// Lo agregamos a la cola de listos para este quantum particular
	this->ready[this->pending[this->pid]].push_back(pid);
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	//! Si es true, tenemos que hacer context switch
	bool context = false;

	switch (m) {
		case TICK:
			++this->ticks;

			if (this->pid != IDLE_TASK) {
				// Si la tarea no es la idle, nos fijamos si hay que seguir ejecutando
				int pending = this->pending[this->pid];
				int quantum = this->quantums[pending];

				if (this->ticks >= quantum) {
					// Nos pasamos del quantum!

					if (this->pending[this->pid] < this->quantums.size() - 1) {
						// Si podemos seguir aumentando el quantum, lo hacemos
						++this->pending[this->pid];
					}

					// Lo ponemos en la cola para el proximo quantum
					this->ready[this->pending[this->pid]].push_back(this->pid);

					// Tratamos de hacer context switch
					context = true;
				}
			} else {
				// Si es la IDLE, tratamos de hacer context switch
				context = true;
			}

			break;
		case BLOCK:
			// Le bajamos el quantum de tiempo
			if (this->pending[this->pid] > 0) {
				--this->pending[this->pid];
			}

			// Tratamos de hacer context switch
			context = true;
			break;
		case EXIT:
			// Lo borramos definitivamente
			pending.erase(pid);

			// Tratamos de hacer context switch
			context = true;
			break;
	}

	if (context) {
		// Si hay que cambiar de contexto, reinicializamos el quantum y ponemos la IDLE
		this->pid = IDLE_TASK;
		this->ticks = 0;

		// Recorremos todas las colas
		for (std::size_t i = 0; i < this->ready.size(); ++i) {
			if (!this->ready[i].empty()) {
				// Utilizamos el proceso con menor quantum!
				this->pid = this->ready[i].front();
				this->ready[i].pop_front();
				break;
			}
		}
	}

	return this->pid;
}
