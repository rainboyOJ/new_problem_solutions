#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys


def has_prefix_relation(words: list[str]) -> bool:
    """判断给定单词集合中是否存在某一个串是另一个串的前缀。"""
    sorted_words = sorted(words)
    return any(
        curr.startswith(prev)
        for prev, curr in zip(sorted_words, sorted_words[1:])
    )


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return

    case_idx = 1
    current_words: list[str] = []

    for token in tokens:
        if token == '9':
            is_decodable = not has_prefix_relation(current_words)
            verdict = "immediately decodable" if is_decodable else "not immediately decodable"
            print(f"Set {case_idx} is {verdict}")
            case_idx += 1
            current_words.clear()
        else:
            current_words.append(token)


if __name__ == "__main__":
    solve()
