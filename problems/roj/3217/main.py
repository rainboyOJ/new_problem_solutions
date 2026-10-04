#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def euler_route(width: int, start: int = 0) -> list[int]:
    """在以 k-1 位窗口为节点的 de Bruijn 图上跑 Hierholzer，返回欧拉回路途经的节点序列。

    节点 v 代表当前窗口，加一位 b 得到的边编号为 v*2+b，到达窗口 (v*2+b) 去掉最高位。
    每个节点恰好两条出边，全图 M=2^k 条边，回路存在且唯一覆盖所有窗口。
    优先走 0 边、逆后序还原，得到字典序最小的回路。
    """
    used = bytearray(width << 2)  # 边 v*2+b 是否已走：共 2^k 条
    stack = [start]
    route: list[int] = []
    while stack:
        v = stack[-1]
        base = v << 1
        nxt = next((base + b for b in (0, 1) if not used[base + b]), None)
        if nxt is None:  # 出边用尽，回溯时记录，逆序即为回路方向
            route.append(stack.pop())
        else:
            used[nxt] = 1
            stack.append(nxt & (width - 1))  # 新窗口 = 去掉最高一位
    route.reverse()
    return route


def solve() -> None:
    k = int(sys.stdin.buffer.read().split()[0])
    width = 1 << (k - 1)  # 节点数：长度 k-1 的窗口
    total = 1 << k        # 环上传感器数 M = 2^k

    route = euler_route(width)
    # 起点窗口是 k-1 个 0，之后每条边贡献一个新位；环是循环的，截取前 M 位
    bits = "0" * (k - 1) + "".join(str(u & 1) for u in route[1:])
    print(total, bits[:total])


if __name__ == "__main__":
    solve()
