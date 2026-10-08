#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:41
# update_at: 2026-10-08 22:41

import sys


def is_prime(x: int) -> bool:
    """判断 x 是否为素数：1 既不是素数也不是合数，只需试除到 sqrt(x)。"""
    if x < 2:
        return False
    i = 2
    while i * i <= x:
        if x % i == 0:
            return False
        i += 1
    return True


def solve() -> None:
    """读入 a、b，按题意逐行输出 [a, b] 区间内的所有素数。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a, b = next(data), next(data)
    # 每个素数占一行（含最后一行）；区间内没有素数时必须输出 0 字节，
    # 所以只能用 write 拼串，不能用 print('\n'.join(...))（那会多出一个换行）。
    sys.stdout.write("".join(f"{x}\n" for x in range(a, b + 1) if is_prime(x)))


if __name__ == "__main__":
    solve()
