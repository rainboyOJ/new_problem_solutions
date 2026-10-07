#!/usr/bin/env python3
# 小数据随机生成器：n <= 30，x,y <= 10，用于 main.cpp 与 brute.cpp 对拍。
# 用法：gen.py [seed]
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else random.randrange(1 << 30)
random.seed(seed)

n = random.randint(2, 30)
total = n * (n - 1) // 2
k = random.randint(1, total)
print(n, k)
for _ in range(n):
    print(random.randint(1, 10), random.randint(1, 10))