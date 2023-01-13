main: main.cpp heap.o
	g++ -Wall -o $@ $^ -lncurses
heap.o: heap.cpp heap.h
	g++ -Wall -c -o $@ $<

.PHONY:
	clean

clean:
	rm -f *.o main 
