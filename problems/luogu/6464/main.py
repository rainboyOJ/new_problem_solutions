import sys


input = sys.stdin.buffer.readline
n, edges = map(int, input().split())
infinity = 10**18
distance = [[infinity] * n for _ in range(n)]
for node in range(n):
    distance[node][node] = 0
for _ in range(edges):
    u, v, weight = map(int, input().split())
    u -= 1
    v -= 1
    distance[u][v] = distance[v][u] = weight
for middle in range(n):
    through = distance[middle]
    for start in range(n):
        row = distance[start]
        base = row[middle]
        for end in range(n):
            row[end] = min(row[end], base + through[end])

answer = infinity
for first in range(n):
    from_first = distance[first]
    for second in range(first + 1, n):
        from_second = distance[second]
        total = 0
        for x in range(n):
            row = distance[x]
            for y in range(x + 1, n):
                total += min(row[y], row[first] + from_second[y], row[second] + from_first[y])
        answer = min(answer, total)
print(answer)
