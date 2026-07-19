n, m = map(int, input().split())
a = [int(input()) for _ in range(n)]
window = answer = sum(a[:m])
for i in range(m, n):
    window += a[i] - a[i - m]
    answer = min(answer, window)
print(answer)
