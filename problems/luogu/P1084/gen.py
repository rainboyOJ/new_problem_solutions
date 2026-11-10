import sys
from cyaron import IO, Graph, randint

io = IO(input_file=sys.stdout, disable_output=True)

n = randint(3, 10)
# 生成以 1 为根的树
t = Graph.tree(n, chain=0.3, flower=0.3)
io.input_writeln(n)

for e in t.iterate_edges():
    # 边权 1 到 20
    w = randint(1, 20)
    io.input_writeln(f"{e.start} {e.end} {w}")

# 军队数 m，保证军队不在 1 号点
m = randint(2, n)
io.input_writeln(m)
armies = [randint(2, n) for _ in range(m)]
io.input_writeln(" ".join(map(str, armies)))
