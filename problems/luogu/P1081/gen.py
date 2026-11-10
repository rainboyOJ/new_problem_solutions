import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 暴力对拍规模：n <= 15, m <= 10
n = randint(3, 15)
io.input_writeln(n)

# 生成 n 个互不相同的海拔
alts = set()
while len(alts) < n:
    alts.add(randint(-50, 50))
io.input_writeln(" ".join(map(str, list(alts))))

x0 = randint(0, 100)
io.input_writeln(x0)

m = randint(1, 10)
io.input_writeln(m)
for _ in range(m):
    s = randint(1, n)
    x = randint(0, 100)
    io.input_writeln(f"{s} {x}")
