import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍规模：n 在 3 到 100 之间，p 在 2 到 10^9 之间
n = randint(3, 100)
p = randint(2, 10**9)

io.input_writeln(f"{n} {p}")
# 随机生成可正可负的数
a = [randint(-1000, 1000) for _ in range(n)]
io.input_writeln(" ".join(map(str, a)))
