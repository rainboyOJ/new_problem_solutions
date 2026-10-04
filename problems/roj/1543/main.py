#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:25
# update_at: 2026-09-30 17:25

import bisect
import sys


def build_st_table(arr: list[int]) -> tuple[list[int], list[list[int]]]:
    """构建区间最大值 ST 表，返回 (log2 预处理表, ST 倍增二维表)。"""
    n = len(arr)
    log_table = [0] * (n + 1)
    for i in range(2, n + 1):
        log_table[i] = log_table[i >> 1] + 1

    st: list[list[int]] = [arr[:]]
    k = log_table[n]
    for j in range(1, k + 1):
        prev = st[j - 1]
        half = 1 << (j - 1)
        st.append([
            max(prev[i], prev[i + half])
            for i in range(n - (1 << j) + 1)
        ])
    return log_table, st


def range_max(st: list[list[int]], log_table: list[int], left: int, right: int) -> int:
    """查询区间 [left, right] 上的最大值。"""
    k = log_table[right - left + 1]
    return max(st[k][left], st[k][right - (1 << k) + 1])


def answer_query(
    left: int,
    right: int,
    start: list[int],
    st: list[list[int]],
    log_table: list[int],
) -> int:
    """计算区间 [left, right] 内最长完美序列长度。"""
    if left > right:
        left, right = right, left

    # 二分找到第一个 start[i] >= left 的位置 mid
    mid = bisect.bisect_left(start, left, left, right + 1)
    left_part = mid - left  # 左半段以 left 为起点的最大长度为 mid - left
    right_part = range_max(st, log_table, mid, right) if mid <= right else 0
    return max(left_part, right_part)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)
    a = [next(data) for _ in range(n)]

    # 预处理每个位置 i 作为右端点时，最左能延伸到的无重复起点 start[i]
    start = [0] * n
    last_pos: dict[int, int] = {}
    for i, val in enumerate(a):
        prev_pos = last_pos.get(val, -1) + 1
        start[i] = max(start[i - 1] if i > 0 else 0, prev_pos)
        last_pos[val] = i

    f = [i - start[i] + 1 for i in range(n)]
    log_table, st = build_st_table(f)

    ans: list[int] = []
    for _ in range(m):
        l = next(data)
        r = next(data)
        ans.append(answer_query(l, r, start, st, log_table))

    sys.stdout.write("\n".join(map(str, ans)) + "\n")


if __name__ == "__main__":
    solve()
