import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 控制对拍数据规模以保证 DFS 在时限内跑出
t = randint(1, 3)
io.input_writeln(t)

for _ in range(t):
    n = randint(2, 6)
    io.input_writeln(n)
    vals = set()
    while len(vals) < n:
        vals.add(randint(1, 50))
    io.input_writeln(" ".join(map(str, sorted(list(vals)))))
