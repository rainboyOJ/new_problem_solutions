#!/usr/bin/env python3
"""生成 20027 聚会 的随机小数据，供对拍使用。

- n 控制在 2..5，保证 brute.cpp 枚举 O(n^2) 候选点很快。
- x_i 在 1..8，v_i 在 1..5，保证答案是有意义的浮点数。
"""
import random
import sys

random.seed(int(sys.argv[1]) if len(sys.argv) > 1 else None)

n = random.randint(2, 5)
xs = [random.randint(1, 8) for _ in range(n)]
vs = [random.randint(1, 5) for _ in range(n)]
print(n)
print(" ".join(map(str, xs)))
print(" ".join(map(str, vs)))
