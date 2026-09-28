#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-28 16:40
# update_at: 2026-09-28 16:40

import sys
from collections import defaultdict
from collections.abc import Iterator

ANY = 0  # 生产者编码：0 = 至少两个人可以接（第 0 轮的值 1 也记成它）


def reachable_values(seq: list[int], person: int, k: int, prev: dict[int, int]) -> Iterator[int]:
    """依次产出本轮这个人能收尾的值（同一个值的多次出现会重复产出）。

    合法起点 pos 覆盖结尾位置 [pos+1, pos+k-1]。起点从左往右扫，pos+k-1 单调递增，
    所以"覆盖到哪"只需一个 deadline，不必记录整段区间。
    """
    deadline = 0
    for pos, value in enumerate(seq, 1):
        covered = pos <= deadline                      # 更早的合法起点已经覆盖到 pos
        if covered:
            yield value
        can_start = prev.get(value, person) != person  # 上一轮到过 value，且不是只有自己
        if can_start:
            deadline = pos + k - 1                     # 从 pos 出发能延伸到的最右位置


def advance(prev: dict[int, int], seqs: list[list[int]], k: int) -> dict[int, int]:
    """由第 r-1 轮可达状态推出第 r 轮状态：合并所有人的可达值。"""
    nxt: dict[int, int] = {}
    for person, seq in enumerate(seqs, 1):
        for value in reachable_values(seq, person, k, prev):
            # 登记生产者：本轮首次出现 value、或唯一生产者还是自己 → person，否则 ANY
            nxt[value] = person if nxt.setdefault(value, person) == person else ANY
    return nxt


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, k, q = next(data), next(data), next(data)

        seqs: list[list[int]] = []
        for _ in range(n):
            length = next(data)  # 题面的 l_i
            seqs.append([next(data) for _ in range(length)])

        # 询问按轮数分桶，桶里存 (原始下标, 结尾值)，这样结果能按输入顺序输出。
        by_round = defaultdict(list)
        for i in range(q):
            r, c = next(data), next(data)
            by_round[r].append((i, c))

        ans = [0] * q
        prev: dict[int, int] = {1: ANY}  # 第 0 轮只有值 1，且没有上一轮的接龙人
        max_round = max(by_round)        # max(dict) 迭代的是 key，最大 key 就是最大轮数
        for rnd in range(1, max_round + 1):
            prev = advance(prev, seqs, k)
            for i, c in by_round[rnd]:
                ans[i] = 1 if c in prev else 0
            if not prev:  # 这一轮一个值都到不了，后面永远都到不了
                break

        out += map(str, ans)

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
