#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 01:34
# update_at: 2026-10-08 01:34

import sys
from itertools import accumulate

type MinTree = list[int]                 # 区间最小值线段树的结点数组，叶子数是 2 的幂
type Chain = list[tuple[int, int, int]]  # 待回溯的状态链：(状态编码, 本段交错和, 本段长度)
type Memo = dict[int, int]               # 状态编码 u*(2N)+v -> 从该状态起、首项取 + 的交错和

BIG = 1 << 62  # 哨兵：比任何 A_i 都大，表示"该区间里没有小于阈值的元素"


def build_min_tree(values: list[int]) -> tuple[MinTree, int]:
    """区间最小值线段树；返回（结点数组, 叶子数），叶子数取 >= len(values) 的最小 2 的幂。"""
    size = 1
    while size < len(values):
        size <<= 1
    tree = [BIG] * (2 * size)
    tree[size:size + len(values)] = values
    for node in range(size - 1, 0, -1):
        left = tree[node + node]
        right = tree[node + node + 1]
        tree[node] = left if left < right else right
    return tree, size


def first_below(tree: MinTree, size: int, start: int, t: int) -> int | None:
    """最小的下标 i >= start 使 A2[i] < t；不存在返回 None（调用方用对面指针兜底）。

    先沿"根 -> 叶子 start"的路径收集被跳过的右儿子，再自近及远检查；
    命中后在该子树里一路向左下降，第一个满足的叶子就是答案。
    """
    node, nl, nr = 1, 0, size - 1
    rights: list[int] = []
    while nl < nr:
        mid = (nl + nr) >> 1
        if start <= mid:
            rights.append(node + node + 1)
            node += node
            nr = mid
        else:
            node += node + 1
            nl = mid + 1
    if tree[node] < t:  # 叶子 start 自己就够小
        return nl
    for i in range(len(rights) - 1, -1, -1):
        node = rights[i]
        if tree[node] < t:
            while node < size:
                node += node
                if tree[node] >= t:
                    node += 1
            return node - size
    return None


def last_below(tree: MinTree, size: int, start: int, t: int) -> int | None:
    """最大的下标 i <= start 使 A2[i] < t；不存在返回 None（调用方用对面指针兜底）。"""
    node, nl, nr = 1, 0, size - 1
    lefts: list[int] = []
    while nl < nr:
        mid = (nl + nr) >> 1
        if start <= mid:
            node += node
            nr = mid
        else:
            lefts.append(node + node)
            node += node + 1
            nl = mid + 1
    if tree[node] < t:
        return nl
    for i in range(len(lefts) - 1, -1, -1):
        node = lefts[i]
        if tree[node] < t:
            while node < size:
                node += node + 1
                if tree[node] >= t:
                    node -= 1
            return node - size
    return None


def alt_sums(doubled: list[int], alt: list[int], tree: MinTree, size: int) -> list[int]:
    """对每个起点 p，求弧 doubled[p+1 .. p+n-1] 上取数序列的交错和 D（首项取 +）。"""
    n = len(doubled) >> 1
    m = len(doubled)
    memo: Memo = {}  # 同一状态 (u, v) 之后的取数序列完全一致，可以复用

    def state_alt_sum(u: int, v: int) -> int:
        """状态 (u, v)（剩余弧的两端）起、首项取 + 的交错和；顺路记忆化整条状态链。

        每步是"同侧连取一整段"：左端更大就一直从左边取，直到遇到第一个比右端小的
        元素（或两指针相遇）；段内符号交替，故整段贡献 = 段交错和 × 当前起手符号。
        """
        chain: Chain = []
        while True:
            key = u * m + v
            cached = memo.get(key)
            if cached is not None:  # 命中记忆，后面都不用再算了
                value = cached
                break
            if u == v:  # 只剩一个数
                value = doubled[u]
                memo[key] = value
                break
            if doubled[u] > doubled[v]:
                w = first_below(tree, size, u + 1, doubled[v])
                if w is None or w > v:  # 段内没有更小的，两指针在 v 相遇
                    w = v
                length = w - u
                seg = alt[w] - alt[u]  # 段 doubled[u .. w-1]，以 + 开头的交错和
                if u & 1:              # 段首下标是奇数，全局符号整体取反
                    seg = -seg
                chain.append((key, seg, length))
                u = w
            else:
                w = last_below(tree, size, v - 1, doubled[u])
                if w is None or w < u:
                    w = u
                length = v - w
                seg = alt[v + 1] - alt[w + 1]  # 段 doubled[v], doubled[v-1], ..., doubled[w+1]
                if v & 1:
                    seg = -seg
                chain.append((key, seg, length))
                v = w
        for key, seg, length in reversed(chain):  # 自链尾回溯，补齐每个状态的交错和
            value = seg - value if length & 1 else seg + value
            memo[key] = value
        return value

    return [state_alt_sum(p + 1, p + n - 1) for p in range(n)]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]
    if n == 1:  # 只有一个数，先手直接取走
        print(a[0])
        return

    total = sum(a)
    doubled = a + a  # 破环成链：起点 p 对应的弧就是 doubled[p+1 .. p+n-1]
    # alt[i] = sum_{j<i} (-1)^j doubled[j]，用前缀差 O(1) 求任意一段的交错和
    alt = list(accumulate((x if (i & 1) == 0 else -x for i, x in enumerate(doubled)), initial=0))
    tree, size = build_min_tree(doubled)

    # 设取数序列为 x0, x1, ...（x0 是后手拿的），D = x0 - x1 + x2 - ...；
    # 剩余数之和 S - a[p] = 后手 + 先手额外，D = 后手 - 先手额外，
    # 于是先手总分 = a[p] + (S - a[p] - D) / 2 = (S + a[p] - D) / 2。
    print('\n'.join(str((total + a[p] - d) // 2) for p, d in enumerate(alt_sums(doubled, alt, tree, size))))


if __name__ == "__main__":
    solve()
