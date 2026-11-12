import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)
n = randint(1, 15)  # 适合暴力 combinations
io.input_writeln(n)
io.input_writeln([randint(1, 50) for _ in range(n)])
