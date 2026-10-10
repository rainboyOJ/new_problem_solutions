#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:05
# update_at: 2026-10-08 22:07

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 题面「输出」节写“偶数之和与奇数之和”，与「题目描述」节顺序相反；
    # 以样例 n=10 -> "30 25" 及 10 个测试点为准：偶数和在前。
    # 题面要求“利用 for 循环”，故一趟循环分别累加，与 C++ 解同阶。
    sum_even = 0
    sum_odd = 0
    for i in range(1, n + 1):
        if i % 2 == 0:
            sum_even += i
        else:
            sum_odd += i

    print(sum_even, sum_odd)  # 单空格分隔、行末换行；n = 1 时输出 "0 1"


if __name__ == "__main__":
    solve()
