import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 控制规模在 n, m <= 6，保证双重 DFS 暴力在毫秒级内完成
n = randint(3, 6)
m = randint(3, 6)
r = randint(1, n)
c = randint(1, m)

io.input_writeln(f"{n} {m} {r} {c}")

for _ in range(n):
    row = [randint(1, 50) for _ in range(m)]
    io.input_writeln(" ".join(map(str, row)))
