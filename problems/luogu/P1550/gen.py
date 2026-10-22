#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 10:20
# update_at: 2026-10-21 10:20
"""随机生成 P1550 的小数据，给 brute.cpp 当对拍输入。

规模压在 n <= 5，因为 brute.cpp 要枚举 2^n 个打井方案 × 2^(n(n-1)/2) 个选管方案。
刻意覆盖的边界：n = 1、W_i 极小、W_i 极大（此时全靠连水管更便宜）、
P_ij 全为 0（免费水管）、P_ij 远大于 W_i（此时打井更便宜）。
"""

import random
import sys


def main() -> None:
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
    random.seed(seed)

    n = random.choice([1, 1, 2, 2, 3, 3, 4, 4, 5, 5])
    # 打井代价的档次：极小 / 常规 / 极大，制造"打井划算"与"连管划算"两类情形
    well_range = random.choice([(1, 3), (1, 20), (1, 100), (1000, 100000)])

    print(n)
    for _ in range(n):
        print(random.randint(*well_range))

    # 管价档次：全 0、小值、大值
    pipe_mode = random.choice(["zero", "small", "big", "mixed"])
    pipe = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(i + 1, n):
            if pipe_mode == "zero":
                w = 0
            elif pipe_mode == "small":
                w = random.randint(0, 5)
            elif pipe_mode == "big":
                w = random.randint(500, 100000)
            else:
                w = random.choice([0, 0, random.randint(1, 20), random.randint(1, 100000)])
            pipe[i][j] = pipe[j][i] = w

    for i in range(n):
        print(*pipe[i])


if __name__ == "__main__":
    main()
