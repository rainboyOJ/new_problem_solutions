#!/usr/bin/env python3
# gen.py：为 P3509 生成小数据随机测试。
# 约束：1 <= k < n（n 很小，方便暴力对拍），m 很小，p 严格递增。

import random
import sys

seed = sys.argv[1] if len(sys.argv) > 1 else None
if seed is not None:
    random.seed(int(seed))

n = random.randint(2, 8)
k = random.randint(1, n - 1)
m = random.randint(1, 15)

# 生成严格递增的位置
positions = sorted(random.sample(range(1, 1000), n))

print(n, k, m)
print(" ".join(map(str, positions)))
