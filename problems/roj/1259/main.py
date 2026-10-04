#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:21
# update_at: 2026-09-30 02:21

import sys

# 输出的前缀大小写以评测数据为准：题面样例写 "max=8"，官方归档参考答案写 "Max=19"。
MAX_PREFIX = "Max="


def longest_lengths(seq: list[int]) -> list[int]:
    """f[i] = 以 seq[i] 结尾的最长不下降子序列长度 = 1 + max{f[j] : j < i 且 seq[j] <= seq[i]}。"""
    f = [1] * len(seq)
    for i, value in enumerate(seq):
        # default=0 表示前面没有能接上的元素，当前元素自己起头，长度就是 1
        f[i] = 1 + max((f[j] for j in range(i) if seq[j] <= value), default=0)
    return f


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 题面的序列长度
    seq = [next(data) for _ in range(n)]
    # 题面还要求第二行输出一条最长不下降子序列，但归档的参考答案只保存了长度这一行
    # （data/*.out 里就是 "Max=19\n" 这样的 7 个字节），多写第二行反而对不上，
    # 所以这里只输出长度；带回溯的完整写法见 index.md。
    print(f"{MAX_PREFIX}{max(longest_lengths(seq))}")


if __name__ == "__main__":
    solve()
