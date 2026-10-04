#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:33
# update_at: 2026-10-02 19:33

import sys


def encode(time_text: str) -> tuple[str, str]:
    """把 HH:MM:SS 摊成 3×6 比特矩阵，返回竖着按列、横着按行取出的两个 18 位串。"""
    # 时、分、秒各补零写成 6 位二进制，各占矩阵一行（时 <= 23、分秒 <= 59 都放得下）
    rows = [f"{value:06b}" for value in map(int, time_text.split(":"))]  # 3 行
    vertical = "".join(map("".join, zip(*rows)))  # 按列读：每列自上而下按时、分、秒取
    horizontal = "".join(rows)                    # 按行读：三行首尾相接
    return vertical, horizontal


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    time_text = next(data).decode()  # 整行只有一个 HH:MM:SS token
    print(*encode(time_text))


if __name__ == "__main__":
    solve()
