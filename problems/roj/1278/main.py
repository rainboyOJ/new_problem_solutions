#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:12
# update_at: 2026-09-30 03:20

import sys


def people_needed(pages: list[int], limit: int) -> int:
    """每人上限 limit 页时，按"装不下才换人"连续切分，最少需要几个人。"""
    used = cuts = 0
    for page in pages:
        used += page
        if used > limit:  # 这本书装不下：刚装满的那一段算一个人，它另起一段
            cuts += 1
            used = page
    return cuts + bool(used)  # 末尾没装满的那段也要一个人；空书稿谁也不抄


def shortest_limit(pages: list[int], k: int) -> int:
    """二分出最短复制时间 C*：limit 越大所需人数越少，人数关于 limit 单调不增。"""
    lo = max(max(pages), -(-sum(pages) // k))  # 下界：容得下最厚的书，且不超过人均页数
    hi = sum(pages)                            # 上界：一个人全抄完
    while lo < hi:
        mid = (lo + hi) // 2
        if people_needed(pages, mid) <= k:     # mid 页够 k 个人抄完
            hi = mid
        else:
            lo = mid + 1
    return lo


def split_plan(pages: list[int], k: int, limit: int) -> list[tuple[int, int]]:
    """从后往前按 limit 页切分：每人尽量多抄，把少抄的机会留给前面的人。

    倒序贪心让第 k、k-1、… 个人依次"能吞多少吞多少"，于是第 1 个人剩下的最少；
    两个必须收尾的条件是：再吞这本书会超过 limit，或剩下的书不够前面的人各分一本。
    """
    plan: list[tuple[int, int]] = []
    person, used, end = k, 0, len(pages)  # end 是当前这个人已抄区间的右端（不含）
    for i in range(len(pages) - 1, -1, -1):
        if used + pages[i] > limit or i < person - 1:  # 超页数，或前面的人不够分
            plan.append((i + 2, end))                  # 收尾：0 下标区间 [i+1, end) 转 1 下标闭区间
            person -= 1
            used, end = 0, i + 1
        used += pages[i]
    plan.append((1, end))
    return plan[::-1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, k = next(data), next(data)
    pages = [next(data) for _ in range(m)]
    if m == 0:
        return
    print('\n'.join(f'{start} {end}' for start, end in split_plan(pages, k, shortest_limit(pages, k))))


if __name__ == "__main__":
    solve()
