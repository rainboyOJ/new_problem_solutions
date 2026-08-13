#!/usr/bin/env python3
"""生成 P1605 随机小迷宫：n,m<=10 配障碍。

障碍密度随网格面积自适应：网格越大障碍越多，
保证简单路径枚举规模适合回溯计数验证与对拍（最大约 10 万条量级）。
"""
import random

random.seed()


def main():
    n = random.randint(1, 10)
    m = random.randint(1, 10)
    sx = random.randint(1, n)
    sy = random.randint(1, m)
    fx = random.randint(1, n)
    fy = random.randint(1, m)

    area = n * m
    if area <= 16:
        frac = random.uniform(0.05, 0.3)
    elif area <= 40:
        frac = random.uniform(0.25, 0.4)
    else:
        frac = random.uniform(0.35, 0.5)

    cells = [(x, y) for x in range(1, n + 1) for y in range(1, m + 1)]
    cells.remove((sx, sy))  # 题面保证起点没有障碍
    random.shuffle(cells)
    t = min(len(cells), max(1, int(area * frac)))
    obstacles = cells[:t]

    print(n, m, t)
    print(sx, sy, fx, fy)
    for x, y in obstacles:
        print(x, y)


if __name__ == "__main__":
    main()
