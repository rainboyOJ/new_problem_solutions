#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10000)
MOD = 10 ** 9 + 7
data = list(map(int, sys.stdin.buffer.read().split()))
n, V = data[0], data[1]
vols = data[2:]

def solve():
    cnt = 0
    def dfs(cur):
        nonlocal cnt
        if cur == V:
            cnt = (cnt + 1) % MOD
            return
        for v in vols:
            if cur + v <= V:
                dfs(cur + v)
    dfs(0)
    return cnt

print(solve())
