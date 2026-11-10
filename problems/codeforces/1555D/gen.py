#!/usr/bin/env python3
import random
import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

n = randint(1, 100)
m = randint(1, 50)
chars = "abc"
s = "".join(random.choice(chars) for _ in range(n))

io.input_writeln(f"{n} {m}")
io.input_writeln(s)

for _ in range(m):
    l = randint(1, n)
    r = randint(1, n)
    if l > r:
        l, r = r, l
    io.input_writeln(f"{l} {r}")
