#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# gen.py：E. Tree 对拍小数据生成器。
# 每组数据：T=1，n <= 12，k <= 8，a_i ∈ {0,1,2}，随机树（第 i 个点随机挂到 1..i-1 上）。
# 生成多组独立测试（每组单独一行 T=1），便于一次对拍多组。
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
rng = random.Random(seed)

T = 1
print(T)
n = rng.randint(1, 12)
k = rng.randint(1, 8)
print(n, k)
a = [0] + [rng.randint(0, 2) for _ in range(n)]
print(" ".join(map(str, a[1:])))
for i in range(2, n + 1):
    u = rng.randint(1, i - 1)
    print(u, i)