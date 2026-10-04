#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 07:09
# update_at: 2026-10-01 07:09

import sys

# 8 种等距变换（D4 群）：原样、上下翻、左右翻、旋转 180°、旋转 90°/270° 及其组合
D4 = (
    lambda r, c: (r, c),
    lambda r, c: (-r, c),
    lambda r, c: (r, -c),
    lambda r, c: (-r, -c),
    lambda r, c: (c, -r),
    lambda r, c: (-c, -r),
    lambda r, c: (c, r),
    lambda r, c: (-c, r),
)


def canonical(shape: frozenset[tuple[int, int]]) -> tuple[tuple[int, int], ...]:
    """形状的规范指纹：8 种变换各自平移到最小行列后，取字典序最小的形态。"""

    def at_origin(pts: frozenset[tuple[int, int]]) -> tuple[tuple[int, int], ...]:
        r0 = min(r for r, _ in pts)
        c0 = min(c for _, c in pts)
        return tuple(sorted((r - r0, c - c0) for r, c in pts))

    # 注意不能用 min 比较 frozenset：< 对集合是子集判断而非全序，同构形状会选出不同代表
    return min(at_origin(frozenset(f(r, c) for r, c in shape)) for f in D4)


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    width, depth = int(tokens[0]), int(tokens[1])
    grid = [row.decode() for row in tokens[2:2 + depth]]
    cells = {(r, c) for r, row in enumerate(grid) for c, ch in enumerate(row) if ch == '1'}

    marks: dict[tuple, str] = {}  # 形状指纹 -> 已分配的小写字母
    while cells:
        # 网格里坐标最小的剩余星星必是它所在星座的最左上角，从它出发洪填整个连通块
        start = min(cells)
        comp: set[tuple[int, int]] = {start}
        frontier = [start]
        while frontier:
            r, c = frontier.pop()
            for dr in (-1, 0, 1):
                for dc in (-1, 0, 1):
                    p = (r + dr, c + dc)
                    if p in cells and p not in comp:
                        comp.add(p)
                        frontier.append(p)
        cells -= comp

        key = canonical(frozenset(comp))
        mark = marks.setdefault(key, chr(ord('a') + len(marks)))
        for r, c in comp:
            grid[r] = grid[r][:c] + mark + grid[r][c + 1:]

    print('\n'.join(grid))


if __name__ == "__main__":
    solve()
