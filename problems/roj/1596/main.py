#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:05
# update_at: 2026-09-30 21:05

import sys

WINDOW = 5
STATES = 1 << WINDOW  # 窗口状态数：5 个围栏各「留 / 移」两种，共 32 种
NEG = -1 << 60        # 不可达状态的初值，比任何合法答案都小


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    fence, kids = data[0], data[1]

    # 按小朋友看到的起始围栏 E 分桶，桶里存 (害怕集合, 喜欢集合) 的 5 位掩码，
    # 位 j 表示他视野里第 j 个围栏（即编号 E+j），1 表示该围栏出现在对应名单里。
    by_start: list[list[tuple[int, int]]] = [[] for _ in range(fence + 1)]
    pos = 2
    for _ in range(kids):
        start, feared, liked = data[pos], data[pos + 1], data[pos + 2]
        pos += 3
        # 围栏编号绕圈回绕：(编号 - E) mod N 就是它在窗口内的下标
        afraid = 0
        for _ in range(feared):
            afraid |= 1 << ((data[pos] - start) % fence)
            pos += 1
        fond = 0
        for _ in range(liked):
            fond |= 1 << ((data[pos] - start) % fence)
            pos += 1
        by_start[start].append((afraid, fond))

    # gain[e][s]：起始围栏为 e、5 位保留情况为 s 时，能高兴的小朋友数。
    # 高兴 <=> 有害怕的动物被移走 (afraid & ~s) 或 有喜欢的动物被留下 (fond & s)。
    # 位 j 对齐，故 s 可直接与两个掩码按位运算。
    # 末尾多出一行全 0：窗口滑到起点 N+1（就是起点 1）时只做平移、不重复计分。
    gain = [
        [sum(1 for afraid, fond in by_start[e] if afraid & ~s or fond & s) for s in range(STATES)]
        for e in range(1, fence + 1)
    ] + [[0] * STATES]

    # next_s: 窗口状态从 s 滑动一格后的两个候选（新围栏的动物留 / 移）。
    # 位 j 记录围栏 pos+j，滑动后旧位 j 变成新位 j-1，新位 4 就是刚进视野的围栏。
    next_s = [(s >> 1, s >> 1 | 16) for s in range(STATES)]

    best = 0
    # 圆环没有天然起点，只能枚举第 1 个窗口的 5 位状态；滑 N 格后必须回到同一个状态。
    for first in range(STATES):
        cur = [NEG] * STATES
        cur[first] = gain[0][first]  # gain[0] 对应起始围栏 1
        # 起点 1 已作为初值算过，再滑 N 次：前 N-1 次补齐起点 2..N，最后一次不带分回到起点 1。
        for row in gain[1:]:
            nxt = [NEG] * STATES
            for s, val in enumerate(cur):
                if val == NEG:
                    continue
                for t in next_s[s]:
                    cand = val + row[t]
                    if cand > nxt[t]:
                        nxt[t] = cand
            cur = nxt
        if cur[first] > best:  # 绕回起点，只有状态吻合的方案才是合法的圆环安排
            best = cur[first]

    print(best)


if __name__ == "__main__":
    solve()
