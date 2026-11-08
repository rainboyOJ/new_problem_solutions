#!/usr/bin/env python3
import sys
from cyaron import IO, randint, Vector

io = IO(input_file=sys.stdout, disable_output=True)
n = randint(1, 40)
io.input_writeln(n)
for i in range(n):
    row = [0] * n
    for j in range(n):
        if i != j and randint(1, 100) <= 30:   # 约 30% 概率有边
            row[j] = 1
    io.input_writeln(row)
