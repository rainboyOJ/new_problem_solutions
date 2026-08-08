n = int(input())
win = set(map(int, input().split()))
ans = [0] * 7
for _ in range(n):
    hit = len(win & set(map(int, input().split())))
    if hit:
        ans[7 - hit] += 1
print(*ans)
