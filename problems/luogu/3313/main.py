import sys
from array import array


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
weight = [0] * (n + 1)
color = [0] * (n + 1)
for node in range(1, n + 1):
    weight[node], color[node] = map(int, input().split())
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
subtree[0] = 0
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

# Node 0 is the shared empty node. Each religion owns one root in the same
# dynamic segment-tree pool.
left_child = array("i", [0])
right_child = array("i", [0])
node_sum = array("q", [0])
node_max = array("i", [0])
roots = array("i", [0]) * 100_001


def new_node():
    left_child.append(0)
    right_child.append(0)
    node_sum.append(0)
    node_max.append(0)
    return len(left_child) - 1


def point_set(root, position, value):
    if root == 0:
        root = new_node()
    node = root
    left, right = 1, n
    path = []
    while left < right:
        path.append(node)
        middle = (left + right) // 2
        if position <= middle:
            if left_child[node] == 0:
                left_child[node] = new_node()
            node = left_child[node]
            right = middle
        else:
            if right_child[node] == 0:
                right_child[node] = new_node()
            node = right_child[node]
            left = middle + 1
    node_sum[node] = value
    node_max[node] = value
    for node in reversed(path):
        node_sum[node] = node_sum[left_child[node]] + node_sum[right_child[node]]
        node_max[node] = max(node_max[left_child[node]], node_max[right_child[node]])
    return root


def range_query(node, left, right, query_left, query_right):
    if node == 0:
        return 0, 0
    if query_left <= left and right <= query_right:
        return node_sum[node], node_max[node]
    middle = (left + right) // 2
    total = maximum = 0
    if query_left <= middle:
        total, maximum = range_query(left_child[node], left, middle, query_left, query_right)
    if middle < query_right:
        right_sum, right_max = range_query(right_child[node], middle + 1, right, query_left, query_right)
        total += right_sum
        maximum = max(maximum, right_max)
    return total, maximum


for node in range(1, n + 1):
    roots[color[node]] = point_set(roots[color[node]], dfn[node], weight[node])


def path_query(x, y, religion):
    total = maximum = 0
    root = roots[religion]
    while top[x] != top[y]:
        if depth[top[x]] < depth[top[y]]:
            x, y = y, x
        part_sum, part_max = range_query(root, 1, n, dfn[top[x]], dfn[x])
        total += part_sum
        maximum = max(maximum, part_max)
        x = parent[top[x]]
    if depth[x] > depth[y]:
        x, y = y, x
    part_sum, part_max = range_query(root, 1, n, dfn[x], dfn[y])
    return total + part_sum, max(maximum, part_max)


answers = []
for _ in range(operations):
    operation, x, value = input().split()
    x, value = int(x), int(value)
    if operation == b'CC':
        roots[color[x]] = point_set(roots[color[x]], dfn[x], 0)
        color[x] = value
        roots[color[x]] = point_set(roots[color[x]], dfn[x], weight[x])
    elif operation == b'CW':
        weight[x] = value
        roots[color[x]] = point_set(roots[color[x]], dfn[x], value)
    else:
        total, maximum = path_query(x, value, color[x])
        answers.append(str(total if operation == b'QS' else maximum))
print("\n".join(answers))
