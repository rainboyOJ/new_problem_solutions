#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 11:20
# update_at: 2026-10-07 11:20

import sys
from bisect import bisect_right

# 命中位置表：一圈内满足 S_i == C 的位置（升序，位置从 1 开始）
type Hits = list[int]
# 序列结构：(圈外尾巴长度 offset, 周期 K, 表格 hits 覆盖第 1..offset+K 天)
type Cycle = tuple[int, int, Hits]


def walk_second_order(a: int, b: int, x: int, y: int, z: int, p: int, c: int) -> Cycle:
    """Y!=0 时状态转移可逆，序列从第 1 项起就是纯周期：返回 (offset=0, 周期 K, 一圈内的命中位置)。"""
    hits: Hits = [i for i, v in enumerate((a, b), 1) if v == c]
    prev, cur, i = a, b, 3
    while True:
        nxt = (x * cur + y * prev + z) % p
        if nxt == b and cur == a:       # 状态 (S(i-1), S(i)) 回到 (A, B)，恰好走满一圈
            k = i - 2
            break
        if nxt == c:
            hits.append(i)
        prev, cur, i = cur, nxt, i + 1
    # 循环点在第 K+1 项与第 1 项同值，重复登记要去掉；K=1 时第 2 项同理
    return 0, k, [i for i in hits if i <= k]


def walk_first_order(a: int, b: int, x: int, z: int, p: int, c: int) -> Cycle:
    """Y=0 退化成一阶递推，状态只由单项决定：返回 (进圈前的位置数 offset, 周期 K, 命中位置)。"""
    hits: Hits = [1] if a == c else []  # 第 1 项不影响后续，永远属于圈外尾巴，单独登记
    first = [-1] * p                    # 每个取值首次出现的位置
    cur, i = b, 2
    while first[cur] < 0:               # 第一次撞上旧值，说明从这里开始进圈
        first[cur] = i
        if cur == c:
            hits.append(i)
        cur = (x * cur + z) % p
        i += 1
    return first[cur] - 1, i - first[cur], hits


def count_up_to(days: int, offset: int, k: int, hits: Hits) -> int:
    """前 days 天（days >= 0）中 S_i == C 的天数 = 尾巴 + 完整周期 + 残缺周期。"""
    if days <= offset + k:                          # 还没走完「尾巴 + 第一圈」，直接查表
        return bisect_right(hits, days)
    tail = bisect_right(hits, offset)               # 尾巴里的命中数
    cycles, left = divmod(days - offset, k)
    return tail + cycles * (len(hits) - tail) + bisect_right(hits, offset + left) - tail


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    t = next(data)

    for _ in range(t):
        a, b, x, y, z, p, c, q = (next(data) for _ in range(8))
        queries = [(next(data), next(data)) for _ in range(q)]  # Q 组 L R

        offset, k, hits = (walk_second_order(a, b, x, y, z, p, c) if y
                           else walk_first_order(a, b, x, z, p, c))
        out += [str(count_up_to(r, offset, k, hits) - count_up_to(l - 1, offset, k, hits))
                for l, r in queries]

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
