#!/usr/bin/env python3
# gen.py：为 T4 棋(Chess) 生成小数据随机测试（n <= 4，供暴力对拍）
# 用法：直接运行即可；duipai.py 会通过环境变量 DUPAI_SEED / DUPAI_CASE_ID 提供种子。
import os
import random
import sys

seed = int(os.environ.get("DUPAI_SEED", os.environ.get("DUPAI_CASE_ID", "0")))
if len(sys.argv) > 1:
    seed = int(sys.argv[1])
random.seed(seed)

# n 偏向 3、4，保证横/对角线三连出现的概率足够大
n = random.choice([1, 2, 3, 3, 4, 4, 4])
print(n)
for _ in range(3):
    print(" ".join(str(random.randint(-10**9, 10**9)) for _ in range(n)))