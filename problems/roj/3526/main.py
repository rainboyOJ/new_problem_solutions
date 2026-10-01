#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:17
# update_at: 2026-10-02 05:17

import sys
from functools import cache


@cache
def best(l: int, r: int, d: tuple[int, ...]) -> tuple[int, int]:
    """中序为 l..r 的子树的 (最高加分, 取到最高的根)；空区间加分为 1、根记 0。

    根 k 的加分 = 左子树加分 × 右子树加分 + d[k]，两棵子树各自独立地也取最高，
    故按区间长度递推；叶子的加分就是它本身的分数（不套空子树规则），
    同分时取最靠左的根，保证前序遍历与标准答案一致。
    """
    if l > r:
        return (1, 0)
    if l == r:
        return (d[l], l)
    top, top_k = 0, l
    for k in range(l, r + 1):
        left = best(l, k - 1, d)[0]
        right = best(k + 1, r, d)[0]
        score = left * right + d[k]
        if score > top:
            top, top_k = score, k
    return (top, top_k)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    d: tuple[int, ...] = (0,) + tuple(next(data) for _ in range(n))  # 下标 1..n 的分数

    top_score, _ = best(1, n, d)

    # 前序遍历：根 → 左子树 → 右子树；用栈把"先压右再压左"倒成正确的出栈顺序
    order: list[int] = []
    stack = [(1, n)]
    while stack:
        l, r = stack.pop()
        if l <= r:
            k = best(l, r, d)[1]
            order.append(k)
            stack.append((k + 1, r))
            stack.append((l, k - 1))

    print(top_score)
    print(*order)


if __name__ == "__main__":
    solve()
