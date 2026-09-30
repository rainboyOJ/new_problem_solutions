#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:00
# update_at: 2026-10-01 04:14

import sys

MOD = 9901  # 题面要求的模数；它不是质数，但本题只用加减乘，不需要逆元


def lift(F: list[int]) -> list[int]:
    """把「高度不超过 h」的计数向量变成「高度不超过 h+1」的计数向量（h >= 1）。

    高度不超过 h+1 的树去掉根，就是左右两棵高度都不超过 h 的子树，
    于是按内部结点数做一次卷积：G[m] = Σ_{a+b=m-1} F[a]·F[b]。
    下标是内部结点数，下标 0 表示那个位置是叶子；左右两边都占一个位置，
    所以 G[0] 恒为 1（由列表头的那个常量给出）。
    """
    return [1] + [
        sum(F[a] * F[i - 1 - a] for a in range(i)) % MOD for i in range(1, len(F))
    ]


def solve() -> None:
    n, k = map(int, sys.stdin.buffer.read().split())

    if n % 2 == 0:  # 每个内部结点恰好贡献两个孩子，总结点数必为奇数
        print(0)
        return

    m = (n - 1) // 2  # 内部结点数；叶子恰好比它多 1 片，两者相加才是 n

    # L_h[m] = 内部结点数恰为 m、高度不超过 h 的家谱个数。
    # 内部结点数为 0 的树就是那片叶子，高度是 1，所以 base 就是 L_1；
    # below / upto 滚动保存 L_{k-1} 与 L_k，两者相减就只剩高度恰好为 k 的那些树。
    base = [1] + [0] * m  # L_1：只有那片叶子，m > 0 的树高度都超过 1
    below, upto = base, base.copy()
    for _ in range(k - 1):  # 每轮把高度上界抬高一层：L_{i+1} = lift(L_i)
        below, upto = upto, lift(upto)

    print((upto[m] - below[m]) % MOD)


if __name__ == "__main__":
    solve()
