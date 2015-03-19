%.o:
	c++ -I /usr/local/include/ -std=c++11 -Wall -g -o $@ -c $<

%.out:
	c++ -I /usr/local/include/ -Wall -g -o $@ $^

%.so:
	c++ -I /usr/local/include -Wall -shared -g -o $@ $^
.PHONY: all
all: tt_decay.out tt_perf.out tt_lib.so

.PHONY: clean
clean:
	rm -f *.o *.out

tt_lib.o: tt_lib.cpp

tt_lib.so: tt_lib.o

tt_decay.o: tt_decay.cpp

tt_perf.o: tt_perf.cpp

tt_decay.out: tt_decay.o

tt_perf.out: tt_perf.o
