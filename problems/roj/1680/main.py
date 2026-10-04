#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    sums = sorted([next(data) for _ in range(2 * n)])
    m = next(data)
    allowed = set([next(data) for _ in range(m)])
    total = sums[-1]

    # 显式栈模拟深度优先搜索，优先尝试作为前缀以保证字典序最小
    # 栈元素: (k, x, y, pre, suf, seq1, seq2)
    stack: list[tuple[int, int, int, int, int, tuple[int, ...], tuple[int, ...]]] = [
        (0, 1, n, 0, 0, (), ())
    ]

    while stack:
        k, x, y, pre, suf, s1, s2 = stack.pop()
        if x == y:
            rem = total - pre - suf
            if 0 < rem <= 500 and rem in allowed:
                print(*(list(s1) + [rem] + list(reversed(s2))))
                return
            continue

        # 后压入作为后缀的分支，先尝试作为前缀的分支
        diff_suf = sums[k] - suf
        if 0 < diff_suf <= 500 and diff_suf in allowed:
            stack.append((k + 1, x, y - 1, pre, sums[k], s1, s2 + (diff_suf,)))

        diff_pre = sums[k] - pre
        if 0 < diff_pre <= 500 and diff_pre in allowed:
            stack.append((k + 1, x + 1, y, sums[k], suf, s1 + (diff_pre,), s2))


if __name__ == "__main__":
    solve()
