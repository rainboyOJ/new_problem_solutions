#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 09:00
# update_at: 2026-10-09 12:35

import sys
from bisect import bisect_right


def half_sums(items: list[int], limit: int) -> list[int]:
    """枚举 items 的全部合法子集和（超过 limit 的分支就地剪掉），返回排序去重后的列表。"""
    sums = [0]
    for weight in items:
        sums += [s + weight for s in sums if s + weight <= limit]   # 拿 / 不拿，规模翻倍
    return sorted(set(sums))                                        # 排序 + 去重，供二分查表


def best_paired(items: list[int], table: list[int], limit: int) -> int:
    """枚举 items 的每种取法（和 S），在 table 里二分找 ≤ limit - S 的最大值，取总和最大者。"""
    best = 0
    stack = [(0, 0)]
    while stack:                                                    # 显式栈迭代，避免深递归
        idx, total = stack.pop()
        if idx == len(items):
            pos = bisect_right(table, limit - total)                # table 已排序且含 0
            if pos and total + table[pos - 1] > best:
                best = total + table[pos - 1]
            continue
        stack.append((idx + 1, total))                              # 不拿第 idx 件
        if total + items[idx] <= limit:
            stack.append((idx + 1, total + items[idx]))             # 拿第 idx 件
    return best


def solve() -> None:
    """读入 W、N 与 N 个重量，用折半搜索求一次能搬动的最大重量。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    limit = next(data, None)
    if limit is None:                                               # 无输入：静默退出
        return
    n = next(data, None)
    if n is None:                                                   # 只有 W 没有 N：同样静默退出
        return
    # 礼物不足 N 件时补 0（题面规定 G_i ≥ 1，补 0 不影响答案），避免 StopIteration
    raw = [next(data, 0) for _ in range(n)]
    usable = sorted((g for g in raw if g <= limit), reverse=True)   # 超重礼物剔除；降序先搜大件
    if not usable:                                                  # 全部超重（或 N = 0）
        print(0)
        return

    half = len(usable) // 2
    table = half_sums(usable[:half], limit)
    print(best_paired(usable[half:], table, limit))


if __name__ == '__main__':
    solve()
