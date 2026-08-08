n, m = map(int, input().split())
best = max(
    (sum(scores) - max(scores) - min(scores)) / (m - 2)
    for scores in (list(map(int, input().split())) for _ in range(n))
)
print(f'{best:.2f}')
