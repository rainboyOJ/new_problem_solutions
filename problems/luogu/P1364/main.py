import sys
from collections import deque


input = sys.stdin.buffer.readline
n = int(input())
population = [0] * (n + 1)
tree = [[] for _ in range(n + 1)]

for node in range(1, n + 1):
    weight, left, right = map(int, input().split())
    population[node] = weight
    for child in (left, right):
        if child:
            tree[node].append(child)
            tree[child].append(node)


def total_distance(start):
    distance = [-1] * (n + 1)
    distance[start] = 0
    queue = deque([start])
    total = 0
    while queue:
        node = queue.popleft()
        total += population[node] * distance[node]
        for neighbor in tree[node]:
            if distance[neighbor] == -1:
                distance[neighbor] = distance[node] + 1
                queue.append(neighbor)
    return total


print(min(map(total_distance, range(1, n + 1))))
