import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 1 组测试数据，小规模 n <= 20, m <= 8
io.input_writeln("1 1")

n = randint(5, 20)
m = randint(1, 8)
k = randint(1, n)
d = randint(1, 10)
io.input_writeln(f"{n} {m} {k} {d}")

for _ in range(m):
    x = randint(1, n)
    y = randint(1, min(x, k))
    v = randint(1, 20)
    io.input_writeln(f"{x} {y} {v}")
