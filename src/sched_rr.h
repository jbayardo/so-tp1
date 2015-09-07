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
		/*! Número de cores
		 */
		int cores;

		/*! Quantums indexados por cpu
		 */
		std::vector<int> quantums;

		/*! Cuanto del quantum lleva corriendo cada proceso
		 */
		std::unordered_map<int, int> running;

		/*! Qué proceso está corriendo cada cpu (podríamos haber utilizado un vector)
		 */
		std::unordered_map<int, int> coreStates;

		/*! Procesos en estado ready
		 */
		std::queue<int> next;
};

#endif
