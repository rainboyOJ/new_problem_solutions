import sys
from cyaron import IO, Graph, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 暴力对拍规模：n <= 5, m <= 6
n = randint(2, 5)
m = randint(n - 1, min(7, n * (n - 1) // 2))

# 生成无向连通图，默认权重即可
g = Graph.connected(n, m)
io.input_writeln(f"{n} {m}")

for e in g.iterate_edges():
    io.input_writeln(f"{e.start} {e.end}")
