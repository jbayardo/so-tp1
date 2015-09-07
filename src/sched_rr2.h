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
		/*! Número de cores
		 */
		int ncores;

		/*! Cantidad de procesos activos totales por procesador
		 */
		std::vector<int> total;

		/*! Quantums correspondientes por procesador
		 */
		std::vector<int> quantums;

		/*! Ticks del quantum actual por procesador
		 */
		std::vector<int> ticks;

		/*! PID de la tarea actual por procesador
		 */	
		std::vector<int> running;

		/*! Procesador en el que corre un proceso bloqueado
		 */
		std::map<int, int> blocked;

		/*! Procesos ready por procesador
		 */
		std::vector<std::queue<int>> queues;

};

#endif
