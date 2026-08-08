import sys

data = sys.stdin.buffer.read().split()
s = int(data[0])

def divisor_sum(x):
    total = 0
    for d in range(1, x):
        if x % d == 0:
            total += d
    return total

val = [0] * (s + 1)
for i in range(1, s + 1):
    val[i] = divisor_sum(i)

ans = 0

def dfs(i, cur_sum, cur_val):
    global ans
    if i > s:
        if cur_val > ans:
            ans = cur_val
        return
    if cur_sum + i <= s:
        dfs(i + 1, cur_sum + i, cur_val + val[i])
    dfs(i + 1, cur_sum, cur_val)

dfs(1, 0, 0)
print(ans)
