import sys


input = sys.stdin.buffer.readline
n, edges = map(int, input().split())
ready = list(map(int, input().split()))
infinity = 10**18
distance = [[infinity] * n for _ in range(n)]
for node in range(n):
    distance[node][node] = 0
for _ in range(edges):
    u, v, weight = map(int, input().split())
    distance[u][v] = distance[v][u] = weight

activated = 0
answers = []
for _ in range(int(input())):
    start, end, time = map(int, input().split())
    while activated < n and ready[activated] <= time:
        middle = activated
        through = distance[middle]
        for x in range(n):
            row = distance[x]
            base = row[middle]
            for y in range(n):
                row[y] = min(row[y], base + through[y])
        activated += 1
    value = distance[start][end]
    answers.append(str(value if ready[start] <= time and ready[end] <= time and value < infinity else -1))
print("\n".join(answers))
