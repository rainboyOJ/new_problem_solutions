#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:50
# update_at: 2026-10-01 12:47

import sys
from heapq import heappop, heappush


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)
    a = [next(data) for _ in range(m)]  # 按加入顺序排列的元素
    u = [next(data) for _ in range(n)]  # u[k]：第 k 次 GET 时盒内元素个数

    small: list[int] = []  # 存相反数的大根堆：始终恰好是"当前最小的 len(small) 个数"
    big: list[int] = []    # 小根堆：剩下的数
    out: list[str] = []
    added = 0  # 已经入盒的元素个数

    for k, need in enumerate(u, 1):
        while added < need:  # 补齐到第 k 次 GET 时的盒内元素个数
            x = a[added]
            added += 1
            if small and x < -small[0]:
                heappush(small, -x)  # x 比"已有最小数"的最大值还小，归入左侧
            else:
                heappush(big, x)
        while len(small) < k:            # 左侧不足 k 个：从右侧借最小的
            heappush(small, -heappop(big))
        while len(small) > k:            # 左侧超过 k 个：把最大的还回右侧
            heappush(big, -heappop(small))
        out.append(str(-small[0]))       # 左侧最大值就是第 k 小

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
