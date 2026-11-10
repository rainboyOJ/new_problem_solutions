import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 暴力对拍规模控制在 n <= 20, Q <= 20
n = randint(1, 20)
io.input_writeln(f"0 {n}")

a = list(range(1, n + 1))
b = list(range(1, n + 1))
random.shuffle(a)
random.shuffle(b)

io.input_writeln(" ".join(map(str, a)))
io.input_writeln(" ".join(map(str, b)))

q = randint(1, 20)
io.input_writeln(q)

for _ in range(q):
    l = randint(1, n)
    r = randint(l, n)
    io.input_writeln(f"{l} {r}")
