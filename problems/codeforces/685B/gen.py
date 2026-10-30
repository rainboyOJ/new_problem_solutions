import sys
import random
from collections import deque
from cyaron import IO, Graph, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 随机小规模对拍，方便暴搜比对
n = randint(2, 300)
q = randint(1, 300)

io.input_writeln(n, q)

# 生成树的形状
shape = random.choice(["random", "chain", "flower", "deep"])

if shape == "chain":
    tree = Graph.chain(n)
elif shape == "flower":
    tree = Graph.flower(n)
elif shape == "deep":
    tree = Graph.tree(n, chain=0.8, flower=0.1)
else:
    tree = Graph.tree(n, chain=0.2, flower=0.2)

# 以 1 为根定向
adj = [[] for _ in range(n + 1)]
for edge in tree.iterate_edges():
    u, v = edge.start, edge.end
    adj[u].append(v)
    adj[v].append(u)

fa = [0] * (n + 1)
visited = [False] * (n + 1)
queue = deque([1])
visited[1] = True

while queue:
    curr = queue.popleft()
    for nxt in adj[curr]:
        if not visited[nxt]:
            visited[nxt] = True
            fa[nxt] = curr
            queue.append(nxt)

# 输出 p_2, p_3, ..., p_n
io.input_writeln(" ".join(str(fa[i]) for i in range(2, n + 1)))

# 输出 q 次查询
for _ in range(q):
    io.input_writeln(randint(1, n))
