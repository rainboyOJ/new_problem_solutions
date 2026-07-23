#!/usr/bin/env python3
# brute.py: 暴力搜索所有合法删除序列，求最终最大 MEX
import sys
from itertools import product

def mex(arr):
    s = set(arr)
    x = 0
    while x in s:
        x += 1
    return x

def solve(a, k):
    n = len(a)
    # BFS: 状态 = 当前数组(tuple)，记录所有可达的终态
    from collections import deque
    start = tuple(a)
    q = deque([start])
    seen = {start}
    best = -1
    while q:
        cur = q.popleft()
        if len(cur) == k - 1:
            m = mex(cur)
            if m > best:
                best = m
            continue
        # 找所有长度 k 的窗口的 MEX
        wins = []
        for i in range(len(cur) - k + 1):
            wins.append(mex(cur[i:i+k]))
        max_mex = max(wins)
        # 从最大 MEX 的窗口中，枚举可删位置
        cand = set()
        for i in range(len(cur) - k + 1):
            if wins[i] == max_mex:
                for j in range(i, i + k):
                    cand.add(j)
        for j in sorted(cand):
            nxt = cur[:j] + cur[j+1:]
            if nxt not in seen:
                seen.add(nxt)
                q.append(nxt)
    return best

def main():
    data = sys.stdin.read().split()
    idx = 0
    t = int(data[idx]); idx += 1
    for _ in range(t):
        n, k = int(data[idx]), int(data[idx+1]); idx += 2
        a = [int(data[idx+i]) for i in range(n)]; idx += n
        print(solve(a, k))

if __name__ == "__main__":
    main()
