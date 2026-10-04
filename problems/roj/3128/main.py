#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:20
# update_at: 2026-10-02 10:20

import sys
from random import getrandbits, seed

INF = 10 ** 18  # 查询日波动值时，"还没找到任何候选"的距离上界

# treap 用四个平铺数组表示，下标即天数（0 号位是空节点哨兵），靠下标运算代替链表。
left: list[int] = []   # 左儿子下标，0 表示空
right: list[int] = []  # 右儿子下标，0 表示空
key: list[int] = []    # 该天营业额，同时是 BST 的键
prio: list[int] = []   # 随机优先级，小根堆保证期望树高 O(log n)


def insert(root: int, node: int) -> int:
    """把 node 插入以 root 为根的 treap，返回插入后的新根。"""
    if not root:
        return node
    path: list[int] = []  # 下降路径，末位是 node 的父节点
    cur = root
    while cur:
        path.append(cur)
        cur = left[cur] if key[node] < key[cur] else right[cur]  # 相等时往右挂
    if key[node] < key[path[-1]]:
        left[path[-1]] = node
    else:
        right[path[-1]] = node
    # 自底向上修正：node 的优先级比父节点小就旋转上浮，直到堆性质恢复
    while path and prio[node] < prio[path[-1]]:
        parent = path.pop()
        grand = path[-1] if path else 0
        if left[parent] == node:  # 右旋：node 从左儿子升上来
            left[parent] = right[node]
            right[node] = parent
        else:  # 左旋
            right[parent] = left[node]
            left[node] = parent
        if grand:  # 换根后要接回祖父
            if left[grand] == parent:
                left[grand] = node
            else:
                right[grand] = node
        else:
            root = node
    return root


def nearest(root: int, value: int) -> int:
    """在已插入的营业额里找与 value 距离最近的一个，返回该距离。"""
    best = INF
    cur = root
    while cur:
        gap = abs(value - key[cur])
        if gap < best:
            best = gap
        if value < key[cur]:
            cur = left[cur]
        elif value > key[cur]:
            cur = right[cur]
        else:
            return 0  # 出现过同一天营业额，波动值为 0
    return best


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    amount = list(map(int, data[1:1 + n]))

    seed(1)  # 固定种子：随机优先级可复现，仍足以让树期望平衡
    left.extend([0] * (n + 1))
    right.extend([0] * (n + 1))
    key.extend([0] + amount)
    prio.extend([0] + [getrandbits(30) for _ in amount])

    ans = 0
    root = 0  # 空树
    for day, value in enumerate(amount):
        gap = value if day == 0 else nearest(root, value)  # 第一天的最小波动值就是 a_1
        ans += gap
        root = insert(root, day + 1)  # 当天营业额进入集合，供后面查询

    print(ans)


if __name__ == "__main__":
    solve()
