#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:30
# update_at: 2026-10-02 12:30

import sys

NEG = -1 << 60  # 空队头哨兵：任何合法存储值都比它大


def simulate(a: list[int], m: int, q: int, u: int, v: int, t: int) -> tuple[list[int], list[int]]:
    """模拟 m 秒切割，返回（每 t 秒记录的切口长度, m 秒后全部蚯蚓长度的降序序列）。

    长度统一存"归一化坐标"：世界长度 = 存储值 + off，off 是每秒对全体（除新生者）
    累加的 q。这样每秒不必真的给每只蚯蚓加 q。三段来源（初始段、左半段、右半段）
    的存储值都天然降序，因此各自只需比较队头就能取到全局最大。
    """
    big = sorted(a, reverse=True)  # 初始段：读入后整体降序
    left: list[int] = []           # 左半段 ⌊px⌋：切出顺序天然降序
    right: list[int] = []          # 右半段 x-⌊px⌋：切出顺序天然降序
    na, off, nb = len(big), 0, 0    # nb 同时是 left/right 的长度（两段总是成对产生）
    ia = ib = ic = 0                # 三个队列各自被取走的个数
    ha = big[0]                     # 三个队头的存储值，空队头记为 NEG
    hb = hc = NEG
    cut: list[int] = []

    for sec in range(1, m + 1):
        if ha >= hb and ha >= hc:    # 谁的队头大就切谁（平局任选，题目允许）
            x = ha + off             # 归一化坐标换回切口前的世界长度
            ia += 1
            ha = big[ia] if ia < na else NEG
        elif hb >= hc:
            x = hb + off
            ib += 1
            hb = left[ib] if ib < nb else NEG
        else:
            x = hc + off
            ic += 1
            hc = right[ic] if ic < nb else NEG

        if sec % t == 0:             # 第 t, 2t, 3t, … 秒记录切口
            cut.append(x)

        off += q                     # 其余蚯蚓本轮集体长 q；新生的两段不参与这一次增长
        head = u * x // v            # ⌊px⌋，p = u/v
        left.append(head - off)      # 新生段用"新 off"归一化，即此刻世界长度恰好是 head
        right.append(x - head - off)
        nb += 1
        # 若某个队头还是哨兵而它的队列刚进了新元素，就把哨头换成真值
        if hb == NEG:
            hb = left[ib] if ib < nb else NEG
        if hc == NEG:
            hc = right[ic] if ic < nb else NEG

    rest = [x + off for x in big[ia:] + left[ib:] + right[ic:]]  # 存储值换回世界长度
    rest.sort(reverse=True)
    return cut, rest


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)
    q = next(data)
    u = next(data)
    v = next(data)
    t = next(data)
    lengths = [next(data) for _ in range(n)]

    cut, rest = simulate(lengths, m, q, u, v, t)

    # 第 1 行取第 t, 2t, … 个切口；第 2 行取降序序列的第 t, 2t, … 名，空行也要输出
    print(' '.join(map(str, cut)))
    print(' '.join(map(str, rest[t - 1::t])))


if __name__ == "__main__":
    solve()
