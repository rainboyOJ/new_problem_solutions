from itertools import combinations


def pipe(x, *fs):
    for f in fs:
        x = f(x)
    return x


def is_opponent(x, y):
    return all(abs(a - b) <= 5 for a, b in zip(x, y)) and abs(sum(x) - sum(y)) <= 10


n = int(input())
students = [tuple(map(int, input().split())) for _ in range(n)]
answer = pipe(
    students,
    lambda xs: combinations(xs, 2),
    lambda pairs: sum(is_opponent(x, y) for x, y in pairs),
)
print(answer)
