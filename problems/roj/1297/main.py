#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:53
# update_at: 2026-10-04 11:13

import sys


def lcs_len(x: bytes, y: bytes) -> int:
    """最长公共子序列长度：滚动数组逐位推进，只保留上一行。"""
    # 走短串做行的方向，空间与内层循环长度都取 min(len(x), len(y))。
    if len(x) > len(y):
        x, y = y, x

    prev = [0] * (len(x) + 1)  # 上一行（即以 y 的前 j 个字符为另一个维度的状态）
    for ch in y:
        cur = [0] * (len(x) + 1)  # 当前行；cur[0] 恒为 0，代表空串
        for j, c in enumerate(x, 1):
            if c == ch:
                cur[j] = prev[j - 1] + 1  # 配对成功，接着左上角的最优值
            elif prev[j] > cur[j - 1]:
                cur[j] = prev[j]  # 丢掉 ch，继承上一行同列
            else:
                cur[j] = cur[j - 1]  # 丢掉 c，继承本行左邻
        prev = cur
    return prev[len(x)]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())  # 一次读完，空白切分即可丢掉行尾
    out = []
    while (x := next(data, None)) is not None:  # 题面不给组数，读到 EOF 为止，每两个 token 是一组 (X, Y)
        y = next(data)
        out.append(str(lcs_len(x, y)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
