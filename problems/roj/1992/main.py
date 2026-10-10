#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:46
# update_at: 2026-10-08 06:46

import sys
from collections.abc import Iterator

SIZE = 2 * 80005 + 80005 + 10  # 坐标轴长度：m 个顶部空位 + n 本书 + m 个底部空位
TOP_CMD = b"Top"
BOTTOM_CMD = b"Bottom"
INSERT_CMD = b"Insert"
ASK_CMD = b"Ask"
QUERY_CMD = b"Query"


def add(bit: list[int], x: int, delta: int) -> None:
    """坐标 x 上的书本数加 delta（树状数组单点修改）。"""
    while x < SIZE:
        bit[x] += delta
        x += x & -x


def prefix(bit: list[int], x: int) -> int:
    """坐标 <= x 的书本数量，也就是坐标 x 上那本书的排名。"""
    total = 0
    while x > 0:
        total += bit[x]
        x -= x & -x
    return total


def select(bit: list[int], k: int) -> int:
    """第 k 个 1 所在的坐标（BIT 上倍增，比"二分 + 前缀和"少一个 log）。"""
    x = 0
    step = 1 << 18  # 2^18 = 262144 > SIZE，从最高位往下试
    while step:
        if x + step < SIZE and bit[x + step] < k:
            x += step
            k -= bit[x]
        step >>= 1
    return x + 1


def simulate(data: Iterator[bytes]) -> list[str]:
    """按命令流模拟书架，按顺序返回所有 Ask / Query 的答案行。

    序列被摊在一根足够长的坐标轴上：Top 只会占用不断左移的空位，
    Bottom 只会占用不断右移的空位，Insert 只交换两本书的坐标，
    因此"位置"始终可以当成静态坐标来用，不需要任何平衡树。
    """
    n = int(next(data))
    m = int(next(data))
    bit = [0] * SIZE      # bit: 坐标 x 上是否有书（树状数组）
    rev = [0] * SIZE      # rev[x] = 坐标 x 上的书编号，0 表示空位
    pos = [0] * (n + 1)   # pos[v] = 书 v 当前的坐标

    base = m + 5          # 初始书堆的起点，左边留 m 格给 Top，右边留 m 格给 Bottom
    for i in range(1, n + 1):
        v = int(next(data))
        x = base + i
        pos[v] = x
        rev[x] = v
        add(bit, x, 1)

    lo = base             # 下一次 Top 的落点，每次左移一格
    hi = base + n         # 下一次 Bottom 的落点，每次右移一格
    out: list[str] = []

    for _ in range(m):
        op = next(data)
        s = int(next(data))

        if op == TOP_CMD:                 # Top S：把 S 搬到最上面
            p = pos[s]
            add(bit, p, -1)
            rev[p] = 0
            lo -= 1
            pos[s] = lo
            rev[lo] = s
            add(bit, lo, 1)

        elif op == BOTTOM_CMD:            # Bottom S：把 S 搬到最下面
            p = pos[s]
            add(bit, p, -1)
            rev[p] = 0
            hi += 1
            pos[s] = hi
            rev[hi] = s
            add(bit, hi, 1)

        elif op == INSERT_CMD:            # Insert S T：与排名相差 T 的那本书换坐标
            t = int(next(data))
            if t == 0:
                continue
            p = pos[s]
            rank = prefix(bit, p)        # S 当前的 1-indexed 排名
            q = select(bit, rank + t)    # 排名相差 t 的那本书的坐标
            other = rev[q]
            rev[p] = other               # 两本书互换坐标：坐标集合没变，BIT 无需改动
            rev[q] = s
            pos[other] = p
            pos[s] = q

        elif op == ASK_CMD:               # Ask S：S 上面有多少本书
            answer = prefix(bit, pos[s] - 1)
            out.append(str(answer))

        elif op == QUERY_CMD:             # Query S：从上数第 S 本书的编号
            answer = rev[select(bit, s)]
            out.append(str(answer))

    return out


def solve() -> None:
    out = simulate(iter(sys.stdin.buffer.read().split()))
    if out:  # 一条 Ask/Query 都没有时不能多打一个空行
        print('\n'.join(out))


if __name__ == "__main__":
    solve()
