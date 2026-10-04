#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:10
# update_at: 2026-09-30 05:10

import sys

THRESHOLD = 16  # 插入排序阈值：段长 ≤16 直接插入排序（libstdc++ 的 _S_threshold）


def lt(x: tuple[int, int], y: tuple[int, int]) -> bool:
    """比较两条记录：只比接水时间；编号只是输出标签，不参与比较。"""
    return x[0] < y[0]


def move_median_to_first(a: list[tuple[int, int]], res: int, i: int, j: int, k: int) -> None:
    """三数取中：把 a[i]、a[j]、a[k] 的中位数换到 res 位置（快速排序选基准）。"""
    if lt(a[i], a[j]):
        if lt(a[j], a[k]):
            a[res], a[j] = a[j], a[res]
        elif lt(a[i], a[k]):
            a[res], a[k] = a[k], a[res]
        else:
            a[res], a[i] = a[i], a[res]
    elif lt(a[i], a[k]):
        a[res], a[i] = a[i], a[res]
    elif lt(a[j], a[k]):
        a[res], a[k] = a[k], a[res]
    else:
        a[res], a[j] = a[j], a[res]


def unguarded_partition(a: list[tuple[int, int]], first: int, last: int, pivot: int) -> int:
    """Hoare 划分：小于基准的挪到左边、大于等于的挪到右边，返回分界点。"""
    while True:
        while lt(a[first], a[pivot]):   # 左指针停在第一个 ≥ 基准处
            first += 1
        last -= 1
        while lt(a[pivot], a[last]):    # 右指针停在第一个 ≤ 基准处
            last -= 1
        if first >= last:
            return first
        a[first], a[last] = a[last], a[first]
        first += 1


def partition_pivot(a: list[tuple[int, int]], first: int, last: int) -> int:
    """三分取中选基准（基准换到段首），再对 [first+1, last) 划分，返回分界点。"""
    mid = first + (last - first) // 2
    move_median_to_first(a, first, first + 1, mid, last - 1)
    return unguarded_partition(a, first + 1, last, first)


def push_heap(a: list[tuple[int, int]], base: int, hole: int, top: int, value: tuple[int, int]) -> None:
    """大顶堆上插：value 从洞 hole 沿父链上浮到合适位置。"""
    parent = (hole - 1) // 2 if hole else 0  # C++ 中 (-1)/2 截断为 0，Python 需手动对齐
    while hole > top and lt(a[base + parent], value):
        a[base + hole] = a[base + parent]
        hole = parent
        parent = (hole - 1) // 2 if hole else 0
    a[base + hole] = value


def adjust_heap(a: list[tuple[int, int]], base: int, hole: int, length: int, value: tuple[int, int]) -> None:
    """大顶堆下沉：value 从洞 hole 逐层下沉，最后经上浮收尾。"""
    top = hole
    child = hole
    while child < (length - 1) // 2:
        child = 2 * (child + 1)
        if lt(a[base + child], a[base + child - 1]):  # 两个孩子里较小的先上位
            child -= 1
        a[base + hole] = a[base + child]
        hole = child
    if length % 2 == 0 and child == (length - 2) // 2:  # 偶数长时右孩子是最后一个
        child = 2 * (child + 1)
        a[base + hole] = a[base + child - 1]
        hole = child - 1
    push_heap(a, base, hole, top, value)


def heapsort(a: list[tuple[int, int]], first: int, last: int) -> None:
    """划分深度耗尽时的兜底：整段堆排序，保证最坏 O(n log n)。"""
    length = last - first
    if length < 2:
        return
    parent = (length - 2) // 2
    while True:                                   # 自底向上建大顶堆
        value = a[first + parent]
        adjust_heap(a, first, parent, length, value)
        if parent == 0:
            break
        parent -= 1
    end = last
    while end - first > 1:                        # 堆顶（最大值）依次换到段尾
        end -= 1
        value = a[end]
        a[end] = a[first]
        adjust_heap(a, first, 0, end - first, value)


def introsort_loop(a: list[tuple[int, int]], first: int, last: int, depth: int) -> None:
    """introsort 主循环：段长超过阈值就划分；深度耗尽改走堆排序。"""
    while last - first > THRESHOLD:
        if depth == 0:
            heapsort(a, first, last)
            return
        depth -= 1
        cut = partition_pivot(a, first, last)
        introsort_loop(a, cut, last, depth)  # 右半段递归
        last = cut                           # 左半段转成循环，避免深递归


def unguarded_linear_insert(a: list[tuple[int, int]], i: int) -> None:
    """把 a[i] 插入左侧已排序前缀（段首 ≤ a[i]，正常不会越过下标 0）。"""
    value = a[i]
    j = i - 1
    while j >= 0 and lt(value, a[j]):  # j >= 0 只是防 Python 负下标回绕的兜底
        a[i] = a[j]
        i, j = j, j - 1
    a[i] = value


def insertion_sort(a: list[tuple[int, int]], first: int, last: int) -> None:
    """插入排序：introsort 对小段的收尾方式。"""
    if first == last:
        return
    for i in range(first + 1, last):
        if lt(a[i], a[first]):
            value = a[i]                          # 比段首还小：整段右移一格，插到最前
            for j in range(i, first, -1):
                a[j] = a[j - 1]
            a[first] = value
        else:
            unguarded_linear_insert(a, i)


def final_insertion_sort(a: list[tuple[int, int]], first: int, last: int) -> None:
    """introsort 收尾：前 16 个用带边界保护的插入排序，其余用无保护版本。"""
    if last - first > THRESHOLD:
        insertion_sort(a, first, first + THRESHOLD)
        for i in range(first + THRESHOLD, last):
            unguarded_linear_insert(a, i)
    else:
        insertion_sort(a, first, last)


def std_sort(a: list[tuple[int, int]]) -> None:
    """按 C++ std::sort（libstdc++ introsort）的步骤排序，并列时间的顺序与参考输出一致。"""
    if a:
        n = len(a)
        introsort_loop(a, 0, n, 2 * (n.bit_length() - 1))  # 深度上限 = 2*floor(log2 n)
        final_insertion_sort(a, 0, n)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 参考程序的接水时间数组是全局的：读不满 n 个时缺项为 0
    times = [next(data, 0) for _ in range(n)]
    order = [(t, i) for i, t in enumerate(times, 1)]

    std_sort(order)  # 贪心：接水时间短的排前面，平均等待时间最小

    # 第 pos 位要等前面所有人接完：总等待 = Σ (n-1-pos) * t，平均 = 总等待 / n
    total = sum(t * (n - 1 - pos) for pos, (t, _) in enumerate(order))
    ids = ' '.join(str(i) for _, i in order)
    print(f'{ids}\n{total / n:.2f}')


if __name__ == "__main__":
    solve()
