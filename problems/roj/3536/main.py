#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:05
# update_at: 2026-10-02 06:05

import sys

STOOL = 30  # 板凳高度（厘米）：直接够不到时，踩上板凳再伸手


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))

    heights = [next(data) for _ in range(10)]  # 10 个苹果到地面的高度
    reach = next(data) + STOOL                 # 踩上板凳后能达到的最大高度

    print(sum(height <= reach for height in heights))  # 碰到即摘到，数一遍即可


if __name__ == "__main__":
    solve()
