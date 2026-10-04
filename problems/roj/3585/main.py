#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:15
# update_at: 2026-10-02 09:15

import re
import sys
from collections.abc import Iterator


def find_hits(article: str, word: str) -> Iterator[int]:
    """产出 word 作为独立单词在 article 中每次匹配的起始下标（不区分大小写）。

    文章只含字母和空格，所以单词边界等价于"前后不是小写字母"；
    两侧的环视让整串匹配只需一次线性扫描，不产生重叠假匹配。
    """
    pattern = re.compile(rf'(?<![a-z]){re.escape(word)}(?![a-z])')
    return (m.start() for m in pattern.finditer(article))


def solve() -> None:
    data = iter(sys.stdin.read().splitlines())  # 文章里的空格是单词边界，必须按行保留
    word = next(data).strip().lower()
    article = next(data).lower()

    hits = list(find_hits(article, word))
    if hits:
        print(len(hits), hits[0])  # 出现次数 + 首次位置（首字母下标，从 0 计）
    else:
        print(-1)


if __name__ == "__main__":
    solve()
