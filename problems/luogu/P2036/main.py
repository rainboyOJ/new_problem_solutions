from itertools import combinations

n = int(input())
ingredients = [tuple(map(int, input().split())) for _ in range(n)]

answer = None

for size in range(1, n + 1):
    for chosen in combinations(ingredients, size):
        sour = 1
        bitter = 0
        for s, b in chosen:
            sour *= s
            bitter += b
        difference = abs(sour - bitter)
        if answer is None or difference < answer:
            answer = difference

print(answer)
