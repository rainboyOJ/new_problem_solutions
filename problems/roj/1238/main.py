#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:12
# update_at: 2026-09-30 01:12

import sys

EPS = 1e-5  # 判根阈值：网格点处 |f(x)| ≤ 1e-5 即认为是根（与评测参考实现一致）


def solve() -> None:
    a, b, c, d = map(float, sys.stdin.buffer.read().split())

    def f(x: float) -> float:
        """方程左端 ax^3+bx^2+cx+d 在 x 处的取值（秦九韶形式）。"""
        return ((a * x + b) * x + c) * x + d

    roots: list[float] = []
    x = -100.0
    for _ in range(3):  # 依次找最小、次小、最大的根
        while x - 100 <= EPS:  # 网格从 -100 扫到 100（含端点，与参考实现一致）
            if abs(f(x)) <= EPS:
                break  # 命中一个根：根是两位小数且两两之差 ≥ 1，步长 0.01 必能扫到
            x += 0.01
        roots.append(x)  # 命中的网格点；若数据不满足"三个实根"约定则与参考实现同样扫到界外
        x += 0.01  # 跳过当前根所在的网格点，继续找下一个根

    print(' '.join(f'{r:.2f}' for r in roots))


if __name__ == "__main__":
    solve()
