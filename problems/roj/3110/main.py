#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:40
# update_at: 2026-10-01 17:54

import sys
from collections.abc import Iterator

ADD = b"C"  # 区间加指令 C l r d；询问指令是 "Q"，题面写 "Q X"（单点值），评测数据写 "Q l r"（区间和）


def bit_add(bit: list[int], i: int, delta: int, limit: int) -> None:
    """在下标 i 处加 delta：沿 i += i & -i 上溯，更新所有覆盖 i 的结点。"""
    while i <= limit:
        bit[i] += delta
        i += i & -i


def bit_sum(bit: list[int], i: int) -> int:
    """求 bit 维护序列的前 i 项和：沿 i -= i & -i 下跳，把沿途结点累加。"""
    total = 0
    while i > 0:
        total += bit[i]
        i -= i & -i
    return total


def range_add(bit1: list[int], bit2: list[int], n: int, l: int, r: int, delta: int) -> None:
    """把 [l, r] 整体加 delta：差分序列上只需改 d[l] 和 d[r+1] 两个位置。

    bit1 维护 d[i]，bit2 维护 i·d[i]。r = n 时 d[n+1] 落在序列之外，
    差分本来到这里就结束了，不必也不能记录。
    """
    bit_add(bit1, l, delta, n)
    bit_add(bit2, l, delta * l, n)
    if r < n:
        bit_add(bit1, r + 1, -delta, n)
        bit_add(bit2, r + 1, -delta * (r + 1), n)


def prefix_sum(bit1: list[int], bit2: list[int], x: int) -> int:
    """求 A[1..x] 的和。

    交换求和次序：Σ_{i≤x} A[i] = Σ_{i≤x} Σ_{j≤i} d[j] = Σ_{j≤x} d[j]·(x-j+1)
    = (x+1)·Σ d[j] - Σ j·d[j]；两个和式分别由 bit1、bit2 查询得到。
    """
    return (x + 1) * bit_sum(bit1, x) - bit_sum(bit2, x)


def solve() -> None:
    stdin = sys.stdin.buffer
    # 按行切分并滤掉空行：bytes.split 无参切分与 line.split() 等价，用 map 只需切一次。
    lines: Iterator[list[bytes]] = (parts for parts in map(bytes.split, stdin) if parts)

    n, m = map(int, next(lines))

    bit1 = [0] * (n + 2)  # 差分数组 d 的树状数组
    bit2 = [0] * (n + 2)  # i·d[i] 的树状数组

    values: list[int] = []
    while len(values) < n:  # 数列可能被折成多行，读满 n 个数为止
        values += map(int, next(lines))

    prev = 0  # 前一个数，用来就地算差分 d[i] = A[i] - A[i-1]（A[0] 视作 0）
    for i, value in enumerate(values, 1):
        diff = value - prev
        prev = value
        bit_add(bit1, i, diff, n)
        bit_add(bit2, i, diff * i, n)

    out: list[str] = []
    for _ in range(m):
        parts = next(lines)
        op, left = parts[0], int(parts[1])
        if op == ADD:
            right, delta = int(parts[2]), int(parts[3])
            range_add(bit1, bit2, n, left, right, delta)
        else:  # 单点询问少一个操作数，取 right = left 就退化成区间和 [x, x]
            right = int(parts[2]) if len(parts) > 2 else left
            out.append(str(prefix_sum(bit1, bit2, right) - prefix_sum(bit1, bit2, left - 1)))

    sys.stdout.write('\n'.join(out) + '\n' if out else '')


if __name__ == "__main__":
    solve()
