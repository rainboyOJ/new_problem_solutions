#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 14:08
# update_at: 2026-09-29 14:08

import math


def remainder(a: float, b: float) -> float:
    """a 除以 b 的余数 r：满足 a = k*b + r（k 为整数，0 <= r < b）。"""
    # fmod 直接给出精确余数，比 a - int(a/b)*b 少一次乘法回代的舍入误差
    return math.fmod(a, b)


def solve() -> None:
    a, b = map(float, input().split())
    # 题面样例与评测数据按 6 位有效数字输出（与 C++ cout 默认精度一致）
    print(f"{remainder(a, b):.6g}")


if __name__ == "__main__":
    solve()
