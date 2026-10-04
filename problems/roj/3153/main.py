#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:19
# update_at: 2026-10-01 21:19

import sys

SPREAD = 2  # 一门炮沿行、沿列都攻击左右各 SPREAD 格；攻击不受地形阻挡


def legal_columns(width: int) -> list[int]:
    """一行内部互不攻击的列方案 x：两炮列距为 1 或 2 时会互相攻击。"""
    return [x for x in range(1 << width) if not x & (x << 1) and not x & (x << 2)]


def advance(states: dict[tuple[int, int], int], allowed: list[int]) -> dict[tuple[int, int], int]:
    """枚举当前行的合法列方案，把状态键从 (本行 x, 上一行 y) 推进到 (新行 z, 本行 x)。

    states 的值是「已决策的那些行里最多放了多少炮」；键用题解里的 (x, y) 符号，
    即本行、上一行的列占用方案，所以新行的候选变量也沿用题解的 z。
    """
    nxt: dict[tuple[int, int], int] = {}
    for (x, y), total in states.items():
        blocked = x | y  # 本行、上行的炮位；新行在这些列同列放置就会误伤
        for z in allowed:
            if z & blocked:  # 同列即纵向距离 ≤ SPREAD，冲突
                continue
            key = (z, x)
            total_here = total + z.bit_count()
            best_before = nxt.get(key, -1)  # 同一个键可能由不同的更早行到达
            if total_here > best_before:
                nxt[key] = total_here
    return nxt


def deploy(rows: list[str], width: int) -> int:
    """逐行推进的状态压缩 DP，返回全地图最多能部署的炮兵数。"""
    legal = legal_columns(width)
    # 每行的平原掩码：第 c 位为 1 表示该格是平原，可以放炮；山地格不能放
    plains = [sum(1 << c for c, cell in enumerate(row) if cell == "P") for row in rows]
    # 行内合法且不含炮位落在山地的方案，就是该行真正可选的列方案集合
    allowed = [[x for x in legal if not x & ~plain] for plain in plains]

    # 第 0 行没有上一行，用 y = 0（空掩码）代表这一层约束不存在
    states = {(x, 0): x.bit_count() for x in allowed[0]}
    for row_allowed in allowed[1:]:
        states = advance(states, row_allowed)
    return max(states.values())


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n, width = int(data[0]), int(data[1])
    # 题面每行可能连写，也可能逐字符用空格分隔，统一拼成一串再按行切
    flat = b"".join(data[2:]).decode()
    rows = [flat[i * width:(i + 1) * width] for i in range(n)]
    print(deploy(rows, width))


if __name__ == "__main__":
    solve()
