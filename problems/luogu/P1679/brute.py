import sys
from math import isqrt

data = sys.stdin.buffer.read().split()
m = int(data[0])

p4 = []
i = 1
while True:
    v = i * i * i * i
    if v > m:
        break
    p4.append(v)
    i += 1

ans = m + 1

def dfs(idx, cnt, cur_sum):
    global ans
    if cnt >= ans:
        return
    if cur_sum == m:
        if cnt < ans:
            ans = cnt
        return
    if cur_sum > m or idx == len(p4):
        return
    for k in range((m - cur_sum) // p4[idx] + 1):
        dfs(idx + 1, cnt + k, cur_sum + k * p4[idx])

dfs(0, 0, 0)
print(ans)
