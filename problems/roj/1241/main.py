#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:19
# update_at: 2026-09-30 01:27

LEFT = 1.5    # 题面保证 f(LEFT) > 0
RIGHT = 2.4   # 题面保证 f(RIGHT) < 0
EPS = 1e-12   # 区间宽度缩到 1e-12，比要求的 1e-6 精度小 6 个数量级


def f(x: float) -> float:
    """题面函数 f(x) 在 x 处的取值，用秦九韶（Horner）形式求值。"""
    return ((((x - 15) * x + 85) * x - 225) * x + 274) * x - 121


def solve() -> None:
    """在唯一零点已知所在区间上二分，输出四舍五入到 6 位小数的根。"""
    left, right = LEFT, RIGHT  # 不变量：f(left) > 0 且 f(right) < 0，零点始终被区间夹住
    while right - left > EPS:
        mid = (left + right) / 2
        if f(mid) > 0:
            left = mid   # 中点为正当，零点落在右半段
        else:
            right = mid  # 中点为负，零点落在左半段
    print(f"{(left + right) / 2:.6f}")


if __name__ == "__main__":
    solve()
