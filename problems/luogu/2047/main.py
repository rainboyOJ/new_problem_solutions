import sys


input = sys.stdin.buffer.readline
n, edges = map(int, input().split())
infinity = 10**18
distance = [[infinity] * n for _ in range(n)]
paths = [[0] * n for _ in range(n)]
for node in range(n):
    distance[node][node] = 0
for _ in range(edges):
    u, v, weight = map(int, input().split())
    u -= 1
    v -= 1
    distance[u][v] = distance[v][u] = weight
    paths[u][v] = paths[v][u] = 1
for middle in range(n):
    for start in range(n):
        if start == middle:
            continue
        for end in range(n):
            if end == middle or start == end:
                continue
            candidate = distance[start][middle] + distance[middle][end]
            if candidate < distance[start][end]:
                distance[start][end] = candidate
                paths[start][end] = paths[start][middle] * paths[middle][end]
            elif candidate == distance[start][end]:
                paths[start][end] += paths[start][middle] * paths[middle][end]
for node in range(n):
    importance = 0.0
    for start in range(n):
        if start == node:
            continue
        for end in range(n):
            if end != node and end != start and distance[start][end] == distance[start][node] + distance[node][end]:
                importance += paths[start][node] * paths[node][end] / paths[start][end]
    print(f"{importance:.3f}")
