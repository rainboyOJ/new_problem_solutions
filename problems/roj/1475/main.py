#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:15
# update_at: 2026-09-30 13:15

import sys

TERMINAL = "#"  # 字典树单词终止标记


def build_trie(words: list[str]) -> dict:
    """构建字典树，节点包含子字符映射及终止标记。"""
    trie: dict = {}
    for word in words:
        node = trie
        for ch in word:
            node = node.setdefault(ch, {})
        node[TERMINAL] = True
    return trie


def longest_prefix(text: str, trie: dict, max_len: int) -> int:
    """计算单个文本在字典树下能被完全拆分理解的最长前缀长度。"""
    length = len(text)
    reach = bytearray(length + 1)
    reach[0] = 1
    last_reach = ans = 0

    for i in range(length + 1):
        if not reach[i]:
            if i - last_reach > max_len:  # 连续空隙超过最长单词，后续前缀必不可达
                break
            continue

        last_reach = ans = i
        node = trie
        for j in range(i, min(i + max_len, length)):
            ch = text[j]
            if ch not in node:
                break
            node = node[ch]
            if TERMINAL in node:
                reach[j + 1] = 1

    return ans


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())

    n = int(next(data))
    m = int(next(data))
    words = [next(data).decode() for _ in range(n)]
    texts = [next(data).decode() for _ in range(m)]

    trie = build_trie(words)
    max_len = max(len(w) for w in words) if words else 0
    ans = [longest_prefix(text, trie, max_len) for text in texts]

    print("\n".join(map(str, ans)))


if __name__ == "__main__":
    solve()
