#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 15:53
# update_at: 2026-10-01 15:53

import sys

COLORS = range(6)      # 颜色编号 0..5
DR = (-1, 0, 1, 0)     # 上、右、下、左
DC = (0, 1, 0, -1)


def neighbors(idx: int, n: int) -> list[int]:
    """格子 idx（按 r*n+c 编号）的相邻格子编号列表。"""
    r, c = divmod(idx, n)
    return [(r + dr) * n + (c + dc)
            for dr, dc in zip(DR, DC)
            if 0 <= r + dr < n and 0 <= c + dc < n]


def start_mask(grid: list[int], nei: list[list[int]]) -> int:
    """初始时与左上角同色连通的区域（位掩码，第 i 位表示第 i 个格子）。"""
    seen = 1
    stack = [0]
    while stack:
        i = stack.pop()
        for j in nei[i]:
            if grid[j] == grid[0] and not seen >> j & 1:
                seen |= 1 << j
                stack.append(j)
    return seen


def expand(grid: list[int], nei: list[list[int]], mask: int, color: int) -> int:
    """区域染成 color 后能吞并的格子：相邻的 color 色格及其连通块。"""
    gained = 0
    # 种子：紧贴区域的 color 色格；再沿同色格 BFS 扩到整个连通块
    stack = [j for i in range(len(nei)) if mask >> i & 1
             for j in nei[i] if grid[j] == color and not mask >> j & 1]
    while stack:
        i = stack.pop()
        if gained >> i & 1:
            continue
        gained |= 1 << i
        stack += [j for j in nei[i]
                  if grid[j] == color and not (mask | gained) >> j & 1]
    return mask | gained


def remaining_colors(color_mask: list[int], mask: int) -> int:
    """还没被吞并的颜色种数：一步只能整块吞掉一种颜色，故它是剩余步数下界。"""
    return sum(cm & ~mask != 0 for cm in color_mask)


def dfs(grid: list[int], nei: list[list[int]], color_mask: list[int],
        full: int, mask: int, left: int) -> bool:
    """IDA* 深度受限搜索：能否再用 left 步吞满整个棋盘。"""
    if mask == full:
        return True
    if remaining_colors(color_mask, mask) > left:
        return False
    # 不同颜色可能吞出同一个局面，用集合去重；先试启发值小的分支，剪枝更早生效
    succ = sorted({expand(grid, nei, mask, c) for c in COLORS} - {mask},
                  key=lambda m: remaining_colors(color_mask, m))
    return any(dfs(grid, nei, color_mask, full, m, left - 1) for m in succ)


def solve_case(n: int, rows: list[list[int]]) -> int:
    """单个棋盘的最少步数：IDA* 从启发函数给出的下界开始逐步加深。"""
    grid = [v for row in rows for v in row]
    nei = [neighbors(i, n) for i in range(n * n)]
    full = (1 << (n * n)) - 1
    # color_mask[c]：颜色 c 的所有格子组成的位掩码
    color_mask = [sum(1 << i for i in range(n * n) if grid[i] == c)
                  for c in COLORS]
    mask = start_mask(grid, nei)
    if mask == full:
        return 0
    depth = remaining_colors(color_mask, mask)  # 最优解不会小于这个下界
    while not dfs(grid, nei, color_mask, full, mask, depth):
        depth += 1
    return depth


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    while (n := next(data)) != 0:
        rows: list[list[int]] = []
        for _ in range(n):
            rows.append([next(data) for _ in range(n)])
        out.append(str(solve_case(n, rows)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
