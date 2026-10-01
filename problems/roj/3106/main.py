#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:27
# update_at: 2026-10-01 17:46

import sys

LIMIT = 30000  # 题面 N <= 30000，战舰编号固定落在这个范围内


def solve() -> None:
    stdin = sys.stdin.buffer
    T = int(stdin.readline())
    out = bytearray()  # C 指令最多 50 万条，攒进 bytearray 一次写出，省内存也省时间

    # 带权并查集：fa[i] 是 i 的父结点，front[i] 是 i 前面还排着多少艘战舰
    # （只统计到父结点这一段，find 时沿路径累加就得到整列里的下标）。
    # 每列的队首（根）额外记一个 size：该列当前的战舰总数。
    fa = list(range(LIMIT + 1))
    front = [0] * (LIMIT + 1)  # 初始每列只有自己，前面没有战舰
    size = [1] * (LIMIT + 1)

    def find(x: int) -> int:
        """返回 x 所在列的队首，并把 x 到队首的 front 累加好、路径压平。

        必须迭代：M 指令能把列接成一条长链，递归会超过 Python 的递归深度。
        """
        root, path = x, []
        while fa[root] != root:  # 先向上走到队首，沿路记下经过的结点
            path.append(root)
            root = fa[root]
        depth = 0
        for node in reversed(path):  # 再从队首一侧往回累加，顺手挂到队首上
            depth += front[node]
            front[node] = depth
            fa[node] = root
        return root

    for _ in range(T):
        op, x, y = stdin.readline().split()
        x, y = int(x), int(y)
        rx, ry = find(x), find(y)

        if op == b"M":  # 指令 M：把 x 所在列整列接到 y 所在列尾部
            if rx != ry:  # 两舰本就在同一列时是空操作，跳过更省时间
                front[rx] = size[ry]  # x 那列的首舰前方正好是 y 那列的全体
                size[ry] += size[rx]
                fa[rx] = ry
        elif rx != ry:  # 指令 C，且两舰不在同一列
            out += b"-1\n"
        else:  # 指令 C，同一列：下标差扣掉对方那艘；问自己时差为 0 不扣
            gap = abs(front[x] - front[y])
            out += str(gap - 1 if gap else 0).encode() + b"\n"

    sys.stdout.buffer.write(out)


if __name__ == "__main__":
    solve()
