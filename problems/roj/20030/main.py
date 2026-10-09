#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 21:00
# update_at: 2026-10-09 21:16

import sys
from functools import reduce
from operator import xor

BITS = 8                                    # 低位块宽，低位状态数 2**8 = 256
SIZE = 1 << BITS
HIGH = 1 << (BITS + 1)                      # x < 2**17 ⇒ x>>8 ≤ 390 < 512，高位子集表留一倍余量

# SUBS[i] = i 的全部子集左移 BITS 位后组成的列表，查询时按 i = x>>BITS 直接查表
SUBS = [[k << BITS for k in range(i + 1) if k & i == k] for i in range(HIGH)]


def build_low_table(a: list[int], n: int) -> list[list[int]]:
    """返回 f：f[j][i] = XOR_{k ⊆ j} a[i + k]，即低位部分恰为 j 的询问答案。

    取 j 的最低位 low，按"不取 low / 取 low"拆成两支递推：
    f[j][i] = f[j ^ low][i] ^ f[j ^ low][i + low]。
    第 j 行只会被下标 < n - j 的询问读到，其余位置补 0 占位。
    """
    f = [a] + [None] * (SIZE - 1)
    for j in range(1, SIZE):
        low = j & -j
        prev = f[j ^ low]
        keep = n - j
        row = list(map(xor, prev[:keep], prev[low:keep + low])) if keep > 0 else []
        f[j] = row + [0] * ((n - keep) if keep > 0 else n)
    return f


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if len(data) < 2:
        return                              # 空输入/只有半行：直接退出，不做越界假设
    n, q = int(data[0]), int(data[1])
    if n <= 0 or len(data) < 2 + n:
        return                              # n=0 或序列长度不足：输入非法，不强行算
    a = [int(v) for v in data[2:2 + n]]

    f = build_low_table(a, n)

    out = []
    pos = 2 + n
    if len(data) < pos + 2 * q:
        return                              # 查询行数不足：输入非法，不强行算
    for _ in range(q):
        x, y = int(data[pos]), int(data[pos + 1])
        pos += 2
        low_row = f[x & (SIZE - 1)]         # 低位查预处理表，高位枚举子集异或
        out.append(str(reduce(xor, (low_row[y + off] for off in SUBS[x >> BITS]), 0)))

    sys.stdout.write('\n'.join(out) + ('\n' if out else ''))


if __name__ == '__main__':
    solve()
