import sys
from heapq import heappop, heappush


input = sys.stdin.buffer.readline
n, edges, start = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(edges):
    u, v, weight = map(int, input().split())
    graph[u].append((v, weight))

infinity = 10**30
distance = [infinity] * (n + 1)
distance[start] = 0
heap = [(0, start)]
while heap:
    current, node = heappop(heap)
    if current != distance[node]:
        continue
    for neighbor, weight in graph[node]:
        candidate = current + weight
        if candidate < distance[neighbor]:
            distance[neighbor] = candidate
            heappush(heap, (candidate, neighbor))
print(*distance[1:])
