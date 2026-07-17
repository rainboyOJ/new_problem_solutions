from itertools import combinations

n = int(input())
students = [tuple(map(int, input().split())) for _ in range(n)]

answer = sum(
    all(abs(a - b) <= 5 for a, b in zip(x, y)) and abs(sum(x) - sum(y)) <= 10
    for x, y in combinations(students, 2)
)
print(answer)
