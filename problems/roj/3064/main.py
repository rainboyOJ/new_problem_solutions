#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 09:00
# update_at: 2026-10-09 11:34

import sys

N = 16                     # 边长与符号个数：16×16 数独，每行/列/宫填 A~P 各一次
NCELL = N * N              # 256 个格子
NCOL = 4 * NCELL           # 1024 个约束列：格 / 行 / 列 / 宫 各 256 个
ROOT = 0                   # 总表头编号，列头是 1..NCOL

UP: list[int] = []         # 节点的上邻居
DOWN: list[int] = []       # 节点的下邻居
LEFT: list[int] = []       # 节点的左邻居
RIGHT: list[int] = []      # 节点的右邻居
COL: list[int] = []        # 节点所属约束列
ROW: list[int] = []        # 节点所属决策行编号（列头为 -1）
SIZE: list[int] = []       # 每列当前的数据节点个数，只有列头用
HEAD: list[int] = []       # 每个决策行横向环的首节点，-1 表示该行还没有节点
CHOSEN: list[int] = []     # CHOSEN[d] = 搜索第 d 层选中的决策行编号
CHOSEN_CNT = 0             # 已选中的决策行个数
NODE_CNT = 0               # 已开出的节点个数，也是下一个可用下标
GRID: list[list[str]] = [] # 当前谜面，解决后原地填满


def init_dlx() -> None:
    """清空十字链表，只留下 ROOT 加 NCOL 个列头（编号 1..NCOL）。"""
    global NODE_CNT
    del UP[:], DOWN[:], LEFT[:], RIGHT[:], COL[:], ROW[:], SIZE[:]
    UP.extend(range(NCOL + 1))
    DOWN.extend(range(NCOL + 1))
    COL.extend(range(NCOL + 1))
    LEFT.extend([i - 1 for i in range(NCOL + 1)])
    RIGHT.extend([i + 1 for i in range(NCOL + 1)])
    LEFT[ROOT], RIGHT[ROOT] = NCOL, 1
    LEFT[1], RIGHT[NCOL] = ROOT, ROOT   # 列头 1..NCOL 与总表头连成横向环
    ROW.extend([-1] * (NCOL + 1))
    SIZE.extend([0] * (NCOL + 1))
    del HEAD[:]
    HEAD.extend([-1] * (NCELL * N + 1))
    NODE_CNT = NCOL


def link(r: int, c: int) -> None:
    """把「决策行 r 覆盖约束列 c」这条边插到 c 列底部、并接进 r 行的横向环。"""
    global NODE_CNT
    NODE_CNT += 1
    COL.append(c)
    ROW.append(r)
    SIZE[c] += 1
    UP.append(UP[c])
    DOWN.append(c)
    DOWN[UP[c]] = NODE_CNT
    UP[c] = NODE_CNT
    if HEAD[r] == -1:
        HEAD[r] = NODE_CNT
        LEFT.append(NODE_CNT)
        RIGHT.append(NODE_CNT)
    else:
        LEFT.append(LEFT[HEAD[r]])
        RIGHT.append(HEAD[r])
        RIGHT[LEFT[HEAD[r]]] = NODE_CNT
        LEFT[HEAD[r]] = NODE_CNT


def cover(c: int) -> None:
    """从列环里摘掉列头 c，并把 c 列每行从它的其他列里一并删除。"""
    RIGHT[LEFT[c]] = RIGHT[c]
    LEFT[RIGHT[c]] = LEFT[c]
    i = DOWN[c]
    while i != c:
        j = RIGHT[i]
        while j != i:
            UP[DOWN[j]] = UP[j]
            DOWN[UP[j]] = DOWN[j]
            SIZE[COL[j]] -= 1
            j = RIGHT[j]
        i = DOWN[i]


def uncover(c: int) -> None:
    """cover 的逆操作，必须严格按被删除的相反顺序恢复。"""
    i = UP[c]
    while i != c:
        j = LEFT[i]
        while j != i:
            SIZE[COL[j]] += 1
            DOWN[UP[j]] = j
            UP[DOWN[j]] = j
            j = LEFT[j]
        i = UP[i]
    RIGHT[LEFT[c]] = c
    LEFT[RIGHT[c]] = c


def search(d: int) -> bool:
    """Knuth Algorithm X：挑剩余候选最少的列分支；所有约束列都覆盖完就成功。"""
    global CHOSEN_CNT
    if RIGHT[ROOT] == ROOT:
        CHOSEN_CNT = d
        return True
    c = best = RIGHT[ROOT]  # 最小列启发式：分支数最少的列优先
    while c != ROOT:
        if SIZE[c] < SIZE[best]:
            best = c
        c = RIGHT[c]
    cover(best)
    i = DOWN[best]
    while i != best:
        CHOSEN.append(ROW[i])
        j = RIGHT[i]
        while j != i:
            cover(COL[j])
            j = RIGHT[j]
        if search(d + 1):
            return True
        j = LEFT[i]
        while j != i:
            uncover(COL[j])
            j = LEFT[j]
        CHOSEN.pop()
        i = DOWN[i]
    uncover(best)
    return False


def build_grid() -> None:
    """把 16×16 数独建成精确覆盖模型：每格一个候选字母是一行，覆盖 4 个约束列。"""
    init_dlx()
    for i in range(N):
        for j in range(N):
            b = (i // 4) * 4 + j // 4
            for k in range(N):
                # 谜面已固定成别的字母时，这一格填 k 的决策直接丢弃
                if GRID[i][j] != '-' and GRID[i][j] != chr(65 + k):
                    continue
                r = i * 256 + j * 16 + k + 1
                link(r, i * 16 + j + 1)         # 约束 1：格子 (i,j) 只能填一个字母
                link(r, 256 + i * 16 + k + 1)   # 约束 2：第 i 行必须出现字母 k
                link(r, 512 + j * 16 + k + 1)   # 约束 3：第 j 列必须出现字母 k
                link(r, 768 + b * 16 + k + 1)   # 约束 4：第 b 个宫必须出现字母 k


def fill_answer() -> None:
    """把解出的决策行还原成字母写回 GRID 并打印。"""
    for t in range(CHOSEN_CNT):
        v = CHOSEN[t] - 1
        k = v % 16
        v //= 16
        GRID[v // 16][v % 16] = chr(65 + k)
    for row in GRID:
        print("".join(row))
    print()  # 题面要求：每个测试用例输出结束后再输出一个空行


def solve() -> None:
    global GRID
    tokens = sys.stdin.buffer.read().split()
    if not tokens:
        return
    tokens = [t.decode() for t in tokens]
    # 组间空行已被 split 吃掉；每组恰好 16 行，读到不足 16 行即结束
    for s in range(0, len(tokens) - 15, 16):
        GRID = [list(tokens[s + i]) for i in range(N)]
        del CHOSEN[:]
        build_grid()
        if search(0):
            fill_answer()


if __name__ == "__main__":
    solve()
