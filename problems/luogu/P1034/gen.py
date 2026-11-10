import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 控制对拍规模：n 在 4 到 12 之间，k 在 2 到 4 之间
n = randint(4, 12)
k = randint(2, 4)

io.input_writeln(f"{n} {k}")
for _ in range(n):
    x = randint(0, 30)
    y = randint(0, 30)
    io.input_writeln(f"{x} {y}")
