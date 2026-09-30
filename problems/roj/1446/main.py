#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:04
# update_at: 2026-09-30 12:04
#
# 质数方阵：行/列/两条对角线都是"位和为 S"的五位素数，左上角给定。
# 核心：枚举列0素数 c0 与主对角线素数 dg（首位=左上角），行1..4 由
# (首位=c0[i], 第i位=dg[i]) 的素数桶确定，行0 由四个列和反推，全程整数位运算。
# 副对角线从左下往右上读（从左到右），它与"列4的和"联立 => 行3满足 r3[1]-r3[4]=Δ，
# 用 (差值)桶 O(1) 过滤；行0/副对角线/列1..4 最后查素数表。

import sys
from collections import defaultdict


def solve() -> None:
    S, corner = map(int, sys.stdin.buffer.read().split())

    def is_prime(n: int) -> bool:
        """试除判断素数（n ≤ 99999，只对位和为 S 的数调用）。"""
        return n > 1 and all(n % d for d in range(2, int(n ** 0.5) + 1))

    # 位和为 S 的全部五位素数：整数集合 pset（查表）+ 逐位元组（取位）
    pset = {n for n in range(10000, 100000) if sum(map(int, str(n))) == S and is_prime(n)}
    firsts = sorted(n for n in pset if n // 10000 == corner)  # 行0/列0/对角线候选
    if not firsts:
        print('NONE')
        return
    tups = [(n // 10000, n // 1000 % 10, n // 100 % 10, n // 10 % 10, n % 10) for n in sorted(pset)]

    # 行 i(1..4) 的素数桶：首位 = 列0第i位，第 i 位 = 主对角线第 i 位
    b1: dict[tuple[int, int], list] = defaultdict(list)              # (d0, d1)
    b2: dict[tuple[int, int], list] = defaultdict(list)              # (d0, d2)
    b3: dict[tuple[int, int], dict] = defaultdict(lambda: defaultdict(list))  # (d0,d3)->d1-d4
    b4: dict[tuple[int, int], list] = defaultdict(list)              # (d0, d4)
    for t in tups:
        b1[(t[0], t[1])].append(t)
        b2[(t[0], t[2])].append(t)
        b3[(t[0], t[3])][t[1] - t[4]].append(t)
        b4[(t[0], t[4])].append(t)

    ans: list[str] = []
    for c0 in firsts:  # 第 0 列（素数）
        c01, c02, c03, c04 = c0 // 1000 % 10, c0 // 100 % 10, c0 // 10 % 10, c0 % 10
        for dg in firsts:  # 主对角线（素数）
            dg1, dg2, dg3, dg4 = dg // 1000 % 10, dg // 100 % 10, dg // 10 % 10, dg % 10
            l1 = b1.get((c01, dg1)); l2 = b2.get((c02, dg2))
            m3 = b3.get((c03, dg3)); l4 = b4.get((c04, dg4))
            if not (l1 and l2 and m3 and l4):
                continue
            for r1 in l1:
                x13, x14 = r1[3], r1[4]
                for r2 in l2:
                    # 列3只剩行4一位、列4只剩行3一位：两位都在 [0,9] 的可行窗口
                    if not S - 18 - dg3 <= x13 + r2[3] <= S - dg3:
                        continue
                    if not S - 18 - dg4 <= x14 + r2[4] <= S - dg4:
                        continue
                    # 副对角线位和 + 列4位和联立 => 行3须满足 r3[1]-r3[4] = Δ
                    for r3 in m3.get(dg4 + x14 + r2[4] - c04 - dg2 - x13, ()):
                        # 列2、列1 同理的可行窗口
                        if not S - 18 - dg2 <= r1[2] + r3[2] <= S - dg2:
                            continue
                        if not S - 18 - dg1 <= r2[1] + r3[1] <= S - dg1:
                            continue
                        for r4 in l4:
                            # 四个列和反推行0的四个数字（列0/主对角线已由 c0,dg 保证）
                            d01 = S - dg1 - r2[1] - r3[1] - r4[1]
                            d02 = S - dg2 - r1[2] - r3[2] - r4[2]
                            d03 = S - dg3 - x13 - r2[3] - r4[3]
                            d04 = S - dg4 - x14 - r2[4] - r3[4]
                            if not (0 <= d01 <= 9 and 0 <= d02 <= 9 and 0 <= d03 <= 9 and 0 <= d04 <= 9):
                                continue
                            r0 = corner * 10000 + d01 * 1000 + d02 * 100 + d03 * 10 + d04
                            # 行0、副对角线、列1..4 都须在素数表（行1..4/列0/主对角线已保证）
                            if (r0 in pset
                                    and c04 * 10000 + r3[1] * 1000 + dg2 * 100 + x13 * 10 + d04 in pset
                                    and d01 * 10000 + r1[1] * 1000 + r2[1] * 100 + r3[1] * 10 + r4[1] in pset
                                    and d02 * 10000 + r1[2] * 1000 + r2[2] * 100 + r3[2] * 10 + r4[2] in pset
                                    and d03 * 10000 + x13 * 1000 + r2[3] * 100 + r3[3] * 10 + r4[3] in pset
                                    and d04 * 10000 + x14 * 1000 + r2[4] * 100 + r3[4] * 10 + r4[4] in pset):
                                ans.append('\n'.join([str(r0)] + [''.join(map(str, t)) for t in (r1, r2, r3, r4)]))

    ans.sort()  # 等长的 25 位串按字典序 = 按 25 位数大小
    print('\n\n'.join(ans) if ans else 'NONE')


if __name__ == "__main__":
    solve()
