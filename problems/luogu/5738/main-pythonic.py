n, m = map(int, input().split())
best = 0.0

for _ in range(n):
    scores = list(map(int, input().split()))
    total = sum(scores) - max(scores) - min(scores)
    average = total / (m - 2)
    best = max(best, average)

print(f"{best:.2f}")
