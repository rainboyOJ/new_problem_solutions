import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍规模：T=1, n, m 在 2 到 6 之间, q 在 2 到 8 之间
T = 1
io.input_writeln(T)

for _ in range(T):
    n = randint(2, 5)
    m = randint(2, 5)
    q = randint(2, min(n * m, 8))
    io.input_writeln(f"{n} {m} {q}")

    for _ in range(n):
        s = "".join(str(randint(0, 3)) for _ in range(m - 1))
        io.input_writeln(s)

    for _ in range(n - 1):
        s = "".join(str(randint(0, 3)) for _ in range(m))
        io.input_writeln(s)

    used_pos = set()
    for _ in range(q):
        while True:
            x = randint(1, n)
            y = randint(1, m)
            if (x, y) not in used_pos:
                used_pos.add((x, y))
                break
        col = randint(0, 1)
        lv = randint(1, q)
        io.input_writeln(f"{col} {lv} {x} {y}")
