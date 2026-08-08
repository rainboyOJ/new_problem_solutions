import sys


input = sys.stdin.buffer.readline
n, operations = map(int, input().split())
children = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    parent, child = map(int, input().split())
    children[parent].append(child)

parent = [0] * (n + 1)
depth = [0] * (n + 1)
order = [1]
for node in order:
    for child in children[node]:
        parent[child] = node
        depth[child] = depth[node] + 1
        order.append(child)
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
        for child in children[node]:
            if child != heavy[node]:
                chains.append((child, child))
        node = heavy[node]

size = 1
while size < n:
    size <<= 1
segment = [0] * (2 * size)


def mark(node):
    position = size + dfn[node] - 1
    segment[position] = dfn[node]
    position //= 2
    while position:
        segment[position] = max(segment[position * 2], segment[position * 2 + 1])
        position //= 2


def range_max(left, right):
    left, right = left - 1 + size, right + size
    answer = 0
    while left < right:
        if left & 1:
            answer = max(answer, segment[left])
            left += 1
        if right & 1:
            right -= 1
            answer = max(answer, segment[right])
        left //= 2
        right //= 2
    return answer


mark(1)
answers = []
for _ in range(operations):
    operation, node = input().split()
    node = int(node)
    if operation == b'C':
        mark(node)
        continue
    while True:
        result = range_max(dfn[top[node]], dfn[node])
        if result:
            answers.append(str(inverse[result]))
            break
        node = parent[top[node]]
print("\n".join(answers))
