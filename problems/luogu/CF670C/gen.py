import sys
from cyaron import IO, randint, Vector

io = IO(input_file=sys.stdout, disable_output=True)
n = randint(1, 6)
m = randint(1, 5)
io.input_writeln(n)
io.input_writeln(Vector.random(n, [1, 5]))
io.input_writeln(m)
io.input_writeln(Vector.random(m, [1, 5]))
io.input_writeln(Vector.random(m, [1, 5]))
