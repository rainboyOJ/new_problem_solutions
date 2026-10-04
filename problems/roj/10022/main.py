#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 18:30
# update_at: 2026-10-02 18:30

import sys
from array import array

SHIFT = 20  # 点编号 n<=1e6<2^20，a<<20|b 把一条边压成一个整数，排序后顺带去重
SPAN = 1 << SHIFT


def solve() -> None:
    src = sys.stdin.buffer
    n, m = map(int, next(src).split())
    packed = [0] * m
    for i in range(m):
        a, b = map(int, next(src).split())
        packed[i] = a << SHIFT | b  # a 占高位、b 占低 20 位，按 (a, b) 字典序排序
    packed.sort()

    # 排序后相同边相邻：pred_cnt 记去重后的前驱数 |H[i]|，pred_max 记最大前驱 last[i]
    pred_cnt = array("i", [0]) * (n + 1)
    pred_max = array("i", [0]) * (n + 1)
    seen = -1
    for key in packed:
        if key != seen:
            seen = key
            b = key & (SPAN - 1)
            pred_cnt[b] += 1
            pred_max[b] = key >> SHIFT  # 同一个 b 的 key 按 a 升序，最后一次即最大前驱

    # P(i)={i}∪H[i] 是包含 i 的最大团。H[i]\{last[i]} ⊆ H[last[i]] 恒成立，
    # 所以 |H[i]|>|H[last[i]]| 等价于 H[i]=H[last[i]]∪{last[i]}=P(last[i])，
    # 即 P(last[i]) 整个被 i 吸收 → last[i] 对应的团被包住，不是极大团。
    covered = bytearray(n + 1)
    for i in range(1, n + 1):
        j = pred_max[i]
        if j and pred_cnt[i] > pred_cnt[j]:
            covered[j] = 1
    print(n - sum(covered))


if __name__ == "__main__":
    solve()
