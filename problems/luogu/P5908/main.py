import sys
from collections import deque


input = sys.stdin.buffer.readline
n, limit = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

distance = [-1] * (n + 1)
distance[1] = 0
queue = deque([1])
answer = 0
while queue:
    node = queue.popleft()
    if distance[node] == limit:
        continue
    for neighbor in graph[node]:
        if distance[neighbor] == -1:
            distance[neighbor] = distance[node] + 1
            answer += 1
            queue.append(neighbor)
print(answer)
