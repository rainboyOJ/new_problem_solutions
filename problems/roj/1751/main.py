#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 21:10
# update_at: 2026-10-07 21:10

import sys
from bisect import bisect_right

ALPHA = 26  # 字母表大小：字母编号 0..25 对应 a..z

type Runs = list[list[int]]  # 连续段列表：一段是 [起点, 字母编号]，按起点严格递增

# 段列表不记终点：第 i 段的终点是下一段的起点减一，最后一段延伸到 n。
# 用 [pos, ALPHA] 当二分键可以定位「起点 <= pos 的最后一段」（字母编号都 < ALPHA）。


def split_at(runs: Runs, pos: int) -> None:
    """让 pos 成为某一段的起点：pos 落在段内部时，从 pos 处补一段同字母的尾巴。"""
    i = bisect_right(runs, [pos, ALPHA]) - 1
    if runs[i][0] != pos:
        runs.insert(i + 1, [pos, runs[i][1]])


def sort_range(runs: Runs, n: int, l: int, r: int, ascending: int) -> None:
    """把 [l, r] 按升序 / 降序重排。

    区间内每个位置恰好属于一个字母，所以只要知道 26 个字母各有多少个，
    就能按顺序把它们的计数整段铺回；区间外的段完全不动。
    每次操作最多新建 26 段、删掉的段不会再回来，段数因此是均摊有界的。
    """
    split_at(runs, l)
    if r < n:
        split_at(runs, r + 1)  # 让 r+1 也成为段起点，区间内的段才连成整片
    a = bisect_right(runs, [l, ALPHA]) - 1  # 区间左端所在段的下标
    b = bisect_right(runs, [r, ALPHA]) - 1  # 区间右端所在段的下标

    cnt = [0] * ALPHA
    for i in range(a, b + 1):
        end = runs[i + 1][0] if i + 1 < len(runs) else n + 1
        cnt[runs[i][1]] += end - runs[i][0]

    order = range(ALPHA) if ascending else range(ALPHA - 1, -1, -1)
    pos = l
    fresh: Runs = []
    for c in order:  # 出现次数为 0 的字母不产生段
        if cnt[c]:
            fresh.append([pos, c])
            pos += cnt[c]

    # 首尾与区间外同字母的邻段相接时把邻居一起纳入替换范围，段数才不会虚增。
    # 左邻居的起点在 l 之前，必须把 fresh[0] 的起点往回拉，否则会丢掉它覆盖的那一截。
    left_same = a > 0 and runs[a - 1][1] == fresh[0][1]
    if left_same:
        fresh[0][0] = runs[a - 1][0]
    # 右邻居的终点由 fresh 之后那一段的起点给出，吸收进 fresh[-1] 即可
    right_same = b + 1 < len(runs) and runs[b + 1][1] == fresh[-1][1]
    runs[a - left_same : b + 1 + right_same] = fresh


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    n, m = int(next(tokens)), int(next(tokens))
    s = next(tokens).decode()
    # 初始串只保留「字母变化处」作为段起点，最多 n 段
    runs: Runs = [[i, ord(ch) - 97] for i, ch in enumerate(s, 1) if i == 1 or ch != s[i - 2]]

    for _ in range(m):
        l = int(next(tokens))
        r = int(next(tokens))
        x = int(next(tokens))
        sort_range(runs, n, l, r, x)

    parts = []
    for i in range(len(runs)):
        end = runs[i + 1][0] if i + 1 < len(runs) else n + 1
        parts.append(chr(97 + runs[i][1]) * (end - runs[i][0]))
    print("".join(parts))


if __name__ == "__main__":
    solve()
