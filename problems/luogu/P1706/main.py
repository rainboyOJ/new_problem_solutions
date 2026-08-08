from itertools import permutations

n = int(input())

for order in permutations(range(1, n + 1)):
    print("".join(f"{number:5d}" for number in order))
