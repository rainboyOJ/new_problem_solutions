import sys
from collections import deque


input = sys.stdin.buffer.readline
answers = []
for _ in range(int(input())):
    n, descriptions = map(int, input().split())
    graph = [[] for _ in range(n + 1)]
    for __ in range(descriptions):
        u, v, weight = map(int, input().split())
        graph[u].append((v, weight))
        if weight >= 0:
            graph[v].append((u, weight))
    infinity = 10**30
    distance = [infinity] * (n + 1)
    edge_count = [0] * (n + 1)
    in_queue = bytearray(n + 1)
    distance[1] = 0
    queue = deque([1])
    in_queue[1] = 1
    negative_cycle = False
    while queue and not negative_cycle:
        node = queue.popleft()
        in_queue[node] = 0
        for neighbor, weight in graph[node]:
            candidate = distance[node] + weight
            if candidate < distance[neighbor]:
                distance[neighbor] = candidate
                edge_count[neighbor] = edge_count[node] + 1
                if edge_count[neighbor] >= n:
                    negative_cycle = True
                    break
                if not in_queue[neighbor]:
                    queue.append(neighbor)
                    in_queue[neighbor] = 1
    answers.append("YES" if negative_cycle else "NO")
print("\n".join(answers))
