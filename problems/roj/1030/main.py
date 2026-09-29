#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

PI = 3.14  # 题面指定的圆周率取值，不取 math.pi


def solve() -> None:
    radius: float = float(input())                     # 半径 r，非负实数
    volume: float = 4 / 3 * PI * radius**3             # 球体积 v = 4/3·π·r³
    print(f"{volume:.2f}")                             # 保留 2 位小数（不足补 0）


if __name__ == "__main__":
    solve()
