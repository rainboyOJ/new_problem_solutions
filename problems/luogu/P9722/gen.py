#!/usr/bin/env python3
"""P9722 [EC Final 2022] Rectangle 随机数据生成器（输出到 stdout）。

坐标上界固定 M = 1e9；n 取小值（<= 8）以便 brute.cpp 的解掩码足够。
为了压到各种边界，坐标混合以下几种取法：
  * 极小簇 1..7
  * 边界值 {1, 2, M-1, M}
  * 全范围 [1, M] 随机
  * x 两端贴边、y 全范围（或反之）
"""
import random
import sys

M = 10 ** 9


def pick_pair(low, high, extra):
    """从 [low,high] 与 extra 里取两个不同整数并升序返回。"""
    while True:
        a = random.choice(extra) if (extra and random.random() < 0.6) \
            else random.randint(low, high)
        b = random.choice(extra) if (extra and random.random() < 0.6) \
            else random.randint(low, high)
        if a == b:
            continue
        if a > b:
            a, b = b, a
        return a, b


def one_rect(mode):
    tiny = [1, 2, 3, 4, 5, 6, 7]
    edge = [1, 2, M - 1, M]
    if mode == 0:                     # 极小簇，容易重叠
        x1, x2 = pick_pair(1, 7, None)
        y1, y2 = pick_pair(1, 7, None)
    elif mode == 1:                   # 只落在坐标边界附近
        x1, x2 = pick_pair(1, M, edge)
        y1, y2 = pick_pair(1, M, edge)
    elif mode == 2:                   # 全范围随机
        x1, x2 = pick_pair(1, M, None)
        y1, y2 = pick_pair(1, M, None)
    elif mode == 3:                   # x 贴边，y 全范围
        x1, x2 = pick_pair(1, M, edge)
        y1, y2 = pick_pair(1, M, None)
    elif mode == 4:                   # y 贴边，x 全范围
        x1, x2 = pick_pair(1, M, None)
        y1, y2 = pick_pair(1, M, edge)
    else:                             # 混合：一端极小，一端极大
        x1 = random.randint(1, 5)
        x2 = random.randint(M - 4, M)
        y1 = random.randint(1, 5)
        y2 = random.randint(M - 4, M)
        x1, x2 = (x1, x2) if x1 < x2 else (x2, x1)
        y1, y2 = (y1, y2) if y1 < y2 else (y2, y1)
    if x1 == x2:
        x2 = x1 + 1
    if y1 == y2:
        y2 = y1 + 1
    return x1, y1, x2, y2


def main():
    random.seed()
    T = random.randint(1, 4)
    out = [str(T)]
    for _ in range(T):
        n = random.randint(1, 8)
        out.append(str(n))
        base = random.randint(0, 4)
        for i in range(n):
            mode = (base + i) % 6 if random.random() < 0.7 else random.randint(0, 5)
            x1, y1, x2, y2 = one_rect(mode)
            out.append("%d %d %d %d" % (x1, y1, x2, y2))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
