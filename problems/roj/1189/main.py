#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:55
# update_at: 2026-09-29 22:55

import sys

MOD = 32767  # 题目要求的模数


def pell_table(limit: int) -> list[int]:
    """pell[k] = Pell 数列第 k 项对 32767 取模，下标从 1 开始，只算到 limit。"""
    pell = [0, 1, 2]  # a(1) = 1，a(2) = 2，下标 0 只做占位
    for k in range(3, limit + 1):
        pell.append((2 * pell[k - 1] + pell[k - 2]) % MOD)  # 每步取模，表内恒为 32767 以内
    return pell


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)  # 测试组数
    queries = [next(data) for _ in range(T)]  # 先收齐全部询问，才知道要预计算到哪个位置

    pell = pell_table(max(queries))  # 一次线性递推，所有询问共享同一张表
    print('\n'.join(map(str, (pell[k] for k in queries))))


if __name__ == "__main__":
    solve()
