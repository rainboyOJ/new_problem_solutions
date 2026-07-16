import sys
from array import array


input = sys.stdin.buffer.readline
n, queries, root = map(int, input().split())
head = array("i", [-1]) * (n + 1)
to = array("i", [0]) * (2 * n - 2)
next_edge = array("i", [0]) * (2 * n - 2)
edge_count = 0


def add_edge(u, v):
    global edge_count
    to[edge_count] = v
    next_edge[edge_count] = head[u]
    head[u] = edge_count
    edge_count += 1


for _ in range(n - 1):
    u, v = map(int, input().split())
    add_edge(u, v)
    add_edge(v, u)

parent = array("i", [0]) * (n + 1)
depth = array("i", [0]) * (n + 1)
depth[root] = 1
order = array("i", [root])
index = 0
while index < n:
    node = order[index]
    index += 1
    edge = head[node]
    while edge != -1:
        neighbor = to[edge]
        if neighbor != parent[node]:
            parent[neighbor] = node
            depth[neighbor] = depth[node] + 1
            order.append(neighbor)
        edge = next_edge[edge]

ancestors = [parent]
for _ in range(1, n.bit_length()):
    previous = ancestors[-1]
    ancestors.append(array("i", (previous[previous[node]] for node in range(n + 1))))


def lca(x, y):
    if depth[x] < depth[y]:
        x, y = y, x
    difference = depth[x] - depth[y]
    bit = 0
    while difference:
        if difference & 1:
            x = ancestors[bit][x]
        difference >>= 1
        bit += 1
    if x == y:
        return x
    for level in range(len(ancestors) - 1, -1, -1):
        if ancestors[level][x] != ancestors[level][y]:
            x = ancestors[level][x]
            y = ancestors[level][y]
    return parent[x]


output = sys.stdout.write
answers = []
for _ in range(queries):
    x, y = map(int, input().split())
    answers.append(str(lca(x, y)))
    if len(answers) == 8192:
        output("\n".join(answers) + "\n")
        answers.clear()
output("\n".join(answers))
