import sys
from array import array


input = sys.stdin.buffer.readline
n, queries = map(int, input().split())
breeds = b" " + input().strip()
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

parent = array("i", [0]) * (n + 1)
depth = array("i", [0]) * (n + 1)
prefix_g = array("i", [0]) * (n + 1)
order = array("i", [1])
depth[1] = 1
prefix_g[1] = breeds[1] == 71
for node in order:
    for neighbor in graph[node]:
        if neighbor != parent[node]:
            parent[neighbor] = node
            depth[neighbor] = depth[node] + 1
            prefix_g[neighbor] = prefix_g[node] + (breeds[neighbor] == 71)
            order.append(neighbor)

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


answer = bytearray()
for _ in range(queries):
    x, y, breed = input().split()
    x, y = int(x), int(y)
    ancestor = lca(x, y)
    g_count = prefix_g[x] + prefix_g[y] - 2 * prefix_g[ancestor] + (breeds[ancestor] == 71)
    path_length = depth[x] + depth[y] - 2 * depth[ancestor] + 1
    answer.append(49 if (g_count if breed == b'G' else path_length - g_count) else 48)
sys.stdout.write(answer.decode())
