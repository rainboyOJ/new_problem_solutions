#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 01:36
# update_at: 2026-10-08 01:36

import sys

MOD = 10007    # 题面模数，是质数且 > n <= 1000，故组合数分母恒不为 0
LIMIT = 1005   # 题面 n <= 1000，留安全余量

type Tree = list[list[int]]  # 孩子的原始顺序（下标 1..n），顺序即喜爱度降序

# 阶乘与其逆元表：供 O(1) 组合数使用，n < MOD 故费马小定理足够、无需求 Lucas
FACT = [1] * LIMIT
for _i in range(1, LIMIT):
    FACT[_i] = FACT[_i - 1] * _i % MOD

INV_FACT = [1] * LIMIT
INV_FACT[LIMIT - 1] = pow(FACT[LIMIT - 1], MOD - 2, MOD)
for _i in range(LIMIT - 1, 0, -1):
    INV_FACT[_i - 1] = INV_FACT[_i] * _i % MOD


def comb(a: int, b: int) -> int:
    """组合数 C(a, b) mod 10007；b 越界时为 0。"""
    if b < 0 or b > a or a < 0:
        return 0
    return FACT[a] * INV_FACT[b] % MOD * INV_FACT[a - b] % MOD


def post_order(tree: Tree, n: int) -> list[int]:
    """以 1 为根的后序遍历序列：孩子一定排在父亲前面，故正序扫描即自底向上。

    迭代实现，避免 n = 1000 的链把递归栈撑爆；stack 顶部正被枚举时，
    直接 pop 掉它的一个孩子当作游标，省掉「每个点已枚举几个孩子」的辅助数组。
    """
    order: list[int] = []
    stack = [1]
    seen = [False] * (n + 1)
    seen[1] = True
    while stack:
        branch = tree[stack[-1]]
        if branch:
            child = branch.pop()
            if not seen[child]:              # 合法输入下恒真，仅防御重复编号
                seen[child] = True
                stack.append(child)
        else:
            order.append(stack.pop())
    return order


def case_answer(tree: Tree, n: int) -> int:
    """一组数据的答案：自底向上树形 DP，返回 f[1]。"""
    f = [1] * (n + 1)    # f[u]：只考虑子树 u 内部节点的合法排列数
    sz = [1] * (n + 1)   # sz[u]：子树 u 的节点数

    kids: Tree = [list(tree[u]) for u in range(n + 1)]  # post_order 会破坏性取用
    for u in post_order(kids, n):
        # 倒序合并：c_i 必占「T(c_i) 及其右侧兄弟子树」的第一位，
        # 余下 sz[c_i]-1 个元素与右侧已合并的 rem 个元素自由插空。
        total = sum(sz[c] for c in tree[u])
        ways, rem = 1, total                # rem = N_i = sum_{j >= i} sz[c_j]
        for c in tree[u]:
            ways = ways * f[c] % MOD * comb(rem - 1, sz[c] - 1) % MOD
            rem -= sz[c]
        sz[u] = total + 1                   # u 自身也要占一位
        f[u] = ways
    return f[1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n = next(data)
        tree: Tree = [[] for _ in range(n + 1)]
        for u in range(1, n + 1):
            tot = next(data)  # 题面的续集个数
            tree[u] = [next(data) for _ in range(tot)]
        out.append(str(case_answer(tree, n)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
