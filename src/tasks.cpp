#include "tasks.h"
#include <random>
#include <set>
#include <iostream>
#include <chrono>

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

void TaskConsola(int pid, vector<int> params) {
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed1);
	uniform_int_distribution<int> distribution(params[1], params[2]);

	for (int i = 0; i < params[0]; ++i) {
		uso_IO(pid, distribution(generator));
	}
}

void TaskBatch(int pid, vector<int> params) {
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed1);
	uniform_int_distribution<int> distribution(0, params[0]-params[1]-2);
	std::set<int> times;

	while (times.size() < params[1]) {
		times.insert(distribution(generator));
	}

	for (int x = 0; x < params[0]-params[1]-1; ++x){
		if (times.find(x) == times.end()){
			uso_CPU(pid, 1);
		} else {
			uso_IO(pid, 1);
		}
	}

}

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskConsola, 3);
	register_task(TaskBatch, 2);
	register_task(TaskAlterno, -1);
}
