#!/usr/bin/env python3
"""P9246 砍树的随机数据生成器，输出到 stdout。

题面约束：1 <= m <= n // 2，a_i 两两不同、b_i 两两不同，且 a_i != b_j（两个集合不交）。
暴力解是 O(n^2 α(n)) 的枚举砍边，所以这里的 n 控制在 1000 以内，保证对拍能跑完。

默认使用固定种子，保证同一个种子一定能复现同一份数据；
需要多跑几组不同数据时用 DUPAI_SEED 环境变量换种子。
"""

import os
import random

SEED = 20231003


def random_tree(n):
    """随机树：每个点 2..n 随机挂到前面某个点上，返回边表。"""
    edges = []
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        edges.append((u, v))
    random.shuffle(edges)
    return edges


def path_tree(n):
    """链：边 (i, i+1)，用来覆盖深度大、路径长的边界情况。"""
    return [(i, i + 1) for i in range(1, n)]


def star_tree(n):
    """菊花：所有边都挂在 1 号点上，用来覆盖“一条边都砍不动”的情况。"""
    return [(1, i) for i in range(2, n + 1)]


def build_tree(n, shape):
    if shape == "path":
        return path_tree(n)
    if shape == "star":
        return star_tree(n)
    return random_tree(n)


def random_pairs(n, m):
    """随机取两个不交的集合 A、B，各含 m 个点，配对成 m 个无序数对。

    因为 A、B 不交，所以 a_i != b_j 自动成立，正好符合题面约束。
    """
    nodes = list(range(1, n + 1))
    random.shuffle(nodes)
    left = nodes[:m]
    right = nodes[m:2 * m]
    return list(zip(left, right))


def root_tree(n, edges):
    """以 1 为根做一次 BFS，返回 par[] 和 bfs 序。"""
    adj = [[] for _ in range(n + 1)]
    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)
    par = [0] * (n + 1)
    in_queue = [False] * (n + 1)
    order = [1]
    in_queue[1] = True
    for u in order:
        for v in adj[u]:
            if not in_queue[v]:
                in_queue[v] = True
                par[v] = u
                order.append(v)
    return par, order


def split_by_edge(n, edges, par, order, edge_index):
    """返回砍掉第 edge_index 条边后，子树一侧的点集。"""
    u, v = edges[edge_index - 1]
    child = u if par[u] == v else v      # 这条边在根树上的儿子端点
    inside_flag = [False] * (n + 1)
    inside_flag[child] = True
    for x in order:                       # bfs 序保证父亲先被处理
        if x != child and inside_flag[par[x]]:
            inside_flag[x] = True
    return [x for x in range(1, n + 1) if inside_flag[x]]


def pairs_across_edge(n, m, edges, inside, outside):
    """从边两侧各取 m 个点配对，这样每一对都跨过这条边。

    因此这组数据保证有解，而且这条边一定在答案里。
    """
    a = random.sample(inside, m)
    b = random.sample(outside, m)
    return list(zip(a, b))


def blocks_case(n, m):
    """构造“有多个可行答案”的数据，专门验证最后要输出最大边号。

    把链上的点依次分为 X、Y、Z 三段，让 |X| >= m、|Z| >= m、Y 非空，
    数对全部是 X 里的点和 Z 里的点配对。这样凡是 X 与 Z 之间的边（Y 两侧的整段）
    都会被全部 m 条路径跨过，答案必须是其中编号最大的那条，能真正检验取最大值这一步。
    """
    left_size = random.randint(m, n - m - 1)
    right_size = random.randint(m, n - left_size - 1)
    mid_size = n - left_size - right_size
    labels = list(range(1, n + 1))
    random.shuffle(labels)
    pos = labels                       # pos[i-1] 是链上第 i 个位置的点编号
    x = pos[:left_size]
    z = pos[left_size + mid_size:]
    edges = [(pos[i], pos[i + 1]) for i in range(n - 1)]
    random.shuffle(edges)
    a = random.sample(x, m)
    b = random.sample(z, m)
    return edges, list(zip(a, b))


# (n, m, 树形状, 是否构造保证有解的数据)
CASES = [
    (2, 1, "random", False),      # 最小 n：只有一条边
    (3, 1, "random", False),
    (6, 3, "random", False),
    (10, 5, "random", False),     # m 取满 n // 2
    (30, 15, "path", True),       # 长链 + 保证有解
    (50, 5, "star", False),       # 菊花：一般无解，答案 -1
    (80, 40, "random", True),     # 保证有解的中规模随机树
    (200, 100, "path", True),     # 满 m 的链
    (400, 20, "random", False),
    (1000, 500, "random", True),  # 暴力仍能跑完的最大规模
    (60, 12, "blocks", False),    # 多个可行答案，验证输出最大编号
    (300, 40, "blocks", False),
]


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    random.seed(SEED if seed_text is None else int(seed_text))

    n, m, shape, force_answer = random.choice(CASES)
    if shape == "blocks":
        edges, pairs = blocks_case(n, m)
        lines = ["%d %d" % (n, m)]
        for u, v in edges:
            lines.append("%d %d" % (u, v))
        for a, b in pairs:
            lines.append("%d %d" % (a, b))
        print("\n".join(lines))
        return

    edges = build_tree(n, shape)

    pairs = None
    if force_answer:
        # 先找出“砍开后两边都至少 m 个点”的所有边，再从里面随机挑一条，
        # 用这条边把数据造成一定有解的情形。
        par, order = root_tree(n, edges)
        valid = []
        for edge_index in range(1, n):
            inside = split_by_edge(n, edges, par, order, edge_index)
            if m <= len(inside) <= n - m:
                valid.append((edge_index, inside))
        if valid:
            edge_index, inside = random.choice(valid)
            inside_set = set(inside)
            outside = [x for x in range(1, n + 1) if x not in inside_set]
            pairs = pairs_across_edge(n, m, edges, inside, outside)
    if pairs is None:
        pairs = random_pairs(n, m)

    lines = ["%d %d" % (n, m)]
    for u, v in edges:
        lines.append("%d %d" % (u, v))
    for a, b in pairs:
        lines.append("%d %d" % (a, b))
    print("\n".join(lines))


if __name__ == "__main__":
    main()
