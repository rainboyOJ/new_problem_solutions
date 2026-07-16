import sys
from array import array


input = sys.stdin.buffer.readline
n, plans = map(int, input().split())
head = array("i", [-1]) * (n + 1)
to = array("i", [0]) * (2 * n - 2)
next_edge = array("i", [0]) * (2 * n - 2)
edge_weight = array("i", [0]) * (2 * n - 2)
edge_count = 0


def add_edge(u, v, weight):
    global edge_count
    to[edge_count] = v
    edge_weight[edge_count] = weight
    next_edge[edge_count] = head[u]
    head[u] = edge_count
    edge_count += 1


for _ in range(n - 1):
    u, v, weight = map(int, input().split())
    add_edge(u, v, weight)
    add_edge(v, u, weight)

parent = array("i", [0]) * (n + 1)
depth = array("i", [0]) * (n + 1)
parent_weight = array("i", [0]) * (n + 1)
distance = array("q", [0]) * (n + 1)
order = array("i", [1])
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
            parent_weight[neighbor] = edge_weight[edge]
            distance[neighbor] = distance[node] + edge_weight[edge]
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


u_values = array("i")
v_values = array("i")
lengths = array("q")
right_bound = 0
for _ in range(plans):
    u, v = map(int, input().split())
    ancestor = lca(u, v)
    length = distance[u] + distance[v] - 2 * distance[ancestor]
    u_values.append(u)
    v_values.append(v)
    lengths.append(length)
    right_bound = max(right_bound, length)

diff = array("i", [0]) * (n + 1)


def feasible(limit):
    for i in range(1, n + 1):
        diff[i] = 0
    bad = 0
    need = 0
    for i, length in enumerate(lengths):
        if length > limit:
            bad += 1
            need = max(need, length - limit)
            u, v = u_values[i], v_values[i]
            ancestor = lca(u, v)
            diff[u] += 1
            diff[v] += 1
            diff[ancestor] -= 2
    if not bad:
        return True
    best_edge = 0
    for node in reversed(order[1:]):
        if diff[node] == bad:
            best_edge = max(best_edge, parent_weight[node])
        diff[parent[node]] += diff[node]
    return best_edge >= need


left, right = 0, right_bound
while left < right:
    middle = (left + right) // 2
    if feasible(middle):
        right = middle
    else:
        left = middle + 1
print(left)
