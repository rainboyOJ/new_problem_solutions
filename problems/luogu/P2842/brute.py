from collections import deque
import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n, w = data[0], data[1]
coins = data[2:2 + n]

INF = 10 ** 9
dist = [INF] * (w + 1)
dist[0] = 0
q = deque([0])
while q:
    cur = q.popleft()
    if cur == w:
        break
    for c in coins:
        nxt = cur + c
        if nxt <= w and dist[nxt] > dist[cur] + 1:
            dist[nxt] = dist[cur] + 1
            q.append(nxt)
print(dist[w])
