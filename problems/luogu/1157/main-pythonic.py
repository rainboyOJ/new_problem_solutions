from itertools import combinations

n, r = map(int, input().split())

for chosen in combinations(range(1, n + 1), r):
    print("".join(f"{number:3d}" for number in chosen))
