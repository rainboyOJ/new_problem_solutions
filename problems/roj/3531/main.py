#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:39
# update_at: 2026-10-02 05:39

import sys


def next_permutation(a: list[int]) -> None:
    """原地求字典序的下一个排列：把排列当作数，做一次 +1。

    从右往左找第一个小于右邻的位置 i（其后缀是降序、已是后缀最大），
    再从右往左找第一个大于 a[i] 的 j 交换，最后把降序后缀反转成升序最小。
    """
    i = len(a) - 2
    while i >= 0 and a[i] >= a[i + 1]:
        i -= 1
    if i < 0:  # 已是全局最大排列；题面保证不会出现，兜底不动
        return
    j = len(a) - 1
    while a[j] <= a[i]:
        j -= 1
    a[i], a[j] = a[j], a[i]
    a[i + 1:] = a[:i:-1]  # 交换后后缀仍降序，反转即得最小后缀


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)  # 要加的小整数，相当于做 m 次"后继"
    a = [next(data) for _ in range(n)]

    for _ in range(m):  # M ≤ 100，逐次 +1 总计 O(N·M)
        next_permutation(a)

    print(' '.join(map(str, a)))


if __name__ == "__main__":
    solve()
