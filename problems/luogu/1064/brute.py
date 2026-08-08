import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n, m = data[0], data[1]
items = [None]
idx = 2
for i in range(1, m + 1):
    v, p, q = data[idx], data[idx + 1], data[idx + 2]
    idx += 3
    items.append((v, p, q))

attach = [[] for _ in range(m + 1)]
for i in range(1, m + 1):
    q = items[i][2]
    if q != 0:
        attach[q].append(i)

best = 0

def dfs(i, cost, value):
    global best
    if i > m:
        if cost <= n:
            best = max(best, value)
        return
    v, p, q = items[i]
    if q != 0:
        dfs(i + 1, cost, value)
        return
    dfs(i + 1, cost, value)
    if cost + v <= n:
        dfs(i + 1, cost + v, value + v * p)
        for at in attach[i]:
            va, pa, _ = items[at]
            if cost + v + va <= n:
                dfs(i + 1, cost + v + va, value + v * p + va * pa)
        if len(attach[i]) >= 2:
            va1, pa1, _ = items[attach[i][0]]
            va2, pa2, _ = items[attach[i][1]]
            if cost + v + va1 + va2 <= n:
                dfs(i + 1, cost + v + va1 + va2, value + v * p + va1 * pa1 + va2 * pa2)

dfs(1, 0, 0)
print(best)
