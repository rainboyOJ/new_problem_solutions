#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:19
# update_at: 2026-10-07 17:19

import sys

ROOT = 1  # 根状态（空串）的编号；状态 0 是"这条出边不存在"的哨兵

ch: list[list[int]] = [[0] * 10, [0] * 10]  # ch[u][c]：状态 u 走字符 c 到哪个状态
fa: list[int] = [0, 1]                      # 并查集父指针，代表元满足 fa[u] == u
fin: list[bool] = [False, False]            # 该状态所在等价类是否已进信息集


def find_root(x: int) -> int:
    """并查集找代表元，顺路把路径上的点都挂到根上。"""
    r = x
    while fa[r] != r:
        r = fa[r]
    while fa[x] != r:
        fa[x], x = r, fa[x]
    return r


def ensure_state(s: bytes) -> int:
    """沿串 s 走自动机（缺的边现场开点），返回末状态所在等价类的代表元。"""
    cur = ROOT
    for d in s:
        c = d - 48
        if ch[cur][c] == 0:
            # 开点：ch / fa / fin 三个数组同步长一位，新状态自成一类
            ch.append([0] * 10)
            fa.append(len(fa))
            fin.append(False)
            ch[cur][c] = len(fa) - 1
        cur = find_root(ch[cur][c])
    return cur


def find_state(s: bytes) -> int:
    """询问串 s 落在哪个等价类；中途缺边说明 s 不在信息集，返回哨兵 0。"""
    cur = ROOT
    for d in s:
        c = d - 48
        nxt = ch[cur][c]
        if nxt == 0:
            return 0
        cur = find_root(nxt)
    return cur


def merge_state(p: int, q: int) -> None:
    """把 p、q 所在等价类并成一类，并对 10 条出边做同余闭包。

    纠缠要求两个状态右语言相同，所以同类状态对每个字符的后继也必须同类；
    后继合并又会引出新的状态对，用显式栈把闭包做到底（不递归，免爆栈）。
    """
    stack = [(p, q)]
    while stack:
        x, y = stack.pop()
        a, b = find_root(x), find_root(y)
        if a == b:  # 已经在同一类里
            continue
        fa[b] = a                                        # b 并入 a 的类
        fin[a] = fin[a] or fin[b]                        # 标记只置真不置假
        for c in range(10):
            u, v = ch[a][c], ch[b][c]
            if v == 0:                                   # b 这条出边是空的
                continue
            if u == 0:
                ch[a][c] = v                             # a 缺的边直接接上 b 的
                continue
            need_merge = find_root(u) != find_root(v)     # 两条后继还不在同一类
            if need_merge:
                stack.append((u, v))


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    m = int(next(data))
    out: list[str] = []
    added = False  # 是否出现过操作 1；一次都没加过串时信息集恒空
    for _ in range(m):
        op = next(data)
        if op == b'1':
            fin[ensure_state(next(data))] = True
            added = True
        elif op == b'2':
            s = next(data)
            v = find_state(s) if added else 0  # 空集直接答 0，省一趟自动机
            out.append('1' if v and fin[v] else '0')
        else:
            merge_state(ensure_state(next(data)), ensure_state(next(data)))
    # 答案先攒进列表再一次写出，避免 10^5 次 print 的开销；末尾补换行收尾
    if out:
        sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
