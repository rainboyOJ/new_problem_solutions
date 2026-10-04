#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 09:00
# update_at: 2026-09-30 09:00

import sys


def replace_words(text: str, target: str, replacement: str) -> str:
    """将文本中与 target 匹配的独立单词替换为 replacement。"""
    words = text.split()
    return " ".join(replacement if word == target else word for word in words)


def solve() -> None:
    lines = sys.stdin.read().splitlines()
    if not lines:
        return
    text = lines[0]
    target = lines[1]
    replacement = lines[2]
    print(replace_words(text, target, replacement))


if __name__ == "__main__":
    solve()
