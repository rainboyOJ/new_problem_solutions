#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:40
# update_at: 2026-10-01 10:40

import sys
from functools import cache


@cache
def fractal(n: int) -> tuple[str, ...]:
    """回答：n 级盒子分形的图案长什么样（每一行是一个定宽字符串）。

    B(n) 的五个位置各放一份 B(n-1)：左上、右上、正中、左下、右下。
    每行始终补齐到整图宽度 size，拼接下一级时副本才不会错位；
    行尾空格留到输出前再去掉。`@cache` 让 7 级图案只算一次，各级复用。
    """
    if n == 1:
        return ("X",)
    size = 3 ** (n - 1)  # B(n) 的边长：每升一级扩大 3 倍
    half = size // 3     # B(n-1) 的边长；也是上/中/下三带的高度与各副本的平移量
    unit = fractal(n - 1)
    gap = " " * half     # 上/下带里左右两份之间的空白，恰好也是 half 宽

    rows = []
    for row in unit:  # 上带：左右两份 B(n-1)
        rows.append(row + gap + row)
    for row in unit:  # 中带：只有一份 B(n-1)，水平居中
        rows.append(gap + row + gap)
    for row in unit:  # 下带：左右两份 B(n-1)
        rows.append(row + gap + row)
    return tuple(rows)


def solve() -> None:
    for token in sys.stdin.read().split():
        n = int(token)
        if n == -1:  # 终止标记
            break
        print("\n".join(row.rstrip() for row in fractal(n)))
        print("-")


if __name__ == "__main__":
    solve()
