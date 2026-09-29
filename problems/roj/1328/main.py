#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:32
# update_at: 2026-09-30 05:32

import sys


def sort_count(seg: list[int]) -> tuple[list[int], int]:
    """归并排序同时数逆序对：返回 (有序序列, 段内逆序对数)。

    逆序对即下标递增而数值严格递减的数对；每次相邻交换恰好消除一个逆序对，
    且逆序对数是交换次数的下界，故最少交换次数就是逆序对总数。
    """
    if len(seg) < 2:
        return seg, 0
    mid = len(seg) // 2
    left, left_inv = sort_count(seg[:mid])
    right, right_inv = sort_count(seg[mid:])

    merged: list[int] = []
    inv = left_inv + right_inv
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:  # 相等时先取左半，保持稳定、不把相等计成逆序
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1
            inv += len(left) - i  # 左半剩余元素都比当前右半元素大，各配成一个逆序对
    merged += left[i:] + right[j:]
    return merged, inv


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    seq = [next(data) for _ in range(n)]
    print(sort_count(seq)[1])


if __name__ == "__main__":
    solve()
