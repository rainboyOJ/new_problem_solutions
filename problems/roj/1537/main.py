#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:55
# update_at: 2026-09-30 16:55

import sys


def add(bit: list[int], i: int) -> None:
    """树状数组 bit 在下标 i 处 +1（下标 = 坐标 + 1）。"""
    while i < len(bit):
        bit[i] += 1
        i += i & -i


def count_le(bit: list[int], i: int) -> int:
    """树状数组 bit 中下标不超过 i 的个数，即坐标不超过 i - 1 的个数。"""
    s = 0
    while i:
        s += bit[i]
        i -= i & -i
    return s


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    road_len, m = next(data), next(data)

    ops: list[tuple[int, int, int]] = []
    for _ in range(m):
        k, l, r = next(data), next(data), next(data)
        ops.append((k, l, r))

    # 下标比坐标大 1（题面保证坐标 > 0），长度覆盖最大坐标 + 1 与向上更新的祖先下标
    size = max(road_len + 1, max(max(l, r) for _, l, r in ops) + 1) + 1
    by_left = [0] * size   # 按左端点计数：下标 i 对应左端点 i - 1
    by_right = [0] * size  # 按右端点计数：下标 i 对应右端点 i - 1

    out: list[str] = []
    for k, l, r in ops:
        if k == 1:  # 种树：这个新种类的段 [l, r] 登记到两棵计数树
            add(by_left, l + 1)
            add(by_right, r + 1)
        else:  # 询问：与 [l, r] 相交的段 = 左端点 <= r 的段 - 右端点 < l 的段
            intersect = count_le(by_left, r + 1) - count_le(by_right, l)
            out.append(str(intersect))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
