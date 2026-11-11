#!/usr/bin/env python3
import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍参数：x 在 2~10 之间，n 在 1~50 之间
x = randint(2, 9)
n = randint(1, 40)

io.input_writeln(n, x)
# 生成 1 到 x 的随机数组 a
a = [randint(1, x) for _ in range(n)]
io.input_writeln(a)
