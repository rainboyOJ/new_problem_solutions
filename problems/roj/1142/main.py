#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 20:15
# update_at: 2026-10-02 20:15

import sys


def solve() -> None:
    # str.split() 不带参数：按任意连续空白切分，天然忽略首尾与词间的多余空格；
    # 切出来的每个片段就是"没有被空格隔开的符号串"，也就是题目定义的单词。
    words = sys.stdin.read().split()
    print(','.join(map(str, map(len, words))))


if __name__ == "__main__":
    solve()
