#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:43
# update_at: 2026-10-01 17:00

import re
import sys

WIDTH = 30  # 10^9 < 2^30，定长二进制串才能按列切片取出每一位


def one_bit_values(column: str) -> tuple[int, int, int]:
    """一位上的三份加权分子：column 是该位按原下标顺序拼成的 0/1 串。

    xor / and / or 的每份答案都是「所有区间的该位值（0 或 1）之和」，
    而三种运算的取值都只由同值连续段的长度决定，所以先压缩成段长表再统计。
    """
    runs = [(int(part[0]), len(part)) for part in re.findall("0+|1+", column)]
    ones = [length for value, length in runs if value]
    zeros = [length for value, length in runs if not value]
    all_one = sum(length * (length + 1) // 2 for length in ones)    # 全是 1 的区间数 = and 为 1 的区间数
    all_zero = sum(length * (length + 1) // 2 for length in zeros)  # 全是 0 的区间数
    total = len(column) * (len(column) + 1) // 2                    # 区间总数

    # 前缀异或 P_i 只在扫过 1 时翻转：1 段内部逐格交替，0 段内部保持不变。
    # P 取到 0 的次数乘取到 1 的次数，就是 xor 为 1 的区间数。
    parity, seen = 0, [1, 0]  # P_0 = 0，先计入偶侧
    for value, length in runs:
        if value:
            seen[parity] += length // 2              # 段内交替，后 floor(L/2) 个落回原奇偶
            seen[parity ^ 1] += (length + 1) // 2    # 前 ceil(L/2) 个翻到对面
            parity ^= length & 1                     # 段的奇偶长度决定出段时的前缀值
        else:
            seen[parity] += length                   # 0 段不改变前缀值

    # 长度大于 1 的区间有 (l, r) 两种取法，单点区间只有一种，故加权数为 2c - s
    singles = sum(ones)  # 该位上 1 的个数 = 单点区间里 op 结果为 1 的个数
    return tuple(2 * count - singles for count in (seen[0] * seen[1], all_one, total - all_zero))


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    signal = data[1:1 + n]

    # 全部数拼成 WIDTH 位定长串：按列切片就一次拿到所有位的 0/1 序列
    packed = ''.join(f'{value:0{WIDTH}b}' for value in signal)
    parts = [one_bit_values(packed[k::WIDTH]) for k in range(WIDTH)]

    # 按位独立：第 k 列的位权是 2^(WIDTH-1-k)（最高位在最左），30 列加权相加即三份答案
    totals = [sum(part[i] << (WIDTH - 1 - k) for k, part in enumerate(parts)) for i in range(3)]
    # 分母是 (l, r) 的有序取法总数 N^2，与上面的加权计数口径一致
    print(' '.join(f'{total / n ** 2:.3f}' for total in totals))


if __name__ == "__main__":
    solve()
