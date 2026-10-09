#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 09:30
# update_at: 2026-10-09 11:24

import sys

# 主席树（可持久化线段树）维护 fa[]：结点 3 个平行 list 存左右儿子与叶子值
# 与 C++ 版同阶：每次 find 跳 O(log n) 次、每次查询 O(log n)，总 O(m log^2 n)
MAX_NODES = 8500000
ls = [0] * MAX_NODES      # 左儿子编号
rs = [0] * MAX_NODES      # 右儿子编号
val = [0] * MAX_NODES     # 叶子值：fa | (dep << 20)
node_cnt = 0
FA_MASK = (1 << 20) - 1


def build(l: int, r: int) -> int:
    """建初始版本：叶子 i 的 fa = i、dep = 0，返回根编号。"""
    global node_cnt
    node_cnt += 1
    p = node_cnt
    if l == r:
        val[p] = l
        return p
    mid = (l + r) // 2
    ls[p] = build(l, mid)
    rs[p] = build(mid + 1, r)
    return p


def update(pre: int, l: int, r: int, idx: int, fa: int, dep: int) -> int:
    """在版本 pre 上把下标 idx 的叶子改成 fa|(dep<<20)，返回新版本根。"""
    global node_cnt
    node_cnt += 1
    p = node_cnt
    ls[p] = ls[pre]
    rs[p] = rs[pre]
    if l == r:
        val[p] = fa | (dep << 20)
        return p
    mid = (l + r) // 2
    if idx <= mid:
        ls[p] = update(ls[pre], l, mid, idx, fa, dep)
    else:
        rs[p] = update(rs[pre], mid + 1, r, idx, fa, dep)
    return p


def query(p: int, l: int, r: int, idx: int) -> int:
    """查询版本 p 中下标 idx 的叶子值（fa | dep<<20）。"""
    if l == r:
        return val[p]
    mid = (l + r) // 2
    if idx <= mid:
        return query(ls[p], l, mid, idx)
    return query(rs[p], mid + 1, r, idx)


def find_root(p: int, n: int, x: int) -> int:
    """沿 fa 链找根，返回根叶子的值。绝不路径压缩：会改写大量历史结点。"""
    while True:
        v = query(p, 1, n, x)
        fa = v & FA_MASK
        if fa == x:
            return v
        x = fa


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
        m = next(data)
    except StopIteration:
        return

    rt = [0] * (m + 1)
    rt[0] = build(1, n)

    last_ans = 0
    out: list[str] = []
    for i in range(1, m + 1):
        op = next(data)
        if op == 1:
            a = next(data) ^ last_ans
            b = next(data) ^ last_ans
            rt[i] = rt[i - 1]
            va = find_root(rt[i], n, a)
            vb = find_root(rt[i], n, b)
            root_a = va & FA_MASK
            root_b = vb & FA_MASK
            if root_a != root_b:
                # 按秩（深度）合并
                dep_a = va >> 20
                dep_b = vb >> 20
                if dep_a < dep_b:
                    rt[i] = update(rt[i - 1], 1, n, root_a, root_b, dep_a)
                elif dep_a > dep_b:
                    rt[i] = update(rt[i - 1], 1, n, root_b, root_a, dep_b)
                else:
                    tmp = update(rt[i - 1], 1, n, root_a, root_b, dep_a)
                    rt[i] = update(tmp, 1, n, root_b, root_b, dep_b + 1)
        elif op == 2:
            k = next(data) ^ last_ans
            rt[i] = rt[k]                        # 回到第 k 次操作之后（k=0 即初始状态）
        else:
            a = next(data) ^ last_ans
            b = next(data) ^ last_ans
            root_a = find_root(rt[i - 1], n, a) & FA_MASK
            root_b = find_root(rt[i - 1], n, b) & FA_MASK
            ans = 1 if root_a == root_b else 0
            out.append(str(ans))
            last_ans = ans
            rt[i] = rt[i - 1]

    sys.stdout.write('\n'.join(out) + ('\n' if out else ''))


if __name__ == '__main__':
    solve()
