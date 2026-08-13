#!/usr/bin/env python3
"""生成 P1596 小数据：n,m<=30 的随机 W/. 网格，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 30)
    # 一半概率生成约一半水格的密网格，另一半只生成约 1/12 水格的疏网格，
    # 让对拍同时覆盖"水塘多"和"水塘少"两种形态。
    dense = random.randint(0, 1) == 0
    chars = "W." if dense else "W............"
    print(n, m)
    for _ in range(n):
        print("".join(random.choice(chars) for _ in range(m)))


if __name__ == "__main__":
    main()
