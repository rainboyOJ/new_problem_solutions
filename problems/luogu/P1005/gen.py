import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍时 m 稍小一些以防 brute 的 DFS 指数爆炸（m <= 12），n <= 4
n = randint(1, 4)
m = randint(1, 10)
io.input_writeln(f"{n} {m}")

for _ in range(n):
    row = [randint(0, 100) for _ in range(m)]
    io.input_writeln(" ".join(map(str, row)))
