#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:09
# update_at: 2026-10-02 09:09

import sys


def keep_top2(cell: list[int], w: int) -> None:
    """用边权 w 刷新某个武将的 (最大, 次大) 默契值。"""
    if w > cell[0]:
        cell[1], cell[0] = cell[0], w  # 原最大降级为次大
    elif w > cell[1]:
        cell[1] = w


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 武将个数：偶数且不小于 4

    # 每个武将维护 (最大, 次大) 两条边：电脑只破坏"最强组合"，次大稳拿
    top: list[list[int]] = [[0, 0] for _ in range(n)]
    for i in range(n - 1):  # 第 i+1 行给出 i 号与 i+1..n-1 号的默契值
        for j in range(i + 1, n):
            w = next(data)
            keep_top2(top[i], w)  # 边 (i, j) 对两端各自刷新
            keep_top2(top[j], w)

    # 必胜：先抢次大值最大的武将 i，电脑抢走 i 的最强搭档，再抢 i 的次强搭档；
    # 电脑任一组合都小于该次大值，故输出 1 和所有次大值中的最大者
    print(1, max(cell[1] for cell in top), sep="\n")


if __name__ == "__main__":
    solve()
