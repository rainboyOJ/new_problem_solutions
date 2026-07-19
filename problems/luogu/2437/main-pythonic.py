m, n = map(int, input().split())
a = b = 1
for _ in range(n - m):
    a, b = b, a + b
print(a)
