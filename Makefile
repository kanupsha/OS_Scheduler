computer.exe: cpu.o memory.o load.o shell.o computer.o scheduler.o print.o printer.o
	g++ -Wall cpu.o memory.o load.o shell.o computer.o scheduler.o print.o printer.o -o computer.exe -pthread
cpu.o: cpu.cpp
	g++ -c cpu.cpp -pthread
memory.o: memory.cpp
	g++ -c memory.cpp -pthread
load.o: load.cpp
	g++ -c load.cpp -pthread
shell.o: shell.cpp
	g++ -c shell.cpp -pthread
scheduler.o: scheduler.cpp
	g++ -c scheduler.cpp -pthread
computer.o: computer.cpp
	g++ -c computer.cpp -pthread
print.o: print.cpp
	g++ -c print.cpp -pthread
printer.o:printer.cpp
	g++ -c printer.cpp -pthread


