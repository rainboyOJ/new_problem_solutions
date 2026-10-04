#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:36
# update_at: 2026-10-02 06:36

import sys


def walk_cycle(wish: list[tuple[int, int]]) -> list[int] | None:
    """从 0 号出发沿愿望边走一圈：愿望图是覆盖全部人的单一环时返回环上顺序，否则 None。"""
    total = len(wish)
    order = [0]
    prev: int | None = None
    cur = 0
    # 每个点度数恰为 2，走一圈必然回到 0；回到 0 时环的大小就是 order 的长度
    for _ in range(total):
        a, b = wish[cur]
        nxt = b if a == prev else a  # 两个愿望邻居里避开刚走来的那个
        if nxt == 0:
            return order if len(order) == total else None  # 只覆盖了部分人 → 还有别的环
        order.append(nxt)
        prev, cur = cur, nxt
    return None


def min_cost(wish: list[tuple[int, int]]) -> int:
    """愿望图是单一环时返回最小总代价，否则返回 -1。"""
    total = len(wish)

    # 愿望必须互相成立，否则按愿望连出的图不是每个点度数为 2 的环
    for i, (a, b) in enumerate(wish):
        if i not in wish[a] or i not in wish[b]:
            return -1

    order = walk_cycle(wish)
    if order is None:
        return -1

    # 命令只能搬人：最终坐对的人里，最初就坐对的不必动，最初坐错的每人至少被搬一次，
    # 故总代价 ≥ 错位人数；而错位者占据的恰是剩余座位，按目标位置拆成若干循环，
    # 每个循环一条命令即可全部归位（代价 = 循环长度），总代价 = 错位人数。
    # 座位圈没有起点、也不分左右：目标环可以整体旋转、也可以反向，
    # 因此对「偏移 = 当前座位 - 目标座位」做直方图，取正反两个方向的最大重合数。
    hit_fwd = [0] * total  # 正向目标圈：偏移 r 的人已在位
    hit_rev = [0] * total  # 反向目标圈：反向座位 = -目标座位，偏移 = 当前 + 目标
    for seat, person in enumerate(order):  # person 的正向目标座位是 seat，它当前坐在 person 号座位
        hit_fwd[(person - seat) % total] += 1
        hit_rev[(person + seat) % total] += 1

    keep = max(max(hit_fwd), max(hit_rev))  # 一个旋转/方向下最多能白坐对的人数
    return total - keep


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    wish = [(next(data) - 1, next(data) - 1) for _ in range(n)]  # 编号 i+1 最希望相邻的两人（0 基）
    print(min_cost(wish))


if __name__ == "__main__":
    solve()
