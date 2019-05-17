
test: schedu_sim.c lib/Queue.h lib/Process.h
	gcc schedu_sim.c -o test && ./test trace/data_3.txt
