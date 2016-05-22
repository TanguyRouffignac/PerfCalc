CPPFLAGS = -g -Wall -Werror -std=c++11

all: perfcalc

perfcalc: perfcalc.o elotable.o

run: perfcalc
	@cat input | ./perfcalc

clean:
	rm -rf *.o perfcalc
