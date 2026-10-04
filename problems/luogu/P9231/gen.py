#!/usr/bin/env python3
"""P9231 随机数据生成器：输出一行 "L R"。

用法：
    python3 gen.py           # 使用固定种子 SEED，结果可复现
    python3 gen.py <seed>    # 指定种子，用于多样本对拍

数据范围贴合题面约束 1 <= L <= R <= 1e9。
为了让暴力解 brute.cpp（对每个 x 枚举因子，O(sqrt(x))）也能在时限内跑完，
生成器把区间长度控制在 2e5 以内：既覆盖 1 附近的小数据、几万的稠密数据，
也包含贴近 1e9 的窄窗口，用来检查前缀计数公式在大数值下不会算错或溢出。
"""
import random
import sys

SEED = 20231003  # 默认固定种子

TINY_MAX = 3000        # 小数据：暴力最容易观察
MID_MAX = 200000       # 中等数据：让暴力跑满区间
LARGE_CENTER = 10 ** 9  # 大数值：贴近上界
LARGE_WINDOW = 1200    # 窄窗口长度，保证 brute 在 20s 内完成


def tiny_case():
    """小数据用例：L、R 都很小，方便逐个数验证。"""
    r = random.randint(1, TINY_MAX)
    l = random.randint(1, r)
    return l, r


def mid_case():
    """中等数据用例：区间长度可达十几万，主要检验计数公式的规模正确性。"""
    r = random.randint(TINY_MAX, MID_MAX)
    if random.random() < 0.5:
        l = random.randint(1, r)          # 大区间
    else:
        l = random.randint(max(1, r - 50), r)  # 贴着 R 的窄区间
    return l, r


def edge_case():
    """边界用例：单点区间、1 与 2 附近、平方数前后、4 的倍数附近。"""
    picks = [1, 2, 3, 4, 5, 7, 8, 9, 15, 16, 17, 24, 25, 36, 49, 99, 100,
             255, 256, 999, 1000, 1023, 1024, 1025]
    r = random.choice(picks)
    if random.random() < 0.4:
        l = r                    # L == R 的单点区间最容易暴露边界错误
    else:
        l = random.randint(1, r)
    return l, r


def large_case():
    """大数值用例：R 贴近 1e9，区间很窄，让暴力也能算。"""
    r = LARGE_CENTER - random.randint(0, 5000)
    length = random.randint(1, LARGE_WINDOW)
    l = r - length + 1
    return l, r


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed(SEED)

    kind = random.random()
    if kind < 0.45:
        l, r = tiny_case()
    elif kind < 0.75:
        l, r = mid_case()
    elif kind < 0.9:
        l, r = edge_case()
    else:
        l, r = large_case()

    print(l, r)


if __name__ == "__main__":
    main()
