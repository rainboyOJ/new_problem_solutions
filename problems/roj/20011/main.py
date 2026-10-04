#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:41
# update_at: 2026-10-02 19:41

import sys

INF = float("inf")


def cook_mask(dishes: list[int]) -> int:
    """把一名厨师会的菜品编号折成 bitmask：第 d 位 = 会做菜 d+1。"""
    return sum(1 << d - 1 for d in dishes)


def min_extra_wage(free: list[tuple[int, int]], covered: list[int]) -> int:
    """按工资升序逐个决定雇不雇零工，返回补满“每道菜两名厨师”的最小工资。

    状态 (one, two)：one = 覆盖数恰为 1 的菜，two = 覆盖数已达 2 的菜。
    亲戚必须保留、工资照付，但他们也计入覆盖数——初始状态由 covered 给出。
    """
    all_dishes = (1 << len(covered)) - 1
    one = sum(1 << d for d, cnt in enumerate(covered) if cnt == 1)
    two = sum(1 << d for d, cnt in enumerate(covered) if cnt >= 2)

    states: dict[tuple[int, int], int] = {(one, two): 0}
    for wage, mask in free:  # free 已按工资升序，先扫到的零工更便宜
        nxt = dict(states)  # 这一轮不雇他的所有旧状态
        for (a, b), cost in states.items():
            new_two = b | (a & mask)  # 原本恰好一人、又被他补一刀的菜凑满两名
            key = ((a | mask) & ~new_two, new_two)
            if nxt.get(key, INF) > cost + wage:
                nxt[key] = cost + wage
        states = nxt

    return min(cost for (_one, b), cost in states.items() if b == all_dishes)


def solve() -> None:
    lines = iter(sys.stdin.read().splitlines())
    s, n, m = map(int, next(lines).split())

    # 每名厨师的菜品清单独占一行，只能按行读，不能把所有数字混成一个流。
    relative_wage = 0
    covered = [0] * s  # covered[d] = 亲戚里会做菜 d+1 的人数（封顶前）
    for _ in range(n):
        parts = next(lines).split()
        relative_wage += int(parts[0])  # 亲戚必须保留，工资无条件照付
        for d in map(int, parts[1:]):
            covered[d - 1] += 1
    covered = [min(cnt, 2) for cnt in covered]  # 覆盖数超过 2 与恰好 2 等价

    free: list[tuple[int, int]] = []
    for _ in range(m):
        parts = list(map(int, next(lines).split()))
        free.append((parts[0], cook_mask(parts[1:])))  # (工资, 会做的菜)
    free.sort()

    print(relative_wage + min_extra_wage(free, covered))


if __name__ == "__main__":
    solve()
