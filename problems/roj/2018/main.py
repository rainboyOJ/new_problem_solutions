#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:06
# update_at: 2026-10-01 03:06

import sys
from collections.abc import Iterator


def is_prime(n: int) -> bool:
    """判定整数 n 是否为素数。"""
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    return all(n % d != 0 for d in range(3, int(n**0.5) + 1, 2))


def generate_palindromes(limit: int) -> Iterator[int]:
    """生成不超过 limit 的所有可能回文质数候选。

    除 11 外，任意偶数长度回文数的奇偶位交错和为 0，必是 11 的倍数且大于 11，
    故只需生成 1 位、2 位(仅11)以及 3, 5, 7 位奇数长度回文。
    """
    # 1 位数: 5, 7
    yield from (d for d in range(1, 10) if d <= limit)

    # 2 位数: 仅 11 可能是质数
    if 11 <= limit:
        yield 11

    # 3, 5, 7, 9 位数：由前半部 root (10^(k-1) .. 10^k-1) 与中间数 mid 拼出
    for half_len in (1, 2, 3, 4):
        start = 10 ** (half_len - 1)
        end = 10**half_len
        for root in range(start, end):
            rev_root = str(root)[::-1]
            for mid in range(10):
                val = int(f"{root}{mid}{rev_root}")
                if val > limit:
                    return
                yield val


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    a, b = int(data[0]), int(data[1])

    # 限制 b 最大 10^8，故奇数位回文上限至 10^8，直接过滤 [a, b] 内的素数
    pals = [p for p in generate_palindromes(b) if p >= a and is_prime(p)]
    pals.sort()
    print("\n".join(map(str, pals)))


if __name__ == "__main__":
    solve()
