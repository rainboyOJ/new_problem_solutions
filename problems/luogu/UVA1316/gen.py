#!/usr/bin/env python3
"""生成 UVA1316 的数据：无输入，stdout 就是一组数据。

本题是多组输入格式：每组先是 n，接着 n 行 "利润 截止日期"，读到 EOF 为止。
用法:
    gen.py              小数据，供 duipai.py 对拍（n 很小，brute 能枚举子集）
    gen.py <n上限>      指定单组规模上限
"""

import sys

from cyaron import IO, randint

max_n = int(sys.argv[1]) if len(sys.argv) > 1 else 8

io = IO(input_file=sys.stdout, disable_output=True)

# 1 到 3 组数据，覆盖单组与多组两种输入形态
group_count = randint(1, 3)

for _ in range(group_count):
    n = randint(1, max_n)
    io.input_writeln(n)
    for _ in range(n):
        p = randint(1, 20)   # 利润
        # 截止日期刻意取很小的范围，制造"位置紧张、必须反悔/放弃"的情形
        d = randint(1, max(1, min(n, 5)))
        io.input_writeln(p, d)
