#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:38
# update_at: 2026-09-29 22:38

import sys

MOD = 1000  # 题目要求的模数


def fib_table(limit: int) -> list[int]:
    """fib[i] = 第 i 个斐波那契数对 1000 取模，下标从 1 开始，只算到 limit。"""
    fib = [0, 1, 1]  # f(1) = f(2) = 1，占住下标 0/1/2
    for i in range(3, limit + 1):
        fib.append((fib[i - 1] + fib[i - 2]) % MOD)  # 每步取模，数值不溢出、表恒为三位数以内
    return fib


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)  # 测试组数
    queries = [next(data) for _ in range(T)]  # 先收齐全部询问，才知道要预计算到哪个位置

    fib = fib_table(max(queries))  # 一次线性递推，所有询问共享同一张表
    print('\n'.join(map(str, (fib[a] for a in queries))))


if __name__ == "__main__":
    solve()
