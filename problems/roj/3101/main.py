#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:06
# update_at: 2026-10-01 17:15

import sys
from collections import Counter
from collections.abc import Iterator
from itertools import islice

DAYS = [b"MON", b"TUE", b"WED", b"THU", b"FRI", b"SAT", b"SUN"]  # 星期几 → 0..6
INV = [0, 1, 4, 5, 2, 3, 6]  # 模 7 的乘法逆元：3·5、2·4、6·6、1·1 都同余 1，INV[0] 用不到
MOD = 7
MIN_DAYS = 3  # 单件耗时下界；余数小于它时加一个周期 7 即还原成 7/8/9 天

UNIQUE, MULTIPLE, INCONSISTENT = 0, 1, 2  # 方程组解的状态；只有 UNIQUE 才有确定的答案
TEXT = {MULTIPLE: "Multiple solutions.", INCONSISTENT: "Inconsistent data."}


def tokens() -> Iterator[bytes]:
    """按行产出输入词元：整份数据有 450 万个数字，一次性读入会多占几百 MB。"""
    for line in sys.stdin.buffer:
        yield from line.split()


def read_case(data: Iterator[bytes], n: int, m: int) -> tuple[list[list[int]], list[int]]:
    """读入 m 条工人记录，返回 (模 7 系数矩阵, 右端余数向量)。

    第 i 条记录给出一条同余方程 sum_j c[i][j] * x_j ≡ d_i (mod 7)：
    c[i][j] 是型号 j 在这批活里出现的次数（同型号做几次就累加几次耗时），
    d_i 是工人在岗天数对 7 取余，开工星期 s、收工星期 e、首尾都算，故 d_i ≡ e - s + 1。
    """
    mat: list[list[int]] = []
    rhs: list[int] = []
    for _ in range(m):
        k = int(next(data))
        start, end = next(data), next(data)
        counts = Counter(map(int, islice(data, k)))
        mat.append([counts[v] % MOD for v in range(1, n + 1)])
        rhs.append((DAYS.index(end) - DAYS.index(start) + 1) % MOD)
    return mat, rhs


def gauss(mat: list[list[int]], rhs: list[int], n: int) -> tuple[int, list[int]]:
    """模 7 高斯消元：先消成阶梯形，再回代，返回 (解的状态, 一组特解)。

    7 是素数，非零系数都有逆元，所以消元过程与实数域一样，只是把除法换成乘逆元。
    """
    pivot_cols: list[int] = []
    for col in range(n):
        pivot = next((r for r in range(len(pivot_cols), len(mat)) if mat[r][col]), None)
        if pivot is None:  # 剩余行在这一列全是 0，说明 x[col] 是自由元
            continue
        rank = len(pivot_cols)
        mat[rank], mat[pivot] = mat[pivot], mat[rank]
        rhs[rank], rhs[pivot] = rhs[pivot], rhs[rank]
        inv = INV[mat[rank][col]]  # 主元归一化成 1
        mat[rank] = [0] * col + [v * inv % MOD for v in mat[rank][col:]]
        rhs[rank] = rhs[rank] * inv % MOD
        for r in range(rank + 1, len(mat)):  # 只往下消成阶梯形，回代时再算具体值
            factor = mat[r][col]
            if factor:
                row = mat[r]
                # 补上前导 0 是为了让「列下标」始终等于变量的编号
                mat[r] = [0] * col + [(v - factor * w) % MOD for v, w in zip(row[col:], mat[rank][col:])]
                rhs[r] = (rhs[r] - factor * rhs[rank]) % MOD
        pivot_cols.append(col)
        if len(pivot_cols) == len(mat):  # 每条方程都拿到主元，剩下的只可能是 0 = 0
            break

    x = [0] * n
    if any(rhs[len(pivot_cols):]):  # 系数全 0 而右端非 0 的行形如 0 = c，方程无解
        return INCONSISTENT, x
    if len(pivot_cols) < n:  # 自由元取 0 就是一组解，故至少两族解对应多组天数
        return MULTIPLE, x
    for i in range(n - 1, -1, -1):  # 回代：主元列右侧的变量此时都已确定
        col = pivot_cols[i]
        x[col] = (rhs[i] - sum(v * x[j] for j, v in enumerate(mat[i][col + 1:], col + 1))) % MOD
    return UNIQUE, x


def solve() -> None:
    data = tokens()
    out: list[str] = []
    while True:
        n, m = int(next(data)), int(next(data))
        if n == 0 and m == 0:
            break
        mat, rhs = read_case(data, n, m)
        state, x = gauss(mat, rhs, n)
        # 耗时 3..9 天与模 7 的 7 个剩余类一一对应：0/1/2 分别还原成 7/8/9 天。
        out.append(" ".join(str(r if r >= MIN_DAYS else r + MOD) for r in x) if state == UNIQUE else TEXT[state])

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
