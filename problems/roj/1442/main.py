#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 10:52
# update_at: 2026-09-30 10:52

import sys


def can_build(pieces: list[int], length: int, used: list[bool], idx: int, rest: int) -> bool:
    """用剩下的碎片把长度 length 的原木棍一根根拼出来，能不能成功。

    pieces 已按从大到小排序；idx 是这一层允许使用的最小下标（靠它避免同一种
    拼法被排列组合重复搜索），rest 是手上这根还差的长度。
    """
    if rest == 0:                      # 这根拼满了，去开下一根
        if not any(not u for u in used):  # 碎片全部用完，说明每根都恰好拼满
            return True
        idx, rest = 0, length
    if idx >= len(pieces):             # 碎片用完这根却没拼满，此分配不可行
        return False
    prev = 0                           # 同一层里试过的长度，等长的碎片只试第一次
    for i in range(idx, len(pieces)):
        cur = pieces[i]
        if used[i] or cur == prev or cur > rest:
            continue
        prev = cur
        used[i] = True
        nxt = rest - cur               # 0 表示这根刚好拼满，下一层会重开一根
        if can_build(pieces, length, used, 0 if nxt == 0 else i + 1, 0 if nxt == 0 else nxt):
            return True
        used[i] = False
        if rest == length or cur == rest:  # 首块 / 恰好填满却失败 ⇒ 该 length 一定无解
            return False
    return False


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    pieces = sorted((next(data) for _ in range(n)), reverse=True)
    total = sum(pieces)

    for length in range(pieces[0], total + 1):
        if total % length:             # 原木棍长度必须是总长的约数
            continue
        if can_build(pieces, length, [False] * n, 0, length):
            print(length)
            return


if __name__ == "__main__":
    solve()
