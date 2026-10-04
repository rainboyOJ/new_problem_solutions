#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-01-14 22:00
# update_at: 2026-10-04 10:41

import sys


def solve() -> None:
    """最长公共子序列：滚动数组 DP。"""
    data = iter(sys.stdin.buffer.read().split())
    x, y = next(data), next(data)  # 两行序列，按 next() 顺序消费（字符数据，不转 int）
    n, m = len(x), len(y)

    prev = [0] * (m + 1)  # 上一行
    cur = [0] * (m + 1)   # 当前行

    for i in range(1, n + 1):
        xi = x[i - 1]
        for j in range(1, m + 1):
            if xi == y[j - 1]:
                cur[j] = prev[j - 1] + 1           # 匹配，继承左上 +1
            else:
                cur[j] = max(prev[j], cur[j - 1])  # 不匹配，取上方或左方较大者
        prev, cur = cur, prev  # 滚动：当前行变上一行，旧上一行复用为草稿

    print(prev[m])


if __name__ == "__main__":
    solve()
