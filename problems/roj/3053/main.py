#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:41
# update_at: 2026-10-01 12:50

import sys


def border_mask(text: str) -> int:
    """text 的所有 border 长度打包成位掩码：第 b 位为 1 表示存在长度为 b 的 border。

    border 指既是前缀又是后缀的真前缀；对定长 text，它和"周期"一一对应：
    有长度 b 的 border ⟺ text 有周期 n-b。
    """
    n = len(text)
    nxt = [0] * (n + 1)          # nxt[i]：text[:i] 的最长 border 长度
    j = 0
    for i in range(1, n):
        while j and text[i] != text[j]:
            j = nxt[j]
        j += text[i] == text[j]  # 相等则 border 再长一位（布尔当 0/1 用）
        nxt[i + 1] = j
    mask, b = 0, nxt[n]          # border 长度沿 nxt 链严格递减，链上每个值都是 border
    while b:
        mask |= 1 << b
        b = nxt[b]
    return mask | 1              # 长度 0 的 border 恒存在，它对应"周期 = 整段长度"


def min_period(lines: list[str]) -> int:
    """一组等长字符串共有的最小周期 = 长度 - 它们共同的最长 border。"""
    common = -1                  # 全 1 掩码，& 上每行的 border 集合即得公共 border
    for line in lines:
        common &= border_mask(line)
    return len(lines[0]) - common.bit_length() + 1


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    R, C = int(next(data)), int(next(data))
    rows = [next(data).decode() for _ in range(R)]

    # 覆盖子矩阵的高、宽互不影响：把每一列看成一个长字符串，横向周期由 rows 决定，
    # 纵向周期由 cols 决定，两者相乘即最小面积。
    cols = ["".join(col) for col in zip(*rows)]
    print(min_period(rows) * min_period(cols))


if __name__ == "__main__":
    solve()
