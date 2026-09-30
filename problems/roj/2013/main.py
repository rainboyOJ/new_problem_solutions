#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:55
# update_at: 2026-10-01 03:13

import sys
from functools import cache
from itertools import product

WHEEL = 4       # 指针只有四种位置：0 = 12 点，1 = 3 点，2 = 6 点，3 = 9 点
FIELD = 0b11    # 每个时钟用一个两位字段存指针位置，取值 0..3
SHIFT = [5 * i for i in range(9)]       # 第 i 只钟的状态在状态整数中的起始位
UNIT = [1 << shift for shift in SHIFT]  # 把某只钟加 1（顺时针转 90 度）对应的加数
LOW = sum(FIELD << shift for shift in SHIFT)    # 九个位置字段的掩码：结果全为 0 即是大功告成

# 九种移动各自影响的时钟下标，顺序与题面表格一致：1 ABDE, 2 ABC, 3 BCEF, 4 ADG,
# 5 BDEFH, 6 CFI, 7 DEGH, 8 GHI, 9 EFHI
GROUP = [(0, 1, 3, 4), (0, 1, 2), (1, 2, 4, 5), (0, 3, 6), (1, 3, 4, 5, 7),
         (2, 5, 8), (3, 4, 6, 7), (6, 7, 8), (4, 5, 7, 8)]
# 施加一次第 i 种移动，等于给受影响的每只钟各加 1（指针顺时针转 90 度）
STEP = [sum(UNIT[i] for i in g) for g in GROUP]


@cache
def plan(state: int) -> tuple[int, ...]:
    """求把 state 拨成九个 12 点所需的次数向量 c：c[i] 是移动 i+1 要做几次。

    时钟只有 4 种状态，移动 i 做 4 次等于没做，所以 c[i] 只需枚举 0..3，共 4^9 个候选。
    设影响矩阵 V（V[i][m] = 1 表示移动 m 拨动第 i 只钟），则 det(V) = 5 是奇数，
    V 在模 4 下可逆，所以候选与结果状态一一对应（枚举验证：4^9 个候选恰好得到 4^9 个
    互不相同的状态）。**每个初态恰有一个合法次数向量**，题面「多种方案取数字拼接最小」
    永远不会触发，因此取第一个可行解即可，长度和字典序都不必比较。

    状态里每只钟预留 5 位，而它最多被 5 种移动碰到（每种最多 3 次，和不超过 15），
    相加不会进位串到相邻字段；于是求和后只看 LOW 就能判断九只钟是否同时指向 12 点。
    """
    return next((c for c in product(range(WHEEL), repeat=len(GROUP))
                 if (state + sum(k * s for k, s in zip(c, STEP))) & LOW == 0), ())


def solve() -> None:
    times = map(int, sys.stdin.buffer.read().split())
    # 12 点记为 0，于是初始状态 = 时间 / 3 mod 4；把九个时钟拼进一个整数
    state = sum((t // 3 % WHEEL) << shift for t, shift in zip(times, SHIFT))
    print(' '.join(str(move) for move, k in enumerate(plan(state), 1) for _ in range(k)))


if __name__ == "__main__":
    solve()
