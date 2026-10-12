#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-12 00:00
# update_at: 2026-10-12 00:00

"""
trie_dfs.py：【例3-2】单词查找树 解法二的 Python 版 —— 先建字典树，再树上 DFS 统计

树用「父亲-孩子表示法」存：fa[u] 记父亲、ch[u] 记孩子列表，向上向下都 O(1)；
label[u] 记结点上的字母（根不含字母，记 -1），孩子按加入顺序排列。
单词逐个插入：公共前缀只复用已有结点，走到头才开新结点，所以结点数自动最少。
建完后 dfs(根) 返回整棵树的结点数（含根）。
"""

import sys

fa: list[int] = []          # fa[u]：u 的父亲；fa[1] = 0 正好表示"根没有父亲"
ch: list[list[int]] = []    # ch[u]：u 的孩子，按加入顺序
label: list[int] = []       # label[u]：u 上的字母（'A'=65 ... 'Z'=90），根记 -1
node_cnt: int               # 已经开出的结点数，根结点固定编号 1


def init(n: int) -> None:
    """把 1..n 清空，fa 全为 0（fa[root] = 0 正好表示"根没有父亲"）。"""
    global fa, ch, label, node_cnt
    fa = [0] * (n + 1)
    ch = [[] for _ in range(n + 1)]
    label = [-1] * (n + 1)
    node_cnt = 1            # 编号 1 = 根，根不含字母


def add_child(u: int, v: int) -> None:
    """u 是 v 的父亲：孩子挂到 ch[u]，父亲写进 fa[v]，加边 O(1)。"""
    ch[u].append(v)
    fa[v] = u


def find_child(u: int, b: int) -> int:
    """在 ch[u] 里找字母为 b 的孩子，没有返回 0（编号从 1 开始，0 表示不存在）。
    每个结点最多 26 个孩子，线性扫也是 O(1)。"""
    for v in ch[u]:
        if label[v] == b:
            return v
    return 0


def new_node(u: int, b: int) -> int:
    """动态开一个字母为 b 的结点，挂在 u 下面，返回它的编号。"""
    global node_cnt
    node_cnt += 1
    v = node_cnt
    label[v] = b
    add_child(u, v)
    return v


def insert(word: bytes) -> None:
    """插入一个单词：已有的前缀直接复用，走到头才开新结点。"""
    u = 1
    for b in word:
        v = find_child(u, b)
        if v == 0:
            v = new_node(u, b)
        u = v


def dfs(u: int) -> int:
    """以 u 为根的子树共有多少个结点（含 u）：dfs(u) = 1 + Σ dfs(孩子)。"""
    cnt = 1
    for v in ch[u]:
        cnt += dfs(v)
    return cnt


def solve() -> None:
    words = sys.stdin.buffer.read().split()   # 按空白切分，忽略空行

    # 结点数不超过 1 + 全部字符总数，先量好空间再一次 init
    init(1 + sum(len(w) for w in words))
    for w in words:
        insert(w)

    # DFS 返回值就是整棵树的结点数（含根）
    print(dfs(1))


if __name__ == "__main__":
    solve()
