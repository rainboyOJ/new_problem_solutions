#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 01:37
# update_at: 2026-10-01 01:37

import sys


def repeated_pair(colors: str) -> tuple[int, int] | None:
    """返回那两支同色笔的编号（较小, 较大）；16 支笔颜色全不同时返回 None。

    题面保证同色最多两支：边扫边记每种颜色首次出现的编号，第二次遇到即成答案，
    且先登记的编号一定更小，天然满足"先小后大"。
    """
    first: dict[str, int] = {}  # 颜色 -> 该颜色首次出现的笔编号
    for pos, color in enumerate(colors, 1):
        seen = first.get(color)  # 这个颜色之前登过记吗
        if seen is not None:
            return seen, pos
        first[color] = pos
    return None


def solve() -> None:
    colors = sys.stdin.buffer.read().decode().strip()
    pair = repeated_pair(colors)
    print("different" if pair is None else f"{pair[0]} {pair[1]}")


if __name__ == "__main__":
    solve()
