#!/usr/bin/env python3
"""
T641741 随机数据生成器
生成多测试用例的迷宫，包含 S、E、#、.
"""
import sys
import random

def gen_one(R, C):
    # 随机生成地图
    g = [['.' for _ in range(C)] for _ in range(R)]
    # 随机放置一些墙壁
    for i in range(R):
        for j in range(C):
            if random.random() < 0.2:
                g[i][j] = '#'
    # 随机放置 S 和 E
    empty = [(i, j) for i in range(R) for j in range(C) if g[i][j] == '.']
    if len(empty) < 2:
        return gen_one(R, C)
    sx, sy = random.choice(empty)
    g[sx][sy] = 'S'
    empty.remove((sx, sy))
    ex, ey = random.choice(empty)
    g[ex][ey] = 'E'
    return [''.join(row) for row in g]

def main():
    random.seed(42)
    T = random.randint(1, 10)
    out = [str(T)]
    for _ in range(T):
        R = random.randint(2, 20)
        C = random.randint(2, 20)
        out.append(f"{R} {C}")
        grid = gen_one(R, C)
        out.extend(grid)
    sys.stdout.write('\n'.join(out))

if __name__ == "__main__":
    main()