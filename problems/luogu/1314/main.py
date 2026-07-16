import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n, m, target = next(data), next(data), next(data)
weight = [0] * n
value = [0] * n
for i in range(n):
    weight[i], value[i] = next(data), next(data)
queries = [(next(data), next(data)) for _ in range(m)]


def evaluate(limit):
    count = [0] * (n + 1)
    total = [0] * (n + 1)
    c = s = 0
    for i, (w, v) in enumerate(zip(weight, value), 1):
        if w >= limit:
            c += 1
            s += v
        count[i] = c
        total[i] = s
    return sum(
        (count[r] - count[l - 1]) * (total[r] - total[l - 1])
        for l, r in queries
    )


left, right = 0, max(weight) + 2
while left < right:
    middle = (left + right) // 2
    if evaluate(middle) > target:
        left = middle + 1
    else:
        right = middle

print(min(abs(evaluate(limit) - target) for limit in {left, max(0, left - 1)}))
