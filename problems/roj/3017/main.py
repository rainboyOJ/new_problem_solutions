#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:25
# update_at: 2026-10-01 11:25

import sys
from operator import mul

INPUT = sys.stdin.buffer


def get_value(seg: list[int], m: int) -> int:
    """段的校验值：排序后最小的 k 个与最大的 k 个反向配对，平方差之和。

    k = min(m, len(seg)//2)。平方差之和用 (a²+b²-2ab) 展开，
    三段求和都走 map(mul, ...) 的 C 层循环，避免 Python 逐对循环。
    """
    seg.sort()
    k = min(m, len(seg) >> 1)
    small = seg[:k]
    large = seg[len(seg) - k:]  # 不能写 seg[-k:]：k=0 时它等于整段
    large.reverse()             # 第 i 小配第 i 大
    return (
        sum(map(mul, small, small))
        + sum(map(mul, large, large))
        - 2 * sum(map(mul, small, large))
    )


def solve() -> None:
    cases = int(INPUT.readline())
    out: list[str] = []

    for _ in range(cases):
        n, m, limit = map(int, INPUT.readline().split())
        A = list(map(int, INPUT.readline().split()))

        # 贪心从左到右切段：每段尽量长（前缀校验值随长度单调不减）。
        segments = 0
        left = 0
        while left < n:
            span = n - left
            lo, hi = 1, 2  # 单元素段校验值为 0，必可行
            # 倍增：长度 2,4,8,... 验证到失败或越界，lo 恒为已知可行长度
            while hi <= span and get_value(A[left:left + hi], m) <= limit:
                lo = hi
                hi <<= 1
            hi = min(hi, span)
            # 二分：在 (lo, hi] 内找最长可行长度
            while lo < hi:
                mid = (lo + hi + 1) >> 1
                if get_value(A[left:left + mid], m) <= limit:
                    lo = mid
                else:
                    hi = mid - 1
            left += lo
            segments += 1

        out.append(str(segments))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
