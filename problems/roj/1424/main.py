#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
from math import sqrt


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, L, W = next(data), next(data), next(data)
        half = W / 2

        # 每个喷头映射成中心线上的有效区间 [l, r]：半径盖不到半宽的喷头无效
        spans: list[tuple[float, float]] = []
        for _ in range(n):
            pos, radius = next(data), next(data)
            ok = radius > half                      # radius == half 时区间退化为点，盖不了长度
            if ok:
                reach = sqrt(radius * radius - half * half)  # 有效覆盖半长（勾股定理）
                spans.append((pos - reach, pos + reach))

        # 经典区间覆盖贪心：区间按左端排序，从起点 cur 出发，反复取
        # "左端不超过 cur 的区间中右端最远者"，跳不到就输出 -1
        spans.sort()
        count, cur, i = 0, 0.0, 0
        n = len(spans)
        while cur < L:
            # 单轮扩展：左端 <= cur 的候选里选最远右端；i 跳过上一轮已完全落在 cur 左侧的区间
            far, j = cur, i
            while j < n and spans[j][0] <= cur:
                far = max(far, spans[j][1])
                j += 1
            if j == i or far <= cur:              # 没有区间能从 cur 继续向前推进
                break
            count += 1
            cur, i = far, j

        out.append(str(count if cur >= L else -1))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
