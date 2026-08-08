#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10000)
data = list(map(int, sys.stdin.buffer.read().split()))
n, V = data[0], data[1]
vols = data[2:]

def solve():
    def dfs(idx, cur):
        if cur == V:
            return True
        if idx == n or cur > V:
            return False
        v = vols[idx]
        max_k = (V - cur) // v
        for k in range(max_k + 1):
            if dfs(idx + 1, cur + k * v):
                return True
        return False
    return dfs(0, 0)

print("true" if solve() else "false")
