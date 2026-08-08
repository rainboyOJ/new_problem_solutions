#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10000)
MOD = 10 ** 9 + 7
data = list(map(int, sys.stdin.buffer.read().split()))
n, V = data[0], data[1]
vols = data[2:]

def solve():
    cnt = 0
    def dfs(idx, cur):
        nonlocal cnt
        if cur == V:
            cnt = (cnt + 1) % MOD
            return
        if idx == n or cur > V:
            return
        v = vols[idx]
        max_k = (V - cur) // v
        for k in range(max_k + 1):
            dfs(idx + 1, cur + k * v)
    dfs(0, 0)
    return cnt

print(solve())
