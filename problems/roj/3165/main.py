#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 11:13
# update_at: 2026-10-09 11:41

import sys


def kth_empty(bit: list[int], k: int, n: int) -> int:
    """倍增求前缀和首次达到 k 的位置，即当前第 k 个空位的下标（1-indexed）。"""
    pos = 0
    step = 1 << (n.bit_length() - 1)
    while step:
        nxt = pos + step
        if nxt <= n and bit[nxt] < k:
            k -= bit[nxt]
            pos = nxt
        step >>= 1
    return pos + 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    for n in data:
        try:
            op = [(next(data), next(data)) for _ in range(n)]  # 每行 (P_i, V_i)
        except StopIteration:  # 输入被截断，放弃这一组
            break

        bit = [0] + [i & -i for i in range(1, n + 1)]  # 初始全空：bit[i] = i & -i
        ans = [0] * (n + 1)

        # 倒序：第 i 个人必定落在当前剩余空位的第 P_i + 1 个
        for pos, val in reversed(op):
            p = kth_empty(bit, pos + 1, n)
            ans[p] = val
            i = p
            while i <= n:  # 占掉这个空位
                bit[i] -= 1
                i += i & -i

        out.append(''.join(f'{x} ' for x in ans[1:]))  # 行末也带一个空格

    sys.stdout.write('\n'.join(out) + '\n' if out else '')


if __name__ == '__main__':
    solve()
