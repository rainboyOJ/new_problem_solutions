#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
from collections import OrderedDict


def solve() -> None:
    """模拟 FIFO 缓存：内存未命中则查词典一次，并淘汰最早进入的单词。"""
    data = sys.stdin.read().split()
    m, n = int(data[0]), int(data[1])
    words = map(int, data[2:2 + n])

    cache: OrderedDict[int, None] = OrderedDict()  # 按进入内存的顺序存放单词
    lookups = 0                                     # 查外存词典的次数
    for w in words:
        if w in cache:                              # 内存命中，直接翻译
            continue
        lookups += 1                                # 未命中：查一次外存词典
        if len(cache) == m:                         # 内存已满，淘汰最早进入的
            cache.popitem(last=False)
        cache[w] = None                             # 新单词进入内存（队尾）
    print(lookups)


if __name__ == "__main__":
    solve()
