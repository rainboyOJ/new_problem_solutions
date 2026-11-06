import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)
S = randint(2, 4)
D = randint(2, 4)
M = randint(1, 20)
io.input_writeln(S, D, M)
for _ in range(S):
    io.input_writeln([randint(1, 10) for _ in range(D)])
