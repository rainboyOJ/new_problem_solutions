#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:28
# update_at: 2026-09-30 00:28

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        w = next(data)  # 口袋承重上限
        s = next(data)  # 金属种类数

        metals = []  # (单位重量价值, 总重量)，后面按单价从高到低取
        for _ in range(s):
            n_i, v_i = next(data), next(data)
            metals.append((v_i / n_i, n_i))

        metals.sort(reverse=True)  # 贪心：单价越高越先装

        value = 0.0  # 已装下的总价值
        for unit, weight in metals:
            taken = min(weight, w)     # 这一种最多还能装多少
            value += taken * unit      # 价值和重量成正比
            w -= taken                 # 剩余承重
            if w == 0:
                break                  # 装满了，后面的金属不再看

        out.append(f"{value:.2f}")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
