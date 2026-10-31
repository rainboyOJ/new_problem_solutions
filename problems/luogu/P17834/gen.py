import sys
from cyaron import IO, Graph, randint

io = IO(input_file=sys.stdout, disable_output=True)

T = 5
io.input_writeln(0, T)

for case_idx in range(T):
    if case_idx == 0:
        # tiny test, k=2
        n = 5
        k = 2
        t = Graph.chain(n)
    elif case_idx == 1:
        # small random, n=10, k=4
        n = 10
        k = randint(2, n)
        t = Graph.tree(n, chain=0.3, flower=0.2)
    elif case_idx == 2:
        # flower tree, n=8, k=3
        n = 8
        k = 3
        t = Graph.tree(n, flower=0.8)
    elif case_idx == 3:
        # chain, n=12, k=5
        n = 12
        k = 5
        t = Graph.chain(n)
    else:
        # general random n=12, k=2
        n = 12
        k = 2
        t = Graph.tree(n, chain=0.5, flower=0.3)

    io.input_writeln(n, k)
    for e in t.iterate_edges():
        io.input_writeln(e.start, e.end)
