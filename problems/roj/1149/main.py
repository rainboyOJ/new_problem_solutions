#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:50
# update_at: 2026-09-29 20:50

import sys


def longest_word(sentence: str) -> str:
    """取最长单词：max 只在新元素严格更长时才替换，天然保留并列时最先出现的那个。"""
    words = sentence.split()          # 单空格分隔，split() 顺带吞掉两端空白
    return max(words, key=len)        # 比较键只有长度，首个最长单词胜出


def solve() -> None:
    sentence = sys.stdin.read().strip().removesuffix('.')  # 句末 '.' 是标点不是单词
    print(longest_word(sentence))


if __name__ == "__main__":
    solve()
