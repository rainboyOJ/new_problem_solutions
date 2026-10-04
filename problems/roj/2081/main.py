#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 08:44
# update_at: 2026-10-01 08:44

import sys
from functools import cache

ROWS = COLS = 4
CELLS = ROWS * COLS
FULL = (1 << CELLS) - 1         # 16 个格子的全集（位掩码）
NEED = (3, 3, 3, 4, 3)          # 需求：A*3 B*3 C*3 D*4 E*3
# NB[i]：第 i 号格的 8 邻域（不含自身）
NB = tuple(
    sum(1 << (r2 * COLS + c2)
        for r2 in range(r - 1, r + 2) for c2 in range(c - 1, c + 2)
        if 0 <= r2 < ROWS and 0 <= c2 < COLS and (r2 != r or c2 != c))
    for r in range(ROWS) for c in range(COLS)
)

memo: dict[int, int] = {}  # 棋盘位编码 -> 从该状态能完成的搬运序列数


@cache
def zone(mask: int) -> int:
    """mask 覆盖的格子们的 8 邻域并集（位掩码），逐低位移除递归累加。"""
    return 0 if mask == 0 else zone(mask & (mask - 1)) | NB[(mask & -mask).bit_length() - 1]


def dfs(step: int, g: int, used: int, occ: list[int], left: list[int],
        path: list[tuple[int, int]], best: list[tuple[int, int]]) -> int:
    """返回当前棋盘能完成的搬运序列总数；字典序扩展保证首个叶子即最小解，存入 best。"""
    if step == CELLS:
        if not best:
            best.extend(path)
        return 1
    cached = memo.get(g)
    if cached is not None:      # 已算过的状态直接复用结果
        return cached
    cnt = 0
    for t in ((3,) if step == 0 else range(5)):  # 第 0 步必须搬 D
        if not left[t]:
            continue
        avail = FULL & ~(used | occ[t] | zone(occ[t]))  # 未被占用且 8 邻域无 t 的空格
        x = avail
        while x:
            b = x & -x
            x ^= b
            i = b.bit_length() - 1
            old = (g >> (3 * i)) & 7
            occ[old] ^= b  # 原住客 old 装上卡车离开
            occ[t] |= b    # 新奶牛 t 入住该格
            left[t] -= 1
            path.append((t, i))
            cnt += dfs(step + 1, g ^ ((t ^ old) << (3 * i)), used | b, occ, left, path, best)
            path.pop()
            left[t] += 1
            occ[t] &= ~b
            occ[old] |= b
    memo[g] = cnt
    return cnt


def solve() -> None:
    data = iter(b"".join(sys.stdin.buffer.read().split()))
    # 棋盘编码：每个格子 3 bit 存字母编号（0=A..4=E），兼容带/不带空格
    g = sum((next(data) - 65) << (3 * i) for i in range(CELLS))
    occ = [0] * 5  # occ[t]：当前放着 t 型奶牛的格子集合
    for i in range(CELLS):
        occ[(g >> (3 * i)) & 7] |= 1 << i
    path: list[tuple[int, int]] = []
    best: list[tuple[int, int]] = []
    total = dfs(0, g, 0, occ, list(NEED), path, best)
    out = [f"{'ABCDE'[t]} {i // COLS + 1} {i % COLS + 1}" for t, i in best]
    out.append(str(total))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
