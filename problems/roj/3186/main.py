#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 00:00
# update_at: 2026-10-02 00:00

import sys
from collections import defaultdict

PARK = 0  # 公园节点编号，人按出现顺序从 1 开始编号


def find(fa: list[int], x: int) -> int:
    """并查集查找（路径压缩），返回 x 所在连通块的根。"""
    while fa[x] != x:
        fa[x] = fa[fa[x]]
        x = fa[x]
    return x


def kruskal(edges: list[tuple[int, int, int]], m: int) -> tuple[list[tuple[int, int, int]], list[int]]:
    """只用人—人边跑最小生成森林，返回 (选中的边, 并查集)。"""
    fa = list(range(m))
    tree = []
    for w, a, b in sorted(edges):
        ra, rb = find(fa, a), find(fa, b)
        if ra != rb:
            fa[ra] = rb
            tree.append((w, a, b))
    return tree, fa


def worst_on_path(tree: list[tuple[int, int, int]], src: int) -> tuple[int, int, int] | None:
    """src 到公园的树上路径中，最重的「非公园边」；路径上没有（单点块）则 None。

    返回边本身而不是权值，调用方要把它从树上删掉。最后一段公园边不参与比较：
    删公园边不会让公园度数 +1，起不到「多停一辆车」的作用。
    """
    adj = defaultdict(list)
    for e in tree:
        w, a, b = e
        adj[a].append((b, w, e))
        adj[b].append((a, w, e))
    stack = [(src, PARK, -1, None)]  # (点, 来时的点, 路径最重非公园边权, 对应边)
    while stack:
        u, fa, w_mx, e_mx = stack.pop()
        for v, w, e in adj[u]:
            if v == fa:
                continue
            if v == PARK:  # 树上路径唯一，碰到公园即可收工
                return e_mx
            stack.append((v, u, max(w_mx, w), e if w > w_mx else e_mx))
    return None


def solve() -> None:
    it = iter(sys.stdin.read().split())
    n = int(next(it))

    name_id: dict[str, int] = {"Park": PARK}

    def ident(name: str) -> int:
        """名字 → 编号：公园固定为 PARK，其他人按出现顺序编号。"""
        if name not in name_id:
            name_id[name] = len(name_id)
        return name_id[name]

    road, link = [], []  # 人—人边 (w,a,b)；人—公园边 (w,人)
    for _ in range(n):
        a, b, w = ident(next(it)), ident(next(it)), int(next(it))
        if a == PARK and b == PARK:
            continue  # 公园—公园的边没有意义
        if a == PARK or b == PARK:
            link.append((w, b if a == PARK else a))
        else:
            road.append((w, a, b))

    s = int(next(it))
    tree, fa = kruskal(road, len(name_id))

    # 第一步：每个连通块用它最便宜的公园边接入公园，此时公园度数 = 连通块数 k
    cheapest: dict[int, tuple[int, int]] = {}  # 块根 -> (权, 人)
    for w, v in link:
        root = find(fa, v)
        if root not in cheapest or w < cheapest[root][0]:
            cheapest[root] = (w, v)
    for w, v in cheapest.values():
        tree.append((w, v, PARK))
    k = len(cheapest)

    # 第二步：还有空车位时，反复做「加一条公园边、删路径上最重的非公园边」的交换
    for _ in range(s - k):
        pick = None  # (净收益 w-删边权, 公园边权, 人, 要删的边)
        for w, v in link:
            drop = worst_on_path(tree, v)
            if drop is None:  # 单人块没有内部边可删，加边只会翻倍停车
                continue
            gain = w - drop[0]
            if gain < 0 and (pick is None or gain < pick[0]):
                pick = (gain, w, v, drop)
        if pick is None:  # 剩下的交换都会变贵，提前收手
            break
        _, w, v, drop = pick
        tree.remove(drop)
        tree.append((w, v, PARK))

    print(f"Total miles driven: {sum(w for w, _, _ in tree)}")


if __name__ == "__main__":
    solve()
