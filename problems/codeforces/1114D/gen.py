#!/usr/bin/env python3
import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 本题只有一组数据：第一行 n，第二行 n 个颜色。
# 生成器无输入、stdout 就是一组测试数据（duipai.py 的约定）。

mode = randint(1, 6)

if mode == 1:
    # 边界：只有一个块
    n = 1
    colors = [randint(1, 3)]
elif mode == 2:
    # 边界：全部同色
    n = randint(1, 12)
    colors = [randint(1, 3)] * n
elif mode == 3:
    # 最容易退化的情况：两色交替
    n = randint(1, 12)
    x, y = randint(1, 3), 0
    while y == 0 or y == x:
        y = randint(1, 3)
    colors = [(x if i % 2 == 0 else y) for i in range(n)]
elif mode == 4:
    # 颜色种类很少，相邻大量重复
    n = randint(1, 12)
    colors = [randint(1, 2) for _ in range(n)]
elif mode == 5:
    # 小规模随机，颜色种类多一些
    n = randint(1, 10)
    colors = [randint(1, 4) for _ in range(n)]
else:
    # 接近完全互不相同的随机
    n = randint(1, 9)
    colors = [randint(1, 6) for _ in range(n)]

io.input_writeln(n)
io.input_writeln(colors)
