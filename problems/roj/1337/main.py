#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:57
# update_at: 2026-09-30 06:01

import sys


def common_prefix(a: bytes, b: bytes) -> int:
    """a、b 的最长公共前缀长度：按位比较，遇到第一个不同的字符就停。"""
    i = 0
    while i < len(a) and i < len(b) and a[i] == b[i]:
        i += 1
    return i


def solve() -> None:
    # 按空白切分即得单词表（忽略多余空行），排序后重复单词必然相邻。
    data = iter(sys.stdin.buffer.read().split())
    words = sorted(data)

    # 字典序下 LCP(w[i], w[i-1]) = max(LCP(w[i], w[j]) for j < i)，
    # 所以 w[i] 新贡献的结点（前缀）数 = len(w[i]) - LCP(w[i], w[i-1])；重复单词贡献 0。
    it = iter(words)
    first = next(it)                                      # 首词贡献全部前缀
    nodes = 1 + len(first)                                # 1 是根结点
    a = first
    for b in it:                                          # 依次与前一词比 LCP
        nodes += len(b) - common_prefix(a, b)
        a = b
    print(nodes)


if __name__ == "__main__":
    solve()
