import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)
t = randint(1, 3)
io.input_writeln(t)

for _ in range(t):
    n = randint(1, 14)  # 适合暴力子集枚举
    k = randint(0, 6)
    io.input_writeln(n, k)
    io.input_writeln([randint(0, 63) for _ in range(n)])
