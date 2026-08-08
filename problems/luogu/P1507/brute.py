import sys

data = sys.stdin.buffer.read().split()
idx = 0
H = int(data[idx]); idx += 1
T = int(data[idx]); idx += 1
n = int(data[idx]); idx += 1

h = [0] * n
t = [0] * n
k = [0] * n
for i in range(n):
    h[i] = int(data[idx]); idx += 1
    t[i] = int(data[idx]); idx += 1
    k[i] = int(data[idx]); idx += 1

ans = 0

def dfs(i, v_sum, m_sum, cal):
    global ans
    if v_sum > H or m_sum > T:
        return
    if cal > ans:
        ans = cal
    if i == n:
        return
    dfs(i + 1, v_sum + h[i], m_sum + t[i], cal + k[i])
    dfs(i + 1, v_sum, m_sum, cal)

dfs(0, 0, 0, 0)
print(ans)
