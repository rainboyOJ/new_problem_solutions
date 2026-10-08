#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 19:48
# update_at: 2026-10-08 19:48

A = 15.0      # 梯形上底（题图标注 15）
B = 25.0      # 梯形下底（题图标注 25）
SHADED = 150.0  # 阴影三角形面积


def solve() -> None:
    """阴影三角形以梯形上底为底、顶点在下底所在直线上，故其高即梯形的高。"""
    height = SHADED * 2.0 / A              # 先求梯形的高
    print(f"{(A + B) * height / 2.0:.2f}")  # 梯形面积，保留两位小数


if __name__ == "__main__":
    solve()
