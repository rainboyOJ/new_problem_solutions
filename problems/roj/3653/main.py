#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 13:37
# update_at: 2026-10-02 13:37

import sys
import bisect
from array import array

FLAT_LIMIT = 10000  # 平表里记录的离队位置超过这个数，整队就换成 Fenwick


def new_queue(base: int, mult: int, off: int, cap: int) -> dict:
    """虚拟队列：前 base 个位置是原始成员，其后是依次补进来的成员。"""
    return {
        "base": base, "mult": mult, "off": off,
        "cap": cap, "bit": 1 << (cap.bit_length() - 1),
        "gone": [], "kept": [], "tree": None,
    }


def add(tree: array, cap: int, pos: int, delta: int) -> None:
    """Fenwick 单点加 delta，pos 是 1 起的虚拟位置。"""
    while pos <= cap:
        tree[pos] += delta
        pos += pos & -pos


def build_tree(q: dict, alive_upto: int, gone: list[int]) -> array:
    """把平表换成 Fenwick：初态 [1, alive_upto] 都站着，再逐个扣掉离队位置。"""
    cap = q["cap"]
    # 树上第 i 个格子管辖 (i-lowbit, i]，只数这段与 [1, alive_upto] 的交集
    tree = array("i", [0] + [
        min(i & -i, max(0, alive_upto - i + (i & -i)))
        for i in range(1, cap + 1)
    ])
    for pos in gone:
        add(tree, cap, pos, -1)
    return tree


def pop_kth(q: dict, k: int) -> int:
    """取走队里还站着的第 k 个成员（1 起），返回它的原始编号。"""
    base, mult, off, tree = q["base"], q["mult"], q["off"], q["tree"]

    if tree is None:
        gone, kept = q["gone"], q["kept"]
        # 存活数 f(p) = p - rank(p) 阶梯式单调，二分最小的 p 使 f(p) >= k；
        # 由 p = k + rank(p) <= k + |gone| 知上界取 k + |gone| 足够
        lo, hi = k, k + len(gone)
        while lo < hi:
            mid = (lo + hi) // 2
            alive = mid - bisect.bisect_right(gone, mid)  # 前 mid 个位置还站着的人数
            if alive >= k:
                hi = mid
            else:
                lo = mid + 1
        pos = lo
        bisect.insort(gone, pos)
        if len(gone) > FLAT_LIMIT:  # 离队记录太厚，先整体换成 Fenwick 再继续
            q["tree"] = tree = build_tree(q, base + len(kept), gone)
            q["gone"] = None
    else:
        # Fenwick 倍增：找最小的 pos 让前缀存活数 >= k
        pos, step = 0, q["bit"]
        while step:
            nxt = pos + step
            if nxt <= q["cap"] and tree[nxt] < k:
                k -= tree[nxt]
                pos = nxt
            step >>= 1
        pos += 1
        add(tree, q["cap"], pos, -1)

    if pos <= base:
        return mult * pos + off  # 原地成员：编号是等差数列
    return q["kept"][pos - base - 1]  # 补位成员：编号在记录里


def push(q: dict, elem: int) -> None:
    """把 elem 补进队尾：它占据下一个虚拟位置。"""
    nxt = q["base"] + len(q["kept"]) + 1
    q["kept"].append(elem)
    if q["tree"] is not None:
        add(q["tree"], q["cap"], nxt, 1)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, q = next(data), next(data), next(data)

    col = new_queue(n, m, 0, n + q)  # 最后一列，补位与归队的同学都从这里进出
    rows: dict[int, dict] = {}
    out: list[int] = []

    for _ in range(q):
        x, y = next(data), next(data)
        moved = pop_kth(col, x)  # (x, m) 位同学被顶出最后一列
        if y == m:
            s = moved  # 离队的正是 (x, m) 位，它绕一圈回到 (n, m)
        else:
            row = rows.get(x)
            if row is None:
                row = rows[x] = new_queue(m - 1, 1, (x - 1) * m, m - 1 + q)
            s = pop_kth(row, y)  # 行内第 y 位同学离队
            push(row, moved)  # 本列同学左移补进该行队尾
        push(col, s)  # 离队同学归队到 (n, m)
        out.append(s)

    sys.stdout.write("\n".join(map(str, out)) + "\n")


if __name__ == "__main__":
    solve()
