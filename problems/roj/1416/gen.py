#!/usr/bin/env python3
"""gen.py：矩形覆盖计数的小数据生成器（对拍用，格式与 main.cpp / brute.cpp 一致）。

坐标范围压到 0..COORD，并刻意制造「点落在边界上」的情况：
很多点的 x 或 y 直接取自矩形的端点，用来检验半开区间 [l,r) x [d,u)
的判定有没有写错（右/上边界不算覆盖）。n、m 都控制在暴力能跑的范围。
"""

import random
import sys

COORD = 8  # 坐标上界，小到暴力 O(n*m) 能瞬间跑完


def main() -> None:
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    rng = random.Random(seed)

    n = rng.randint(1, 8)
    m = rng.randint(1, 8)

    rects = []
    for _ in range(n):
        l = rng.randint(0, COORD)
        r = rng.randint(l + 1, COORD + 1)  # 保证 l < r
        d = rng.randint(0, COORD)
        u = rng.randint(d + 1, COORD + 1)  # 保证 d < u
        rects.append((l, d, r, u))

    print(n, m)
    for l, d, r, u in rects:
        print(l, d, r, u)

    for _ in range(m):
        # 一半概率取矩形端点，专门打半开区间的边界
        if rng.random() < 0.5:
            l, d, r, u = rects[rng.randrange(n)]
            x = rng.choice((l, r))       # 左边界含，右边界不含
            y = rng.choice((d, u))       # 下边界含，上边界不含
        else:
            x = rng.randint(0, COORD + 1)
            y = rng.randint(0, COORD + 1)
        print(x, y)


if __name__ == "__main__":
    main()
