#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:33
# update_at: 2026-09-30 01:38

from math import sin, cos

EPS = 1e-12  # 二分终止精度：角度差小于它就不再细分（与 std.cpp 的 E 一致）


def solve() -> None:
    length, n, c = map(float, input().split())
    expanded = (1 + n * c) * length  # 受热后的弧长 L'

    # 圆心角 θ 唯一：半径 r = L'/θ，弦长 2r·sin(θ/2)，要求弦长恰等于原长 L。
    # 弦长关于 θ 严格递减（θ→0 时弦→弧长 L'，θ=π 时弦=2L'/π 的最小值），可二分。
    lo, hi = 0.0, 3.15  # 上界取略大于 π 即可覆盖弧长 ≤ 1.5L 的全部情形
    while hi - lo > EPS:
        mid = (lo + hi) / 2
        chord_too_long = 2 * expanded * sin(mid / 2) / mid > length  # 该角度下的弦长
        if chord_too_long:
            lo = mid  # 弦偏长说明还不够弯，角度要变大
        else:
            hi = mid

    # 中心偏移 = 弓形高 = r - r·cos(θ/2)，其中 r = L' / θ
    radius = expanded / hi
    print(f"{radius * (1 - cos(hi / 2)):.3f}")


if __name__ == "__main__":
    solve()
