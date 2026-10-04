#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 13:52
# update_at: 2026-10-02 13:52

import sys

VAL: list[int] = []  # 点权，下标即节点编号，0 号位补 0 占位
L: list[int] = []    # 左孩子编号，-1 表示不存在
R: list[int] = []    # 右孩子编号，-1 表示不存在
# 镜像判定缓存：同一对节点只展开一次，key = (a, b)
MEMO: dict[tuple[int, int], bool] = {}


def mirror(a: int, b: int) -> bool:
    """以 a、b 为根的两棵子树是否互为镜像（交换后结构与点权都相同）。"""
    if a < 0 or b < 0:  # 只有一侧为空就谈不上镜像
        return a < 0 and b < 0
    stack: list[tuple[int, int, int]] = [(a, b, 0)]  # (节点对, 阶段)：0 去下探，1 回收
    while stack:
        x, y, stage = stack.pop()
        if x < 0 or y < 0:  # 空树对的结论即时成立，不占缓存
            continue
        key = (x, y)
        if stage:  # 两个子对已在栈上方判完，按子对结果汇总
            lx, ry = L[x], R[y]
            rx, ly = R[x], L[y]
            MEMO[key] = MEMO.get((lx, ry), lx < 0 and ry < 0) and MEMO.get(
                (rx, ly), rx < 0 and ly < 0
            )
        elif key in MEMO:  # 该节点对早已判定，直接复用
            continue
        elif VAL[x] != VAL[y]:  # 根权不同，不必再看子树
            MEMO[key] = False
        else:  # 下探两对交叉孩子：左对右、右对左
            stack.append((x, y, 1))
            stack.append((L[x], R[y], 0))
            stack.append((R[x], L[y], 0))
    return MEMO[(a, b)]


def largest_symmetric() -> int:
    """后序累计子树大小，返回对称子树里最大的节点数。"""
    order: list[int] = []
    stack = [1]
    while stack:  # 迭代先序收集遍历序，倒着走就是孩子先于父亲
        x = stack.pop()
        order.append(x)
        if L[x] > 0:
            stack.append(L[x])
        if R[x] > 0:
            stack.append(R[x])

    size = [0] * len(VAL)
    best = 0
    for x in reversed(order):
        left, right = L[x], R[x]
        size[x] = sub = 1 + (size[left] if left > 0 else 0) + (size[right] if right > 0 else 0)
        can_beat = sub > best  # 更小的候选更新不了答案，连镜像判定一起省掉
        if can_beat and mirror(left, right):
            best = sub
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    global VAL, L, R
    n = next(data)  # 节点数，编号 1~n，1 是树根
    VAL = [0] + [next(data) for _ in range(n)]
    L = [0] * (n + 1)
    R = [0] * (n + 1)
    for i in range(1, n + 1):  # 第 i 行是节点 i 的左、右孩子编号
        L[i] = next(data)
        R[i] = next(data)
    print(largest_symmetric())


if __name__ == "__main__":
    solve()
