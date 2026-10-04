#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:56
# update_at: 2026-10-01 09:56

import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    a = data[1 : n + 1]

    # 差分槽位 b[i] = a[i] - a[i-1]（a[0] = 0），下标 2..n 是必须清零的约束槽位；
    # b[1] 与虚拟槽 b[n+1] 自由：前者唯一决定最终的公共值，后者吸收对后缀的操作
    diff = [a[i] - a[i - 1] for i in range(1, n)]  # 依次是 b[2..n]

    pos = sum(x for x in diff if x > 0)   # 正槽位之和：需要被 -1 操作消掉的量
    neg = sum(-x for x in diff if x < 0)  # 负槽位绝对值之和：需要被 +1 操作消掉的量

    # 一对正负槽可被同一次区间操作各消 1，剩余的单边缺口靠自由槽吸收 → max(pos, neg)
    print(max(pos, neg))
    # 单边缺口的每次操作可任意分配给 b[1]（改公共值）或 b[n+1]（不改）→ 缺口 k 对应 k+1 种结果
    print(abs(pos - neg) + 1)


if __name__ == "__main__":
    solve()
