import sys
from collections import deque


input = sys.stdin.buffer.readline
n, constraints = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(constraints):
    left, right, limit = map(int, input().split())
    graph[right].append((left, limit))

distance = [0] * (n + 1)
edge_count = [0] * (n + 1)
in_queue = bytearray(b"\x01") * (n + 1)
queue = deque(range(1, n + 1))
possible = True
while queue and possible:
    node = queue.popleft()
    in_queue[node] = 0
    for neighbor, weight in graph[node]:
        candidate = distance[node] + weight
        if candidate < distance[neighbor]:
            distance[neighbor] = candidate
            edge_count[neighbor] = edge_count[node] + 1
            if edge_count[neighbor] >= n:
                possible = False
                break
            if not in_queue[neighbor]:
                queue.append(neighbor)
                in_queue[neighbor] = 1
print(*distance[1:]) if possible else print("NO")
