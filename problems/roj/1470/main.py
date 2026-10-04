#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:44
# update_at: 2026-09-30 12:44

import sys
from collections import deque


def build_automaton(words: list[bytes]) -> tuple[list[list[int]], list[int]]:
    """对屏蔽词建 AC 自动机：返回转移表 ch 与 end（节点 i 结尾的屏蔽词长度）。"""
    ch: list[list[int]] = [[0] * 26]  # 先只有 trie 边，0 = 无边（也是根）
    end: list[int] = [0]
    for w in words:
        cur = 0
        for c in w:
            c -= 97  # 'a' 的字节值
            if not ch[cur][c]:
                ch[cur][c] = len(ch)
                ch.append([0] * 26)
                end.append(0)
            cur = ch[cur][c]
        end[cur] = len(w)  # 屏蔽词互不为子串 → 每个节点至多结尾一个词

    fail: list[int] = [0] * len(ch)
    queue = deque(v for v in ch[0] if v)  # 第一层的 fail 都是根，默认即 0
    while queue:
        u = queue.popleft()
        for c in range(26):
            v = ch[u][c]
            if v:  # 真·孩子：定 fail 并沿链继承"以多长屏蔽词结尾"
                fail[v] = ch[fail[u]][c]
                end[v] = end[v] or end[fail[v]]
                queue.append(v)
            else:  # 补全成 trie 图：缺边改指向 fail 的同边，扫描时免跳 fail
                ch[u][c] = ch[fail[u]][c]
    return ch, end


def censor(s: bytes, ch: list[list[int]], end: list[int]) -> bytes:
    """从头匹配、命中即删：栈里存保留字符与各自前缀对应的自动机状态。"""
    kept: list[int] = []  # 保留字符（字节值）
    states: list[int] = [0]  # states[i] = 前缀 kept[:i] 的状态，states[0] = 根
    cur = 0
    for c in s:
        cur = ch[cur][c - 97]  # trie 图上一步转移，自带 fail 语义
        kept.append(c)
        states.append(cur)
        if end[cur]:  # 栈顶拼出了屏蔽词：连当前字符一起整段弹出，状态回到删除前的位置
            length = end[cur]
            del kept[-length:]
            del states[-length:]
            cur = states[-1]
    return bytes(kept)


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    s: bytes = data[0]
    if data[1].isdigit():  # 题面格式：第二行是屏蔽词个数 n
        n = int(data[1])
        words = data[2:2 + n]
    else:  # USACO 原始数据：第二行直接是唯一的屏蔽词
        words = data[1:]
    ch, end = build_automaton(words)
    sys.stdout.buffer.write(censor(s, ch, end))


if __name__ == "__main__":
    solve()
