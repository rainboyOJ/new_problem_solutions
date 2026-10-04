#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def shadow_len(x: float, H: float, h: float, D: float) -> float:
    """计算人距灯泡水平距离为 x 时的总影子长度（地面部分 + 墙面部分）。"""
    split_x = D * (H - h) / H
    return x * h / (H - h) if x <= split_x else D - x + H - D * (H - h) / x


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    test_cases = int(next(it))

    for _ in range(test_cases):
        H, h, D = float(next(it)), float(next(it)), float(next(it))
        low, high = 0.0, D
        for _ in range(80):
            m1 = low + (high - low) / 3.0
            m2 = high - (high - low) / 3.0
            if shadow_len(m1, H, h, D) < shadow_len(m2, H, h, D):
                low = m1
            else:
                high = m2
        print(f"{shadow_len(low, H, h, D):.3f}")


if __name__ == "__main__":
    solve()
