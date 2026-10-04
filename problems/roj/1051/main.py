#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:21
# update_at: 2026-09-29 16:21

import sys

# 三段分支按区间起点排序：[(起点, 表达式)]，x 落在最后一个起点 ≤ x 的段里。
PIECES = [
    (0.0, lambda x: -x + 2.5),                       # 0 ≤ x < 5
    (5.0, lambda x: 2 - 1.5 * (x - 3) * (x - 3)),    # 5 ≤ x < 10
    (10.0, lambda x: x / 2 - 1.5),                   # 10 ≤ x < 20
]


def f(x: float) -> float:
    """分段函数值：取起点不超过 x 的最后一段的表达式计算。"""
    formula = [formula for start, formula in PIECES if start <= x][-1]
    return formula(x)


def solve() -> None:
    x = float(sys.stdin.buffer.read())
    print(f"{f(x):.3f}")


if __name__ == "__main__":
    solve()
