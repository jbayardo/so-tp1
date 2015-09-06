#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Ponemos la cantidad de cores que tenemos
	this->cores = argn[0];

	for (int i = 1; i < argn.size(); ++i) {
		// Inicializamos todos los cores a correr la IDLE, y ponemos el tamaño de cada quantum
		this->quantums.push_back(argn[i]);
		this->coreStates[i-1] = IDLE_TASK;
	}

	// Da IDLE is running, nigga!
	running[IDLE_TASK] = 1;
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	// Llega una tarea, asi que la ponemos en la cola global
	this->next.push(pid);
}

void SchedRR::unblock(int pid) {
	// Se desbloquea una tarea, asi que la volvemos a poner en la cola global
	this->next.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	// Tick de CPU
	switch (m) {
		case TICK: {
			// Obtenemos el PID actual
			int pid = coreStates[cpu];

			// Forzamos el quantum a 1, asi si estamos en la IDLE hacemos context switch
			int quantum = 1;

			if (pid != IDLE_TASK) {
				// Como no estamos en la IDLE, ponemos el quantum apropiado
				quantum = running[pid];
			}

			// Lo decrementamos
			--quantum;

			if (quantum == 0) {
				// Si termino el quantum, buscamos que podemos hacer
				if (next.empty()) {
					// No queda nada más para procesar, asi que le renovamos el quantum!
					running[pid] = quantums[cpu];
					return pid;
				} else {
					if (pid != IDLE_TASK) {
						// Volvemos a ponerlo en la cola, para schedulearlo globalmente
						next.push(pid);
					}

					// Obtenemos el proximo proceso
					int nextPid = next.front();
					next.pop();

					// Inicializamos todo lo necesario!
					running.erase(pid);
					running[nextPid] = quantums[cpu];
					coreStates[cpu] = nextPid;

					return nextPid;
				}
			} else {
				// Seguimos corriendo, solo actualizamos cuanto nos queda
				running[pid] = quantum;
				return pid;
			}

			break;
		}
		// Bloquear es practicamente lo mismo que salir, para nosotros
		case BLOCK:
		case EXIT: {
			// Obtenemos el PID actual
			int pid = coreStates[cpu];

			// Nos aseguramos de no usarlo más
			running.erase(pid);

			if (next.empty()) {
				// Si no queda otra, nos vamos a la IDLE
				coreStates[cpu] = IDLE_TASK;

				return IDLE_TASK;
			} else {
				// Si no, obtenemos el próximo proceso!
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
