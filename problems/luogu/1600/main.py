import sys
from array import array
from collections import defaultdict


input = sys.stdin.buffer.readline
n, players = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)
watch = [0] + list(map(int, input().split()))

parent = array("i", [0]) * (n + 1)
depth = array("i", [0]) * (n + 1)
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


events_up = defaultdict(list)
events_down = defaultdict(list)
offset = n + 2
for _ in range(players):
    start, end = map(int, input().split())
    ancestor = lca(start, end)
    events_up[start].append((depth[start], 1))
    if ancestor != 1:
        events_up[parent[ancestor]].append((depth[start], -1))
    key = depth[start] - 2 * depth[ancestor] + offset
    events_down[end].append((key, 1))
    events_down[ancestor].append((key, -1))

bucket_size = 2 * n + 5
count_up = array("i", [0]) * bucket_size
count_down = array("i", [0]) * bucket_size
answer = array("i", [0]) * (n + 1)
stack = []
key_up = depth[1] + watch[1]
key_down = watch[1] - depth[1] + offset
stack.append([1, 0, count_up[key_up], count_down[key_down]])
while stack:
    node, child_index, before_up, before_down = stack[-1]
    if child_index < len(graph[node]):
        neighbor = graph[node][child_index]
        stack[-1][1] += 1
        if neighbor == parent[node]:
            continue
        key_up = depth[neighbor] + watch[neighbor]
        key_down = watch[neighbor] - depth[neighbor] + offset
        stack.append([neighbor, 0, count_up[key_up], count_down[key_down]])
        continue
    for key, delta in events_up.get(node, ()):
        count_up[key] += delta
    for key, delta in events_down.get(node, ()):
        count_down[key] += delta
    key_up = depth[node] + watch[node]
    key_down = watch[node] - depth[node] + offset
    answer[node] = count_up[key_up] - before_up + count_down[key_down] - before_down
    stack.pop()

print(" ".join(map(str, answer[1:])))
