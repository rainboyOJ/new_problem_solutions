#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 13:00
# update_at: 2026-10-02 13:00

import sys


def find(fa: list[int], x: int) -> int:
    """并查集查根：路径压缩，把沿途节点直接挂到根上。"""
    while fa[x] != x:
        fa[x] = fa[fa[x]]
        x = fa[x]
    return x


def union(fa: list[int], a: int, b: int) -> None:
    """把 a、b 所属的连通块合并成一个。"""
    ra, rb = find(fa, a), find(fa, b)
    if ra != rb:
        fa[rb] = ra


def can_escape(holes: list[tuple[int, int, int]], h: int, r: int) -> bool:
    """能否借助相切/相交的空洞从下表面走到上表面。

    最后两个元素是虚拟节点，分别代表下表面与上表面；两球相切或相交
    等价于球心距离不大于 2r，用平方比较避免开方。
    """
    holes.sort(key=lambda hole: hole[2])  # 按 z 升序，方便只检查 z 窗口内的球对
    bottom, top = len(holes), len(holes) + 1
    fa = list(range(len(holes) + 2))
    reach, link = 2 * r, 4 * r * r  # 球心 z 差上限、球心距离平方上限

    for i, (x, y, z) in enumerate(holes):
        if z <= r:  # 与下表面 z = 0 相交或相切
            union(fa, bottom, i)
        if z + r >= h:  # 与上表面 z = h 相交或相切
            union(fa, top, i)

    for i, (x1, y1, z1) in enumerate(holes):
        for j, (x2, y2, z2) in enumerate(holes[i + 1:], i + 1):
            if z2 - z1 > reach:  # 已排序，后面的球 z 只会更大，窗口到头了
                break
            if (x1 - x2) ** 2 + (y1 - y2) ** 2 + (z1 - z2) ** 2 <= link:
                union(fa, i, j)

    return find(fa, bottom) == find(fa, top)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, h, r = next(data), next(data), next(data)
        holes = [(next(data), next(data), next(data)) for _ in range(n)]  # n 个球心
        out.append('Yes' if can_escape(holes, h, r) else 'No')

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
