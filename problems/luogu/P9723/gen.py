#!/usr/bin/env python3
"""P9723 [EC Final 2022] Chinese Checker 随机数据生成器（输出到 stdout）。

格式（与题面一致）：

    第一行 T
    每个测试点：第一行 n，随后 n 行 "行号 列号"

用法：

    python3 gen.py              # 用计数器在若干固定种子间轮换，保证连跑多次数据不同
    python3 gen.py <seed>       # 指定种子
    DUPAI_SEED=<seed> python3 gen.py

注意：brute.cpp 是按题面逐字枚举 pivot、并用 set 收集终局的暴力，
所以 n 必须开得很小（<= 8），否则对拍会超时。生成器只产出小数据。
"""
import os
import random
import sys

# 17 行的格子数（从上到下）
ROWS = [1, 2, 3, 4, 13, 12, 11, 10, 9, 10, 11, 12, 13, 4, 3, 2, 1]
ALL_CELLS = [(r, c) for r in range(1, 18) for c in range(1, ROWS[r - 1] + 1)]
COUNT_PATH = "/tmp/P9723-gen-count"

MAX_N = 8        # 暴力能跑完的上限
MAX_T = 20


def top_triangle():
    """棋盘上方的小三角形：行 1..4。"""
    return [(r, c) for r in range(1, 5) for c in range(1, ROWS[r - 1] + 1)]


def row_cells(r):
    """某一行的全部格子。"""
    return [(r, c) for c in range(1, ROWS[r - 1] + 1)]


def mid_row():
    """正中间那一行（13 格）。"""
    return row_cells(9)


def line_cells():
    """最宽的那一行（13 格），容易形成连锁跳跃。"""
    return row_cells(5)


def sample(k, cells, rnd):
    k = min(k, len(cells))
    return rnd.sample(cells, k)


def gen_case(rnd, mode):
    if mode == 0:                       # 极小数据，方便肉眼核对
        cells = sample(rnd.randint(1, 2), ALL_CELLS, rnd)
    elif mode == 1:                     # 一般随机小数据
        cells = sample(rnd.randint(3, MAX_N), ALL_CELLS, rnd)
    elif mode == 2:                     # 顶部小三角形
        cells = sample(rnd.randint(1, min(MAX_N, 10)), top_triangle(), rnd)
    elif mode == 3:                     # 中间一行
        cells = sample(rnd.randint(2, MAX_N), mid_row(), rnd)
    elif mode == 4:                     # 同一斜线 / 同一行上的密集棋子
        cells = sample(rnd.randint(2, MAX_N), line_cells(), rnd)
    elif mode == 5:                     # 极端：n = 1
        cells = [rnd.choice(ALL_CELLS)]
    else:                               # 全盘随机但 n 很小
        cells = sample(MAX_N, ALL_CELLS, rnd)
    rnd.shuffle(cells)
    return cells


def gen(seed):
    rnd = random.Random(seed)
    T = rnd.randint(1, MAX_T)
    out = [str(T)]
    for _ in range(T):
        cells = gen_case(rnd, rnd.randrange(7))
        out.append(str(len(cells)))
        for r, c in cells:
            out.append("%d %d" % (r, c))
    sys.stdout.write("\n".join(out) + "\n")


def main():
    if len(sys.argv) > 1:
        seed = int(sys.argv[1])
    elif "DUPAI_SEED" in os.environ:
        seed = int(os.environ["DUPAI_SEED"])
    else:
        # 没有显式给种子时，用一个计数器让连续多次运行产生不同数据
        # （对拍脚本会连着跑 gen.py 8 次，这样 8 组数据互不相同）。
        n = 0
        try:
            with open(COUNT_PATH) as f:
                n = int(f.read().strip() or "0")
        except (OSError, ValueError):
            n = 0
        try:
            with open(COUNT_PATH, "w") as f:
                f.write(str(n + 1))
        except OSError:
            pass
        seed = 972300 + n

    gen(seed)


if __name__ == "__main__":
    main()
