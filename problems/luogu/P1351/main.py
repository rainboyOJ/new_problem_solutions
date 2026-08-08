import sys


input = sys.stdin.buffer.readline
n = int(input())
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)
weight = [0] + list(map(int, input().split()))

maximum = total = 0
for neighbors in graph[1:]:
    if len(neighbors) < 2:
        continue
    first = second = 0
    neighbor_sum = square_sum = 0
    for neighbor in neighbors:
        value = weight[neighbor]
        neighbor_sum += value
        square_sum += value * value
        if value > first:
            first, second = value, first
        elif value > second:
            second = value
    maximum = max(maximum, first * second)
    total += neighbor_sum * neighbor_sum - square_sum
print(maximum, total % 10007)
