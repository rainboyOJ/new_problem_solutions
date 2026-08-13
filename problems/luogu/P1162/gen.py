#!/usr/bin/env python3
"""生成 P1162 小数据：n*n 方阵，1 构成一个矩形闭合圈，圈内至少一个 0，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(3, 30)

    # 闭合圈取一个严格的矩形边框，四边都离矩阵边界至少 1 格，
    # 保证圈外 0 都能走到边界、圈内 0 都被 1 围住。
    top = random.randint(1, n - 2)
    bottom = random.randint(top + 1, n - 1)
    left = random.randint(1, n - 2)
    right = random.randint(left + 1, n - 1)

    g = [[0] * (n + 1) for _ in range(n + 1)]
    for j in range(left, right + 1):
        g[top][j] = 1
        g[bottom][j] = 1
    for i in range(top, bottom + 1):
        g[i][left] = 1
        g[i][right] = 1

    # 在闭合圈外部稀疏撒一些额外的 1，让圈外 0 区域更丰富（不改变圈内性质）。
    extra = random.randint(0, n * n // 10)
    for _ in range(extra):
        i = random.randint(1, n)
        j = random.randint(1, n)
        if i < top or i > bottom or j < left or j > right:
            g[i][j] = 1

    print(n)
    for i in range(1, n + 1):
        print(" ".join(str(g[i][j]) for j in range(1, n + 1)))


if __name__ == "__main__":
    main()
