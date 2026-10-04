#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:44
# update_at: 2026-10-01 04:44

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    A, B, n = next(data), next(data), next(data)

    # rects[0] 是白纸，之后按放置顺序叠放：后放者盖住先放者
    rects: list[tuple[int, int, int, int, int]] = [
        (0, 0, A, B, 1)  # 底层的白纸：颜色 1
    ]
    for _ in range(n):
        rects.append(
            tuple(next(data) for _ in range(5))  # llx, lly, urx, ury, color
        )
    rects.reverse()  # 倒序：从最顶层往下找，第一个盖住点的长方形即最终颜色

    # 坐标压缩：只保留出现过的 x/y（左下角与右上角都要收进来）
    xs = sorted({v for llx, _, urx, _, _ in rects for v in (llx, urx)})
    ys = sorted({v for _, lly, _, ury, _ in rects for v in (lly, ury)})
    nx, ny = len(xs) - 1, len(ys) - 1            # 格子数比坐标数少 1
    idx_x = {x: i for i, x in enumerate(xs)}     # 坐标 -> 压缩下标
    idx_y = {y: i for i, y in enumerate(ys)}

    # 长方形转成压缩下标后的格子区间 [x0, x1) x [y0, y1)：与原矩形覆盖完全相同的格子集合
    crects = [
        (idx_x[llx], idx_y[lly], idx_x[urx], idx_y[ury], color)
        for llx, lly, urx, ury, color in rects
    ]

    # ans[i][j] = 格子 (i, j)（x∈[xs[i],xs[i+1]], y∈[ys[j],ys[j+1]]）最终的颜色
    ans: list[list[int]] = [
        [
            next(  # 自顶向下第一个覆盖格子的长方形决定该格颜色
                color
                for x0, y0, x1, y1, color in crects
                if x0 <= i < x1 and y0 <= j < y1
            )
            for j in range(ny)
        ]
        for i in range(nx)
    ]

    area = [0] * 1001  # 颜色编号 1..1000，area[c] 为可见面积
    for i in range(nx):
        for j in range(ny):
            area[ans[i][j]] += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j])

    print('\n'.join(f'{c} {area[c]}' for c in range(1, 1001) if area[c]))


if __name__ == "__main__":
    solve()
