#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 10:20
# update_at: 2026-10-08 10:20

import sys

START = -1  # 栈底哨兵：起点顶点没有「进入它的弧」，回溯时跳过


def euler_cycle(n: int) -> list[int]:
    """返回顶点集 Z_n 上一条欧拉回路的弧标号序列，即一组合法座位圈。

    弧 a 从顶点 a//2 出发指向顶点 a%n，共 2n 条；每个顶点出入度都是 2，
    故必存在欧拉回路。Hierholzer 迭代写法：能走就走，走不动了把「进来的那条弧」
    压进 path，最后把 path 逆序即为答案。
    """
    used = bytearray(n)     # 顶点 v 已用掉的出弧数（0 或 1 或 2）
    stack = [START]         # 栈元素是「进入当前顶点的弧号」
    path: list[int] = []    # 回溯顺序登记的弧号（答案的逆序）
    while stack:
        arc = stack[-1]
        v = 0 if arc == START else arc % n          # 弧 arc 的头顶点
        if used[v] < 2:                             # 还有没走过的出弧，继续深入
            used[v] += 1
            stack.append(2 * v + used[v] - 1)       # 出弧编号：2v 或 2v+1
        else:                                       # 出弧走完，回溯时登记进来的弧
            path.append(arc)
            stack.pop()
    return path[-2::-1]     # 逆序，并丢掉末尾的起点哨兵


def solve() -> None:
    data = map(int, sys.stdin.buffer.read().split())
    print('\n'.join(' '.join(map(str, euler_cycle(n))) for n in data))


if __name__ == "__main__":
    solve()
