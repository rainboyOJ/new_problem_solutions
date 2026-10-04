#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:04
# update_at: 2026-10-02 09:04

import sys
from collections import deque


def count_lookups(capacity: int, words: list[int]) -> int:
    """FIFO 内存模拟：统计需要去外存查词典（未命中）的次数。

    deque 按进入顺序存词，集合 O(1) 判在不在；内存满时淘汰队首，
    即题面要求的"清空最早进入内存的那个单词"。
    """
    cache: deque[int] = deque()   # 进入内存的先后顺序
    present: set[int] = set()     # 配合 deque 做 O(1) 命中判断
    lookups = 0

    for word in words:
        if word in present:
            continue                                   # 内存里有，不查词典
        lookups += 1                                   # 没有，去外存查一次
        if capacity == 0:                              # M=0 时内存存不下任何词
            continue
        if len(cache) == capacity:                         # 内存满了
            oldest = cache.popleft()                       # 淘汰最早进入的词
            present.discard(oldest)
        cache.append(word)
        present.add(word)

    return lookups


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    capacity = next(data)  # M：内存单元数
    length = next(data)    # N：文章单词数
    words = [next(data) for _ in range(length)]

    print(count_lookups(capacity, words))


if __name__ == "__main__":
    solve()
