#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 22:30
# update_at: 2026-10-10 00:05

import math
import sys


def solve() -> None:
    """多组数据读到 EOF，每组 A M B N，输出 A 绕 B 滚动回原位所需的旋转次数。

    把 B 的边界拉直成总长 N*B 的线段（每隔 B 有一个拐角），A 每走完一条边 A
    旋转一次、每碰到一个拐角也多旋转一次，两时刻重合只算一次
    ⇒ 答案 = (0, X] 内「A 的倍数或 B 的倍数」的个数，X = lcm(A, N*B)。
    """
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    # 四份引用共用同一个迭代器，每组正好吃掉 4 个；末尾不足一组则整组丢弃，
    # 与官方 std.cpp 的 while (cin >> a >> m >> b >> n) 行为一致。m 只消费不参与计算。
    for a, m, b, n in zip(data, data, data, data):
        nb = n * b
        x = a // math.gcd(a, nb) * nb                   # x = lcm(a, n*b)：回到原位走过的总路程
        y = a // math.gcd(a, b) * b                     # y = lcm(a, b)
        ans = x // a + x // y * (y // b - 1)            # 容斥：A 的倍数 ∪ B 的倍数 的个数
        out.append(str(ans))

    if out:
        print('\n'.join(out))


if __name__ == '__main__':
    solve()
