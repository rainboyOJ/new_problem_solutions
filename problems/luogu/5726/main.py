n = int(input())
scores = list(map(int, input().split()))

total = sum(scores) - max(scores) - min(scores)
answer = total / (n - 2)

print(f"{answer:.2f}")
