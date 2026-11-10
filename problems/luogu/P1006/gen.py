import sys
from cyaron import IO, randint, Vector

io = IO(input_file=sys.stdout, disable_output=True)

# 暴力对拍规模控制在 m, n <= 8 以内，保证 DFS 在 2s 内能跑完
m = randint(2, 7)
n = randint(2, 7)
io.input_writeln(m, n)

for i in range(1, m + 1):
    row = [randint(0, 50) for _ in range(n)]
    if i == 1:
        row[0] = 0
    if i == m:
        row[n - 1] = 0
    io.input_writeln(" ".join(map(str, row)))
