#!/usr/bin/env python3
# gen.py：「区间最大和」随机小数据生成器，用于和 brute.cpp 对拍。
# 用法：python3 gen.py <seed> > t.in

import random
import sys

seed = int(sys.argv[1])
random.seed(seed)

n = random.randint(1, 30)                 # 小 n：brute.cpp 的 O(NQ) 也扛得住
arr = [random.randint(1, 20) for _ in range(n)]
total = sum(arr)
q = random.randint(1, 20)

print(n, q)
print(*arr)
for _ in range(q):
    print(random.randint(0, total))       # T 不超过总和，和题面一致
