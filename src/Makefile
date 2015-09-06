export LC_ALL=C
CXXFLAGS= -Wall -std=c++11 -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_no_mistery.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN)

$(MAIN): $(OBJS) sched_mistery.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

clean:
	rm -f $(OBJS) $(MAIN)

ejercicio1: all
	./simusched "../ejercicios/ejercicio 1.tsk" 1 10 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 1.png"

ejercicio2: all
	./simusched "../ejercicios/ejercicio 2.tsk" 1 4 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 2 - 1 nucleo.png"
	./simusched "../ejercicios/ejercicio 2.tsk" 2 4 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 2 - 2 nucleos.png"

ejercicio3: all
	./simusched "../ejercicios/ejercicio 3.tsk" 1 4 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 3.png"

ejercicio5: all
	./simusched "../ejercicios/ejercicio 5.tsk" 1 2 10 SchedRR 2 | python graphsched.py > "../ejercicios/ejercicio 5 - quantum 2.png"
	./simusched "../ejercicios/ejercicio 5.tsk" 1 2 10 SchedRR 10 | python graphsched.py > "../ejercicios/ejercicio 5 - quantum 10.png"
	./simusched "../ejercicios/ejercicio 5.tsk" 1 2 10 SchedRR 50 | python graphsched.py > "../ejercicios/ejercicio 5 - quantum 50.png"

ejercicio6: all
	./simusched "../ejercicios/ejercicio 5.tsk" 1 2 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 6 - quantum 2.png"
	./simusched "../ejercicios/ejercicio 5.tsk" 1 2 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 6 - quantum 10.png"
	./simusched "../ejercicios/ejercicio 5.tsk" 1 2 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 6 - quantum 50.png"

ejercicio7: all
	./simusched "../schedmistery/test1.tsk" 1 1 1 SchedMistery 50 25 10 | python graphsched.py > "../ejercicios/ejercicio 7-1.png"
	./simusched "../schedmistery/test2.tsk" 1 1 1 SchedMistery 50 25 10 | python graphsched.py > "../ejercicios/ejercicio 7-2.png"

ejercicios: ejercicio1 ejercicio2 ejercicio3 ejercicio5 ejercicio7 ejercicio6

new: clean all

