#!/usr/bin/env python3
"""生成 U502676 的数据：无输入，stdout 就是一组数据。

用法:
    gen.py            小数据，供 duipai.py 对拍
    gen.py <n上限>    指定规模上限
    gen.py <n上限> <种子上限>

注意本题数组元素允许重复（样例里就有两个 3），所以必须用
VectorRandomMode.repeatable，默认的 unique 模式会在小值域时报错。
"""

import sys

from cyaron import IO, Vector, randint
from cyaron.vector import VectorRandomMode

max_n = int(sys.argv[1]) if len(sys.argv) > 1 else 60
max_v = int(sys.argv[2]) if len(sys.argv) > 2 else 20

io = IO(input_file=sys.stdout, disable_output=True)

n = randint(1, max_n)
m = randint(1, max_n)

# 一半概率用很小的值域：这样 k 更容易恰好卡在边界上，
# 能大量制造"整段无解"和"答案就在 l 处"这两种容易写错的询问。
if randint(1, 2) == 1:
    upper = randint(1, min(4, max_v))
else:
    upper = randint(1, max_v)

a = Vector.random(n, [(1, upper)], mode=VectorRandomMode.repeatable)
io.input_writeln(n, m)
io.input_writeln(a)

for _ in range(m):
    l = randint(1, n)
    r = randint(l, n)
    # k 在值域附近取，覆盖 a 中元素全大于 k、全不大于 k、部分大于 k 三种情况
    k = randint(1, upper + 2)
    io.input_writeln(l, r, k)
