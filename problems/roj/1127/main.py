#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:02
# update_at: 2026-09-29 20:02

import sys


def solve() -> None:
    """顺时针旋转 90 度后输出图像。"""
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    n = next(it)          # 行数
    m = next(it)          # 列数
    a = [[next(it) for _ in range(m)] for _ in range(n)]  # n × m 像素矩阵

    # 旋转后尺寸为 m × n：新图第 i 行是原图第 i 列从下到上读取
    out = [
        ' '.join(str(a[n - 1 - j][i]) for j in range(n))
        for i in range(m)
    ]
    sys.stdout.write('\n'.join(out))


if __name__ == "__main__":
    solve()
