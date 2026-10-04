#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 18:45
# update_at: 2026-10-01 18:45

import sys

COVER: list[int] = []       # 每个节点被整段盖住的次数：只记在最高的大节点上，不下传
SEGMENT: list[int] = []     # 该节点内部「被盖住的极大区间」个数
LEFT_ON: list[int] = []     # 最左元区间是否被盖住
RIGHT_ON: list[int] = []    # 最右元区间是否被盖住


def build(coords: list[int]) -> int:
    """按压缩坐标建一棵空树，返回元区间（相邻两个坐标之间）的个数。"""
    global COVER, SEGMENT, LEFT_ON, RIGHT_ON
    leaves = len(coords) - 1
    size = 4 * leaves + 4
    COVER = [0] * size
    SEGMENT = [0] * size
    LEFT_ON = [0] * size
    RIGHT_ON = [0] * size
    return leaves


def pull(node: int, nl: int, nr: int) -> None:
    """由两个孩子的覆盖信息重算 node 的区间个数与左右端标志。"""
    if COVER[node]:                      # 整段被盖住，内部必然只剩一个极大区间
        SEGMENT[node] = 1
        LEFT_ON[node] = RIGHT_ON[node] = 1
    elif nl == nr:                       # 叶子且没被盖住
        SEGMENT[node] = 0
        LEFT_ON[node] = RIGHT_ON[node] = 0
    else:
        left, right = node << 1, node << 1 | 1
        # 两孩子在交界处都被盖住时，它们其实属于同一个极大区间，要减去这一次重复
        SEGMENT[node] = SEGMENT[left] + SEGMENT[right] - (RIGHT_ON[left] & LEFT_ON[right])
        LEFT_ON[node] = LEFT_ON[left]
        RIGHT_ON[node] = RIGHT_ON[right]


def update(node: int, nl: int, nr: int, ql: int, qr: int, val: int) -> None:
    """把元区间 [ql, qr] 的覆盖次数加上 val：val = 1 加矩形，val = -1 删矩形。"""
    if ql <= nl and nr <= qr:
        COVER[node] += val
        pull(node, nl, nr)
        return
    mid = (nl + nr) >> 1
    if ql <= mid:
        update(node << 1, nl, mid, ql, qr, val)
    if qr > mid:
        update(node << 1 | 1, mid + 1, nr, ql, qr, val)
    pull(node, nl, nr)


def sweep(rects: list[tuple[int, int, int, int]]) -> int:
    """沿第一个坐标扫描，返回平行于扫描方向的那些边的总长。

    rects 每项是 (起点, 终点, 区间下端, 区间上端)。相邻两个扫描位置之间截面是不变的，
    该条带上截面里每个极大区间都会有两个端点各扫出一条平行于扫描方向的边，
    所以贡献是 2 * 极大区间个数 * 条带宽；把每个条带加起来就是对 2 * 极大区间个数 求积分。
    """
    coords = sorted({v for r in rects for v in r[2:]})
    leaves = build(coords)
    if leaves <= 0:                      # 连一个元区间都没有，也就没有边
        return 0
    index_of = {v: i for i, v in enumerate(coords)}
    events = sorted(
        [(r[0], index_of[r[2]], index_of[r[3]] - 1, 1) for r in rects]
        + [(r[1], index_of[r[2]], index_of[r[3]] - 1, -1) for r in rects]
    )

    total = 0
    last = events[0][0]                  # 第一个事件开出一条空条带，(first, first) 宽度为 0
    for pos, lo, hi, val in events:
        width = pos - last               # 同一位置上的多个事件之间宽度为 0，不影响结果
        total += 2 * SEGMENT[1] * width  # 截面上每个极大区间贡献上下两条平行于扫描方向的边
        last = pos
        update(1, 0, leaves - 1, lo, hi, val)
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 题面给的 (x1, y1, x2, y2) 是左下角 / 右上角，这里整理成 (起点, 终点, 下端, 上端)
    rects: list[tuple[int, int, int, int]] = []
    for _ in range(n):
        x1, y1, x2, y2 = next(data), next(data), next(data), next(data)
        rects.append((min(x1, x2), max(x1, x2), min(y1, y2), max(y1, y2)))

    # 竖直边的总长 = 把矩形转 90°（交换 x / y 两个方向）后再照同一套扫描线求一次
    vertical = [(lo, hi, start, end) for start, end, lo, hi in rects]
    print(sweep(rects) + sweep(vertical))


if __name__ == "__main__":
    solve()
