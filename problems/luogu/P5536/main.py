import sys
from collections import deque


input = sys.stdin.buffer.readline
n, core_count = map(int, input().split())
graph = [[] for _ in range(n + 1)]
degree = [0] * (n + 1)
for _ in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)
    degree[u] += 1
    degree[v] += 1

layer = [0] * (n + 1)
queue = deque()
for node in range(1, n + 1):
    if degree[node] <= 1:
        layer[node] = 1
        queue.append(node)
while queue:
    node = queue.popleft()
    for neighbor in graph[node]:
        if degree[neighbor] > 1:
            degree[neighbor] -= 1
            if degree[neighbor] == 1:
                layer[neighbor] = layer[node] + 1
                queue.append(neighbor)
print(sorted(layer[1:], reverse=True)[core_count])
