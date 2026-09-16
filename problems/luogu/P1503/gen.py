#!/usr/bin/env python3
"""P1503 随机数据生成器：生成 n,m 规模内的随机操作序列。"""
import random
import sys


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else random.randint(1, 10)
    m = int(sys.argv[2]) if len(sys.argv) > 2 else random.randint(1, 20)
    random.seed()

    ops = []      # 已摧毁的房子，模拟栈
    lines = [f"{n} {m}"]
    for _ in range(m):
        r = random.randint(1, 10)
        if r <= 4 or not ops:          # D
            x = random.randint(1, n)
            lines.append(f"D {x}")
            ops.append(x)
        elif r <= 6:                   # R
            lines.append("R")
            ops.pop()
        else:                          # Q
            x = random.randint(1, n)
            lines.append(f"Q {x}")
    print("\n".join(lines))


if __name__ == "__main__":
    main()
