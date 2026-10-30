#!/usr/bin/env python3
"""P3478 对拍数据生成器：无输入，stdout 就是一组数据。

默认产出小规模数据（brute.cpp 的 MAXN 是 505，所以默认 n <= 500）。
用 argv[1] 或环境变量 P3478_MAXN 可以把上限放大到 1e6，用来测主解性能。
形态上混合随机树、链、菊花和 n=1 的边界。
"""
import sys

from cyaron import Graph, randint

# brute.cpp 用 MAXN = 505 的静态数组，对拍时默认不超过 500
max_n = int(sys.argv[1] if len(sys.argv) > 1 else 500)

kind = randint(1, 10)
if kind == 1:
    n = 1                                    # 边界：单点树
elif kind == 2:
    n = randint(2, min(max_n, 3))            # 边界：极小规模
elif kind == 3:
    n = max_n                                # 边界：规模上限
else:
    n = randint(1, max_n)

# 形态：2/10 链（换根时子树大小变化最剧烈），1/10 菊花，其余随机树
shape = randint(1, 10)
if shape <= 2:
    tree = Graph.chain(n)
elif shape == 3:
    tree = Graph.flower(n)
else:
    tree = Graph.tree(n, chain=0.3, flower=0.2)

print(n)
for edge in tree.iterate_edges():
    print(edge.start, edge.end)
