import sys


input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

parent = [0] * (n + 1)
depth = [0] * (n + 1)
order = [1]
for node in order:
    for neighbor in graph[node]:
        if neighbor != parent[node]:
            parent[neighbor] = node
            depth[neighbor] = depth[node] + 1
            order.append(neighbor)
subtree = [1] * (n + 1)
heavy = [0] * (n + 1)
for node in reversed(order[1:]):
    subtree[parent[node]] += subtree[node]
    if subtree[node] > subtree[heavy[parent[node]]]:
        heavy[parent[node]] = node
top = [0] * (n + 1)
dfn = [0] * (n + 1)
timer = 0
chains = [(1, 1)]
while chains:
    node, chain_top = chains.pop()
    while node:
        top[node] = chain_top
        timer += 1
        dfn[node] = timer
        for neighbor in graph[node]:
            if neighbor != parent[node] and neighbor != heavy[node]:
                chains.append((neighbor, neighbor))
        node = heavy[node]

bit = [0] * (n + 2)


def add(index, value):
    while index <= n:
        bit[index] += value
        index += index & -index


def prefix(index):
    result = 0
    while index:
        result += bit[index]
        index -= index & -index
    return result


def range_add(left, right, value):
    add(left, value)
    add(right + 1, -value)


def path_update(x, y):
    while top[x] != top[y]:
        if depth[top[x]] < depth[top[y]]:
            x, y = y, x
        range_add(dfn[top[x]], dfn[x], 1)
        x = parent[top[x]]
    if depth[x] > depth[y]:
        x, y = y, x
    if x != y:
        range_add(dfn[x] + 1, dfn[y], 1)


def edge_query(x, y):
    child = x if depth[x] > depth[y] else y
    return prefix(dfn[child])


answers = []
for _ in range(operations):
    operation, x, y = input().split()
    x, y = int(x), int(y)
    if operation == b'P':
        path_update(x, y)
    else:
        answers.append(str(edge_query(x, y)))
print("\n".join(answers))
