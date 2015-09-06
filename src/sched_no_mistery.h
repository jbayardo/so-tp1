#ifndef __SCHED_NOMIS__
#define __SCHED_NOMIS__

#include <vector>
#include <list>
#include <map>
#include "basesched.h"

class SchedNoMistery : public SchedBase {
  public:
    SchedNoMistery(std::vector<int> argn);
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);  
  private:
  	/*! Cola de procesos en ready
  	 */
  	std::vector<std::list<int>> ready;

  	/*! Vector con los quantums que hay que asignar, en el orden que se desea
  	 */
  	std::vector<int> quantums;

  	/*! Indice en el vector de quantums que lleva la tarea, asi sabemos la longitud del proximo quantum a asignarle
  	 */
  	std::map<int, int> pending;

  	/*! PID del proceso corriendo actualmente
  	 */
  	int pid;

  	/*! Parte del quantum por el que va la tarea actual
  	 */
  	int ticks;
};

#endif
