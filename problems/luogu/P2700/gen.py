#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 21:40
# update_at: 2026-10-21 21:40
"""随机生成 P2700 的小数据，给 brute.cpp 当对拍输入。

规模压在 n <= 10，因为 brute.cpp 要枚举 2^(n-1) 种删边方案。
刻意覆盖的边界：
  - n = 2 的最小规模、K = N 全城皆敌、K = 2 只看一对敌城；
  - 边权含 0（免费公路，破坏它不花钱）与较大值（1e6 级别，决定取舍）；
  - 树形随机（完全随机连边）与链形（退化成一维，任意两点间只有一条路）。
"""

import random
import sys


def main() -> None:
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
    random.seed(seed)

    n = random.randint(2, 10)
    k = random.choice([2, 2, 3, n, random.randint(2, n)])
    k = min(k, n)  # 防御性截断：K 不能超过 N

    # 树的形状：链形更容易出现「一条必经之路」，随机形则更分散
    shape = random.choice(["chain", "random"])
    # 边权档次：全 0、小值、大值、混合（含 0 与 1e6 两端）
    weight_mode = random.choice(["zero", "small", "large", "mixed"])

    def make_weight() -> int:
        if weight_mode == "zero":
            return 0
        if weight_mode == "small":
            return random.randint(0, 10)
        if weight_mode == "large":
            return random.choice([0, 10**6, random.randint(5 * 10**5, 10**6)])
        return random.choice([0, 0, random.randint(1, 10), random.randint(1, 10**6)])

    lines: list[str] = []
    for city in range(1, n):
        if shape == "chain":
            other = city - 1  # 每个新城市接到前一个城市，形成一条链
        else:
            other = random.randint(0, city - 1)
        lines.append(f"{other} {city} {make_weight()}")

    enemies = random.sample(range(n), k)  # 随机挑 K 个不同的敌城
    print(n, k)
    print(*enemies)
    print("\n".join(lines))


if __name__ == "__main__":
    main()
