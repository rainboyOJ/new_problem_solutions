n, m = map(int, input().split())
squares = sum((n - s + 1) * (m - s + 1) for s in range(1, min(n, m) + 1))
print(squares, n * (n + 1) * m * (m + 1) // 4 - squares)
