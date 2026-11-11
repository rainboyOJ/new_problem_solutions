#!/usr/bin/env python3
import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

t = randint(1, 3)
io.input_writeln(t)

for _ in range(t):
    n = randint(1, 15)
    m = randint(1, 5)
    io.input_writeln(f"{n} {m}")
    for _ in range(n):
        perm = list(range(1, m + 1))
        random.shuffle(perm)
        io.input_writeln(" ".join(map(str, perm)))
