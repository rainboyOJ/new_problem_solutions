#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:20
# update_at: 2026-10-02 10:20

import sys
from functools import cache

DIGITS = 10   # 十进制数位取值 0..9
LEAD = 10     # 状态哨兵：当前这位还没定下来（更高位全是前导零），下一位可以任取


@cache
def ways(length: int, low: int) -> int:
    """长度为 length、每一位都取自 [low, 9] 且相邻不降的串有多少个。

    这就是"从 low..9 里允许重复地取 length 个数的非降序列"的数量，
    即组合数 C(length + 9 - low, length)：把 length 个位置上的取值
    和 9 - low 个"分隔板"排成一列，选 length 个位置当作取值即可。
    """
    return 1 if length == 0 else ways(length - 1, low) * (DIGITS + length - 1 - low) // length


def count_upto(n: int) -> int:
    """统计 [0, n] 内有多少个"从左到右各位数字不降"的数（含 0，它只有一位）。"""
    if n < 0:
        return 0
    digits = [int(c) for c in str(n)]

    # 逐位确定前缀。high 是上一位的数字，LEAD 表示更高位还全是前导零；
    # 前导零不参与"不降"的判定，所以数位长度天然可以比 len(digits) 短。
    total, high = 0, LEAD
    for i, cur in enumerate(digits):
        rest = len(digits) - i - 1  # 这一位固定后，低位还剩多少位
        low = 0 if high == LEAD else high
        # 这一位取 [low, cur-1]，低位就能自由填任意不降串（上限已被压小，不再受限）
        total += sum(ways(rest, d) for d in range(low, cur))
        if cur < low:  # n 自身在这一位就违反了不降，前缀只能到此为止
            return total
        high = cur
    return total + 1  # 每一位都贴着 n，n 本身也是不降数


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out = []
    # 多组数据，EOF 结束；a-1 可能为 0，count_upto 已处理
    for a, b in zip(data, data):
        out.append(count_upto(b) - count_upto(a - 1))
    print('\n'.join(map(str, out)))


if __name__ == "__main__":
    solve()
