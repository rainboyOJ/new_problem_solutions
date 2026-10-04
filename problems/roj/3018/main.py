#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:26
# update_at: 2026-10-01 10:26

import sys
from heapq import heappop, heappush


def max_satisfied(cows: list[tuple[int, int]], bottles: list[tuple[int, int]]) -> int:
    """按 SPF 从小到大发放防晒霜，每个强度下优先喂给 maxSPF 最小（最快过期）的奶牛。

    左端点不足的奶牛晚点才进入待选池，所以扫描 SPF 时把它们按 minSPF 逐个入堆，
    堆按 maxSPF 排序：堆顶一旦连当前 SPF 都够不到，就再也用不上任何防晒霜了。
    """
    pending: list[int] = []  # 待选奶牛的 maxSPF，堆顶是其中最急的一头
    next_cow = 0             # 下一头等待进入待选池的奶牛下标
    ans = 0
    for spf, cover in bottles:
        while next_cow < len(cows) and cows[next_cow][0] <= spf:  # minSPF 已到，可以接受这瓶
            heappush(pending, cows[next_cow][1])
            next_cow += 1
        while pending and pending[0] < spf:  # 堆顶这头牛的 maxSPF 已经过期，彻底放弃
            heappop(pending)
        while cover > 0 and pending:  # 同强度的每一瓶都给当前最快过期的奶牛
            heappop(pending)
            cover -= 1
            ans += 1
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    C, L = next(data), next(data)

    cows = sorted((next(data), next(data)) for _ in range(C))     # 按 minSPF 升序，配合扫描依次入堆
    bottles = sorted((next(data), next(data)) for _ in range(L))  # 按 SPF 升序依次发放

    print(max_satisfied(cows, bottles))


if __name__ == "__main__":
    solve()
