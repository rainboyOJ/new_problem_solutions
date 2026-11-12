import sys
from cyaron import IO, Graph, randint, String

io = IO(input_file=sys.stdout, disable_output=True)
n = randint(1, 10)
m = randint(0, 15)
io.input_writeln(n, m)
# 生成长度为 n 的小写字母字符串
s = "".join([chr(randint(ord("a"), ord("c"))) for _ in range(n)])  # 字母集中在 a, b, c 便于产生较大频次
io.input_writeln(s)

for _ in range(m):
    u = randint(1, n)
    v = randint(1, n)
    io.input_writeln(u, v)
