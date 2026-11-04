#!/usr/bin/env python3
"""1398C 造数据：无输入，stdout 就是一组数据。

用法：gen.py [n]
不给 n 就随机小规模，方便对拍。
"""
import sys

from cyaron import randint, String

n = int(sys.argv[1]) if len(sys.argv) > 1 else randint(1, 12)

kind = randint(0, 3)
if kind == 0:
    s = String.random(n, charset="0123456789")
elif kind == 1:
    s = "0" * n                      # 全是 0：前缀和一路下降，答案 0
elif kind == 2:
    s = "9" * n                      # 全是 9：前缀和一路上升，答案 0
elif kind == 3:
    s = "1" * n                      # 全是 1：所有子段都合法，答案 n(n+1)/2
else:
    s = String.random(n, charset="01")   # 前缀和频繁相等，专压计数

print(1)
print(n)
print(s)
