#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:20
# update_at: 2026-09-30 14:20

import sys
from collections import deque

MOD = 10007       # 题面要求的结果模数
ALPHABET = 26     # 只可能出现英文大写字母


def build_automaton(words: list[bytes]) -> tuple[list[list[int]], list[bool]]:
    """插入所有单词建 trie 并 BFS 补全转移表，返回完整 goto 表 go 与危险标记 dead。

    go[v][c] 是"在状态 v 读到字符 c 后该去哪"；若 v 本身没有 c 边，就直接继承
    go[fail[v]][c]，根上缺的边指向根自己。补全后每步只查一次表，不必沿 fail 链回退。
    dead[v] 表示"走到状态 v 就已经包含了至少一个完整单词"：既包括 v 自己就是词尾，
    也包括某个词尾是 v 的真后缀——后者刚好由 fail 链给出，顺着 BFS 顺序把父亲的
    dead 往下传即可。
    """
    trie: list[list[int]] = [[-1] * ALPHABET]  # -1 表示这条边在 trie 上还不存在
    dead: list[bool] = [False]

    for w in words:
        node = 0
        for ch in w:
            c = ch - 65
            if trie[node][c] == -1:            # 该前缀第一次出现，新建节点
                trie[node][c] = len(trie)
                trie.append([-1] * ALPHABET)
                dead.append(False)
            node = trie[node][c]
        dead[node] = True                      # 词尾本身当然算"已包含单词"

    fail = [0] * len(trie)                     # 根和根的孩子失配后都回到根
    root = trie[0]                             # 根那一行，缺边时直接写 0

    # 先处理根的孩子：它们缺的边一律指向根，同时入队等待做 BFS。
    queue = deque()
    for c in range(ALPHABET):
        child = root[c]
        if child == -1:
            root[c] = 0
        else:
            queue.append(child)

    while queue:
        node = queue.popleft()
        dead[node] |= dead[fail[node]]         # fail 链上的词尾都算命中，向下传递
        inherit = trie[fail[node]]             # 缺边时整行继承的那一行
        for c in range(ALPHABET):
            child = trie[node][c]
            if child == -1:
                trie[node][c] = inherit[c]     # 补全：等价于沿 fail 链继续尝试读 c
            else:
                fail[child] = inherit[c]       # child 的真实失配边
                queue.append(child)
    return trie, dead


def count_safe(states: int, dead: list[bool], go: list[list[int]], length: int) -> int:
    """统计长度恰为 length、且完全不含任何单词的字符串个数（即"不可读文本"数）。

    dp[v] 是扫完当前长度后停在状态 v 的文本数；每一步让每个非死状态向它的 26 条
    出边转移，落在死状态上的文本直接丢弃。状态数 = trie 节点数，与文本长度无关。
    """
    dp = [0] * states
    dp[0] = 1                                  # 空串停在根
    for _ in range(length):
        nxt = [0] * states
        for v in range(states):
            ways = dp[v]
            if ways:
                for u in go[v]:
                    if not dead[u]:            # 只有落点安全才保留这条转移
                        nxt[u] = (nxt[u] + ways) % MOD
        dp = nxt
    return sum(dp) % MOD


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])                  # 单词数 N、文本固定长度 M
    words = data[2:2 + n]                              # 紧随其后的 N 行就是单词
    go, dead = build_automaton(words)

    total = pow(ALPHABET, m, MOD)                      # 全部可能的文章数 26^m
    readable = (total - count_safe(len(go), dead, go, m)) % MOD
    print(readable)


if __name__ == "__main__":
    solve()
