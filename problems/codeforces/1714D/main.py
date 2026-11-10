#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-09 17:35
# update_at: 2026-11-10 10:25

import sys
from collections.abc import Iterator

# 匹配区间：(左端点 l, 右端点 r, 单词序号 w, 1 起起始位置 p)，半开区间 [l, r)
type Match = tuple[int, int, int, int]
type Plan = list[tuple[int, int]]


def occurrences(t: str, s: str) -> Iterator[int]:
    """产出子串 s 在 t 中的所有起始位置（允许重叠）。"""
    p = t.find(s)
    while p != -1:
        yield p
        p = t.find(s, p + 1)


def min_color(t: str, words: list[str]) -> Plan | None:
    """计算将 t 涂红的最少区间方案；若无法涂满返回 None。"""
    matches: list[Match] = [
        (p, p + len(s), w, p + 1)
        for w, s in enumerate(words, 1)
        for p in occurrences(t, s)
    ]

    cur, plan = 0, []
    while cur < len(t):
        valid = [(r, w, p) for l, r, w, p in matches if l <= cur < r]
        if not valid:
            return None
        r, w, p = max(valid)  # 贪心选择右开端点 r 最大的区间
        plan.append((w, p))
        cur = r

    return plan


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    q = int(next(data))

    for _ in range(q):
        t = next(data).decode()
        n = int(next(data))
        words = [next(data).decode() for _ in range(n)]

        plan = min_color(t, words)
        if plan is None:
            out.append("-1")
        else:
            out.append(str(len(plan)))
            out.extend(f"{w} {p}" for w, p in plan)

    print("\n".join(out))


if __name__ == "__main__":
    solve()
