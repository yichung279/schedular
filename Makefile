.PHONY: all test clean

prefix=trace/data_
postfix=.txt

test: schedu_sim.c lib/Heap.h lib/Process.h
	gcc schedu_sim.c -o test -lm -Wall&& ./test $(schedular) $(prefix)$(data)$(postfix)
