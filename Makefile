CFLAGS = -g -Wall -Werror -std=c99

all: perfcalc

perfcalc: perfcalc.o elotable.o

run: perfcalc
	@cat input | ./perfcalc

clean:
	rm -rf *.o perfcalc
