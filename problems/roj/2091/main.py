#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 08:40
# update_at: 2026-10-01 08:40

# x、y 上只有 2N 个坐标会真正切开覆盖状态，其余整数都夹在中间陪跑；压成条带之后，
# 相邻两行只差几个事件，于是「逐行比较覆盖状态」可以整段交给 numpy 向量化。

import sys

import numpy as np


def compress(lo: np.ndarray, hi: np.ndarray) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    """一维坐标压缩：返回 (每条带的真实宽度, 每条带起点下标, 终点下标)。"""
    edges = np.unique(np.concatenate((lo, hi)))     # 只有这些坐标会切开覆盖状态
    return np.diff(edges), np.searchsorted(edges, lo), np.searchsorted(edges, hi)


def events_by_row(
    Y: np.ndarray, Y2: np.ndarray, X: np.ndarray, X2: np.ndarray, ny: int
) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    """把 4N 个扫描线事件按 y 区间分桶，返回 (差分位置, 增量, 桶边界)。

    每个矩形贡献四个事件：进入时在左端 +1、右端 -1，离开时施加相反的一对，
    使得前缀和恰好等于「该 y 区间内被覆盖的条带」。
    """
    sign = np.ones(len(Y), dtype=np.int64)
    row = np.concatenate((Y, Y, Y2, Y2))            # 依次对应下面 4 个事件块
    pos = np.concatenate((X, X2, X, X2))
    inc = np.concatenate((sign, -sign, -sign, sign))
    order = np.argsort(row, kind='stable')          # 按行分桶，同一行事件之间的次序无关
    pos, inc = pos[order], inc[order]
    bounds = np.searchsorted(row[order], np.arange(ny + 1))   # 第 i 行的事件是 [bounds[i], bounds[i+1])
    return pos, inc, bounds


def perimeter(
    pos: np.ndarray, inc: np.ndarray, bounds: np.ndarray, dx: np.ndarray, dy: np.ndarray
) -> int:
    """自下而上扫描，累加轮廓：水平边看相邻两行的差异，竖直边看行内的翻转。"""
    level = np.zeros(len(dx) + 1, dtype=np.int64)   # x 方向差分；末尾一格接「最右端之后的 -1」
    prev = np.zeros(len(dx), dtype=bool)            # 上一行的覆盖状态，最下面一行的下面是空的
    ans = 0
    for i in range(len(dy)):
        lo, hi = bounds[i], bounds[i + 1]
        np.add.at(level, pos[lo:hi], inc[lo:hi])    # 逐事件累加，同一条带上的多个事件不能互相覆盖
        cover = np.cumsum(level[:len(dx)]) > 0
        horizontal = int(dx[cover != prev].sum())   # 与上一行状态不同的条带，整段露出水平边
        border = int(cover[0]) + int(cover[-1]) + int(np.count_nonzero(cover[1:] != cover[:-1]))
        ans += horizontal + int(dy[i]) * border     # 竖直边 = 本行左右两端 + 行内翻转处
        prev = cover
    return ans + int(dx[prev].sum())                # 最上面一行之上没有矩形，顶部整条边界都算


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    rects = np.array(
        [(next(data), next(data), next(data), next(data)) for _ in range(n)],
        dtype=np.int64,
    )                                                  # 左下角、右上角拆成四列
    x1, y1, x2, y2 = rects.T

    dx, X, X2 = compress(x1, x2)
    dy, Y, Y2 = compress(y1, y2)
    pos, inc, bounds = events_by_row(Y, Y2, X, X2, len(dy))
    print(perimeter(pos, inc, bounds, dx, dy))


if __name__ == "__main__":
    solve()
