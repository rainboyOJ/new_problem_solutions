#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 16:46
# update_at: 2026-10-02 16:46

import sys
from array import array
from itertools import accumulate

ALPHA = 18  # 字符表只有前 18 个小写字母，一个字符集合正好装进 18 位掩码


def positions(s: bytes) -> list[list[int]]:
    """字符分桶：buckets[c] 是字符 c 在原串里的全部出现位置，下标天然递增。"""
    buckets: list[list[int]] = [[] for _ in range(ALPHA)]
    for i, ch in enumerate(s):
        buckets[ch - 97].append(i)
    return buckets


def prefix_counts(s: bytes) -> list[array]:
    """字符前缀个数表：pref[y][i] = 字符 y 在位置 i 之前出现的次数。

    用 translate 把「是否等于 y」翻译成 0/1 串，再用 accumulate 求前缀和，
    两步都在 C 语言级别完成，整张表 O(ALPHA * len(s)) 建好。
    """
    pref: list[array] = []
    for y in range(ALPHA):
        table = bytearray(256)
        table[y + 97] = 1  # 只把字符 y 映成 1，其余字符全映成 0
        counts = array('I', accumulate(s.translate(table)))  # counts[i] 数到位置 i（含）
        counts.insert(0, 0)  # 开头补 0，让 pref[y][i] 恰好是位置 i 之前的个数
        pref.append(counts)
    return pref


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    s1, s2 = data[0], data[1]
    n = int(data[2])  # 询问次数
    queries = data[3:3 + n]
    pos1, pos2 = positions(s1), positions(s2)

    # 单字符集合：某个字符在两边出现次数不同，只保留它就必然不等
    bad_single = 0
    for c in range(ALPHA):
        if len(pos1[c]) != len(pos2[c]):
            bad_single |= 1 << c

    # 二字符集合 {a,b}：只保留 a、b 后的子序列相等，当且仅当两边 a、b 次数
    # 分别相等，且「每个 a 前面有多少个 b」这一列数完全一致——
    # 这列数（非降、每项不超过 b 的总数）加 b 的总数能唯一还原该子序列。
    pref1, pref2 = prefix_counts(s1), prefix_counts(s2)
    bad_pair = [0] * ALPHA  # bad_pair[a]：与 a 组队后必不相等的字符集合（位掩码）
    for a in range(ALPHA):
        for b in range(a + 1, ALPHA):
            before1 = tuple(pref1[b][p] for p in pos1[a])  # 每个 a 前面的 b 个数
            before2 = tuple(pref2[b][p] for p in pos2[a])
            cnt_ok = len(pos1[a]) == len(pos2[a]) and len(pos1[b]) == len(pos2[b])
            if not cnt_ok or before1 != before2:
                bad_pair[a] |= 1 << b
                bad_pair[b] |= 1 << a

    out: list[str] = []
    for q in queries:
        mask = 0
        for ch in q:
            mask |= 1 << (ch - 97)
        # 每轮取走最低位 c：二元子集 {c,d} 只在 c 被取走的那一轮被检查一次，
        # 因此整个集合的坏对检查恰好是 O(|q|) 而不是 O(|q|^2)。
        bad = mask & bad_single
        while mask and not bad:
            bit = mask & -mask
            mask ^= bit
            bad = bad_pair[bit.bit_length() - 1] & mask
        out.append('N' if bad else 'Y')

    sys.stdout.write(''.join(out) + '\n')


if __name__ == "__main__":
    solve()
