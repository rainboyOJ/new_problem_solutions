import sys
from cyaron import IO, randint

# duipai.py --gen 约定的生成器：无参数，直接输出到 sys.stdout
io = IO(input_file=sys.stdout, disable_output=True)

# N 取值 1 到 9
n = randint(1, 9)
io.input_writeln(n)

# 随机填入若干非零格，格数从 0 到 n*n
num_points = randint(0, min(15, n * n))
used = set()
for _ in range(num_points):
    x = randint(1, n)
    y = randint(1, n)
    if (x, y) not in used:
        used.add((x, y))
        v = randint(1, 30)
        io.input_writeln(f"{x} {y} {v}")

# 以 0 0 0 结尾
io.input_writeln("0 0 0")
