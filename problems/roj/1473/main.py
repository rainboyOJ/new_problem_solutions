#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:05
# update_at: 2026-09-30 13:05

import sys
from array import array
from collections.abc import Iterator
from itertools import accumulate
from operator import xor


def prefix_best(a: list[int], bits: int) -> Iterator[int]:
    """依次产出 best[0..n-1]：best[k] = a[0..k] 里所有子数组异或和的最大值。

    前缀异或 P 满足 xor(a[l..i]) = P[i+1] ^ P[l]：把 P[0..n] 依次喂给 01-Trie，
    每轮先拿 P[i] 查最大异或 partner、再把它自己插入，partner 下标天然更小。
    第一轮（空前缀 P[0]）只插入不产出；逐个 yield 不攒整表，省内存。
    """
    ch = array("i", [0]) * 4       # ch[t<<1|b]：结点 t 的 b 儿子结点号，0 表示没有；int32 平坦数组省内存
    top = 1      # 已用结点的最大编号；0 号空置，1 号是根
    best = 0     # 前缀最大值：至今见过的最大子数组异或
    for i, v in enumerate(accumulate(a, xor, initial=0)):  # v 依次取 P[0]=0, P[1], …, P[n]
        # —— 先查：v 对着集合里已有的前缀异或贪心取最大异或 ——
        t, acc = 1, 0
        for s in range(bits - 1, -1, -1):
            b = v >> s & 1
            w = ch[t + t + (b ^ 1)]  # 最想要与当前位相反的儿子
            if w:
                acc |= 1 << s
                t = w
            else:
                t = ch[t + t + b]
        if acc > best:
            best = acc
        if i:  # 跳过空前缀那一轮（对应空输入，无真实子数组）
            yield best
        # —— 后插：把 v 自己放进集合，供后面的位置查询 ——
        t = 1
        for s in range(bits - 1, -1, -1):
            b = v >> s & 1
            nxt = ch[t + t + b]
            if not nxt:
                top += 1
                if len(ch) < top + top + 2:  # 槽位只在新建结点时变大，按 4MB 块增量扩，避免大块拷贝峰值
                    ch.extend(array("i", [0]) * (1 << 20))
                ch[t + t + b] = top
                nxt = top
            t = nxt


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    a = [int(x) for x in data[1 : n + 1]]
    del data                      # 及时释放 split 出的 bytes，压低峰值内存
    bits = max(1, max(a).bit_length())  # 异或不会超出 max(a) 的最高位
    # right[k]：a[k..n-1] 内的最大子数组异或（int32 数组，比列表省 10MB+）
    right = array("i", prefix_best(a[::-1], bits))
    right.reverse()
    # left 边算边用不落表：答案 = max_k left[k] + right[k+1]（两段以 k 为分割点）
    ans = max(lv + right[k + 1] for k, lv in enumerate(prefix_best(a, bits)) if k + 1 < n)
    print(ans)


if __name__ == "__main__":
    solve()
