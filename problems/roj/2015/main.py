#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys


def build_bisquare_table(max_m: int) -> tuple[bytearray, list[int]]:
    """生成双平方数布尔查找表与有序升序列表。"""
    max_val = 2 * max_m * max_m
    is_bisquare = bytearray(max_val + 1)
    for p in range(max_m + 1):
        p2 = p * p
        for q in range(p, max_m + 1):
            is_bisquare[p2 + q * q] = 1
    # 列表推导提取有序双平方数
    bisquares = [val for val, exists in enumerate(is_bisquare) if exists]
    return is_bisquare, bisquares


def find_arithmetic_progressions(
    n: int, max_m: int, is_bisquare: bytearray, bisquares: list[int]
) -> list[tuple[int, int]]:
    """搜索所有长度为 n 的双平方数等差数列 (a, b)。"""
    max_val = 2 * max_m * max_m
    results: list[tuple[int, int]] = []
    total = len(bisquares)

    for i in range(total):
        first = bisquares[i]
        diff_limit = (max_val - first) // (n - 1)
        for j in range(i + 1, total):
            diff = bisquares[j] - first
            if diff > diff_limit:
                break
            # 先剪枝末项，再倒序检查中间项
            last = first + (n - 1) * diff
            if not is_bisquare[last]:
                continue
            is_valid = True
            for step in range(n - 2, 1, -1):
                if not is_bisquare[first + step * diff]:
                    is_valid = False
                    break
            if is_valid:
                results.append((diff, first))

    results.sort()
    return [(first, diff) for diff, first in results]


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    seq_len, max_coord = int(tokens[0]), int(tokens[1])

    is_bisquare, bisquares = build_bisquare_table(max_coord)
    ans = find_arithmetic_progressions(seq_len, max_coord, is_bisquare, bisquares)

    if not ans:
        print("NONE")
    else:
        print("\n".join(f"{first} {diff}" for first, diff in ans))


if __name__ == "__main__":
    solve()
