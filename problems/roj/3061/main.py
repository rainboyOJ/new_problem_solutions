#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:55
# update_at: 2026-10-01 12:55

import sys

N = 16  # 边长与符号个数：16×16 数独，每行/列/宫填 A~P 各一次
NCELL = N * N                    # 256 个格子
NCOL = 4 * NCELL                 # 1024 个约束列：格 / 行 / 列 / 宫 各 256 个
ROOT = NCOL                      # 总表头，0..NCOL-1 是列头
ROWCOLS = [None] * (NCELL * N)   # 每个候选行 (p, v) 覆盖的 4 个约束列

for p in range(NCELL):
    r, c = p >> 4, p & 15
    b = r // 4 * 4 + c // 4
    for v in range(N):
        ROWCOLS[p << 4 | v] = (p, (256 | r) << 8 | v if False else 256 + r * N + v,
                              512 + c * N + v, 768 + b * N + v)

# Dancing Links 的环形十字链表：0..NCOL-1 列头 + NCOL 根 + 每候选行 4 个节点
L: list[int] = []
R: list[int] = []
U: list[int] = []
D: list[int] = []
C: list[int] = []
S: list[int] = []
ROW: list[int] = []  # 节点 -> 候选行编号 p<<4|v，列头为 -1


def build() -> None:
    """把 4096 个候选行 × 4 约束列建成 DLX 矩阵，只建一次。"""
    del L[:], R[:], U[:], D[:], C[:], S[:], ROW[:]
    for i in range(NCOL + 1):  # 列头横向环 + 根
        L.append(i - 1)
        R.append(i + 1)
    L[0], R[ROOT] = ROOT, 0
    U.extend(range(NCOL + 1))
    D.extend(range(NCOL + 1))
    C.extend(range(NCOL + 1))
    S.extend([0] * (NCOL + 1))
    ROW.extend([-1] * (NCOL + 1))
    for row_id, cols in enumerate(ROWCOLS):
        first = len(C)
        for cid in cols:  # 竖向插到列底
            U.append(U[cid])
            D.append(cid)
            D[U[cid]] = len(C)
            U[cid] = len(C)
            C.append(cid)
            S[cid] += 1
            ROW.append(row_id)
        for k in range(4):  # 同一行的 4 个节点横向成环
            i = first + k
            L.append(first + (k - 1) % 4)
            R.append(first + (k + 1) % 4)


def cover(cid: int) -> None:
    """从列环中摘掉列头，并把该列每行从各自的其他列里删除。"""
    L[R[cid]] = L[cid]
    R[L[cid]] = R[cid]
    i = D[cid]
    while i != cid:
        j = R[i]
        while j != i:
            D[U[j]] = D[j]
            U[D[j]] = U[j]
            S[C[j]] -= 1
            j = R[j]
        i = D[i]


def uncover(cid: int) -> None:
    """cover 的逆操作，严格按相反顺序恢复链表。"""
    i = U[cid]
    while i != cid:
        j = L[i]
        while j != i:
            S[C[j]] += 1
            D[U[j]] = j
            U[D[j]] = j
            j = L[j]
        i = U[i]
    L[R[cid]] = cid
    R[L[cid]] = cid


def search(sol: list[int]) -> bool:
    """Knuth Algorithm X：挑剩余候选最少的列分支；列环空即完全覆盖。"""
    if R[ROOT] == ROOT:
        return True
    c, best = R[ROOT], R[ROOT]  # 最小列启发式：分支数最少
    s = S[c]
    while c != ROOT:
        if S[c] < s:
            s, best = S[c], c
        c = R[c]
    cover(best)
    i = D[best]
    while i != best:
        sol.append(ROW[i])
        j = R[i]
        while j != i:
            cover(C[j])
            j = R[j]
        if search(sol):
            return True
        j = L[i]
        while j != i:
            uncover(C[j])
            j = L[j]
        sol.pop()
        i = D[i]
    uncover(best)
    return False


def solve_puzzle(puzzle: str) -> str:
    """从建好的矩阵出发解一个谜面，返回 16 行文本。"""
    U[:] = base_U
    D[:] = base_D
    L[:] = base_L
    R[:] = base_R
    S[:] = base_S
    givens: list[tuple[int, int]] = []
    board = ["-"] * NCELL
    for p, ch in enumerate(puzzle):
        if ch not in "-.":  # 数据用 '-' 表示空格（题面写作 '.'）
            v = ord(ch) - 65
            givens.append((p, v))
            board[p] = ch
            for cid in ROWCOLS[p << 4 | v]:  # 给定行永久选中，不再恢复
                cover(cid)
    sol: list[int] = list(givens and [])
    sol = [p << 4 | v for p, v in givens]
    search(sol)
    for row_id in sol:
        p, v = row_id >> 4, row_id & 15
        board[p] = chr(65 + v)
    return "\n".join("".join(board[i:i + N]) for i in range(0, NCELL, N))


build()
base_U, base_D, base_L, base_R, base_S = U[:], D[:], L[:], R[:], S[:]


def solve() -> None:
    # 兼容两种写法：整行一个谜面、或每行 16 个字符逐行给出；end 终止符直接丢弃
    # 整篇输入要保留空格/换行并做整行/整 token 拼接，比 next() 顺序消费更自然
    raw = sys.stdin.read().split()
    body = "".join(t for t in raw if t != "end")
    out = [solve_puzzle(body[i:i + NCELL]) for i in range(0, len(body), NCELL)]
    print("\n\n".join(out))  # 谜面之间用空行分隔，与数据一致


if __name__ == "__main__":
    solve()
