#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:16
# update_at: 2026-09-29 21:16

LIMIT = 100  # 题目只拆 6~100 的偶数


def sieve(limit: int) -> list[bool]:
    """埃氏筛：is_prime[x] 为 True 表示 x 是素数。"""
    is_prime = [False, False] + [True] * (limit - 1)
    for p in range(2, int(limit ** 0.5) + 1):
        if is_prime[p]:
            is_prime[p * p::p] = [False] * ((limit - p * p) // p + 1)
    return is_prime


def solve() -> None:
    is_prime = sieve(LIMIT)

    # 偶数只能拆成"奇+奇"（2+偶数必非素数），从小到大试奇数，
    # 第一个让两数都是素数的 p 就是题面要求的"最小的第一加数"。
    out: list[str] = []
    for n in range(6, LIMIT + 1, 2):
        p = next(p for p in range(3, n, 2) if is_prime[p] and is_prime[n - p])
        out.append(f"{n}={p}+{n - p}")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
