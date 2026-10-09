#!/usr/bin/env python3
# Author: 2026-10-09 22:30

import sys

def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    a = []
    for i in range(1, n + 1):
        a.append(int(input_data[i]))
    
    a.sort(reverse=True)
    
    ans = 0
    for i in range(n):
        if a[i] >= i:
            ans = i + 1
        else:
            break
            
    print(ans)

if __name__ == '__main__':
    solve()
