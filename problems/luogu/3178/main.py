import sys


input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
values = [0] + list(map(int, input().split()))
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

bit1 = [0] * (n + 2)
bit2 = [0] * (n + 2)


def add(tree, index, value):
    while index <= n:
        tree[index] += value
        index += index & -index


def range_add(left, right, value):
    add(bit1, left, value)
    add(bit1, right + 1, -value)
    add(bit2, left, value * (1 - left))
    add(bit2, right + 1, value * right)


def prefix_sum(index):
    result1 = result2 = 0
    position = index
    while position:
        result1 += bit1[position]
        result2 += bit2[position]
        position -= position & -position
    return result1 * index + result2


def range_sum(left, right):
    return prefix_sum(right) - prefix_sum(left - 1)


for node in range(1, n + 1):
    range_add(dfn[node], dfn[node], values[node])


def root_path_sum(node):
    answer = 0
    while top[node] != top[1]:
        answer += range_sum(dfn[top[node]], dfn[node])
        node = parent[top[node]]
    return answer + range_sum(dfn[1], dfn[node])


answers = []
for _ in range(operations):
    operation = list(map(int, input().split()))
    node = operation[1]
    if operation[0] == 1:
        range_add(dfn[node], dfn[node], operation[2])
    elif operation[0] == 2:
        range_add(dfn[node], dfn[node] + subtree[node] - 1, operation[2])
    else:
        answers.append(str(root_path_sum(node)))
print("\n".join(answers))
