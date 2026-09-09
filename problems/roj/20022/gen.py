#!/usr/bin/env python3
"""gen.py：随机小数据生成器（对拍用）。

- n <= 15，保证 2^n 枚举的暴力能在时限内跑完
- 收益混合小范围与大范围随机值，包含负数，覆盖 |a_i|, |b_i| <= 1e9 边界
- m 在 0..n 中随机，覆盖 m=0、m=n、名额用不满等边界
- 种子从环境变量 DUPAI_SEED 读取（duipai.py 约定）
"""
import os
import random

seed = int(os.environ.get("DUPAI_SEED", "0"))
random.seed(seed)

n = random.randint(1, 15)
m = random.randint(0, n)


def rand_val():
    r = random.random()
    if r < 0.3:
        return random.randint(-10, 10)        # 小范围，易出现 d <= 0 与 d > 0 混合
    if r < 0.6:
        return random.randint(-10**6, 10**6)  # 中范围
    return random.randint(-10**9, 10**9)      # 大范围（含负数）


a = [rand_val() for _ in range(n)]
b = [rand_val() for _ in range(n)]

print(n, m)
print(*a)
print(*b)
