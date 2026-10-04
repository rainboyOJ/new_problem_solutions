#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:31
# update_at: 2026-09-30 12:31

import sys


def count_non_overlapping(text: str, pattern: str) -> int:
    """计算模式串在主串中互不重叠出现的最大次数（KMP 匹配与贪心跳跃）。"""
    m = len(pattern)
    pi = [0] * m
    j = 0
    for i in range(1, m):
        while j > 0 and pattern[i] != pattern[j]:
            j = pi[j - 1]
        j += pattern[i] == pattern[j]
        pi[i] = j

    ans = 0
    j = 0
    for ch in text:
        while j > 0 and ch != pattern[j]:
            j = pi[j - 1]
        j += ch == pattern[j]
        if j == m:
            ans += 1
            j = 0  # 剪下饰条后不可重叠，重置匹配进度
    return ans


def solve() -> None:
    lines = sys.stdin.read().splitlines()
    out: list[str] = []
    for line in lines:
        if line == "#":
            break
        parts = line.split()
        if not parts:
            continue
        text, pattern = parts[0], parts[1]
        out.append(str(count_non_overlapping(text, pattern)))
    print("\n".join(out))


if __name__ == "__main__":
    solve()
