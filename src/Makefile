export LC_ALL=C
CXXFLAGS= -Wall -std=c++11 -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_no_mistery.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN) ejercicios

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

ejercicio1: $(MAIN)
	./simusched "../ejercicios/ejercicio 1.tsk" 1 10 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 1.png"

ejercicio2: $(MAIN)
	./simusched "../ejercicios/ejercicio 2.tsk" 1 4 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 2 - 1 nucleo.png"
	./simusched "../ejercicios/ejercicio 2.tsk" 2 4 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 2 - 2 nucleos.png"

ejercicio3: $(MAIN)
	./simusched "../ejercicios/ejercicio 3.tsk" 1 4 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 3.png"

ejercicio5: $(MAIN)
	./simusched "../ejercicios/ejercicio 5.tsk" 1 2 10 SchedRR 2 | python graphsched.py > "../ejercicios/ejercicio 5 - quantum 2.png"
	./simusched "../ejercicios/ejercicio 5.tsk" 1 2 10 SchedRR 10 | python graphsched.py > "../ejercicios/ejercicio 5 - quantum 10.png"
	./simusched "../ejercicios/ejercicio 5.tsk" 1 2 10 SchedRR 50 | python graphsched.py > "../ejercicios/ejercicio 5 - quantum 50.png"

ejercicio6: $(MAIN)
	./simusched "../ejercicios/ejercicio 5.tsk" 1 2 10 SchedFCFS | python graphsched.py > "../ejercicios/ejercicio 6.png"

ejercicio7: $(MAIN)
	./simusched "../schedmistery/test1.tsk" 1 1 1 SchedMistery 50 25 10 | python graphsched.py > "../ejercicios/ejercicio 7-1.png"
	./simusched "../schedmistery/test2.tsk" 1 1 1 SchedMistery 50 25 10 | python graphsched.py > "../ejercicios/ejercicio 7-2.png"
	./simusched "../schedmistery/test3.tsk" 1 1 1 SchedMistery 50 25 10 | python graphsched.py > "../ejercicios/ejercicio 7-3.png"

ejercicio8: $(MAIN)
	./simusched "../ejercicios/ejercicio 8-1.tsk" 2 2 10 SchedRR2 10 10| python graphsched.py > "../ejercicios/ejercicio 8-1.png"
	./simusched "../ejercicios/ejercicio 8-1.tsk" 2 2 10 SchedRR 10 10| python graphsched.py > "../ejercicios/ejercicio 8-1RR.png"

	./simusched "../ejercicios/ejercicio 5.tsk" 2 2 10 SchedRR2 10 10| python graphsched.py > "../ejercicios/ejercicio 8-1b.png"
	./simusched "../ejercicios/ejercicio 5.tsk" 2 2 10 SchedRR 10 10| python graphsched.py > "../ejercicios/ejercicio 8-1bRR.png"

	./simusched "../ejercicios/ejercicio 8-2.tsk" 2 2 10 SchedRR 10 10| python graphsched.py > "../ejercicios/ejercicio 8-2m.png"
	./simusched "../ejercicios/ejercicio 8-2.tsk" 2 2 10 SchedRR2 10 10| python graphsched.py > "../ejercicios/ejercicio 8-2.png"


ejercicios: ejercicio1 ejercicio2 ejercicio3 ejercicio5 ejercicio7 ejercicio6 ejercicio8

new: clean all

