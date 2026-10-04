#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys


def count_inversions(arr: list[int]) -> int:
    """求一维数组的逆序对总数。利用归并排序在 O(M log M) 时间内统计。"""
    temp = [0] * len(arr)

    def merge_sort(left: int, right: int) -> int:
        if left >= right:
            return 0
        mid = (left + right) // 2
        inv = merge_sort(left, mid) + merge_sort(mid + 1, right)
        i, j, k = left, mid + 1, left
        while i <= mid and j <= right:
            if arr[i] <= arr[j]:
                temp[k] = arr[i]
                i += 1
            else:
                temp[k] = arr[j]
                inv += mid - i + 1
                j += 1
            k += 1
        while i <= mid:
            temp[k] = arr[i]
            i += 1
            k += 1
        while j <= right:
            temp[k] = arr[j]
            j += 1
            k += 1
        arr[left : right + 1] = temp[left : right + 1]
        return inv

    return merge_sort(0, len(arr) - 1)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    for n in data:
        total_cells = n * n
        # 读取两个局面并忽略空格 0
        seq1 = [v for _ in range(total_cells) if (v := next(data)) != 0]
        seq2 = [v for _ in range(total_cells) if (v := next(data)) != 0]

        inv1 = count_inversions(seq1)
        inv2 = count_inversions(seq2)

        is_reachable = (inv1 & 1) == (inv2 & 1)
        out.append("TAK" if is_reachable else "NIE")

    print("\n".join(out))


if __name__ == "__main__":
    solve()
