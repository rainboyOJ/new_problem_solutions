import sys
from cyaron import IO, Graph, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 暴力对拍规模
n = randint(3, 30)
m = randint(1, 30)
io.input_writeln(f"{n} {m} C3")

p = [randint(1, 100) for _ in range(n)]
io.input_writeln(" ".join(map(str, p)))

tree = Graph.tree(n, chain=0.3, flower=0.2)
for edge in tree.iterate_edges():
    io.input_writeln(f"{edge.start} {edge.end}")

for _ in range(m):
    a = randint(1, n)
    b = randint(1, n)
    while b == a:
        b = randint(1, n)
    x = randint(0, 1)
    y = randint(0, 1)
    io.input_writeln(f"{a} {x} {b} {y}")
