#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:21
# update_at: 2026-09-30 17:21

import sys
from collections.abc import Iterator


def build_st(a: list[int]) -> list[list[int]]:
    """ST 表：st[k][i] = a[i..i+2^k-1] 的最大值，由下一层两个半段合并。"""
    st = [a]
    span = 2  # 当前层区间长度
    while span <= len(a):
        prev = st[-1]
        half = span >> 1
        st.append([max(prev[i], prev[i + half]) for i in range(len(a) - span + 1)])
        span <<= 1
    return st


def query(st: list[list[int]], left: int, right: int) -> int:
    """回答闭区间 [left, right] 的最大值：两块可重叠的 2 的幂区间取 max。"""
    length = right - left + 1
    k = length.bit_length() - 1                      # 不超过区间长度的最大 2 的幂指数
    # 幂等的 max 允许重叠，两块并起来恰好盖住 [left, right]
    return max(st[k][left], st[k][right - (1 << k) + 1])


def solve() -> None:
    data: Iterator[int] = iter(map(int, sys.stdin.buffer.read().split()))
    count = next(data)                               # 数字个数 N
    values = [next(data) for _ in range(count)]
    ask_count = next(data)                           # 询问次数 M

    st = build_st(values)

    # 题目按 1-based 给出左右端点，依次减 1 转成 0-based 下标
    out = [str(query(st, next(data) - 1, next(data) - 1)) for _ in range(ask_count)]
    sys.stdout.write('\n'.join(out))


if __name__ == "__main__":
    solve()
