#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 00:41
# update_at: 2026-10-09 00:41

import sys


def solve() -> None:
    """读入三个整数，三次比较交换排成降序，单空格分隔输出。"""
    # 题面只说「按从大到小的顺序输出」，未指定实现手段（关键词/括号/标题三步判据全空），
    # 故不调用内置 sorted，保留与 C++ 侧同阶的三次比较交换。
    # 数据含 32 位极值（如三个 -2147483648）：这里只做比较与赋值，未取反/取绝对值，无溢出风险。
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a, b, c = next(data), next(data), next(data)

    if a < b:
        a, b = b, a  # 先保证 a >= b
    if a < c:
        a, c = c, a  # 再保证 a >= c，此时 a 已是三者最大
    if b < c:
        b, c = c, b  # 最后保证 b >= c

    print(a, b, c)  # 单空格分隔、行末换行（实测 .out 无行尾空格）


if __name__ == "__main__":
    solve()
