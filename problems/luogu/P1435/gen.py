#!/usr/bin/env python3
# 对拍数据生成器：输出一行长度不超过 10 的随机字符串（大小写字母 + 数字）。
# 保持小规模，保证 brute.cpp 的指数级搜索能在时限内跑完。
import random
import string

n = random.randint(1, 10)
chars = string.ascii_letters + string.digits
print(''.join(random.choice(chars) for _ in range(n)))
