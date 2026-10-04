#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:09
# update_at: 2026-10-02 01:09

import sys
from array import array

NO_ARC = -1  # 邻接链表结束标记；弧编号从 0 开始，所以只能用负数当空指针


def euler_circuit(nxt: array, to: array, head: array, start: int) -> list[int]:
    """从 start 出发逐条用掉弧，返回欧拉回路的顶点序列（逆序，需翻转后输出）。

    每条无向边拆成互为反向的两条有向弧，因此每个点入度 = 出度，
    有向图必有欧拉回路。栈里存的是一条尚未走完的路径前缀：
    栈顶点还有弧就从它继续往下走，一条弧都没有了就说明它的后继已经确定，
    可以立刻钉死在回路的末尾。
    """
    stack = [start]
    tour: list[int] = []
    while stack:
        arc = head[stack[-1]]
        if arc == NO_ARC:
            tour.append(stack.pop())  # 出边用光：这个点已经可以固定到回路末尾
        else:
            head[stack[-1]] = nxt[arc]  # 摘掉这条弧，保证正、反方向各只用一次
            stack.append(to[arc])
    return tour


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])

    # 弧 2i / 2i+1 是同一条边的两个方向：弧 arc 的起点是 to[arc ^ 1]，终点是 to[arc]
    to = array('i', map(int, data[2:2 + 2 * m]))
    nxt = array('i', [NO_ARC]) * (2 * m)
    head = array('i', [NO_ARC]) * (n + 1)
    for arc in range(2 * m):
        v = to[arc ^ 1]
        nxt[arc] = head[v]
        head[v] = arc

    tour = euler_circuit(nxt, to, head, 1)
    sys.stdout.write('\n'.join(map(str, tour[::-1])))


if __name__ == "__main__":
    solve()
