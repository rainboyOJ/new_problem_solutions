x, n = map(int, input().split())
print(sum((x - 1 + i) % 7 < 5 for i in range(n)) * 250)
