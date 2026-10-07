#!/usr/bin/env python3
"""生成 20026 非递减字符串 的随机小数据，供对拍使用。

- n 控制在 1..15，保证 brute.cpp 的 2^n 枚举可以秒出。
- 字符随机取 A / B。
"""
import random
import sys

random.seed(int(sys.argv[1]) if len(sys.argv) > 1 else None)

n = random.randint(1, 15)
s = "".join(random.choice("AB") for _ in range(n))
print(s)
