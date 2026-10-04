#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:41
# update_at: 2026-10-01 11:50

import sys


def prefix_function(s: bytes) -> list[int]:
    """KMP 失配数组：nxt[i] 是 s[:i+1] 最长的「真前缀 = 真后缀」的长度，下标从 0 起。"""
    n = len(s)
    nxt = [0] * n
    for i in range(1, n):
        j = nxt[i - 1]
        while j and s[i] != s[j]:  # 失配就沿失配链回跳，直到能接上或跳到 0
            j = nxt[j - 1]
        if s[i] == s[j]:
            j += 1
        nxt[i] = j
    return nxt


def repeats(s: bytes) -> list[tuple[int, int]]:
    """每个「恰好由循环节拼成的前缀」(前缀长度 length, 重复次数 k)，按 length 升序。"""
    nxt = prefix_function(s)
    # 长度 length 的最短周期 period = length - nxt[length-1]；
    # period < length 说明循环节不是前缀本身，即 k > 1；
    # period 再整除 length 时，该前缀恰好是 k = length/period 个 period 的重复。
    cycles = ((length, length - nxt[length - 1]) for length in range(2, len(s) + 1))
    return [
        (length, length // period)
        for length, period in cycles
        if period < length and length % period == 0
    ]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())  # token 混有字符串 s，不能整体 map(int)
    out: list[str] = []
    case = 0
    while n := int(next(data)):  # 每组先读长度 n，读到 0 结束
        case += 1
        s = next(data)
        out.append(f"Test case #{case}")
        out += [f"{length} {k}" for length, k in repeats(s)]  # 输入保证 len(s) == n，无需再截断
        out.append("")  # 每组末尾的空行，同时也是下一组的前导空行

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
