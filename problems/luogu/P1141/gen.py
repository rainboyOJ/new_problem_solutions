#!/usr/bin/env python3
"""为 P1141 01迷宫 生成对拍数据。

brute.cpp 对每个询问都单独 BFS 一次，复杂度 O(m*n^2)，
所以这里只生成小规模数据（n <= 12，m <= 30），保证暴力能在 2 秒内跑完。
覆盖的迷宫形态：n=1、全 0、全 1、棋盘交错、按行条纹、随机。
覆盖的询问形态：重复询问同一格、四个角落的边界下标、一般随机位置。
"""
import os
import random


def build_grid(n, kind):
    """按 kind 生成 n 行 n 列的 0/1 迷宫，返回字符串列表。"""
    if kind == "all_zero":
        return ["0" * n for _ in range(n)]
    if kind == "all_one":
        return ["1" * n for _ in range(n)]
    if kind == "chess":
        # 棋盘交错：每格和上下左右四邻数值都不同，整幅图是一个大连通块
        return ["".join(str((i + j) % 2) for j in range(n)) for i in range(n)]
    if kind == "stripe":
        # 按行交替：相邻两行数值不同，同一行内数值相同，横向走不动
        return [str(i % 2) * n for i in range(n)]
    return ["".join(random.choice("01") for _ in range(n)) for _ in range(n)]


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    kind = random.choice(
        ["random", "random", "random", "all_zero", "all_one", "chess", "stripe"]
    )
    n = random.randint(1, 12)
    m = random.randint(1, 30)
    if random.random() < 0.15:
        n = 1  # 小概率压到单格迷宫，专门测 n = 1

    grid = build_grid(n, kind)

    queries = []
    for _ in range(m):
        roll = random.random()
        if roll < 0.35:
            queries.append((1, 1))  # 重复询问同一格，考察答案是否稳定
        elif roll < 0.60:
            # 四个角落：下标 1 和 n 都取到，且始终落在合法范围内
            queries.append(random.choice([(1, 1), (1, n), (n, 1), (n, n)]))
        else:
            queries.append((random.randint(1, n), random.randint(1, n)))

    print(n, m)
    for row in grid:
        print(row)
    for x, y in queries:
        print(x, y)


if __name__ == "__main__":
    main()
