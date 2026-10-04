#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:22
# update_at: 2026-10-01 05:22

import sys
from functools import cache


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))

    # offer = ((单品下标, 份数), ...) + 优惠价；只保留被购物清单覆盖的方案，
    # 这样状态向量的每一维都恰好对应一种要买的商品。
    raw: list[tuple[list[tuple[int, int]], int]] = []
    for _ in range(next(data)):
        n = next(data)
        pairs = [(next(data), next(data)) for _ in range(n)]  # 必须立即求值，否则 p 会先被读走
        raw.append((pairs, next(data)))

    count_of_species = next(data)
    order = [next(data) for _ in range(count_of_species * 3)]
    # 清单按商品编号排序，方便下面把优惠方案里的编号换算成状态维度下标。
    species = sorted((order[i * 3], order[i * 3 + 1], order[i * 3 + 2]) for i in range(count_of_species))
    index_of = {c: i for i, (c, _, _) in enumerate(species)}
    want = tuple(k for _, k, _ in species)

    # 每个方案表示成 len(species) 长的份数向量 + 价格；同一个向量可能有多个报价，取最小。
    deals: dict[tuple[int, ...], int] = {}
    for pairs, price in raw:
        need = [0] * count_of_species
        for c, k in pairs:
            if c not in index_of:  # 方案里出现清单外的商品：题面禁止顺带购买，丢弃
                break
            need[index_of[c]] = k
        else:
            key = tuple(need)
            if key != tuple([0] * count_of_species):  # 空方案等于白送，不合题意
                deals[key] = min(deals.get(key, price), price)
    options = [(key, price) for key, price in deals.items()]

    @cache
    def best(left: tuple[int, ...]) -> int:
        """left 为各商品还差几件时的最低花费：要么按原价买一件，要么用某个能装下的方案。"""
        if not any(left):
            return 0
        ans = 10**9
        for i, rest in enumerate(left):
            if rest:  # 按原价补一件，保证状态一定向 0 收敛
                ans = min(ans, species[i][2] + best(left[:i] + (rest - 1,) + left[i + 1:]))
        for key, price in options:
            nxt = tuple(a - b for a, b in zip(left, key))
            if min(nxt) >= 0:  # 方案不超过剩余需求，题面禁止多买
                ans = min(ans, price + best(nxt))
        return ans

    print(best(want))


if __name__ == "__main__":
    solve()
