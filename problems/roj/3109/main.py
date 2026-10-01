#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:40
# update_at: 2026-10-01 17:43

import sys


def prefix_less(seq: list[int], n: int) -> list[int]:
    """权值树状数组扫一遍：less[j] = seq[j] 前面（已扫过的部分）比它小的元素个数。

    传入 seq[::-1] 再翻转结果，就得到每个位置右侧比它小的个数，
    所以 V 与 ∧ 的四个计数只需要这一个函数。
    """
    tree = [0] * (n + 1)
    less: list[int] = []
    for value in seq:
        i = value - 1
        s = 0
        while i:                       # 前缀和 [1, value-1]：比 value 小的个数
            s += tree[i]
            i -= i & -i
        less.append(s)
        i = value                      # 把 value 插进树状数组
        while i <= n:
            tree[i] += 1
            i += i & -i
    return less


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]

    left = prefix_less(a, n)                 # left[j]：j 左侧比 a[j] 小的个数
    right = prefix_less(a[::-1], n)[::-1]    # right[j]：j 右侧比 a[j] 小的个数

    # 左侧更大的个数 = 左侧总数 j 减去左侧更小的；右侧同理，右侧总数是 n-1-j。
    # 与右侧部分做笛卡尔积，就分别是 V（左大右大）和 ∧（左小右小）的数目。
    print(sum((j - l) * (n - 1 - j - r) for j, (l, r) in enumerate(zip(left, right))),
          sum(l * r for l, r in zip(left, right)))


if __name__ == "__main__":
    solve()
