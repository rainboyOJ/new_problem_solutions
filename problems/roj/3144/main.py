#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:24
# update_at: 2026-10-01 20:24

import sys


def batch_sizes(count: int) -> list[int]:
    """把 count 枚同面值硬币拆成 1,2,4,... 枚的若干组，每组当作一件 0/1 物品。"""
    sizes: list[int] = []
    size = 1
    while count:
        take = min(size, count)  # 最后一组可能不满，用 min 一步收尾，不必单独判残留
        sizes.append(take)
        count -= take
        size <<= 1
    return sizes


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while True:
        n, m = next(data), next(data)
        if n == 0 and m == 0:  # 终止用例，不产生输出
            break
        values = [next(data) for _ in range(n)]
        counts = [next(data) for _ in range(n)]

        # 用一个大整数的第 s 位表示「面值 s 能被拼成」，第 0 位 = 空集。
        # 一组面值和 shift 的硬币就是一次整体左移；mask 保证只留下 0..m 位。
        reach: int = 1
        mask = (1 << (m + 1)) - 1
        for value, count in zip(values, counts):
            for take in batch_sizes(count):
                shift = value * take
                if shift <= m:  # 位移超过 m 的组只会落到 m 之外，对答案没有任何影响
                    reach |= reach << shift
                    reach &= mask

        out.append(str(reach.bit_count() - 1))  # 去掉第 0 位的空集

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
