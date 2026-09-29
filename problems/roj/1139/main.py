#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:37
# update_at: 2026-09-29 20:37

import sys


def normalize(word: str) -> str:
    """首字符若为字母则大写，其余字符一律小写；数字和 - 原样保留。"""
    return word[:1].upper() + word[1:].lower()


def solve() -> None:
    data = sys.stdin.read().split()
    n = int(data[0])               # 第一行是药名个数，n 不超过 100

    # 每个药名长度不超过 20，逐个规范化后按行输出
    print('\n'.join(normalize(word) for word in data[1:n + 1]))


if __name__ == "__main__":
    solve()
