#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:45
# update_at: 2026-09-29 16:45

import sys


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))                            # 样本容量 n
    samples = [float(next(data)) for _ in range(n)]  # n 个浮点样本
    mean = sum(samples) / n                # 均值 = 总和 / 容量
    print(f"{mean:.4f}")


if __name__ == "__main__":
    solve()
