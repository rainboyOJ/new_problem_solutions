#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 21:30
# update_at: 2026-10-07 21:35

import sys

# 每个线段树结点用一个三元组 (cap, need, kept) 描述一段连续操作，含义固定如下：
#   cap  —— 该段“弹出值之和 - 压入次数”，即需求函数 F(x) = max(need, x + cap) 的斜率
#   need —— 右侧没有外部需求时，该段仍需继续向左侧弹出的个数，即 F(0)
#   kept —— 右侧没有外部需求时，该段最终留在栈中的元素之和
# 其中 x 是从这段右侧灌进来的弹出需求个数。因为 F 恒是这个形状，两段复合后形状不变
# （cap 相加、need 取 max），所以结点信息可以自底向上合并；need - cap 恰好是
# “无外部需求时存活的元素个数”，用来判断一个需求会不会把整段吃光。
type Node = tuple[int, int, int]  # (cap, need, kept)
type Seg = list[Node]             # 满二叉线段树，下标 1 为根，空位用恒等段填充

IDLE: Node = (0, 0, 0)  # 恒等段 F(x) = x：既不供给也不索取，用于右端对齐的补位


def leaf_of(kind: int, value: int) -> Node:
    """一个操作对应的叶子：压入 v 供给 1 个元素，弹出 v 是纯需求 v。"""
    return (value, value, 0) if kind else (-1, 0, value)


def keep_sum(seg: Seg, k: int, demand: int) -> int:
    """结点 k 在右侧灌进 demand 个需求时，最终留在栈中的元素之和。

    需求总是先吃掉最靠右的压入，所以只需沿一条从根到叶的链下推：
    右儿子能吸收需求就整段保留左儿子，吸收不完就把剩余需求转交左儿子。
    """
    total = 0
    while True:
        cap, need, kept = seg[k]
        if demand <= 0:
            return total + kept      # 本段没有需求，整段原样保留
        alive = need - cap           # 本段存活元素个数，也是能吸收的需求上限
        if demand >= alive:
            return total             # 需求吃光本段全部存活元素
        ls = k * 2
        rs = ls + 1
        cap_r, need_r, kept_r = seg[rs]
        room_r = need_r - cap_r  # 右儿子能独自吸收的需求上限
        if demand <= room_r:
            # 右儿子独自吸收需求：左儿子收到的需求恒为 need_r，贡献固定不变
            total += kept - kept_r
            k = rs
        else:
            # 右儿子被吃光，剩下的需求 y 满足 y > need_r，此时 F_r(y) = y + cap_r
            demand += cap_r
            k = ls


def refresh(seg: Seg, k: int) -> None:
    """用左右儿子重算结点 k：先让右儿子消化外部需求，再把它的缺口转交左儿子。"""
    ls = k * 2
    rs = ls + 1
    cap_l, need_l, _ = seg[ls]
    cap_r, need_r, kept_r = seg[rs]
    seg[k] = (cap_l + cap_r,
              max(need_l, need_r + cap_l),
              kept_r + keep_sum(seg, ls, need_r))


def build(ops: list[Node]) -> tuple[Seg, int]:
    """把 m 个操作装进满二叉线段树，返回 (树, 叶子偏移 base)。

    叶子数取不小于 m 的 2 的幂，右端空位是恒等段，因此第 c 个操作落在 base + c - 1。
    """
    base = 1
    while base < len(ops):
        base <<= 1
    seg: Seg = [IDLE] * (2 * base)
    for i, node in enumerate(ops):
        seg[base + i] = node
    for k in range(base - 1, 0, -1):
        refresh(seg, k)
    return seg, base


def update(seg: Seg, base: int, index: int, node: Node) -> None:
    """把第 index 个操作改成 node，并自底向上重算受影响的那条根到叶路径。"""
    pos = base + index - 1
    seg[pos] = node
    pos >>= 1
    while pos:               # 只有一条链上的结点变了
        refresh(seg, pos)
        pos >>= 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, q = next(data), next(data)

    ops: list[Node] = []  # 第 c 个操作（1 起编号）的叶子信息，修改时原地覆盖
    for _ in range(m):
        ops.append(leaf_of(next(data), next(data)))
    seg, base = build(ops)

    out: list[str] = []
    for _ in range(q):
        index = next(data)       # 题面的 c
        ops[index - 1] = leaf_of(next(data), next(data))
        update(seg, base, index, ops[index - 1])
        out.append(str(seg[1][2]))  # 根在“右侧无需求”下保留的和就是答案

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
