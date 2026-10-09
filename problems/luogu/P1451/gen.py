#!/usr/bin/env python3
"""生成 P1451 的随机数据：n,m <= 100 的数字网格，规模适合暴力对拍。

按 DUPAI_SEED 定随机种子（对拍脚本会传进来），同一个种子能复现同一组合法数据。
除了普通随机网格，还刻意覆盖题目边界：只有一行、只有一列、单格、全 0、全非 0。
"""
import os
import random


def random_row(m, nonzero_prob):
    """生成一行：每一格以 nonzero_prob 的概率是细胞数字 '1'..'9'，否则是 '0'。"""
    cells = []
    for _ in range(m):
        if random.random() < nonzero_prob:
            cells.append(random.choice("123456789"))
        else:
            cells.append("0")
    return "".join(cells)


def random_grid(n, m):
    """生成普通随机网格：在 1/5、1/2、9/10 三种非 0 密度里随机挑一种。"""
    nonzero_prob = random.choice([0.2, 0.5, 0.9])
    return [random_row(m, nonzero_prob) for _ in range(n)]


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    case = random.randint(0, 7)

    if case == 0:  # 只有一行：上下方向的行边界全部触底
        n, m = 1, random.randint(1, 10)
        grid = random_grid(n, m)
    elif case == 1:  # 只有一列：左右方向的列边界全部触底
        n, m = random.randint(1, 10), 1
        grid = random_grid(n, m)
    elif case == 2:  # 单格
        n, m = 1, 1
        grid = random_grid(n, m)
    elif case == 3:  # 全 0：答案必然为 0
        n, m = random.randint(1, 20), random.randint(1, 20)
        grid = ["0" * m for _ in range(n)]
    elif case == 4:  # 全非 0：整个网格是一个细胞，答案必然为 1
        n, m = random.randint(1, 20), random.randint(1, 20)
        grid = [random_row(m, 1.0) for _ in range(n)]
    elif case == 5:  # 小网格：细胞碎、边界多，容易暴露计数错误
        n, m = random.randint(1, 5), random.randint(1, 5)
        grid = random_grid(n, m)
    else:  # 普通随机网格，含 0 与非 0
        n, m = random.randint(1, 100), random.randint(1, 100)
        grid = random_grid(n, m)

    print(n, m)
    for row in grid:
        print(row)


if __name__ == "__main__":
    main()
