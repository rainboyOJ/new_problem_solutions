#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:28
# update_at: 2026-10-01 11:36

import sys
from itertools import islice

TWIN = "Twin snowflakes found."
ALIKE = "No two snowflakes are alike."


def shape_key(flake: tuple[int, ...]) -> tuple[int, ...]:
    """雪花的最小表示：顺时针 6 个旋转 + 逆时针 6 个旋转里最小的那个六元组。

    形状相同的两片雪花，12 个旋转组成的集合完全相同，取最小值后必然相等；
    反过来最小值相等就说明两个集合有公共元素，即形状相同。所以最小表示是
    “形状”的精确指纹，不含哈希碰撞。元组比较由 CPython 在 C 层完成，
    比在 Python 里手写数值哈希还快。
    """
    reverse = flake[::-1]                                        # 逆时针方向读到的序列
    return min(
        [flake[k:] + flake[:k] for k in range(6)]                # 顺时针 6 个旋转
        + [reverse[k:] + reverse[:k] for k in range(6)]          # 逆时针 6 个旋转
    )


def solve() -> None:
    data = map(int, sys.stdin.buffer.read().split())
    n = next(data)

    seen: set[tuple[int, ...]] = set()
    for _ in range(n):
        flake = tuple(islice(data, 6))  # 每行 6 个角，正好构成一片雪花
        key = shape_key(flake)
        if key in seen:
            print(TWIN)
            return
        seen.add(key)
    print(ALIKE)


if __name__ == "__main__":
    solve()
