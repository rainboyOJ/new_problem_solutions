import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍小规模：n <= 5, k <= 3, w_i <= 6
n = randint(1, 5)
k = randint(1, 3)
io.input_writeln(f"{n} {k}")

w = [randint(1, 6) for _ in range(k)]
io.input_writeln(" ".join(map(str, w)))

for _ in range(n):
    c = randint(1, k)
    d = 1 if randint(0, 1) == 1 else -1
    io.input_writeln(f"{c} {d}")
