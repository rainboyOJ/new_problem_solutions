#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:20
# update_at: 2026-09-30 18:20

import sys


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    n = int(next(tokens))
    par = [-1] + [int(next(tokens)) for _ in range(n - 1)]  # 1..n-1 号各自依赖的软件包
    q = int(next(tokens))

    # 孩子表 + 先序（祖先先于后代），逆序即为自底向上的求值顺序
    ch: list[list[int]] = [[] for _ in range(n)]
    for v in range(1, n):
        ch[par[v]].append(v)
    order: list[int] = []
    stack = [0]
    while stack:
        v = stack.pop()
        order.append(v)
        stack.extend(ch[v])

    size = [1] * n
    heavy = [-1] * n
    for v in reversed(order):
        for c in ch[v]:
            size[v] += size[c]
            if heavy[v] < 0 or size[c] > size[heavy[v]]:
                heavy[v] = c  # 最重儿子：子树最大的儿子，重链沿它延伸

    # 重链优先的先序压成 pos：重链区间连续、子树区间 [pos, pos+size-1] 也连续
    pos = [0] * n
    head = [0] * n
    seq: list[int] = []
    stack = [0]
    while stack:
        v = stack.pop()
        seq.append(v)
        for c in reversed(ch[v]):
            if c != heavy[v]:
                stack.append(c)  # 轻儿子先压栈，重儿子最后压 = 最先弹出
        if heavy[v] != -1:
            stack.append(heavy[v])
    for i, v in enumerate(seq):
        pos[v] = i
    head[0] = 0
    for v in seq[1:]:
        head[v] = v if heavy[par[v]] != v else head[par[v]]  # 轻儿子自立链头

    # 线段树：区间求和 + 区间赋值，标记 -1 表示该节点没有未下推的赋值
    tr = [0] * (4 * n)
    tg = [-1] * (4 * n)

    def cover(i: int, nl: int, nr: int, l: int, r: int, v: int) -> int:
        """把区间 [l,r] 全部赋值为 v，返回它们修改前的和。"""
        if r < nl or nr < l:
            return 0
        if l <= nl and nr <= r:
            prev = tr[i]
            tr[i] = v * (nr - nl + 1)
            tg[i] = v
            return prev
        mid = (nl + nr) >> 1
        t = tg[i]
        if t != -1:  # 下推标记后才能安全地下探
            tr[i << 1] = t * (mid - nl + 1)
            tr[i << 1 | 1] = t * (nr - mid)
            tg[i << 1] = tg[i << 1 | 1] = t
            tg[i] = -1
        prev = cover(i << 1, nl, mid, l, r, v) + cover(i << 1 | 1, mid + 1, nr, l, r, v)
        tr[i] = tr[i << 1] + tr[i << 1 | 1]
        return prev

    last = n - 1
    out: list[str] = []

    for _ in range(q):
        op = next(tokens)
        x = int(next(tokens))
        if op == b"install":
            # 沿重链跳到根：路径拆成 O(log n) 段连续区间，逐段置 1，
            # 段长减去原有和 = 这段里原来是 0（未安装）的个数
            cnt, v = 0, x
            while True:
                h = head[v]
                lo, hi = pos[h], pos[v]
                cnt += hi - lo + 1 - cover(1, 0, last, lo, hi, 1)
                if h == 0:
                    break
                v = par[h]
            out.append(str(cnt))
        else:
            # 子树在 pos 上是连续区间：置 0 前的和即被卸载的个数
            lo = pos[x]
            out.append(str(cover(1, 0, last, lo, lo + size[x] - 1, 0)))

    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()
