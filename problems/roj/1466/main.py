#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:33
# update_at: 2026-09-30 12:33

import sys

STOP = b"."  # 题面的结束标记，单独占一行


def power_count(s: bytes) -> int:
    """返回 s 的最短周期的重数 len(s)//p；若最短正周期分不尽 s 则返回 1。

    KMP 失败函数：pi[i] = s[:i+1] 的最长「真前缀 = 真后缀」长度。
    len(s) - pi[-1] 是 s 的最小正周期，只有当它是 len(s) 的约数时周期才整分 s。
    """
    n = len(s)
    pi = [0] * n               # 失败函数数组，与 s 等长
    border = 0                 # 已匹配的 border 长度，即 pi[i-1] 的滚动值
    for i in range(1, n):
        ch = s[i]
        while border and s[border] != ch:  # 失配就沿 border 链回退
            border = pi[border - 1]
        if s[border] == ch:    # 配上了，border 变长
            border += 1
        pi[i] = border
    p = n - border
    return n // p if n % p == 0 else 1


def solve() -> None:
    out: list[str] = []
    for line in sys.stdin.buffer.read().split():
        if line == STOP:
            break                  # 结束行之后不再有数据
        out.append(str(power_count(line)))
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
