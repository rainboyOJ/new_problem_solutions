import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍规模：n, m 在 10 到 40 之间，q 在 2 到 4 之间
c = 3
n = randint(10, 40)
m = randint(10, 40)
q = randint(2, 4)

io.input_writeln(f"{c} {n} {m} {q}")
a = [randint(1, 100) for _ in range(n)]
b = [randint(1, 100) for _ in range(m)]
io.input_writeln(" ".join(map(str, a)))
io.input_writeln(" ".join(map(str, b)))

for _ in range(q):
    kx = randint(0, 3)
    ky = randint(0, 3)
    io.input_writeln(f"{kx} {ky}")
    px_list = []
    while len(px_list) < kx:
        pos = randint(1, n)
        if pos not in px_list:
            px_list.append(pos)
            val = randint(1, 100)
            io.input_writeln(f"{pos} {val}")
    py_list = []
    while len(py_list) < ky:
        pos = randint(1, m)
        if pos not in py_list:
            py_list.append(pos)
            val = randint(1, 100)
            io.input_writeln(f"{pos} {val}")
