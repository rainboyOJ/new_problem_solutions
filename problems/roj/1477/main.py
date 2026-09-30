#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:24
# update_at: 2026-09-30 13:24

import sys

ROOT = 0    # 虚拟根：它不是一个单词，代表"没有任何后缀"的起点
BASE = 26   # 字母表大小，把 (节点, 字符) 压成一个整数键


def build_reversed_trie(words: list[str]) -> tuple[list[int], bytearray]:
    """把每个单词反转后插入字典树；反转后"后缀"关系变成"前缀"关系。

    返回每个节点的父节点 parent 与单词终止标记 is_end。
    节点编号沿插入路径严格递增，所以父编号一定小于子编号。
    """
    nxt: dict[int, int] = {}
    parent = [-1]
    is_end = bytearray(1)
    for word in words:
        node = ROOT
        for ch in reversed(word):                    # 插入反转串：单词的后缀成为树上的祖先
            key = node * BASE + ord(ch) - 97
            child = nxt.get(key)
            if child is None:
                child = len(parent)
                nxt[key] = child
                parent.append(node)
                is_end.append(0)
            node = child
        is_end[node] = 1
    return parent, is_end


def nearest_end_ancestor(parent: list[int], is_end: bytearray) -> list[int]:
    """每个节点最近的"单词终止"祖先，没有则挂在虚拟根 0 上。

    节点编号父小于子，正序一趟即可用父亲的答案推出自己的答案。
    """
    up = [ROOT] * len(parent)
    for v in range(1, len(parent)):
        p = parent[v]
        up[v] = p if is_end[p] else up[p]
    return up


def greedy_dfs_order(up: list[int], words_nodes: list[int]) -> int:
    """按"子树小的先填"的 DFS 前序排单词，返回 Σ(序号 − 父单词序号)。

    合法序下某个单词最后一个被填的后缀就是它的父节点，所以让每个词尽量靠近父亲，
    就是让每个节点的儿子按子树大小升序访问。
    """
    size = {v: 1 for v in words_nodes}               # 只统计单词节点，中转节点不计
    for v in reversed(words_nodes):                  # 逆序保证先算完儿子再算父亲
        p = up[v]
        if p in size:
            size[p] += size[v]

    children: dict[int, list[int]] = {ROOT: []}
    for v in words_nodes:
        children.setdefault(up[v], []).append(v)
    for kids in children.values():
        kids.sort(key=size.__getitem__)              # 子树小的先访问

    ans = 0
    pos = 0                                          # 已填单词数，也是下一个词的序号
    stack = [(v, 0) for v in reversed(children[ROOT])]  # 根的儿子没有后缀，父亲序号视作 0
    while stack:
        node, parent_pos = stack.pop()
        pos += 1
        ans += pos - parent_pos
        stack.extend((kid, pos) for kid in reversed(children.get(node, ())))
    return ans


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    words = [w.decode() for w in data[1:]]           # 首个数是 n，其余每行一个单词

    parent, is_end = build_reversed_trie(words)
    words_nodes = [v for v in range(1, len(parent)) if is_end[v]]
    print(greedy_dfs_order(nearest_end_ancestor(parent, is_end), words_nodes))


if __name__ == "__main__":
    solve()
