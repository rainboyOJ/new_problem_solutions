import sys

data = list(map(int, sys.stdin.buffer.read().split()))
N = data[0]
blocks = []
idx = 1
for _ in range(N):
    h, a, c = data[idx], data[idx + 1], data[idx + 2]
    idx += 3
    blocks.append((a, h, c))

blocks.sort()

best = 0

def dfs(i, cur_h):
    global best
    if i == N:
        best = max(best, cur_h)
        return
    a, h, c = blocks[i]
    dfs(i + 1, cur_h)
    for k in range(1, c + 1):
        nh = cur_h + k * h
        if nh <= a:
            dfs(i + 1, nh)

dfs(0, 0)
print(best)
