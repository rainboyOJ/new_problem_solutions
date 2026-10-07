#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:54
# update_at: 2026-10-08 03:54

import sys
from collections.abc import Iterator


def primes_upto(limit: int) -> bytearray:
    """返回下标可查的质数表 is_prime[0..limit]：埃氏筛，第 i 项为 1 表示 i 是质数。"""
    is_prime = bytearray([1]) * (limit + 1)
    is_prime[0] = is_prime[1] = 0
    for i in range(2, int(limit ** 0.5) + 1):
        if is_prime[i]:
            is_prime[i * i:: i] = bytearray(len(range(i * i, limit + 1, i)))
    return is_prime


def greedy_pick(n: int, target: int) -> Iterator[int]:
    """从 n 往下贪心取数凑出 target：1..n 的连续整数一定能凑满任意不超过级数和的目标。"""
    rest = target
    for i in range(n, 0, -1):
        if rest <= 0:
            return
        if i <= rest:          # 余量还装得下 i，就取走 i
            yield i
            rest -= i


def plan_sets(n: int, S: int, is_prime: bytearray) -> tuple[int, list[int]]:
    """按"S 需要几个质数相加"给出最少集合数与方案；答案只会是 1、2、3。"""
    if is_prime[S]:            # S 自身是质数：全部数字放一个集合
        return 1, [1] * (n + 1)

    # 取最小的质数 x 使 x 与 S-x 都是质数，则只拆两个集合：集合 1 凑出和 x
    two = next((x for x in range(2, S // 2 + 1) if is_prime[x] and is_prime[S - x]), None)
    if two is not None:
        group = [2] * (n + 1)
        for i in greedy_pick(n, two):
            group[i] = 1
        return 2, group

    # 否则 S 是奇数且 S-2 是合数：挑两个不同质数 a、b 单列，其余数之和 S-a-b 仍是质数
    prime_list = [i for i in range(2, n + 1) if is_prime[i]]
    a, b = next(
        (a, b)
        for a in prime_list
        for b in prime_list
        if a != b and is_prime[S - a - b]
    )
    group = [3] * (n + 1)      # 集合 3 = 其余全部数，和为 S-a-b，是质数
    group[a] = 1               # 集合 1 = {a}
    group[b] = 2               # 集合 2 = {b}
    return 3, group


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    if n == 1:                 # S = 1 既不是质数也无法再拆，唯一无解情形
        print(-1)
        return

    S = n * (n + 1) // 2
    cnt, group = plan_sets(n, S, primes_upto(S))
    print(cnt)
    print(' '.join(map(str, group[1:])))


if __name__ == "__main__":
    solve()
