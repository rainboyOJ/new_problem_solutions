#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:03
# update_at: 2026-09-29 23:08

import sys


def shift_ring(mask: int, step: int, k: int, full: int) -> int:
    """把「可达余数集合」整体沿环平移 step 步，超出的位绕回低位（循环移位）。

    mask 的第 r 位为 1 表示余数 r 可达；每位移到 r+step，所以 +a 是环形左移 a 位，-a 是环形左移 k-a 位。
    """
    step %= k                            # 归约到 [0,k)：既完成 a 取模，也把 -a 折成 k-(a mod k)
    return (mask << step | mask >> (k - step)) & full


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    next(data)                           # n：循环直接迭代剩余整数，这里只跳过它
    k = next(data)
    full = (1 << k) - 1                  # k 个余数位全为 1 的封顶掩码
    reach = 1                            # 只有余数 0 可达（空序列和为 0）

    for a in data:                       # 逐个数字决定前面放 + 还是 -
        reach = shift_ring(reach, a, k, full) | shift_ring(reach, -a, k, full)

    print("YES" if reach & 1 else "NO")  # 第 0 位仍是 1 就说明存在和为 k 倍数的符号方案


if __name__ == "__main__":
    solve()
