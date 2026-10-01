#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:44
# update_at: 2026-10-01 10:44

import sys


def prefix_parity(groups: list[tuple[int, int, int]], x: int) -> int:
    """位置 x 及其左侧防具总数的奇偶性：1 表示唯一破绽落在 x 或其左侧。"""
    return sum(
        (min(e, x) - s) // d + 1 if x >= s else 0  # 该组在 [S, x] 区间内的件数
        for s, e, d in groups
    ) & 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n = next(data)
        groups = [(next(data), next(data), next(data)) for _ in range(n)]
        groups = [(s, e if d else s, d or 1) for s, e, d in groups]  # D=0 时退化为单点 S

        lo = min(s for s, _, _ in groups) - 1  # lo 左侧没有任何防具，奇偶性必为 0
        hi = max(e for _, e, _ in groups)
        if prefix_parity(groups, hi) == 0:
            out.append("There's no weakness.")  # 整条防线累计仍是偶数：没有破绽
            continue

        # 奇偶性在破绽 P 处由 0 翻转为 1，且之后恒为 1：二分找第一个翻转位置
        while hi - lo > 1:
            mid = (lo + hi) // 2
            if prefix_parity(groups, mid):
                hi = mid
            else:
                lo = mid
        p = hi

        # 每组等差数列至多在 p 处放一件，直接数出落在 p 上的组数即为该处件数
        count = sum(1 for s, e, d in groups if s <= p <= e and (p - s) % d == 0)
        out.append(f"{p} {count}")

    print("\n".join(out))


if __name__ == "__main__":
    solve()
