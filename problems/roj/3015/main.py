#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:13
# update_at: 2026-10-01 10:13

import sys
from collections.abc import Iterator


def merge_count(a: list[int], buf: list[int], lo: int, mid: int, hi: int) -> int:
    """合并有序的 a[lo:mid] 与 a[mid:hi]，返回跨中线的逆序对数，并就地排好。"""
    buf[lo:hi] = a[lo:hi]
    i, j, cross = lo, mid, 0
    for k in range(lo, hi):
        if j >= hi or (i < mid and buf[i] <= buf[j]):
            a[k] = buf[i]
            i += 1
        else:
            a[k] = buf[j]
            j += 1
            cross += mid - i  # buf[j] 跳过的是右半还在等待的所有左半元素
    return cross


def inversions(a: list[int], lo: int, hi: int, buf: list[int]) -> int:
    """统计 a[lo:hi] 的逆序对数：左内部 + 右内部 + 跨中线，归并排序一趟完成。"""
    if hi - lo <= 1:
        return 0
    mid = (lo + hi) // 2
    return inversions(a, lo, mid, buf) + inversions(a, mid, hi, buf) \
        + merge_count(a, buf, lo, mid, hi)


def answers(tokens: Iterator[int]) -> Iterator[str]:
    """依次处理每个用例，产出每个序列的最小交换次数。"""
    for n in tokens:
        if n == 0:  # 终止用例
            return
        a = [next(tokens) for _ in range(n)]
        yield str(inversions(a, 0, n, [0] * n))


def solve() -> None:
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    print('\n'.join(answers(tokens)))


if __name__ == "__main__":
    solve()
