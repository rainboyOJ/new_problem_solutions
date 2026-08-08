#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10000)
data = list(map(int, sys.stdin.buffer.read().split()))
n, V = data[0], data[1]
items = [(data[i], data[i + 1], data[i + 2]) for i in range(2, len(data), 3)]

best = 0
def dfs(idx, cur_w, cur_v):
    global best
    if idx == n:
        if cur_v > best:
            best = cur_v
        return
    v_i, w_i, s_i = items[idx]
    max_k = min(s_i, (V - cur_w) // v_i)
    for k in range(max_k + 1):
        dfs(idx + 1, cur_w + k * v_i, cur_v + k * w_i)

dfs(0, 0, 0)
print(best)
