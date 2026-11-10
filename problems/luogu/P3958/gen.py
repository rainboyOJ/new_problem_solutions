import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍生成 1 组数据
T = 1
io.input_writeln(T)

for _ in range(T):
    n = randint(2, 50)
    h = randint(10, 1000)
    r = randint(5, 200)
    io.input_writeln(f"{n} {h} {r}")
    for _ in range(n):
        x = randint(-500, 500)
        y = randint(-500, 500)
        z = randint(0, h)
        io.input_writeln(f"{x} {y} {z}")
