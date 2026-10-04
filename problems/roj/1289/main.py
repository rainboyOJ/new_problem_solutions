#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:28
# update_at: 2026-09-30 03:28

import sys


def max_intercept(seq: list[int]) -> int:
    """f[i]：以 seq[i] 结尾的最长不增子序列长度；答案取所有结尾位置里的最大值。"""
    f = [1] * len(seq)
    for i, value in enumerate(seq):
        # 接在"前面不比它高、且最长"的那一段后面；一个都接不上就自己单独开头
        f[i] = max((f[j] + 1 for j in range(i) if seq[j] >= value), default=1)
    return max(f)


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    count = data[0]  # 导弹数 N
    print(max_intercept(data[1:count + 1]))


if __name__ == "__main__":
    solve()
