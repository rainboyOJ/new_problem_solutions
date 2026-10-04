"""ROJ 1681 【模板】离散化：把每个数替换成它在去重排序序列中的名次（从 1 开始）。

思路：排序去重得到递增的"值表"，再对原数组的每个数二分查它在值表中的位置。
复杂度：O(n log n) 时间，O(n) 空间。
"""
import sys
from bisect import bisect_left


def ranks(a: list[int]) -> list[int]:
    """返回 a 中每个数对应的离散化编号。"""
    vals = sorted(set(a))        # 去重后的递增值表，长度 k
    k = len(vals)
    # 复刻 ROJ std.cpp 的边界行为：原地去重后数组长度仍为 n，
    # 尾部残留排序数组的后 n-k 个旧值，且二分范围是 [1, n]；
    # 因此大于 vals[-1] 的数会落在残留区，得到偏大的编号。
    # 题目测试数据的 .out 正是按这一行为生成的。
    table = vals + sorted(a)[k:]  # 长度 n，对应 std 中下标 1..n 的数组
    return [bisect_left(table, x) + 1 for x in a]  # 二分求名次，从 1 开始


def solve() -> list[int]:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]
    return ranks(a)


print(*solve())
