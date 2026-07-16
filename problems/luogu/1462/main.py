import sys
from heapq import heappop, heappush


input = sys.stdin.buffer.readline
n, edges, health = map(int, input().split())
fee = [0] + [int(input()) for _ in range(n)]
graph = [[] for _ in range(n + 1)]
for _ in range(edges):
    u, v, damage = map(int, input().split())
    graph[u].append((v, damage))
    graph[v].append((u, damage))


def feasible(limit):
    if fee[1] > limit or fee[n] > limit:
        return False
    infinity = health + 1
    distance = [infinity] * (n + 1)
    distance[1] = 0
    heap = [(0, 1)]
    while heap:
        current, node = heappop(heap)
        if current != distance[node]:
            continue
        if node == n:
            return True
        for neighbor, damage in graph[node]:
            candidate = current + damage
            if fee[neighbor] <= limit and candidate < distance[neighbor] and candidate <= health:
                distance[neighbor] = candidate
                heappush(heap, (candidate, neighbor))
    return False


fees = sorted(set(fee[1:]))
if not feasible(fees[-1]):
    print("AFK")
else:
    left, right = 0, len(fees) - 1
    while left < right:
        middle = (left + right) // 2
        if feasible(fees[middle]):
            right = middle
        else:
            left = middle + 1
    print(fees[left])
