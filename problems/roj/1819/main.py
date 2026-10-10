#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:41
# update_at: 2026-10-08 06:41

import sys
from collections.abc import Iterator

HY = 'HY wins!'
TEACHER = 'Teacher wins!'

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Trie = list[dict[int, int]]  # ch[u][字符] = 子节点编号，节点 u 代表某个前缀，0 号是空串根
type RootAbility = tuple[bool, bool]  # 根节点的 (先手能否强行赢本轮, 先手能否强行输本轮)


def read_groups(tokens: Iterator[bytes]) -> Iterator[tuple[int, list[bytes]]]:
    """按 EOF 逐组产出 (轮数 k, 这一组的 n 个串)；n 只用来切出这一组的串。"""
    while (head := next(tokens, None)) is not None:
        n, k = int(head), int(next(tokens))
        yield k, [next(tokens) for _ in range(n)]


def build_trie(words: list[bytes]) -> Trie:
    """把所有串插进 Trie，返回 ch[u] = {字符: 子节点编号}。"""
    ch: Trie = [{}]
    for s in words:
        cur = 0
        for c in s:  # bytes 迭代出的是字符的 ASCII 码，直接当字典键
            nxt = ch[cur].get(c)
            if nxt is None:
                ch.append({})
                nxt = len(ch) - 1
                ch[cur][c] = nxt
            cur = nxt
    return ch


def root_ability(ch: Trie) -> RootAbility:
    """自底向上求根节点的两维能力：能否强行赢、能否强行输。"""
    order: list[int] = []
    stack = [0]
    while stack:  # 迭代式先序遍历，避免 1e5 深链时超递归深度
        u = stack.pop()
        order.append(u)
        stack.extend(ch[u].values())

    win = bytearray(len(ch))  # win[u]：轮到 u 处行棋的人能否强行赢下本轮
    lose = bytearray(len(ch))  # lose[u]：同上，能否强行输掉本轮（把先手权让出去）
    for u in reversed(order):  # 先序的逆序 = 每个点都排在它的子节点之后
        if not ch[u]:  # 叶子：轮到的人无路可走，本轮已经输了
            lose[u] = 1
            continue
        kids = ch[u].values()
        win[u] = any(not win[v] for v in kids)   # 走到对手无法强赢的点
        lose[u] = any(not lose[v] for v in kids)  # 走到对手无法强输的点（对手只能赢，于是自己输）
    return bool(win[0]), bool(lose[0])


def verdict(k: int, ability: RootAbility) -> str:
    """把根节点的两维能力和轮数 k 翻译成最终胜者。"""
    win, lose = ability
    if not win:  # 一轮也赢不了：输者仍是下一轮先手，Teacher 连赢 k 轮
        return TEACHER
    if lose:  # 可自选胜负：先连输 k-1 轮保持先手，最后一轮赢
        return HY
    return HY if k % 2 else TEACHER  # 只能赢不能输：胜负交替，只看 k 的奇偶


def solve() -> None:
    out: list[str] = []
    for k, words in read_groups(iter(sys.stdin.buffer.read().split())):
        out.append(verdict(k, root_ability(build_trie(words))))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
