#!/bin/bash

for i in {1..1000}; do
	printf "\r$i"
	./rnd.out > in # 数据生成
	./1.out <in >out1
	./baoli.out <in >out2
	diff out1 out2 || exit 1
done
