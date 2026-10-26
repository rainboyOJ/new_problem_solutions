#!/usr/bin/env python3
# gen.py: 对拍数据生成器, 无输入, stdout 即一组数据.
# 规模用环境变量 F / V 控制; 默认小规模随机, 便于对拍.
import os
import sys
from cyaron import IO, Vector
from cyaron.vector import VectorRandomMode

F = int(os.environ.get("F", "8"))
V = int(os.environ.get("V", "10"))

io = IO(input_file=sys.stdout, disable_output=True)
io.input_writeln(F, V)
for _ in range(F):
    # Vector.random 返回 list[list[int]], 单维向量每个元素形如 [x].
    row = Vector.random(V, [(-50, 50)], VectorRandomMode.repeatable)
    io.input_writeln([x[0] for x in row])
