import sys
from cyaron import IO, Graph, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 随机小树 n <= 8, m <= n-1
n = randint(3, 8)
m = randint(1, n - 1)
io.input_writeln(f"{n} {m}")

t = Graph.tree(n, chain=0.3, flower=0.3)
for e in t.iterate_edges():
    w = randint(1, 20)
    io.input_writeln(f"{e.start} {e.end} {w}")
