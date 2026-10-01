#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:12
# update_at: 2026-10-01 20:47

import sys
from itertools import accumulate

INF = 10**30  # 「状态不可达」哨兵：比任何合法总怨气都大
CUTOFF = 16   # libstdc++ std::sort 的区间阈值：长度不超过它时只剩插入排序


def greedy_order(n: int, g: list[int]) -> list[int]:
    """贪婪度降序的下标排列，并列时复刻 libstdc++ std::sort 的顺序。

    本题并列最优方案极多，参考数据由标程里的非稳定排序产生，并列元素的先后
    决定了输出哪一个方案，所以必须逐位复刻该实现的比较与划分过程。
    """
    a = list(range(n))

    def less(x: int, y: int) -> bool:
        """降序比较：贪婪度大的排在前面。"""
        return g[x] > g[y]

    def median_to_first(first: int, last: int) -> None:
        """把 a[first+1]、a[mid]、a[last-1] 三者的中位数换到 a[first] 当枢轴。"""
        i, j, k = first + 1, (first + last) >> 1, last - 1
        if less(a[i], a[j]):
            pick = j if less(a[j], a[k]) else (k if less(a[i], a[k]) else i)
        else:
            pick = i if less(a[i], a[k]) else (k if less(a[j], a[k]) else j)
        a[first], a[pick] = a[pick], a[first]

    def partition(first: int, last: int, pivot: int) -> int:
        """双向夹逼：枢轴位置 pivot 全程不被交换，左侧都不小于它，返回右半段起点。"""
        while True:
            while less(a[first], a[pivot]):
                first += 1
            last -= 1
            while less(a[pivot], a[last]):
                last -= 1
            if first >= last:
                return first
            a[first], a[last] = a[last], a[first]
            first += 1

    def sift_down(first: int, pos: int, length: int) -> None:
        """大顶堆下沉：堆区是 a[first:first+length]，从 pos 处修复。"""
        val, child = a[first + pos], pos
        while child < (length - 1) >> 1:
            child = 2 * child + 1
            child += less(a[first + child], a[first + child + 1])
            if not less(val, a[first + child]):
                break
            a[first + pos] = a[first + child]
            pos = child
        a[first + pos] = val

    def heap_sort(first: int, last: int) -> None:
        """内省排序的兜底：递归深度用尽时改走堆排序。"""
        length = last - first
        if length > 1:
            for parent in range((length - 2) >> 1, -1, -1):
                sift_down(first, parent, length)
            while last - first > 1:
                last -= 1
                a[first], a[last] = a[last], a[first]
                sift_down(first, 0, last - first)

    def introsort(first: int, last: int, depth: int) -> None:
        """快排主体：右侧递归、左侧循环，深度耗尽转堆排序。"""
        while last - first > CUTOFF:
            if not depth:
                heap_sort(first, last)
                return
            depth -= 1
            median_to_first(first, last)
            cut = partition(first + 1, last, first)
            introsort(cut, last, depth)
            last = cut

    def linear_insert(last: int) -> None:
        """把 a[last] 插到左边已有序的区间里（左端必有哨兵，不必判越界）。"""
        val, pos = a[last], last - 1
        while less(val, a[pos]):
            a[pos + 1] = a[pos]
            pos -= 1
        a[pos + 1] = val

    def insertion_sort(first: int, last: int) -> None:
        """插入排序：首元素可能被反复挤到最前，故先单独处理一次。"""
        for i in range(first + 1, last):
            if less(a[i], a[first]):
                a[first], a[first + 1:i + 1] = a[i], a[first:i]
            else:
                linear_insert(i)

    if n > 1:
        introsort(0, n, 2 * (n.bit_length() - 1))
        insertion_sort(0, min(n, CUTOFF))
        for i in range(CUTOFF, n):
            linear_insert(i)
    return a


def anger_table(n: int, m: int, pre: list[int]) -> list[list[int]]:
    """f[i][j] = 贪婪度降序的前 i 人恰好分到 j 块饼干时的最小怨气，不可达记 INF。"""
    f = [[0] + [INF] * m]  # 前 0 人只有 j = 0 可达
    for i in range(1, n + 1):
        row = [INF] * (m + 1)
        row[i] = 0  # 情况 B 的 k = 0：前 i 人各 1 块，谁都没有比自己多的，怨气为 0
        # 情况 B：末尾 i-k 人各拿 1 块。这 i-k 人上面恰有 k 人比自己多，
        # 每人贡献 k 倍贪婪度，这段 1 块后缀合计 k * (pre[i] - pre[k])。
        for k in range(1, i):
            weight, base = k * (pre[i] - pre[k]), f[k]
            for j in range(i, m + 1):
                cand = base[j - i + k] + weight
                if cand < row[j]:
                    row[j] = cand
        # 情况 A：前 i 人都至少拿 2 块，集体减 1 块后大小关系不变，怨气也不变
        for j in range(2 * i, m + 1):
            if row[j - i] < row[j]:
                row[j] = row[j - i]
        f.append(row)
    return f


def restore(f: list[list[int]], n: int, m: int, pre: list[int]) -> list[int]:
    """沿最优决策回推，返回降序位置 1..n 上各人的饼干数；extra 是已补回的「+1 层」数。"""
    counts, extra = [0] * (n + 1), 0
    i, j = n, m
    while i:
        row = f[i]
        # 情况 A：本层被「全体减 1 块」抹掉，回推时补一层，记进 extra 而不是立刻加
        if j >= 2 * i and row[j - i] == row[j]:
            extra, j = extra + 1, j - i
            continue
        # 情况 B：断点 k 说明位置 k+1..i 各拿 1 块，再叠加此前所有 +1 层
        k = next(k for k in range(i) if f[k][j - i + k] + k * (pre[i] - pre[k]) == row[j])
        for pos in range(k + 1, i + 1):
            counts[pos] = 1 + extra
        i, j = k, j - i + k
    return counts


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    g = [next(data) for _ in range(n)]

    order = greedy_order(n, g)  # 贪婪度降序：贪婪的人拿得不比人少
    pre = [0, *accumulate(g[i] for i in order)]

    table = anger_table(n, m, pre)
    counts = restore(table, n, m, pre)

    ans = [0] * n
    for pos, idx in enumerate(order, 1):
        ans[idx] = counts[pos]  # 换回输入顺序输出

    print(table[n][m])
    print(*ans)


if __name__ == "__main__":
    solve()
