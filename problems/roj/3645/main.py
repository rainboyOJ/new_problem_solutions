#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:32
# update_at: 2026-10-02 12:32

import sys

pow10 = [1] * 8  # pow10[k] = 10**k，用来按长度截取编码的末 k 位


def build_pow10() -> None:
    """预处理 10 的幂：需求码长度 ≤ 7，取末 k 位只需要这张小表。"""
    for k in range(1, 8):
        pow10[k] = pow10[k - 1] * 10


def best_suffix_match(codes: list[int], queries: list[tuple[int, int]]) -> list[int]:
    """对每个询问 (长度 k, 需求码 need) 返回以 need 结尾的最小图书编码，不存在为 -1。

    编码按从小到大排好后从左往右扫，命中的第一个后缀就是最小答案，
    于是每个询问只需在有序编码里做一次顺序查找，O(n) 回答。
    """
    return [
        next((code for code in codes if code % pow10[k] == need), -1)  # 首个匹配即最小
        for k, need in queries
    ]


def solve() -> None:
    build_pow10()
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, q = next(data), next(data)
    codes = sorted(next(data) for _ in range(n))  # 排序让「首个命中 = 最小答案」成立
    queries = [(next(data), next(data)) for _ in range(q)]
    print('\n'.join(map(str, best_suffix_match(codes, queries))))


if __name__ == "__main__":
    solve()
