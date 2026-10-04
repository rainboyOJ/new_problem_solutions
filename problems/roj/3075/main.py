#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
from collections import defaultdict
from itertools import count


def build_grid(n: int) -> list[tuple[int, ...]]:
    """完整 n×n 网格里所有正方形各自用到哪些火柴编号，按边长从小到大排列。

    编号规则（进阶指南版）：把网格逐行展平，每行占 2n+1 个位置——
    先是该横线的 n 根火柴，再是该行上侧的 n+1 根竖火柴；底部横线之后没有竖火柴。
    """
    dd = 2 * n + 1  # 展平后每行的位置数

    def h(r: int, j: int) -> int:
        """第 r 条横线上第 j 段（自左向右）的编号。"""
        return r * dd + j + 1

    def v(c: int, r: int) -> int:
        """第 c 条竖线（自左向右）上第 r 段（自上而下）的编号。"""
        return r * dd + c + n + 1

    return [
        tuple(
            {h(i, j + t) for t in range(size)} | {h(i + size, j + t) for t in range(size)}
            | {v(j, i + t) for t in range(size)} | {v(j + size, i + t) for t in range(size)}
        )
        for size in range(1, n + 1)
        for i in range(n - size + 1)
        for j in range(n - size + 1)
    ]


def min_removals(n: int, missing: set[int]) -> int:
    """已经缺了 missing 这些火柴，再抽走最少几根才能破坏所有正方形（IDA* 重复覆盖）。"""
    squares = [ids for ids in build_grid(n) if not (set(ids) & missing)]  # 尚存的正方形
    if not squares:
        return 0
    stick_sq: dict[int, int] = defaultdict(int)  # 火柴 -> 它参与的正方形位掩码
    for idx, ids in enumerate(squares):
        for s in ids:
            stick_sq[s] |= 1 << idx

    # (正方形位, 整组火柴位掩码, 分支用的火柴列表)，按边长升序 ⇒ 第一个存活的即最小正方形
    alive = [(1 << idx, sum(1 << s for s in ids),
              sorted(ids, key=lambda s: -stick_sq[s].bit_count()))
             for idx, ids in enumerate(squares)]

    def lower_bound(full: int) -> int:
        """估价函数：贪心挑互不相交的存活正方形，每根火柴至多破坏其中一个，故为答案下界。"""
        cnt = 0
        taken = 0  # 已被选中正方形占用的火柴
        for bit, smask, _ in alive:
            if full & bit and not (smask & taken):
                cnt += 1
                taken |= smask
        return cnt

    def dfs(budget: int, full: int) -> bool:
        """还能抽 budget 根，能否破坏 full 位掩码里的所有正方形。"""
        if not full:
            return True
        if budget == 0 or lower_bound(full) > budget:
            return False
        # 最小正方形必须被破坏，枚举抽走它的哪根火柴
        bit, _, ids = next(entry for entry in alive if full & entry[0])
        return any(dfs(budget - 1, full & ~stick_sq[s]) for s in ids)

    full0 = (1 << len(squares)) - 1
    for depth in count(max(1, lower_bound(full0))):  # IDA*：逐层加深，首个可行深度即答案
        if dfs(depth, full0):
            return depth


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)
    for _ in range(T):
        n = next(data)
        k = next(data)
        missing = {next(data) for _ in range(k)}  # 题面已缺的火柴编号
        out.append(str(min_removals(n, missing)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
