#!/usr/bin/env python3
"""生成 P3147 对拍数据。

覆盖的边界与结构:
  - n 从最小 2 到较大规模(暴力 brute.cpp 只能承受小 n, 默认取小)
  - 值域: 全 1、全同值、随机 1..40、窄值域 1..k

用法:
  python3 gen.py            # 随机一组小数据, 用于与暴力对拍
  python3 gen.py 12         # 指定 n
环境变量:
  P3147_MAXV=3              # 限制值域上界 (1..MAXV), 默认按模式随机
"""
import os
import sys

from cyaron import IO, randint

MAX_A = 40  # 题面: 每个数在 1..40


def build(n):
    """返回 n 个数的序列, 覆盖若干典型分布。"""
    env_maxv = os.environ.get("P3147_MAXV")
    if env_maxv is not None:
        maxv = max(1, min(int(env_maxv), MAX_A))
        return [randint(1, maxv) for _ in range(n)]

    mode = randint(0, 3)
    if mode == 0:
        # 全部相同: 能一路合并, 用来验证答案增长到 40+log2(n) 的路径
        x = randint(1, MAX_A)
        return [x] * n
    if mode == 1:
        # 窄值域: 容易大量合并
        maxv = randint(1, 3)
        return [randint(1, maxv) for _ in range(n)]
    if mode == 2:
        # 宽值域: 合并机会少, 答案接近初始最大值
        return [randint(1, MAX_A) for _ in range(n)]
    # 两值交替: 局部可合并但整体很难
    x = randint(1, MAX_A)
    y = randint(1, MAX_A)
    return [x if i % 2 == 0 else y for i in range(n)]


def main():
    if len(sys.argv) > 1:
        n = int(sys.argv[1])
    else:
        # 暴力只能跑小数据, 默认小规模
        n = randint(2, 10)
    n = max(2, n)  # 题面: 2 <= N

    seq = build(n)

    io = IO(input_file=sys.stdout, disable_output=True)
    io.input_writeln(n)
    for x in seq:
        io.input_writeln(x)


if __name__ == "__main__":
    main()
