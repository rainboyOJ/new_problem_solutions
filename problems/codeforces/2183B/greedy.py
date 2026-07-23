#!/usr/bin/env python3
# greedy.py: 用户想法 — 扫描数组，从 0 开始凑 0,1,2,... 找 k-1 个数
# 看这样能不能覆盖 0..x-1 来最大化 MEX
import sys

def mex(arr):
    s = set(arr)
    x = 0
    while x in s:
        x += 1
    return x

def solve(a, k):
    n = len(a)
    # 贪心：从 0 开始，依次在数组中找 0, 1, 2, ...
    # 每找到一个就标记已用，直到凑够 k-1 个
    used = [False] * n
    found = 0
    target = 0
    while found < k - 1:
        # 在数组中找 target
        ok = False
        for i in range(n):
            if not used[i] and a[i] == target:
                used[i] = True
                found += 1
                target += 1
                ok = True
                break
        if not ok:
            # 找不到 target，停止
            break
    # 最终 MEX = target（因为 0..target-1 都找到了）
    return target

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
