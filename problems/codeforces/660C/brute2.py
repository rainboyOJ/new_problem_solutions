#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-10 11:12
# update_at: 2026-11-10 11:35

import sys
from itertools import accumulate, combinations

data = iter(map(int, sys.stdin.read().split()))
n = next(data)
k = next(data)
a = [next(data) for _ in range(n)]

# 1. 0 的个数前缀和（半开区间）：p[i] 表示 a[0..i-1] 中 0 的数量
p = [0] + list(accumulate(x == 0 for x in a))

# 2. combinations(range(n + 1), 2) 天然生成所有 0 <= i < j <= n，对应半开区间 [i, j)
best_len, best_l, best_r = 0, 0, 0
for i, j in combinations(range(n + 1), 2):
    zeros = p[j] - p[i]
    length = j - i
    if zeros <= k and length > best_len:
        best_len, best_l, best_r = length, i, j

# 3. 翻转最优区间并输出
a[best_l:best_r] = [1] * best_len
print(best_len)
print(*a)
