#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:29
# update_at: 2026-10-04 11:56

import sys


def find(father: list[int], x: int) -> int:
    """求 x 所在家族的根，并把路径上的点全部直接挂到根上（路径压缩）。"""
    root = x
    while father[root] != root:  # 第一趟：顺着父亲指针走到根
        root = father[root]
    while father[x] != root:     # 第二趟回溯：整条路径一次改挂到根
        father[x], x = root, father[x]
    return root


def solve() -> None:
    """M a b 合并两个家族，Q a 输出 a 所在家族的人数。"""
    # token 里整数与操作符 M/Q 混排，没法整体 map(int)，按位置顺序消费、用到时再转 int
    data = iter(sys.stdin.buffer.read().split())
    n, m = int(next(data)), int(next(data))
    father = list(range(n + 1))
    cnt = [0] + [1] * n  # cnt[r] = 根 r 所在家族的人数；cnt[0] = 0 对应 std 全局数组的零初始化

    out: list[str] = []
    for _ in range(m):
        op = next(data)  # 操作符 token：b"M" 合并 / b"Q" 查询
        if op == b"M":
            a, b = int(next(data)), int(next(data))
            ra, rb = find(father, a), find(father, b)
            if ra != rb:  # 按大小合并：小家族整棵挂到大家族的根下
                if cnt[ra] < cnt[rb]:
                    ra, rb = rb, ra
                father[rb] = ra
                cnt[ra] += cnt[rb]
        elif op == b"Q":
            a = int(next(data))
            out.append(str(cnt[find(father, a)]))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
