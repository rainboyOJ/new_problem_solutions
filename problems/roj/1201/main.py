#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:16
# update_at: 2026-09-29 23:28

import sys
from functools import cache


@cache
def fib(a: int) -> int:
    """返回斐波那契数列第 a 项：F(1)=F(2)=1，F(a)=F(a-1)+F(a-2)。"""
    return 1 if a <= 2 else fib(a - 1) + fib(a - 2)  # 递归定义，@cache 把算过的 a 记下来


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 题面的测试数据组数
    print('\n'.join(str(fib(next(data))) for _ in range(n)))


if __name__ == "__main__":
    solve()
