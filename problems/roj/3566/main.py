#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:05
# update_at: 2026-10-02 08:05

import sys
from functools import cache

DIGIT_COST = (6, 2, 5, 5, 4, 5, 6, 3, 7, 6)  # 数字 0-9 各自所需火柴根数


@cache
def cost(x: int) -> int:
    """整数 x 拼成所需火柴根数（按十进制逐位查表，0 本身要 6 根）。"""
    total = 0
    while x:
        total += DIGIT_COST[x % 10]
        x //= 10
    return total or DIGIT_COST[0]


def count_equations(n: int) -> int:
    """数出恰好用完 n 根火柴的 A+B=C 等式个数，A、B 有序、全部火柴必须用完。"""
    k = n - 4  # “+”和“=”固定各占 2 根，剩下 k 根分给 A、B、C 三个数
    if k < 0:
        return 0

    # 关键观察：每位数字至少 2 根（1 最省），且 C=A+B 的位数不小于 A、B 的位数，
    # 所以 (位数A, 位数B) 必须满足 2*(位数A+位数B+max(位数A,位数B)) <= k；
    # 反解出单个数最多 (k-2)//4 位（n<=24 时为 4 位），按位数分桶后只枚举可行桶对。
    d_max = max((k - 2) // 4, 1)  # k < 6 时没有任何合法等式，留 1 位空跑即可
    groups: list[list[int]] = [[] for _ in range(d_max + 1)]
    for x in range(10 ** d_max):
        groups[len(str(x))].append(x)

    ans = 0
    for da in range(1, d_max + 1):
        for db in range(1, d_max + 1):
            if 2 * (da + db + max(da, db)) > k:
                continue  # 该位数组合的火柴下界已超预算，桶内不可能有解
            for a in groups[da]:
                ca = cost(a)
                if ca > k - 4:  # cost(B)、cost(C) 各至少还要 2 根
                    continue
                for b in groups[db]:
                    cb = cost(b)
                    if ca + cb <= k - 2:  # 剩余根数容得下 cost(C) 至少 2 根
                        ans += ca + cb + cost(a + b) == k  # 余额恰好等于 C 的根数
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    print(count_equations(n))


if __name__ == "__main__":
    solve()
