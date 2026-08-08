import sys
from array import array


input = sys.stdin.buffer.readline
n = int(input())
graph = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v, weight = map(int, input().split())
    u -= 1
    v -= 1
    graph[u].append((v, weight))
    graph[v].append((u, weight))

xor_from_root = array("I", [0]) * n
stack = [(0, -1)]
while stack:
    node, parent = stack.pop()
    for neighbor, weight in graph[node]:
        if neighbor != parent:
            xor_from_root[neighbor] = xor_from_root[node] ^ weight
            stack.append((neighbor, node))
del graph, stack

child_zero = array("i", [0])
child_one = array("i", [0])


def insert(value):
    node = 0
    for bit in range(30, -1, -1):
        children = child_one if value >> bit & 1 else child_zero
        if not children[node]:
            children[node] = len(child_zero)
            child_zero.append(0)
            child_one.append(0)
        node = children[node]


def maximum_xor(value):
    node = answer = 0
    for bit in range(30, -1, -1):
        wanted = child_zero if value >> bit & 1 else child_one
        other = child_one if value >> bit & 1 else child_zero
        if wanted[node]:
            answer |= 1 << bit
            node = wanted[node]
        else:
            node = other[node]
    return answer


insert(0)
answer = 0
for value in xor_from_root[1:]:
    answer = max(answer, maximum_xor(value))
    insert(value)
print(answer)
