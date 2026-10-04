#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 23:48
# update_at: 2026-10-01 23:48

import sys
from collections import Counter
from functools import cache

MASK = (1 << 64) - 1  # 答案对 2^64 取模；Python 整数不溢出，只能主动掩码
SHIFT = (0, 4, 8, 12)  # 状态码高位中“恰好还剩 k 张的面值个数”占的位偏移，k = size-1


@cache
def free_ways(code: int) -> int:
    """状态码 code 对应的牌集合，按相邻面值不同排成一列有多少种放法。

    花色不参与冲突，只有“面值”约束相邻关系，所以一个面值只需记住还剩几张
    （0~4 张，而 0 张的面值用不着记录）。高位按剩余张数分 4 档存面值个数，
    低 2 位存上一张牌的面值档次（size-1），0 表示还没放过任何牌——它不是任何
    真实档次，所以天然不会和“上一张同面值”的判断冲突。
    """
    body, last = code >> 2, code & 3
    if not body:
        return 1  # 牌放完了，空后缀算一种放法

    total = 0
    for size, shift in enumerate(SHIFT, 1):
        left = body >> shift & 15           # 还剩 size 张的面值有多少个
        pick = left - (last == size)        # 上一张同面值的牌后面这个空位不能放
        if pick <= 0:
            continue
        nxt = body - (1 << shift)           # 该面值掉到 size-1 档
        if size > 1:
            nxt += 1 << SHIFT[size - 2]
        # size 种“选哪张牌”与 pick 个“插进哪个空位”相互独立，直接相乘
        total += size * pick * free_ways(nxt << 2 | size - 1)
    return total & MASK


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    T = int(next(data))

    for case in range(1, T + 1):
        n = int(next(data))
        cards = [next(data) for _ in range(n)]  # 每张牌形如 2S，面值取第 0 个字符

        # 只需统计“剩 k 张的面值有几个”，花色与面值具体是什么都不影响答案。
        by_size = Counter(Counter(card[:1] for card in cards).values())
        code = sum(cnt << SHIFT[size - 1] for size, cnt in by_size.items()) << 2
        out.append(f"Case #{case}: {free_ways(code)}")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
