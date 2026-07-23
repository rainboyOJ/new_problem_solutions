#!/usr/bin/env python3
# greedy2.py: 新想法 — 统计数组中出现的 {0, 1, ..., k-2} 的不同值个数
import sys

def solve(a, k):
    present = set(a)
    ans = 0
    for v in range(k - 1):
        if v in present:
            ans += 1
        else:
            break
    return ans

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
