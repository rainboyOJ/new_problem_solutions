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
inverse = [0] * (n + 1)
timer = 0
chains = [(1, 1)]
while chains:
    node, chain_top = chains.pop()
    while node:
        top[node] = chain_top
        timer += 1
        dfn[node] = timer
        inverse[timer] = node
        for neighbor in graph[node]:
            if neighbor != parent[node] and neighbor != heavy[node]:
                chains.append((neighbor, neighbor))
        node = heavy[node]

size = 1
while size < n:
    size <<= 1
infinity = n + 1
segment = [infinity] * (2 * size)
black = bytearray(n + 1)


def toggle(node):
    black[node] ^= 1
    position = size + dfn[node] - 1
    segment[position] = dfn[node] if black[node] else infinity
    position //= 2
    while position:
        segment[position] = min(segment[position * 2], segment[position * 2 + 1])
        position //= 2


def range_min(left, right):
    left, right = left - 1 + size, right + size
    answer = infinity
    while left < right:
        if left & 1:
            answer = min(answer, segment[left])
            left += 1
        if right & 1:
            right -= 1
            answer = min(answer, segment[right])
        left //= 2
        right //= 2
    return answer


answers = []
for _ in range(operations):
    operation, node = map(int, input().split())
    if operation == 0:
        toggle(node)
        continue
    segments = []
    while top[node] != top[1]:
        segments.append((dfn[top[node]], dfn[node]))
        node = parent[top[node]]
    segments.append((dfn[1], dfn[node]))
    answer = infinity
    for left, right in reversed(segments):
        answer = range_min(left, right)
        if answer != infinity:
            break
    answers.append(str(-1 if answer == infinity else inverse[answer]))
print("\n".join(answers))
