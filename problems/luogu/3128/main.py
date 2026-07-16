import sys
from array import array


input = sys.stdin.buffer.readline
n, path_count = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

parent = array("i", [0]) * (n + 1)
depth = array("i", [0]) * (n + 1)
depth[1] = 1
order = array("i", [1])
for node in order:
    for neighbor in graph[node]:
        if neighbor != parent[node]:
            parent[neighbor] = node
            depth[neighbor] = depth[node] + 1
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


difference = [0] * (n + 1)
for _ in range(path_count):
    start, end = map(int, input().split())
    ancestor = lca(start, end)
    difference[start] += 1
    difference[end] += 1
    difference[ancestor] -= 1
    difference[parent[ancestor]] -= 1

answer = 0
for node in reversed(order):
    answer = max(answer, difference[node])
    difference[parent[node]] += difference[node]
print(answer)
