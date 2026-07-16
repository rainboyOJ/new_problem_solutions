import sys
from heapq import heappop, heappush


input = sys.stdin.buffer.readline
n, edges = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(edges):
    u, v, weight = map(int, input().split())
    graph[u].append((v, weight))
    graph[v].append((u, weight))

infinity = 10**30
shortest = [infinity] * (n + 1)
second = [infinity] * (n + 1)
shortest[1] = 0
heap = [(0, 1)]
while heap:
    current, node = heappop(heap)
    if current > second[node]:
        continue
    for neighbor, weight in graph[node]:
        candidate = current + weight
        if candidate < shortest[neighbor]:
            candidate, shortest[neighbor] = shortest[neighbor], candidate
            heappush(heap, (shortest[neighbor], neighbor))
        if shortest[neighbor] < candidate < second[neighbor]:
            second[neighbor] = candidate
            heappush(heap, (candidate, neighbor))
print(second[n])
