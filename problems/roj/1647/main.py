#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:56
# update_at: 2026-10-01 00:08

import sys
from array import array

MOD = 2009   # 题目要求的模数，每步都取模可让矩阵元素恒小于 2009
CHAIN = 9    # 每个原节点拆成 9 个状态，第 k 个表示「还需 k 步才真正到达」
SLOT = 32    # 行打包的位宽；一行的内积 <= 90*2008^2 < 2^32，所以段与段不会串位

Row = list[int]
Matrix = list[Row]


def pack_rows(mat: Matrix) -> tuple[int, ...]:
    """把每行的所有元素按固定位宽压进一个大整数，充当「一行乘整个矩阵」的常数。"""
    return tuple(sum(v << (SLOT * j) for j, v in enumerate(row)) for row in mat)


def unpack_row(bits: int, size: int) -> Row:
    """把打包好的乘积按 SLOT 位一段拆回一行，再对 2009 取模。"""
    return [v % MOD for v in array('I', bits.to_bytes(4 * size, 'little'))]


def mat_mul(a: Matrix, b: Matrix, size: int) -> Matrix:
    """矩阵乘法：a 的每一行各自与打包好的 b 相乘，即得结果矩阵的每一行。"""
    packed_b = pack_rows(b)
    return [unpack_row(sum(x * y for x, y in zip(row, packed_b)), size) for row in a]


def build_matrix(n: int, grid: list[str]) -> tuple[Matrix, int]:
    """把「边权 1~9 的 N 点图走恰好 T 步」改写成 9N 个点的无权 0/1 转移矩阵。

    状态 (v,k) 的含义：人已经踏上通往 v 的那条边、并且还要 k 个单位时间才真正落到 v。
    于是 (v,0) 才是「人站在 v 上」，而 (v,1)..(v,8) 只是把长边拆开后的等待态。
    """
    size = n * CHAIN
    # (u,0) 走一条耗时 w 的边后进入等待态 (v,w-1)，再靠链式状态逐个消耗剩余时间
    trans: Matrix = [[0] * size for _ in range(size)]
    for u in range(n):
        for v, ch in enumerate(grid[u]):
            if ch != '0':
                trans[u * CHAIN][v * CHAIN + int(ch) - 1] = 1
    # 链 (v,k) -> (v,k-1)：原地消耗一个单位时间，不改变最终要到达的节点
    for v in range(n):
        for k in range(1, CHAIN):
            trans[v * CHAIN + k][v * CHAIN + k - 1] = 1
    return trans, size


def pow_vec(mat: Matrix, exp: int, start: Row, size: int) -> Row:
    """求 start · mat^exp（行向量右乘），按 exp 的二进制位倍增：O(size^3 log exp)。

    方向不能反：x_k = x_{k-1}·M，因此只有右乘 M^{2^i} 才能累乘出 x_0·M^exp。
    """
    while exp:
        if exp & 1:                    # 行向量当 1×size 矩阵，复用同一个乘法入口
            start = mat_mul([start], mat, size)[0]
        exp >>= 1
        if exp:                        # 已是最后一个二进制位时不必再平方
            mat = mat_mul(mat, mat, size)
    return start


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, t = next(data), next(data)
    grid = [str(next(data)).zfill(n) for _ in range(n)]

    trans, size = build_matrix(n, grid)
    vec: Row = [1] + [0] * (size - 1)  # 时刻 0 唯一可达的状态是站在起点上的 (0,0)
    answer = pow_vec(trans, t, vec, size)
    print(answer[(n - 1) * CHAIN])     # 终点的落地状态 (N-1,0)


if __name__ == "__main__":
    solve()
