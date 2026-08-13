#!/usr/bin/env python3
"""P1101 单词方阵随机数据生成器。

生成 n x n 字母方阵：随机埋入少量 yizhong 单词（随机起点 + 随机方向），
其余位置填随机小写字母，用于 main.cpp 与 main.py 的对拍验证。
"""

import random
import sys


def main():
    random.seed()
    n = random.randint(7, 20)
    grid = [
        [random.choice("abcdefghijklmnopqrstuvwxyz") for _ in range(n)]
        for _ in range(n)
    ]

    word = "yizhong"
    directions = [
        (dx, dy)
        for dx in (-1, 0, 1)
        for dy in (-1, 0, 1)
        if (dx, dy) != (0, 0)
    ]

    # 随机埋入 1~3 个单词，保证对拍数据有实际匹配
    for _ in range(random.randint(1, 3)):
        dx, dy = random.choice(directions)
        x = random.randint(0, n - 1)
        y = random.randint(0, n - 1)
        end_x = x + dx * (len(word) - 1)
        end_y = y + dy * (len(word) - 1)
        if not (0 <= end_x < n and 0 <= end_y < n):
            continue
        for step, ch in enumerate(word):
            grid[x + dx * step][y + dy * step] = ch

    print(n)
    for row in grid:
        print("".join(row))


if __name__ == "__main__":
    sys.exit(main())
