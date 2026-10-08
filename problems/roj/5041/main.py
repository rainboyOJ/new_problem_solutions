#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:55
# update_at: 2026-10-08 22:55

import sys


def bubble_sort(a: list[int]) -> None:
    """冒泡排序（降序），原地修改：题面显式要求冒泡，故不调用语言内置排序。"""
    n = len(a)
    for i in range(n - 1):          # 外层控制趟数
        for j in range(n - 1 - i):  # 每趟结束，末尾 i 个数已就位，内层范围收缩
            if a[j] < a[j + 1]:     # 降序：前一个数比后一个小就交换
                a[j], a[j + 1] = a[j + 1], a[j]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, 0)
    if n == 0:
        return

    a = [next(data) for _ in range(n)]

    bubble_sort(a)

    sys.stdout.write("\n".join(map(str, a)) + "\n")  # 题面要求每个数占一行


if __name__ == "__main__":
    solve()
