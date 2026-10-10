#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 21:00
# update_at: 2026-10-09 21:45

import sys


def check(L: int, n: int, pts: list[tuple[int, int]]) -> bool:
    """判定能否放下边长 L 的正方形：合法左上角域 [1,lim]^2 是否被禁放矩形全覆盖。"""
    if L > n:
        return False
    lim = n - L + 1

    xs = [1, n - L + 2]  # 搜索域左右哨兵（右端取开区间）
    ys = [1, n - L + 2]
    rects: list[tuple[int, int, int, int]] = []  # 禁放矩形 (x1, x2, y1, y2)，半开 [x1,x2) × [y1,y2)
    for x, y in pts:
        x1, x2 = max(1, x - L + 1), min(lim, x) + 1
        y1, y2 = max(1, y - L + 1), min(lim, y) + 1
        if x1 < x2 and y1 < y2:
            rects.append((x1, x2, y1, y2))
            xs += [x1, x2]
            ys += [y1, y2]

    xs = sorted(set(xs))
    ys = sorted(set(ys))
    xi = {v: i for i, v in enumerate(xs)}
    yi = {v: i for i, v in enumerate(ys)}
    xn, yn = len(xs), len(ys)

    diff = [[0] * yn for _ in range(xn)]
    for x1, x2, y1, y2 in rects:  # 矩形区间加一：二维差分
        i1, i2, j1, j2 = xi[x1], xi[x2], yi[y1], yi[y2]
        diff[i1][j1] += 1
        diff[i2][j1] -= 1
        diff[i1][j2] -= 1
        diff[i2][j2] += 1

    for i in range(xn - 1):  # 二维前缀和原位还原（diff 复用为 cov）
        row = diff[i]
        pre = diff[i - 1] if i else None
        for j in range(yn - 1):
            v = row[j] + (pre[j] if i else 0) + (row[j - 1] if j else 0)
            if i and j:
                v -= pre[j - 1]
            row[j] = v
            if v == 0 and xs[i] <= lim and ys[j] <= lim:
                return True
    return False


def solve() -> None:
    """二分答案：答案关于边长单调，故二分最大可行边长，答案为 0 表示放不下任何正方形。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:
        return
    T = next(data)
    pts = [(next(data), next(data)) for _ in range(T)]

    lo, hi, ans = 1, n, 0
    while lo <= hi:
        mid = (lo + hi) // 2
        if check(mid, n, pts):
            ans, lo = mid, mid + 1
        else:
            hi = mid - 1
    print(ans)


if __name__ == '__main__':
    solve()
