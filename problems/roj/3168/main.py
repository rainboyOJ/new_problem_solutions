#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 22:31
# update_at: 2026-10-01 22:38

import sys

MOD = 11380  # 题面里的“当前年份”，答案对它取余


def build_le(L1: int, L2: int, L3: int, D: int) -> list[list[list[list[int]]]]:
    """le[d][i][j][k]：深度不超过 d、含 i 对 {}、j 对 []、k 对 () 的 SS 串数。

    非空串唯一拆成「首原子 + 剩余部分」：首原子 = 第一个字符到它匹配的右括号。
    首原子内层深度必须 ≤ d-1（包裹加一层），剩余部分仍是 ≤ d 的 SS 串。
    """
    le = [[[[0] * (L3 + 1) for _ in range(L2 + 1)] for _ in range(L1 + 1)] for _ in range(D + 1)]
    for d in range(D + 1):
        le[d][0][0][0] = 1  # 空串深度为 0，对任何上界 d 都合法

    for d in range(1, D + 1):
        prev, cur = le[d - 1], le[d]
        for i in range(L1 + 1):
            for j in range(L2 + 1):
                for k in range(L3 + 1):
                    if i == j == k == 0:
                        continue  # 空串，上面已置 1
                    # 首原子 (A)：内层 A 只能含 ()，故内层用 prev[0][0][a]，剩余串拿走 k-1-a 对 ()
                    t = sum(cur[i][j][k - 1 - a] * prev[0][0][a] for a in range(k))
                    # 首原子 [A]：内层 A 不含 {}，故内层用 prev[0][a][b]，剩余的 {} 全给剩余串
                    t += sum(prev[0][a][b] * cur[i][j - 1 - a][k - b]
                             for a in range(j) for b in range(k + 1))
                    # 首原子 {A}：内层 A 无字符限制，三种括号都要在内层与剩余串间分配
                    t += sum(prev[a][b][c] * cur[i - 1 - a][j - b][k - c]
                             for a in range(i) for b in range(j + 1) for c in range(k + 1))
                    cur[i][j][k] = t % MOD
    return le


def solve() -> None:
    L1, L2, L3, D = map(int, sys.stdin.buffer.read().split())

    total = L1 + L2 + L3
    if D > total:
        print(0)  # 每层嵌套至少吃掉一对括号，深度不可能超过括号总对数
        return

    le = build_le(L1, L2, L3, D)
    # 深度恰为 D = 深度不超过 D 减去深度不超过 D-1；D = 0 时只有空串，无前一档
    ans = le[D][L1][L2][L3] - le[D - 1][L1][L2][L3] if D else le[0][L1][L2][L3]
    print(ans % MOD)


if __name__ == "__main__":
    solve()
