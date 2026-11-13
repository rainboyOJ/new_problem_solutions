import sys
from cyaron import IO, randint, Graph

io = IO(input_file=sys.stdout, disable_output=True)
t = randint(1, 3)
io.input_writeln(t)

for _ in range(t):
    n = randint(3, 7)
    m = randint(n - 1, 10)
    io.input_writeln(f"{n} {m}")

    g = Graph.connected(n, m, weight_limit=(1, 30))
    for edge in g.iterate_edges():
        io.input_writeln(f"{edge.start} {edge.end} {edge.weight}")

    s = [randint(1, 20) for _ in range(n)]
    io.input_writeln(" ".join(map(str, s)))
