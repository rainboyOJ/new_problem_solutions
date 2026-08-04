#!/usr/bin/env python3
"""P2196 挖地雷 的随机小数据生成器（配合 brute.cpp 对拍，n 保持很小）。"""

import random


def main():
    random.seed()
    n = random.randint(1, 10)
    print(n)
    # 每个地窖的地雷数（1..300）
    print(" ".join(str(random.randint(1, 300)) for _ in range(n)))
    # 只输出 i < j 的连通关系；随机连边保证图是 DAG（编号天然拓扑序）
    for i in range(1, n):
        row = [str(1 if random.random() < 0.4 else 0) for _ in range(i + 1, n + 1)]
        print(" ".join(row))


if __name__ == "__main__":
    main()
