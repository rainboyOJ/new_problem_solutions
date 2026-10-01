import sys
from functools import reduce
from operator import mul

# g[d]：位集，d 经任意次变换能到达的数字个数（含 d 自身）
g = [1 << d for d in range(10)]
tok = sys.stdin.read().split()  # 全部读入并按空白切分（兼容 \r\n 行尾）
n, k = tok[0], int(tok[1])
for i in range(k):
    g[int(tok[2 + 2 * i])] |= 1 << int(tok[3 + 2 * i])
for m in range(10):  # Floyd 传递闭包：若 i->j 且 j 可达 d，则 i 可达 d
    for i in range(10):
        if g[i] >> m & 1:
            g[i] |= g[m]
# 答案 = 每一位可选数字个数之积（n 最大 30 位，乘积用 Python 大整数）
print(reduce(mul, (bin(g[int(c)]).count('1') for c in n)))
