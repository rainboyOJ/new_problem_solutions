import sys
from cyaron import IO, randint, Vector

io = IO(input_file=sys.stdout, disable_output=True)
t = randint(1, 5)
io.input_writeln(t)

for _ in range(t):
    n = randint(1, 10)
    m = randint(1, 60)
    io.input_writeln(f"{n} {m}")
    a = [randint(1, 20) for _ in range(n)]
    b = [randint(1, 2) for _ in range(n)]
    io.input_writeln(" ".join(map(str, a)))
    io.input_writeln(" ".join(map(str, b)))
