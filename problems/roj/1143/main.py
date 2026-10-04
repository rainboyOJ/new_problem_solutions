#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:40
# update_at: 2026-09-29 20:40

import re
import sys


def solve() -> None:
    # 题面是一整行句子，词与词之间靠空格和逗号分隔：必须原样保留这些分隔符
    # 才能用正则按"非字母"切词，所以整篇读入，而不是按空白 token 顺序消费。
    text = sys.stdin.read()
    words: list[str] = re.findall(r"[A-Za-z]+", text)
    print(max(words, key=len))
    print(min(words, key=len))


if __name__ == "__main__":
    solve()
