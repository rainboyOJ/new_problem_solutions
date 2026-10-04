#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:48
# update_at: 2026-09-30 18:48

import bisect
import math
import sys


def add_val(blocks: list[list[int]], block_size: int, val: int) -> None:
    """在分块有序结构中插入元素 val。"""
    for b in blocks:
        if not b or val <= b[-1]:
            bisect.insort(b, val)
            if len(b) > 2 * block_size:
                rebuild(blocks, block_size)
            return
    if not blocks:
        blocks.append([val])
    else:
        bisect.insort(blocks[-1], val)
        if len(blocks[-1]) > 2 * block_size:
            rebuild(blocks, block_size)


def remove_val(blocks: list[list[int]], block_size: int, val: int) -> None:
    """在分块有序结构中删除一个 val。"""
    for b in blocks:
        if b and val <= b[-1]:
            idx = bisect.bisect_left(b, val)
            if idx < len(b) and b[idx] == val:
                b.pop(idx)
                return


def query_rank(blocks: list[list[int]], val: int) -> int:
    """查询 val 的排名（严格小于 val 的元素个数 + 1）。"""
    smaller = 0
    for b in blocks:
        if not b:
            continue
        if b[-1] < val:
            smaller += len(b)
        else:
            smaller += bisect.bisect_left(b, val)
            break
    return smaller + 1


def query_kth(blocks: list[list[int]], k: int) -> int:
    """查询排名为 k（即第 k 小，1-indexed）的数。"""
    cur = k
    for b in blocks:
        if cur <= len(b):
            return b[cur - 1]
        cur -= len(b)
    return -1


def query_prev(blocks: list[list[int]], val: int) -> int:
    """求小于 val 且最大的数（前趋）。"""
    ans = -float('inf')
    for b in blocks:
        if not b or b[0] >= val:
            break
        if b[-1] < val:
            ans = b[-1]
        else:
            idx = bisect.bisect_left(b, val)
            if idx > 0:
                ans = b[idx - 1]
            break
    return int(ans)


def query_next(blocks: list[list[int]], val: int) -> int:
    """求大于 val 且最小的数（后继）。"""
    for b in blocks:
        if not b or b[-1] <= val:
            continue
        idx = bisect.bisect_right(b, val)
        if idx < len(b):
            return b[idx]
    return -1


def rebuild(blocks: list[list[int]], block_size: int) -> None:
    """重构分块以维持块大小均匀。"""
    flattened: list[int] = [x for b in blocks for x in b]
    blocks.clear()
    for i in range(0, len(flattened), block_size):
        blocks.append(flattened[i:i + block_size])


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:
        return

    block_size = max(100, int(math.isqrt(n) * 2))
    blocks: list[list[int]] = []
    out: list[int] = []

    for _ in range(n):
        opt = next(data)
        x = next(data)
        if opt == 1:
            add_val(blocks, block_size, x)
        elif opt == 2:
            remove_val(blocks, block_size, x)
        elif opt == 3:
            out.append(query_rank(blocks, x))
        elif opt == 4:
            out.append(query_kth(blocks, x))
        elif opt == 5:
            out.append(query_prev(blocks, x))
        elif opt == 6:
            out.append(query_next(blocks, x))

    sys.stdout.write('\n'.join(map(str, out)) + '\n')


if __name__ == '__main__':
    solve()
