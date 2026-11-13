import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)
t = randint(1, 5)
io.input_writeln(t)

for _ in range(t):
    n = randint(1, 25)
    io.input_writeln(n)
    s = "".join([str(randint(0, 1)) for _ in range(n)])
    io.input_writeln(s)
