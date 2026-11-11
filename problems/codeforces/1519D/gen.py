#!/usr/bin/env python3
import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 适中规模用于对拍 O(n^3) 暴力，同时覆盖边界
n = randint(1, 50)
io.input_writeln(n)
io.input_writeln([randint(1, 10**6) for _ in range(n)])
io.input_writeln([randint(1, 10**6) for _ in range(n)])
