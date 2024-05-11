log.out: log.o main.o
	g++ log.o main.o -o log.out

log.o: src/log.cc
	g++ -c src/log.cc -o log.o

main.o: src/main.cc
	g++ -c src/main.cc -o main.o

clean:
	rm *.o
