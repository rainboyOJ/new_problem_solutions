import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n, required_count = next(data), next(data)
required = [next(data) for _ in range(required_count)]
distance = [[next(data) for _ in range(n)] for __ in range(n)]
for middle in range(n):
    through = distance[middle]
    for start in range(n):
        row = distance[start]
        start_to_middle = row[middle]
        for end in range(n):
            row[end] = min(row[end], start_to_middle + through[end])
print(sum(distance[x - 1][y - 1] for x, y in zip(required, required[1:])))
