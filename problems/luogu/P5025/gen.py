#!/usr/bin/env python3
"""P5025 [SNOI2017] 炸弹 随机数据生成器。

生成 n 个严格递增的坐标，并随机挑选几种爆炸半径分布，
覆盖「半径 0」「小半径链式引爆」「大半径整体连通」等边界。
"""

import random
import sys


def main():
    # 允许外部指定随机种子与规模，方便复现失败样例
    seed = None
    n = None
    for arg in sys.argv[1:]:
        if arg.startswith("--seed="):
            seed = int(arg.split("=", 1)[1])
        elif arg.startswith("--n="):
            n = int(arg.split("=", 1)[1])
    if seed is None:
        seed = random.randrange(1 << 30)
    random.seed(seed)
    if n is None:
        n = random.randint(1, 9)

    # 坐标严格递增：小规模时用稀疏大步长，也允许出现负坐标
    coords = []
    current = random.randint(-30, 10)
    for _ in range(n):
        coords.append(current)
        current += random.randint(1, random.choice([2, 5, 30]))

    # 每个炸弹的半径从四种形态里取，制造不同引爆链结构
    lines = [str(n)]
    for i in range(n):
        mode = random.randrange(4)
        if mode == 0:
            radius = 0
        elif mode == 1:
            # 刚好够不到邻近炸弹，形成孤立点
            radius = random.randint(0, 1)
        elif mode == 2:
            # 中等半径，容易形成链式引爆
            radius = random.randint(1, 10)
        else:
            # 大半径，一次引爆大量炸弹
            radius = random.randint(1, 120)
        lines.append(f"{coords[i]} {radius}")

    print("\n".join(lines))


if __name__ == "__main__":
    main()
