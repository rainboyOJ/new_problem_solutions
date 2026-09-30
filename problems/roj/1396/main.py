#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:34
# update_at: 2026-09-30 08:34

import sys
from heapq import heapify, heappop, heappush

FAIL = '0'  # 字典残缺或自相矛盾时输出的唯一一个字符


def first_diff(u: bytes, v: bytes) -> tuple[int, int] | None:
    """相邻两词首个不同位置的字母对（密文前驱, 密文后继）；其中一个是另一个前缀时返回 None。"""
    for a, b in zip(u, v):
        if a != b:
            return a, b
    return None  # 例如 ac < acd：短词是长词前缀，不告诉任何字母的大小关系


def relation(words: list[bytes], i: int) -> tuple[int, int] | None:
    """第 i 与第 i+1 个词给出的字母大小关系；两词完全相同时这对词作废。"""
    if i + 1 < len(words) and words[i] == words[i + 1]:
        return None  # 排列严格递增，不该出现重复词，更不该让它的首不同对又去连一条边
    return first_diff(words[i], words[i + 1])


def recover(words: list[bytes], target: bytes) -> str:
    """还原明文串；字典不足以定序（成环或多解）时返回 FAIL。"""
    edges = set(filter(None, map(lambda i: relation(words, i), range(len(words) - 1))))
    # 只有当过"首不同对"主角的字母才被字典约束住；只作普通字符出现的字母进了图会冒充最小字母
    alphabet = sorted({c for a, b in edges for c in (a, b)})
    if not alphabet:                                 # 一个相邻词对都挑不出来：字典只剩一个字母的余地
        alphabet = sorted(set(target))               # 按明文序重编号后就是按字母表顺序，直接小写序
    succ = {c: set() for c in alphabet}              # 明文序中必须紧跟在 c 后面的那些字母
    for a, b in edges:
        succ[a].add(b)

    indeg = {c: 0 for c in alphabet}
    for d in succ.values():
        for x in d:
            indeg[x] += 1
    ready = [c for c in alphabet if not indeg[c]]
    heapify(ready)                                   # 每轮取最小编号，等价于反复扫候选表
    order: list[int] = []
    unique = True
    while ready:
        if len(ready) > 1:                           # 同时有两个可选字母 ⇒ 至少两种合法明文序
            unique = False
        c = heappop(ready)
        order.append(c)
        for d in succ[c]:
            indeg[d] -= 1
            if not indeg[d]:
                heappush(ready, d)

    if len(order) != len(alphabet) or not unique:    # 有环，或有字母的位置没被唯一确定
        return FAIL
    if not set(target) <= set(alphabet):             # 待还原串里出现了字典之外的字母
        return FAIL                                  # 说明这份字典根本没覆盖全部字母
    table = bytes.maketrans(bytes(order), bytes(range(97, 97 + len(order))))
    return target.translate(table).decode()          # 密文按明文序重编号，再换成 a,b,c,...


def solve() -> None:
    data = sys.stdin.buffer
    k = int(data.readline())
    words = [data.readline().strip() for _ in range(k)]
    target = data.readline().strip()
    print(recover(words, target))


if __name__ == "__main__":
    solve()
