#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 04:05
# update_at: 2026-10-08 04:05

import sys

SMALL = (2, 3, 5, 7, 11, 13, 17, 19)  # n<=500 时 sqrt(n)<=22，小质数恰为这 8 个

type Mask = int                # 8 位小质因子掩码（第 j 位 = 含质数 SMALL[j]）
type Key = tuple[Mask, Mask]   # (小 G 掩码, 小 W 掩码)，两者必无交集
type Table = dict[Key, int]    # 状态 -> 方案数（已对 p 取模）
type Item = tuple[int, Mask]   # (大质因子, 小质因子掩码)，1 表示只含小质数


def split(x: int) -> Item:
    """把一个数拆成 (大质因子, 小质因子掩码)；指数不影响互质性，可除干净。"""
    mask = 0
    for j, q in enumerate(SMALL):
        if x % q == 0:
            mask |= 1 << j
            while x % q == 0:
                x //= q  # 除完所有小质数，剩下的就是那个唯一的大质因子（或 1）
    return x, mask


def push(table: Table, s: Mask, to_g: bool, mod: int) -> Table:
    """把寿司 s 并入「本组只能给某一人」的表：每个状态多出「不选它」与「给它」两条去路。"""
    nxt = dict(table)  # 保留「不选」这一支
    for (x, y), v in table.items():
        if to_g:
            if s & y:
                continue  # s 与小 W 已有的质因子撞车，不能给小 G
            key = (x | s, y)
        else:
            if s & x:
                continue  # s 与小 G 已有的质因子撞车，不能给小 W
            key = (x, y | s)
        nxt[key] = (nxt.get(key, 0) + v) % mod
    return nxt


def absorb(dp: Table, group: list[Item], mod: int) -> Table:
    """整组只能给同一个人：分别算出「只给 G」「只给 W」两份表，再容斥并回全局。"""
    g1, g2 = dp, dp  # 组内逐个数累加，两份表各自从旧状态出发
    for _, s in group:
        g1 = push(g1, s, True, mod)
        g2 = push(g2, s, False, mod)
    # 「本组一个都不选」在 g1、g2 里各被数了一次，容斥时各减掉一份旧状态
    merged: Table = {}
    for key in g1.keys() | g2.keys():
        merged[key] = (g1.get(key, 0) + g2.get(key, 0) - dp.get(key, 0)) % mod
    return merged


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, mod = next(data), next(data)

    items = sorted(split(x) for x in range(2, n + 1))  # 按大质因子排序，同因子的连成一段
    dp: Table = {(0, 0): 1}
    i, cnt = 0, len(items)

    while i < cnt:
        bigp = items[i][0]
        j = i
        if bigp > 1:  # 大质因子为 1 的数各自单独成组；否则同一大质因子的整段归一组
            while j + 1 < cnt and items[j + 1][0] == bigp:
                j += 1
        dp = absorb(dp, items[i : j + 1], mod)
        i = j + 1

    print(sum(dp.values()) % mod)  # 非法状态（两掩码有交集）在转移中取不到值，直接全加


if __name__ == "__main__":
    solve()
