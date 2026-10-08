#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 02:20
# update_at: 2026-10-09 07:30

import sys

BOY_SCORE = 87   # 男生平均分（题面给定的常量，不是答案）
GIRL_SCORE = 85  # 女生平均分（题面给定的常量，不是答案）


def solve() -> None:
    """读入男生数 x 与女生数 y，输出全班平均分，保留 4 位小数。

    全体总分 = BOY_SCORE * x + GIRL_SCORE * y，总人数 = x + y。
    Python 的 `/` 本就是实数除法，与 C++ 侧「先抬成 double 再除」等价：
    分子分母都是整数，`(87x + 85y) / (x + y)` 与 `1.0 * (87x + 85y) / (x + y)`
    在 2901234 个舍入平局点上逐位相同。
    """
    data = iter(map(int, sys.stdin.buffer.read().split()))
    x = next(data, None)  # 单组输入：一行两个人数
    if x is None:
        return
    y = next(data, None)  # 缺第二个数：与 C++ 侧 cin 读取失败一样静默结束
    if y is None:
        return

    avg = (BOY_SCORE * x + GIRL_SCORE * y) / (x + y)
    print(f"{avg:.4f}")


if __name__ == "__main__":
    solve()
