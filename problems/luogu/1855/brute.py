import sys

data = sys.stdin.buffer.read().split()
n = int(data[0])
M = int(data[1])
T = int(data[2])

m = [0] * n
t = [0] * n
idx = 3
for i in range(n):
    m[i] = int(data[idx]); idx += 1
    t[i] = int(data[idx]); idx += 1

ans = 0

def dfs(i, money, time, cnt):
    global ans
    if money > M or time > T:
        return
    if cnt > ans:
        ans = cnt
    if i == n:
        return
    dfs(i + 1, money + m[i], time + t[i], cnt + 1)
    dfs(i + 1, money, time, cnt)

dfs(0, 0, 0, 0)
print(ans)
