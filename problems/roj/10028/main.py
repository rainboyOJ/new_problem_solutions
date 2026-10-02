#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:08
# update_at: 2026-10-02 19:22

import sys

LIMIT = 1_000_000  # 题面 N 的上界
SIEVE = LIMIT + 100  # 筛表外扩：N=10^6 时需要知道它右侧第一个素数 1000003


def prime_gaps(limit: int) -> list[int]:
    """返回 gap[v]：合数 v 所处素数间隔的宽度（v 为素数时记 0）。

    欧拉筛按从小到大顺序生成素数列表 p，p[i] 与 p[i+1] 之间的合数 v
    满足 p[i] < v < p[i+1]，其间隔宽度就是 p[i+1] - p[i]。
    """
    gap = [0] * (limit + 1)
    composite = bytearray(limit + 1)
    primes: list[int] = []
    for v in range(2, limit + 1):
        if not composite[v]:  # v 未被更小的素数划掉，v 是素数
            primes.append(v)
        # 用 v 和已筛出的每个素数 p 去划掉 p*v，p 取到 v 的最小素因子为止
        for p in primes:
            if v * p > limit:
                break
            composite[v * p] = 1
            if v % p == 0:  # p 是 v 的最小素因子，再大的素数交给后续轮次
                break

    # 前一个素数 prev 与当前素数 p 之间的每个合数都登记间隔 p - prev
    prev = 2
    for p in primes[1:]:
        for v in range(prev + 1, p):
            gap[v] = p - prev
        prev = p
    return gap


def solve() -> None:
    n = int(sys.stdin.buffer.read())
    print(prime_gaps(SIEVE)[n])


if __name__ == "__main__":
    solve()
