#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:05
# update_at: 2026-10-01 03:05

import sys
from itertools import permutations, product

BASE = 4          # 题目固定 4 个矩形块


def enclosing_sizes(placed: list[tuple[int, int]]) -> list[tuple[int, int]]:
    """计算六种基本铺放方案的封闭矩形 (宽, 高)；方案 4、5 实为同一拓扑。

    前置约定：placed 已按方案图的编号排好序——方案 1~3 中矩形 4
    在右侧/下方独立伸出，方案 4~6 中矩形 1、3 叠放在左柱，
    矩形 2、4（方案 6 记号里为 2、3）分跨右柱与横梁。
    """
    w1, h1, w2, h2, w3, h3, w4, h4 = sum(placed, ())
    beam = (w1 + max(w2, w4) + w3, max(h1, h3, h2 + h4))          # 方案 4/5：双柱加横梁
    # 方案 6：风车形。凸出矩形只盖住自己柱子时，另一柱可以完全嵌进缺口里
    if h3 >= h2 + h4:
        width = max(w1, w2 + w3, w3 + w4)
    elif h3 > h4:                                                  # 矩形 3 凸出，矩形 4 需让出宽 w1+w2
        width = max(w1 + w2, w2 + w3, w3 + w4)
    elif h4 > h3:                                                  # 矩形 4 凸出，矩形 3 需让出宽 w1+w2
        width = max(w1 + w2, w1 + w4, w3 + w4)
    elif h4 >= h1 + h3:                                            # 矩形 4 只盖住矩形 1，矩形 3 完全嵌进
        width = max(w2, w1 + w4, w3 + w4)
    else:                                                          # h3 == h4：两柱平齐，谁也不盖谁
        width = max(w1 + w2, w3 + w4)
    pinwheel = (width, max(h1 + h3, h2 + h4))
    return [
        (w1 + w2 + w3 + w4, max(h1, h2, h3, h4)),                  # 方案 1：一字排开
        (max(w1 + w2 + w3, w4), max(h1, h2, h3) + h4),             # 方案 2：三下一上
        (max(w1 + w2, w3) + w4, max(h1 + h3, h2 + h3, h4)),        # 方案 3：两左一右上，矩形 4 立在右侧
        beam,
        pinwheel,
    ]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    blocks = [(next(data), next(data)) for _ in range(BASE)]

    best_area = sys.maxsize                                        # 最小封闭矩形面积
    solutions: set[tuple[int, int]] = set()                        # 取到最小面积的所有 (p, q)
    for order in permutations(blocks):                             # 枚举每个图位放哪个矩形
        for turned in product(*[((a, b), (b, a)) for a, b in order]):  # 枚举每个矩形横放/竖放
            for width, height in enclosing_sizes(list(turned)):
                area = width * height
                if area < best_area:
                    best_area = area
                    solutions = {(min(width, height), max(width, height))}
                elif area == best_area:
                    solutions.add((min(width, height), max(width, height)))

    print(best_area)
    for p, q in sorted(solutions):
        print(p, q)


if __name__ == "__main__":
    solve()
