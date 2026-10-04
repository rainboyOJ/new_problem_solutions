#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:28
# update_at: 2026-10-01 17:28

import sys

ODD = 1  # 回答编码：1 = 奇数个 1（前缀异或不同），0 = 偶数个 1（前缀异或相同）


def find(kind: dict[int, int], parent: dict[int, int], x: int) -> int:
    """路径压缩地返回 x 的根，并把 kind[x] 修正为 x 到根的异或。"""
    path: list[int] = []
    while parent[x] != x:
        path.append(x)
        x = parent[x]
    root, acc = x, 0
    for node in reversed(path):  # 从靠近根的一端往回走，先修正父亲再修正儿子
        acc ^= kind[node]
        kind[node] = acc  # node 到根的异或
        parent[node] = root  # 顺带把这条路径压平
    return root


def add_constraint(
    kind: dict[int, int],
    parent: dict[int, int],
    size: dict[int, int],
    x: int,
    y: int,
    parity: int,
) -> bool:
    """加入约束 `kind[y] ^ kind[x] = parity`；与已有约束矛盾时返回 False。"""
    rx, ry = find(kind, parent, x), find(kind, parent, y)
    if rx == ry:
        return kind[x] ^ kind[y] == parity  # 同集合：已有约束的推论必须与本次回答一致
    if size[rx] < size[ry]:  # 小树挂到大树，控制树高
        rx, ry, x, y = ry, rx, y, x
    parent[ry] = rx
    kind[ry] = kind[x] ^ kind[y] ^ parity  # 使 y 到 x 的新路径异或恰好是 parity
    size[rx] += size[ry]
    return True


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    length = int(next(it))  # 序列长度（只界定前缀下标范围，判定过程不用它）
    m = int(next(it))       # 回答数量

    kind: dict[int, int] = {}  # kind[v] = 点 v 到其父亲的异或（根恒为 0）
    parent: dict[int, int] = {}
    size: dict[int, int] = {}

    answer = m  # 所有回答都不矛盾时，能撑过的回答数就是 M
    for i in range(m):
        left = next(it)
        right = next(it)
        word = next(it)
        x, y = int(left) - 1, int(right)  # 前缀坐标：S[l..r] 对应点 l-1 与点 r
        for v in (x, y):  # 坐标只有 2M 个且 N 可达 1e9，按需开点
            parent.setdefault(v, v)
            kind.setdefault(v, 0)
            size.setdefault(v, 1)
        parity = ODD if word == b"odd" else 0
        if not add_constraint(kind, parent, size, x, y, parity):
            answer = i  # 第 i 条回答与前面矛盾，说明序列能同时满足的是前 i 条
            break

    print(answer)  # length 只界定前缀下标范围，判定过程与它无关


if __name__ == "__main__":
    solve()
