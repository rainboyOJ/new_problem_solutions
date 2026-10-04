#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:07
# update_at: 2026-09-30 20:07

import sys

EMPTY_SCORE = 1  # 空子树的加分，即长度 0 区间的值


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    d = [next(data) for _ in range(n)]  # d[i] 是节点 i+1 的分数，节点编号整体减一

    # 区间用半开区间 [l, r) 表示，左右子树天然写成 [l, k) 与 [k+1, r)
    # score[l][r]: 中序区间 [l, r) 组成的子树的最大加分
    # root[l][r] : 该最优子树的根在中序里的下标，用于还原前序遍历
    score = [[EMPTY_SCORE] * (n + 1) for _ in range(n + 1)]  # 空区间（l == r）加分恒为 1
    root = [[0] * (n + 1) for _ in range(n + 1)]

    for i in range(n):                    # 长度 1 的区间是叶子：加分就是自己的分数
        score[i][i + 1] = d[i]
        root[i][i + 1] = i

    for length in range(2, n + 1):        # 长度递增，保证两个子区间都已算完
        for l in range(n - length + 1):
            r = l + length
            best = 0
            for k in range(l, r):         # 枚举根 k：左 [l, k)、右 [k+1, r)
                cand = score[l][k] * score[k + 1][r] + d[k]
                if cand > best:
                    best, root[l][r] = cand, k
            score[l][r] = best

    # 前序遍历 = 根 + 左子树 + 右子树；用栈展开，避免深递归
    order: list[int] = []
    stack = [(0, n)]
    while stack:
        l, r = stack.pop()
        if l >= r:
            continue                      # 空区间没有根
        k = root[l][r]
        order.append(k + 1)               # 还原成 1-based 的节点编号
        stack.append((k + 1, r))          # 栈后进先出：先压右子树，才能先弹出左子树
        stack.append((l, k))

    print(score[0][n])
    print(' '.join(map(str, order)))


if __name__ == "__main__":
    solve()
