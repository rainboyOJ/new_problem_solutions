#!/usr/bin/env python3
# 2026-10-09 18:30

import sys

def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    if n == 0:
        print(0)
        return
        
    a = [int(x) for x in input_data[1:n+1]]
    
    dp = {}
    ans = 0
    for x in a:
        dp[x] = dp.get(x - 1, 0) + 1
        if dp[x] > ans:
            ans = dp[x]
            
    print(ans)

if __name__ == '__main__':
    solve()