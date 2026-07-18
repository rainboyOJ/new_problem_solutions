n = int(input())
possible = [{0}] + [set() for _ in range(n)]

for total in range(1, n + 1):
    for parallel in range(1, total + 1):
        possible[total].update(
            intersections + parallel * (total - parallel)
            for intersections in possible[total - parallel]
        )

print(len(possible[n]))
