import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

a = randint(0, 10**6)
b = randint(0, 10**6)
k = randint(0, 1000)
n = randint(0, k)
m = k - n

io.input_writeln(f"{a} {b} {k} {n} {m}")
