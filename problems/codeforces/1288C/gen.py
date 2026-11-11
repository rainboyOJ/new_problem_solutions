#!/usr/bin/env python3
import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)
n = randint(1, 1000)
m = randint(1, 10)
io.input_writeln(f"{n} {m}")
