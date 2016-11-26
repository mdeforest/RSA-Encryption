OPTS = -Wall

ReallyLongInt.o: ReallyLongInt.h ReallyLongInt.cc
	g++ ${OPTS} -c ReallyLongInt.cc

encrypt: numberTheory.h ReallyLongInt.o encrypt.cc
	g++ ${OPTS} -o encrypt encrypt.cc ReallyLongInt.o

decrypt: numberTheory.h ReallyLongInt.o decrypt.cc
	g++ ${OPTS} -o decrypt decrypt.cc ReallyLongInt.o

keygen: numberTheory.h ReallyLongInt.o keygen.cc
	g++ ${OPTS} -o keygen keygen.cc ReallyLongInt.o

factorial: ReallyLongInt.o factorial.cc
	g++ ${OPTS} -o factorial factorial.cc ReallyLongInt.o

clean:
	rm *.o
	rm encrypt decrypt keygen factorial

cleanemacs:
	rm *~

all: ReallyLongInt.o encrypt decrypt keygen factorial
