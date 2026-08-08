import sys

data = sys.stdin.buffer.read().decode().split()
ts_h, ts_m = map(int, data[0].split(':'))
te_h, te_m = map(int, data[1].split(':'))
n = int(data[2])

T = (te_h * 60 + te_m) - (ts_h * 60 + ts_m)

trees = []
idx = 3
for _ in range(n):
    t = int(data[idx])
    c = int(data[idx + 1])
    p = int(data[idx + 2])
    idx += 3
    trees.append((t, c, p))

best = 0

def dfs(i, time_left, value):
    global best
    if i == n:
        best = max(best, value)
        return
    t, c, p = trees[i]
    if p == 0:
        max_k = time_left // t
    else:
        max_k = min(p, time_left // t)
    for k in range(max_k + 1):
        dfs(i + 1, time_left - k * t, value + k * c)

dfs(0, T, 0)
print(best)
