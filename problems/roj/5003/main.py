#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 15:54
# update_at: 2026-10-02 15:54

import sys


def min_cross_time(people: list[int]) -> int:
    """升序数组从最慢的一端贪心送人：返回全部过河的最少总耗时。"""
    total = 0
    l, r = 0, len(people) - 1          # 还没过河的人是 people[l..r]
    while r - l > 2:                   # 人数 > 3 才需要在两种送法间选择
        a, b = people[l], people[l + 1]     # 最快的两人
        c, d = people[r - 1], people[r]     # 最慢的两人
        # 护送两人：a,b 过河(b)、a 划回(a)、c,d 过河(d)、b 划回(b)
        # 单送一人：a,d 过河(d)、a 划回(a)；分两次单送走 c,d 合计 2a+c+d
        # 护送比连续单送便宜（2b < a+c）时才一次送走最慢两人
        if 2 * b < a + c:
            total += a + 2 * b + d
            r -= 2
        else:
            total += a + d
            r -= 1
    # 剩 3 人：a 带最慢的过河后划回、再带次慢的过去（a+b+c）；剩 1、2 人直接上船
    total += sum(people[l:r + 1]) if r - l == 2 else people[r]
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    people = sorted(next(data) for _ in range(n))
    print(min_cross_time(people))


if __name__ == "__main__":
    solve()
