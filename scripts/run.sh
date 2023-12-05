#!/bin/bash

f=makeaffine.csv

echo "runs,warmup,time" | tee $f
for x in `seq 40`
do
	rosrun benchmark_robot_state_initialization benchmark_robot_state_initialization \
		_runs:=1000000 \
		_warmup:=100 \
		| tee -a $f
done
