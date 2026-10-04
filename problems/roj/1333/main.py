#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-28 16:40
# update_at: 2026-09-28 16:40

import sys


def blah(a: int, n: int) -> int:
    """求以 a 为基的 Blah 数集升序排列后的第 n 个元素。"""
    seq = [0] + [a]  # q[1] = a；留出下标 0 的哨兵位，双指针都从 1 出发
    head2, head3 = 1, 1  # 2x+1 家族 / 3x+1 家族各自消费到的前缀位置
    for _ in range(n - 1):  # 已有第 1 个元素，再生成 n-1 个
        x = seq[head2] * 2 + 1
        y = seq[head3] * 3 + 1
        smaller = x if x < y else y  # 两族队首的较小者就是下一个数
        seq.append(smaller)
        head2 += x <= y  # x 被消费（含相等时两族同时消费）
        head3 += y <= x
    return seq[n]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    for a in data:  # 读到文件尾为止，每组两个数：基 a 与序号 n
        n = next(data)
        out.append(str(blah(a, n)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
