import sys


input = sys.stdin.buffer.readline
n, edges = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(edges):
    u, v, weight = map(int, input().split())
    graph[u].append((v, weight))
    graph[v].append((u, weight))


def distances(start):
    distance = [-1] * (n + 1)
    distance[start] = 0
    order = [start]
    for node in order:
        for neighbor, weight in graph[node]:
            if distance[neighbor] == -1:
                distance[neighbor] = distance[node] + weight
                order.append(neighbor)
    return distance


from_one = distances(1)
first = max(range(1, n + 1), key=from_one.__getitem__)
from_first = distances(first)
second = max(range(1, n + 1), key=from_first.__getitem__)
from_second = distances(second)
print(from_first[second] + max(map(min, zip(from_first[1:], from_second[1:]))))
