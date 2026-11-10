import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍数据
d = randint(1, 10)
n = randint(1, 15)
io.input_writeln(d)
io.input_writeln(n)

used = set()
for _ in range(n):
    while True:
        x = randint(0, 128)
        y = randint(0, 128)
        if (x, y) not in used:
            used.add((x, y))
            k = randint(1, 50)
            io.input_writeln(f"{x} {y} {k}")
            break
