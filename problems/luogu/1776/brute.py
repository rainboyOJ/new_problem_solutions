import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n, W = data[0], data[1]
items = []
idx = 2
for _ in range(n):
    v, w, m = data[idx], data[idx + 1], data[idx + 2]
    idx += 3
    items.append((v, w, m))

best = 0

def dfs(i, weight, value):
    global best
    if i == n:
        best = max(best, value)
        return
    v, w, m = items[i]
    for k in range(m + 1):
        nw = weight + k * w
        if nw > W:
            break
        dfs(i + 1, nw, value + k * v)

dfs(0, 0, 0)
print(best)
