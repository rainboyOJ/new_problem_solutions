#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

ALL_ODD = (1 << 6) - 1  # 6 个价值全部为奇数时的位掩码：第 v 位 = 1 表示 a[v] 是奇数


def half_reachable(a: list[int]) -> bool:
    """价值总和的一半能否由各价值取 0..a[v] 个凑出（多重背包可行性）。"""
    half, total = divmod(sum((v + 1) * cnt for v, cnt in enumerate(a)), 2)
    if total:  # 总价值为奇数，无法平分
        return False

    reach = 1  # reach 的第 s 位 = 1：恰好凑出价值 s；初始只有 0 可达
    for v, cnt in enumerate(a):
        for _ in range(cnt):  # 朴素多重背包：逐个加入该价值的每一块
            reach |= reach << v + 1  # 每块贡献价值 v+1，更新可达和集合
            reach &= (1 << half + 1) - 1  # 超过 half 的部分对答案无用，截断
    return reach >> half & 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    while any(a := [next(data) for _ in range(6)]):  # 全 0 行是结束标志
        odd_mask = sum((cnt & 1) << v for v, cnt in enumerate(a))  # a[v] 为奇数 → 第 v 位
        can = half_reachable(a) if odd_mask != ALL_ODD else False  # 全奇数时总和为奇数
        out.append("Can" if can else "Can't")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
