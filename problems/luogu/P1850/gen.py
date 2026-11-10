import sys
from cyaron import IO, Graph, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍小规模：n <= 6, m <= 3, v <= 5, e <= 8
n = randint(2, 6)
m = randint(0, min(3, n))
v = randint(2, 5)
e = randint(v - 1, min(8, v * (v - 1) // 2))

io.input_writeln(f"{n} {m} {v} {e}")

c = [randint(1, v) for _ in range(n)]
d = [randint(1, v) for _ in range(n)]
io.input_writeln(" ".join(map(str, c)))
io.input_writeln(" ".join(map(str, d)))

probs = [f"{randint(0, 10) / 10.0:.1f}" for _ in range(n)]
io.input_writeln(" ".join(probs))

g = Graph.connected(v, e, weight_limit=(1, 20))
for edge in g.iterate_edges():
    io.input_writeln(f"{edge.start} {edge.end} {edge.weight}")
