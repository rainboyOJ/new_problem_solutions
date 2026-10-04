#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 14:05
# update_at: 2026-09-29 14:05

import sys

# 题面要求的四种格式：%f、%f 保留 5 位小数、%e、%g（与 C 的 printf 同义）
FORMATS = ('{:.6f}', '{:.5f}', '{:.6e}', '{:g}')


def solve() -> None:
    x = float(sys.stdin.readline())  # 输入只有一个双精度浮点数
    print('\n'.join(f.format(x) for f in FORMATS))


if __name__ == "__main__":
    solve()
