#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:38
# update_at: 2026-09-29 20:38

# 题面给的三种后缀，按题面顺序排列；删除后单词长度不为 0，所以单词不会就是后缀本身
SUFFIXES = ("er", "ly", "ing")


def solve() -> None:
    """读入一个单词，命中 er / ly / ing 后缀就删掉，否则原样输出。"""
    word = input().strip()
    # 三个后缀的末尾两字符分别是 er / ly / ng，互不相同，因此最多命中一个，顺序无关
    suffix = next((tail for tail in SUFFIXES if word.endswith(tail)), "")
    print(word.removesuffix(suffix))  # 后缀为空串时 removesuffix 原样返回，省掉 if-else


if __name__ == "__main__":
    solve()
