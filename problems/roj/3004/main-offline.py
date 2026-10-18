#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-18 16:43
# update_at: 2026-10-18 16:43
#
# 离线做法：把询问按 T 排序 + 双指针。
#   sum[i] 严格递增 => T 越大答案 k 越大，
#   于是按 T 升序处理询问，指针 k 只会向右走，边加边回答。
#   先读完所有询问再统一处理，因此是离线的。

import sys
from itertools import accumulate


def solve() -> None:
    read = sys.stdin.buffer.readline
    n, q = map(int, read().split())

    a = []
    while len(a) < n:  # 数组可能被拆成多行，读满 n 个为止
        a.extend(map(int, read().split()))
    sum_ = [0, *accumulate(a)]  # sum_[i] = A[1] + ... + A[i]

    queries = []
    while len(queries) < q:
        queries.extend(map(int, read().split()))

    # 按 T 升序排序，同时记住原始下标，最后要按原顺序输出
    order = sorted(range(q), key=lambda i: queries[i])

    ans = [0] * q
    k = 0  # 双指针：当前已验证 sum_[k] <= 当前 T 的最右位置
    for i in order:
        t = queries[i]
        while k + 1 <= n and sum_[k + 1] <= t:  # k 只向右走
            k += 1
        ans[i] = k

    sys.stdout.write("\n".join(map(str, ans)) + "\n")


if __name__ == "__main__":
    solve()
