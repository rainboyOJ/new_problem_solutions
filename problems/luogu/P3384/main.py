import sys


sys.setrecursionlimit(1_000_000)
input = sys.stdin.buffer.readline
n, operations, root, modulus = map(int, input().split())
values = [0] + list(map(int, input().split()))
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

parent = [0] * (n + 1)
depth = [0] * (n + 1)
order = [root]
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
chains = [(root, root)]
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

tree = [0] * (4 * n)
lazy = [0] * (4 * n)


base = [0] * (n + 1)
for node in range(1, n + 1):
    base[dfn[node]] = values[node] % modulus


def build_fast(node, left, right):
    if left == right:
        tree[node] = base[left]
        return
    middle = (left + right) // 2
    build_fast(node * 2, left, middle)
    build_fast(node * 2 + 1, middle + 1, right)
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % modulus


def apply(node, length, value):
    tree[node] = (tree[node] + length * value) % modulus
    lazy[node] = (lazy[node] + value) % modulus


def push(node, left, right):
    if lazy[node] and left != right:
        middle = (left + right) // 2
        apply(node * 2, middle - left + 1, lazy[node])
        apply(node * 2 + 1, right - middle, lazy[node])
        lazy[node] = 0


def update(node, left, right, query_left, query_right, value):
    if query_left <= left and right <= query_right:
        apply(node, right - left + 1, value)
        return
    push(node, left, right)
    middle = (left + right) // 2
    if query_left <= middle:
        update(node * 2, left, middle, query_left, query_right, value)
    if middle < query_right:
        update(node * 2 + 1, middle + 1, right, query_left, query_right, value)
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % modulus


def query(node, left, right, query_left, query_right):
    if query_left <= left and right <= query_right:
        return tree[node]
    push(node, left, right)
    middle = (left + right) // 2
    answer = 0
    if query_left <= middle:
        answer += query(node * 2, left, middle, query_left, query_right)
    if middle < query_right:
        answer += query(node * 2 + 1, middle + 1, right, query_left, query_right)
    return answer % modulus


build_fast(1, 1, n)


def path_update(x, y, value):
    while top[x] != top[y]:
        if depth[top[x]] < depth[top[y]]:
            x, y = y, x
        update(1, 1, n, dfn[top[x]], dfn[x], value)
        x = parent[top[x]]
    if depth[x] > depth[y]:
        x, y = y, x
    update(1, 1, n, dfn[x], dfn[y], value)


def path_query(x, y):
    answer = 0
    while top[x] != top[y]:
        if depth[top[x]] < depth[top[y]]:
            x, y = y, x
        answer += query(1, 1, n, dfn[top[x]], dfn[x])
        x = parent[top[x]]
    if depth[x] > depth[y]:
        x, y = y, x
    return (answer + query(1, 1, n, dfn[x], dfn[y])) % modulus


answers = []
for _ in range(operations):
    operation = list(map(int, input().split()))
    if operation[0] == 1:
        path_update(operation[1], operation[2], operation[3] % modulus)
    elif operation[0] == 2:
        answers.append(str(path_query(operation[1], operation[2])))
    elif operation[0] == 3:
        update(1, 1, n, dfn[operation[1]], dfn[operation[1]] + subtree[operation[1]] - 1, operation[2] % modulus)
    else:
        answers.append(str(query(1, 1, n, dfn[operation[1]], dfn[operation[1]] + subtree[operation[1]] - 1)))
print("\n".join(answers))
