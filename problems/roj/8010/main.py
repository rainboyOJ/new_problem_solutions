#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 21:30
# update_at: 2026-10-09 22:55

import sys


def solve() -> None:
    """双指针顺序扫描：q 是否是 s1 的子序列（保持 s1 中的相对位置）。"""
    data = sys.stdin.buffer.read().split()
    if len(data) < 2:
        return
    s1 = data[0].decode()
    q = data[1].decode()

    i = j = 0              # i 扫 s1，j 扫 q
    n, m = len(s1), len(q)
    while i < n and j < m:
        if s1[i] == q[j]:  # q 的当前字符在 s1 中按序匹配上了
            j += 1
        i += 1

    print("Yes" if j == m else "No")  # 全部字符按原相对位置匹配完成才算通过


if __name__ == "__main__":
    solve()
