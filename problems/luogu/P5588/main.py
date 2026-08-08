import sys
from array import array


input = sys.stdin.buffer.readline
n = int(input())
colors = array("i", [0])
colors.extend(map(int, input().split()))
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
            order.append(neighbor)
        edge = next_edge[edge]
subtree = array("i", [1]) * (n + 1)
for node in reversed(order[1:]):
    subtree[parent[node]] += subtree[node]

ancestors = [parent]
for _ in range(1, n.bit_length()):
    previous = ancestors[-1]
    ancestors.append(array("i", (previous[previous[node]] for node in range(n + 1))))


def jump(node, steps):
    bit = 0
    while steps:
        if steps & 1:
            node = ancestors[bit][node]
        steps >>= 1
        bit += 1
    return node


def lca(x, y):
    if depth[x] < depth[y]:
        x, y = y, x
    x = jump(x, depth[x] - depth[y])
    if x == y:
        return x
    for level in range(len(ancestors) - 1, -1, -1):
        if ancestors[level][x] != ancestors[level][y]:
            x = ancestors[level][x]
            y = ancestors[level][y]
    return parent[x]


def distance(x, y):
    ancestor = lca(x, y)
    return depth[x] + depth[y] - 2 * depth[ancestor]


color_head = array("i", [0]) * (n + 1)
next_same = array("i", [0]) * (n + 1)
color_count = array("i", [0]) * (n + 1)
present_colors = array("i")
for node in range(1, n + 1):
    color = colors[node]
    if color_count[color] == 0:
        present_colors.append(color)
    next_same[node] = color_head[color]
    color_head[color] = node
    color_count[color] += 1
all_pairs = n * (n - 1) // 2
answer = array("q", [all_pairs]) * (n + 1)


def side_size(x, y):
    """Size of the component containing x after cutting the first edge x -> y."""
    ancestor = lca(x, y)
    if ancestor == x:
        child = jump(y, depth[y] - depth[x] - 1)
        return n - subtree[child]
    return subtree[x]


for color in present_colors:
    if color_count[color] == 1:
        x = color_head[color]
        excluded = (n - subtree[x]) * (n - subtree[x] - 1) // 2
        edge = head[x]
        while edge != -1:
            child = to[edge]
            if parent[child] == x:
                size = subtree[child]
                excluded += size * (size - 1) // 2
            edge = next_edge[edge]
        answer[color] = all_pairs - excluded
        continue
    first = color_head[color]
    second = first
    best_distance = -1
    node = first
    while node:
        current_distance = distance(first, node)
        if current_distance > best_distance:
            best_distance = current_distance
            second = node
        node = next_same[node]
    third = second
    best_distance = -1
    node = first
    while node:
        current_distance = distance(second, node)
        if current_distance > best_distance:
            best_distance = current_distance
            third = node
        node = next_same[node]
    diameter_length = distance(second, third)
    node = first
    lies_on_path = True
    while node:
        if distance(second, node) + distance(node, third) != diameter_length:
            lies_on_path = False
            break
        node = next_same[node]
    if lies_on_path:
        answer[color] = side_size(second, third) * side_size(third, second)
    else:
        answer[color] = 0

output = sys.stdout.write
buffer = []
for color in range(1, n + 1):
    buffer.append(str(answer[color]))
    if len(buffer) == 8192:
        output("\n".join(buffer) + "\n")
        buffer.clear()
output("\n".join(buffer))
