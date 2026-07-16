import sys
from collections import deque


input = sys.stdin.buffer.readline
n, roads = map(int, input().split())
price = [0] + list(map(int, input().split()))
graph = [[] for _ in range(n + 1)]
for _ in range(roads):
    x, y, kind = map(int, input().split())
    graph[x].append(y)
    if kind == 2:
        graph[y].append(x)

infinity = 10**9
minimum = [infinity] * (n + 1)
profit = [-1] * (n + 1)
in_queue = bytearray(n + 1)
minimum[1] = price[1]
profit[1] = 0
queue = deque([1])
in_queue[1] = 1
while queue:
    node = queue.popleft()
    in_queue[node] = 0
    for neighbor in graph[node]:
        next_minimum = min(minimum[node], price[neighbor])
        next_profit = max(profit[node], price[neighbor] - minimum[node])
        if next_minimum < minimum[neighbor] or next_profit > profit[neighbor]:
            minimum[neighbor] = min(minimum[neighbor], next_minimum)
            profit[neighbor] = max(profit[neighbor], next_profit)
            if not in_queue[neighbor]:
                queue.append(neighbor)
                in_queue[neighbor] = 1
print(profit[n])
