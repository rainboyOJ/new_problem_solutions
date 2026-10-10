#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:23
# update_at: 2026-10-07 17:23

import sys


def is_break(x: int, y: int) -> bool:
    """x 与 y 不是相差 1 的相邻整数就算一个断点（y 允许是虚拟的 n + 1）。"""
    return abs(x - y) != 1


def min_flips(a: list[int]) -> int:
    """把排列 a 翻成升序所需的最少前缀翻转次数（迭代加深 + 断点数估价）。

    断点数 = 在末尾补一个虚拟的 n+1 后，相邻两数差的绝对值不等于 1 的位置数。
    翻转前缀 1..i（i < n）只改动「块尾 a[i] 与后继 a[i+1]」这一处邻接；翻转整串
    则块内邻接全不变、只把末项换成原来的首项。两种情况下断点数都至多减 1，
    而升序排列的断点数为 0，所以它是剩余步数的可采纳下界。
    反过来断点数为 0 时内部邻接全好、序列单调，末项又是 n，只能是升序。
    """
    n = len(a)
    arr = a[:]
    h0 = sum(is_break(arr[i], arr[i + 1]) for i in range(n - 1)) + is_break(arr[-1], n + 1)

    def dfs(tot: int, last: int, h: int, limit: int) -> bool:
        """在 limit 步上限内搜索；h 为当前断点数，h 归零即已升序。"""
        if tot + h > limit:
            return False                       # 估价剪枝
        if h == 0:                             # 先剪枝再判达成：超限的升序不算解
            return True
        for i in range(2, n + 1):
            if i == last:
                continue                       # 连着翻同一长度 = 白翻一步
            head, tail = arr[0], arr[i - 1]    # 翻转后位置 i-1 变成原来的 arr[0]
            nh = h
            if i < n:                          # 只有 (arr[i-1], arr[i]) 这一处邻接会变
                nh += is_break(head, arr[i]) - is_break(tail, arr[i])
            else:                              # 翻整串：末项换成原来的首项
                nh += is_break(head, n + 1) - is_break(tail, n + 1)
            arr[:i] = arr[i - 1::-1]
            if dfs(tot + 1, i, nh, limit):
                return True
            arr[:i] = arr[i - 1::-1]           # 再翻同一前缀即还原
        return False

    limit = 0
    while not dfs(0, 0, h0, limit):            # 深度上限逐层加深，首个成功的就是答案
        limit += 1
    return limit


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    t = next(data)
    for _ in range(t):
        n = next(data)
        perm = [next(data) for _ in range(n)]
        out.append(str(min_flips(perm)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
