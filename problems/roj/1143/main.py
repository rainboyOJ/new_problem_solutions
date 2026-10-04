#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:40
# update_at: 2026-09-29 20:40

import re
import sys


def solve() -> None:
    line = sys.stdin.readline()
    words: list[str] = re.findall(r"[A-Za-z]+", line)
    print(max(words, key=len))
    print(min(words, key=len))


if __name__ == "__main__":
    solve()
