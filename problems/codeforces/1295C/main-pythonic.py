#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-04 23:08
# update_at: 2026-11-04 23:08

import sys
from bisect import bisect_right

ALPHA = 26  # 小写字母表大小，位置列表按 ch - 97 分桶


def positions(s: bytes) -> list[list[int]]:
    """pos[c] = 字符 c 在 s 中出现的所有下标；顺着扫一遍，天然升序。"""
    pos: list[list[int]] = [[] for _ in range(ALPHA)]
    for i, ch in enumerate(s):
        pos[ch - 97].append(i)
    return pos


def trips(pos: list[list[int]], t: bytes) -> int:
    """沿 t 一路向右跳，跳不动就重开一趟，返回最少趟数；无解返回 -1。"""
    ans, cur = 1, -1                  # 第一趟总要开；-1 表示还没用过 s 的任何位置
    for ch in t:
        p = pos[ch - 97]
        if not p:                     # t 要的字符 s 里一个都没有，永远拼不出
            return -1
        j = bisect_right(p, cur)      # 严格大于 cur 的第一个出现位置
        gone = j == len(p)            # 越界 = s 后面没有这个字符了，只能重开一趟
        ans += gone
        cur = p[0] if gone else p[j]  # 重开时取它第一个出现位置，这一趟已经用掉
    return ans


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    for _ in range(int(next(data))):
        s, t = next(data), next(data)  # 直接按字节处理，ch - 97 就是字母编号
        out.append(str(trips(positions(s), t)))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
