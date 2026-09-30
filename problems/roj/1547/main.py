#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:55
# update_at: 2026-09-30 17:55

import sys

ADD = 1     # 操作码：在 a 处累加 b
QUERY = 2   # 操作码：询问闭区间 [a, b] 的和


def build_bit(values: list[int]) -> list[int]:
    """用初始数组直接建树状数组：tree[i] 管辖 (i - lowbit(i), i] 这一段的和。

    从小到大把每个点的贡献推给它的父亲 i + lowbit(i)，一趟 O(n) 建完，不必 n 次插入。
    """
    size = len(values)
    tree = values[:]                              # 下标 1..n，tree[0] 留作占位
    for i in range(1, size):
        parent = i + (i & -i)
        if parent < size:
            tree[parent] += tree[i]
    return tree


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    tree = build_bit([0] + [next(data) for _ in range(n)])  # 补一个下标 0 占位

    out: list[str] = []
    for _ in range(m):
        k, a, b = next(data), next(data), next(data)
        if k == QUERY:
            # 前缀和之差：先向后跳着消掉低位，累出 [1, b] 与 [1, a-1] 的和
            total = 0
            i = b
            while i > 0:
                total += tree[i]
                i -= i & -i
            i = a - 1
            while i > 0:
                total -= tree[i]
                i -= i & -i
            out.append(str(total))
        else:
            # 单点累加：沿 i += lowbit(i) 把增量加到所有管辖 a 的位置上
            i = a
            while i <= n:
                tree[i] += b
                i += i & -i

    sys.stdout.write('\n'.join(out) + ('\n' if out else ''))


if __name__ == "__main__":
    solve()
