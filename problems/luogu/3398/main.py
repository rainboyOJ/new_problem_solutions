import sys
from array import array


input = sys.stdin.buffer.readline
n, queries = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

parent = array("i", [0]) * (n + 1)
depth = array("i", [0]) * (n + 1)
entry = array("i", [0]) * (n + 1)
leave = array("i", [0]) * (n + 1)
order = array("i", [1])
depth[1] = 1
for node in order:
    for neighbor in graph[node]:
        if neighbor != parent[node]:
            parent[neighbor] = node
            depth[neighbor] = depth[node] + 1
            order.append(neighbor)

# Build a real DFS preorder; unlike the parent-building BFS order, it makes
# every subtree a contiguous interval.
subtree = array("i", [1]) * (n + 1)
for node in reversed(order[1:]):
    subtree[parent[node]] += subtree[node]
preorder = []
stack = [1]
while stack:
    node = stack.pop()
    preorder.append(node)
    for neighbor in reversed(graph[node]):
        if neighbor != parent[node]:
            stack.append(neighbor)
for index, node in enumerate(preorder, 1):
    entry[node] = index
    leave[node] = index + subtree[node] - 1

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


def is_ancestor(x, y):
    return entry[x] <= entry[y] <= leave[x]


def on_path(node, x, y, ancestor):
    return is_ancestor(ancestor, node) and (is_ancestor(node, x) or is_ancestor(node, y))


answers = []
for _ in range(queries):
    a, b, c, d = map(int, input().split())
    ab, cd = lca(a, b), lca(c, d)
    candidates = (ab, cd, lca(a, c), lca(a, d), lca(b, c), lca(b, d))
    meet = any(on_path(node, a, b, ab) and on_path(node, c, d, cd) for node in candidates)
    answers.append('Y' if meet else 'N')
print("\n".join(answers))
