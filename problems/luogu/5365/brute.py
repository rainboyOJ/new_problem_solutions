import sys

data = list(map(int, sys.stdin.buffer.read().split()))
N, M = data[0], data[1]
K = data[2:2 + N]
C = data[2 + N:2 + N + N]

limit = sum(K[i] * C[i] for i in range(N))

best = limit + 1

def dfs(i, cost, ways):
    global best
    if ways >= M:
        best = min(best, cost)
        return
    if i == N:
        return
    dfs(i + 1, cost, ways)
    for x in range(2, K[i] + 1):
        nc = cost + x * C[i]
        nw = ways * x
        if nw > M:
            nw = M
        dfs(i + 1, nc, nw)

dfs(0, 0, 1)
print(best)
