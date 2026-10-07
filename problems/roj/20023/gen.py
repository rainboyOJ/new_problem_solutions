#!/usr/bin/env python3
"""gen.py：T3 琴(instrument) 随机数据生成器。

生成小数据，供 brute.cpp 与 main.cpp 对拍：
- 难度 a_i 随机取 1..50
- 询问区间 [l, r] 随机生成，保证 l <= r

duipai.py 会把种子通过环境变量 DUPAI_SEED 传入，无种子时随机。
"""
import os
import random

seed = os.environ.get("DUPAI_SEED")
if seed is not None:
    random.seed(int(seed))
else:
    random.seed()

n = random.randint(1, 30)
print(n)
print(" ".join(str(random.randint(1, 50)) for _ in range(n)))

m = random.randint(1, 30)
print(m)
for _ in range(m):
    l = random.randint(1, n)
    r = random.randint(1, n)
    if l > r:
        l, r = r, l
    print(l, r)
