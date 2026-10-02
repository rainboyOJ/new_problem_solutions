#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:10
# update_at: 2026-10-02 11:17

import sys

sys.set_int_max_str_digits(20000)  # 系数可达上万位十进制，放开 int() 的转换位数限制

P = 2147483647  # 梅森素数 2^31-1：期望假阳性 O(m/p) ≈ 0，幸存者再精确复验


def mod_horner(coeffs_rev_mod: list[int], x: int) -> int:
    """模意义下秦九韶：传入倒序（a_n 在前）的系数，反复乘 x 加下一项，随时取模。"""
    v = 0
    for c in coeffs_rev_mod:
        v = (v * x + c) % P
    return v


def horner(coeffs: list[int], x: int) -> int:
    """大整数精确秦九韶：Python 原生大整数直接算，不怕系数上百位。"""
    v = 0
    for c in reversed(coeffs):
        v = v * x + c
    return v


def solve() -> None:
    it = map(int, sys.stdin.buffer.read().split())
    n, m = next(it), next(it)
    coeffs = [next(it) for _ in range(n + 1)]

    # 第一遍：模 P 筛掉绝大多数非根（C++ 正解的本体就是这一步）。
    # Horner 要从最高次算起：把负系数先归一到 [0, P)，再整体反转成 a_n 在前。
    coeffs_rev_mod = [c % P for c in reversed(coeffs)]
    candidates = [x for x in range(1, m + 1) if mod_horner(coeffs_rev_mod, x) == 0]

    # 第二遍：幸存者用原系数精确复验，保证零误判。
    roots = [x for x in candidates if horner(coeffs, x) == 0]

    print(len(roots))
    print('\n'.join(map(str, roots)))


if __name__ == "__main__":
    solve()
