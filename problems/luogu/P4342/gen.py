#!/usr/bin/env python3
"""P4342 随机数据生成器：生成环形多边形，重点覆盖负数、乘法、断点字典序。

用法：python3 gen.py [n] [seed]
默认 n = 8，seed 随机。输出两行：n，然后 n 组 (运算符, 顶点权值)。
"""
import random
import sys


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 8
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else random.randrange(1 << 30)
    random.seed(seed)
    n = max(3, min(n, 50))
    # 用小值域 + 负数 + 0，保证乘法产生正负交替、便于触发「负负得正」
    vals = [random.randint(-8, 8) for _ in range(n)]
    ops = [random.choice('tx') for _ in range(n)]
    print(n)
    parts = []
    for i in range(n):
        parts.append(ops[i])
        parts.append(str(vals[i]))
    print(' '.join(parts))


if __name__ == '__main__':
    main()
