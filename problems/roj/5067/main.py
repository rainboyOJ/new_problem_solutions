#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 02:08
# update_at: 2026-10-09 02:08

import sys

DISC = 0.8      # 8 折 = 按原价的 80% 付款
ZERO_EPS = 1e-6  # 零附近归一化阈值


def solve() -> None:
    """读入 n、m，输出买书后剩余的钱（保留 2 位小数：n - 0.8*m）。"""
    # 题面未声明类型，随仓 10 点实测全为整数（最大 10^6）；用 float 读入同时兼容小数金额，
    # 与 C++ 侧 scanf("%lf") / cin >> double 语义一致。
    data = iter(sys.stdin.buffer.read().split())
    n_tok = next(data, None)
    m_tok = next(data, None)
    if n_tok is None or m_tok is None:  # 题面保证有两个数；缺输入时不输出（与 C++ 侧 cin 失败一致）
        return
    n, m = float(n_tok), float(m_tok)

    # 数学答案为 0 时（n = 0.8m，如 80 100）浮点残差可能带负号，会输出 "-0.00"；
    # 精确值是 0.2 的整数倍，最小非零 |rest| = 0.2，而 double 误差实测上界 9.3e-11，
    # 故 |rest| < 1e-6 只可能是舍入残差，归零安全。
    rest = n - m * DISC
    if abs(rest) < ZERO_EPS:
        rest = 0.0

    print(f"{rest:.2f}")


if __name__ == "__main__":
    solve()
