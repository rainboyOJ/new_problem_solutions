import sys
from heapq import heappop, heappush


input = sys.stdin.buffer.readline
n, edges, free_limit = map(int, input().split())
start, target = map(int, input().split())
graph = [[] for _ in range(n)]
for _ in range(edges):
    u, v, price = map(int, input().split())
    graph[u].append((v, price))
    graph[v].append((u, price))

infinity = 10**30
distance = [[infinity] * n for _ in range(free_limit + 1)]
distance[0][start] = 0
heap = [(0, start, 0)]
while heap:
    current, node, used = heappop(heap)
    if current != distance[used][node]:
        continue
    for neighbor, price in graph[node]:
        candidate = current + price
        if candidate < distance[used][neighbor]:
            distance[used][neighbor] = candidate
            heappush(heap, (candidate, neighbor, used))
        if used < free_limit and current < distance[used + 1][neighbor]:
            distance[used + 1][neighbor] = current
            heappush(heap, (current, neighbor, used + 1))
print(min(layer[target] for layer in distance))
