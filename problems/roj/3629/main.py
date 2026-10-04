#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:31
# update_at: 2026-10-02 11:52

import sys
from collections.abc import Iterator

N = 200000  # 题面 n 的上界，静态数组长度

to = [0] * (N + 1)    # to[i]：i 的信息传递对象（内向基环森林的出边）
color = [0] * (N + 1)  # 0 = 未访问，1 = 本轮在路上，2 = 已归档（含环与入链）


def read_ints(buf: bytes) -> Iterator[int]:
    """逐字节解析全部整数：split() 会一次造出 n 个小 bytes 对象，峰值内存顶破限制。"""
    num = 0
    in_num = False
    for b in buf:
        if 48 <= b <= 57:  # 数字位
            num = num * 10 + b - 48
            in_num = True
        elif in_num:       # 分隔符：收下刚攒完的数
            yield num
            num, in_num = 0, False
    if in_num:
        yield num


def rings(n: int) -> Iterator[int]:
    """从每个未访问点沿出边走到底，产出本轮新发现的环长。

    每人恰好一条出边，走到底必然撞上三种点：本轮在路上的点（自己的链闭成环）、
    已归档的点（走进别人的链/环，不产生新环）。环长 = 撞点在本轮路径中的位置到末尾。
    """
    for start in range(1, n + 1):
        if color[start]:
            continue  # 别人的链或环已覆盖，进去也找不到新环

        path: list[int] = []
        u = start
        while color[u] == 0:
            color[u] = 1  # 标"在路上"，链走到别处时立刻能认出
            path.append(u)
            u = to[u]

        if color[u] == 1:  # 撞回本轮标记：这条链自己闭成了环
            # 环长 = 撞点在路径中的位置到末尾；每个点只属于一条路径，总代价仍是 O(n)
            yield len(path) - path.index(u)

        for v in path:     # 归档整条链，之后任何链都不必再走第二遍
            color[v] = 2


def solve() -> None:
    data = read_ints(sys.stdin.buffer.read())
    n = next(data)
    for i in range(1, n + 1):
        to[i] = next(data)  # 题面的 T_i

    # 自己的生日只会沿环转回来：第 L 轮听到 = 自己在长 L 的环上，答案取最小环长
    print(min(rings(n)))


if __name__ == "__main__":
    solve()
