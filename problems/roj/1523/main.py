#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:55
# update_at: 2026-09-30 15:55

import sys

NO_ANSWER = "No solution"  # 找不到必经点时的输出


def reachable(g: list[set[int]], src: int, dst: int, skip: int) -> bool:
    """删掉顶点 skip 后，src 是否还能到达 dst（显式栈 DFS）。"""
    seen = {skip}  # 把 skip 预置为已访问，等于从图中删掉它
    stack = [src]
    while stack:
        v = stack.pop()
        if v == dst:
            return True
        seen.add(v)
        stack += [w for w in g[v] if w not in seen]
    return False


def find_sniffer(g: list[set[int]], n: int, a: int, b: int) -> int | None:
    """编号最小的中间服务器 v：a 到 b 的每条路径都必经 v；不存在则返回 None。"""
    # v 在所有 a-b 路径上 ⟺ 删掉 v 后 a 到不了 b（割点判定）。
    # 逐点删一次再测连通即可；v 不能是 a、b 自身，它们不是"中间"服务器。
    for v in range(1, n + 1):
        if v != a and v != b and not reachable(g, a, b, v):
            return v
    return None


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 服务器数目
    g: list[set[int]] = [set() for _ in range(n + 1)]
    while True:
        i, j = next(data), next(data)
        if i == 0 and j == 0:  # 0 0 标志拓扑描述结束
            break
        g[i].add(j)
        g[j].add(i)  # 连接是双向的
    a, b = next(data), next(data)  # 两个信息中心

    ans = find_sniffer(g, n, a, b)
    print(NO_ANSWER if ans is None else ans)


if __name__ == "__main__":
    solve()
