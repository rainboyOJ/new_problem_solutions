import sys


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n = int(input())
prices = [0] + list(map(int, input().split()))
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

minimum = [0] * (4 * n)
maximum = [0] * (4 * n)
forward = [0] * (4 * n)
backward = [0] * (4 * n)
lazy = [0] * (4 * n)
base = [0] * (n + 1)
for node in range(1, n + 1):
    base[dfn[node]] = prices[node]


def pull(node):
    left, right = node * 2, node * 2 + 1
    minimum[node] = min(minimum[left], minimum[right])
    maximum[node] = max(maximum[left], maximum[right])
    forward[node] = max(forward[left], forward[right], maximum[right] - minimum[left])
    backward[node] = max(backward[left], backward[right], maximum[left] - minimum[right])


def build(node, left, right):
    if left == right:
        minimum[node] = maximum[node] = base[left]
        return
    middle = (left + right) // 2
    build(node * 2, left, middle)
    build(node * 2 + 1, middle + 1, right)
    pull(node)


def apply(node, value):
    minimum[node] += value
    maximum[node] += value
    lazy[node] += value


def push(node):
    if lazy[node]:
        apply(node * 2, lazy[node])
        apply(node * 2 + 1, lazy[node])
        lazy[node] = 0


def update(node, left, right, query_left, query_right, value):
    if query_left <= left and right <= query_right:
        apply(node, value)
        return
    push(node)
    middle = (left + right) // 2
    if query_left <= middle:
        update(node * 2, left, middle, query_left, query_right, value)
    if middle < query_right:
        update(node * 2 + 1, middle + 1, right, query_left, query_right, value)
    pull(node)


def merge(first, second):
    if first is None:
        return second
    if second is None:
        return first
    first_min, first_max, first_best, first_reverse = first
    second_min, second_max, second_best, second_reverse = second
    return (min(first_min, second_min), max(first_max, second_max),
            max(first_best, second_best, second_max - first_min),
            max(first_reverse, second_reverse, first_max - second_min))


def query(node, left, right, query_left, query_right):
    if query_left <= left and right <= query_right:
        return minimum[node], maximum[node], forward[node], backward[node]
    push(node)
    middle = (left + right) // 2
    result = None
    if query_left <= middle:
        result = query(node * 2, left, middle, query_left, query_right)
    if middle < query_right:
        result = merge(result, query(node * 2 + 1, middle + 1, right, query_left, query_right))
    return result


def reverse_info(info):
    return info[0], info[1], info[3], info[2]


build(1, 1, n)


def path_info(x, y):
    left_parts = []
    right_parts = []
    while top[x] != top[y]:
        if depth[top[x]] >= depth[top[y]]:
            left_parts.append(reverse_info(query(1, 1, n, dfn[top[x]], dfn[x])))
            x = parent[top[x]]
        else:
            right_parts.append(query(1, 1, n, dfn[top[y]], dfn[y]))
            y = parent[top[y]]
    if depth[x] >= depth[y]:
        left_parts.append(reverse_info(query(1, 1, n, dfn[y], dfn[x])))
    else:
        right_parts.append(query(1, 1, n, dfn[x], dfn[y]))
    result = None
    for info in left_parts:
        result = merge(result, info)
    for info in reversed(right_parts):
        result = merge(result, info)
    return result


query_count = int(input())
answers = []
for _ in range(query_count):
    x, y, increase = map(int, input().split())
    info = path_info(x, y)
    answers.append(str(max(0, info[2])))
    while top[x] != top[y]:
        if depth[top[x]] < depth[top[y]]:
            x, y = y, x
        update(1, 1, n, dfn[top[x]], dfn[x], increase)
        x = parent[top[x]]
    if depth[x] > depth[y]:
        x, y = y, x
    update(1, 1, n, dfn[x], dfn[y], increase)
print("\n".join(answers))
