#!/usr/bin/env python3
"""1395C 的数据生成器：无输入，stdout 就是一组数据。

规模由环境变量控制，方便同一份脚本出小数据和满规模数据：
  GEN_MAXN / GEN_MAXM   n、m 的上界（默认 200）
  GEN_MAXV              数值上界（默认 512，即 2^9）
  DUPAI_SEED            duipai.py 传入的随机种子
"""

import os
import random
import sys

from cyaron import IO, Vector, randint
from cyaron.vector import VectorRandomMode


def main():
    seed = os.environ.get("DUPAI_SEED")
    if seed is not None:
        random.seed(int(seed))

    max_n = int(os.environ.get("GEN_MAXN", "200"))
    max_m = int(os.environ.get("GEN_MAXM", "200"))
    max_v = int(os.environ.get("GEN_MAXV", "512"))

    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(1, max_n)
    m = randint(1, max_m)

    # 元素允许重复：候选值本来就可能撞车，用 unique 模式在极小范围会报错
    repeatable = VectorRandomMode.repeatable

    # 三分之一的用例压到极小规模或极值，剩下的用随机值
    roll = randint(0, 2)
    if roll == 0:
        a = Vector.random(n, [(0, 0), (max_v - 1, max_v - 1)], repeatable)
        b = Vector.random(m, [(0, 0), (max_v - 1, max_v - 1)], repeatable)
    elif roll == 1:
        a = Vector.random(n, [(0, 1), (max_v - 2, max_v - 1)], repeatable)
        b = Vector.random(m, [(0, 1), (max_v - 2, max_v - 1)], repeatable)
    else:
        a = Vector.random(n, [(0, max_v - 1)], repeatable)
        b = Vector.random(m, [(0, max_v - 1)], repeatable)

    # 偶尔让 n = 1 或 m = 1，覆盖单行、单候选的退化情形
    if randint(0, 5) == 0:
        n = 1
        a = a[:1]
    if randint(0, 5) == 0:
        m = 1
        b = b[:1]

    io.input_writeln(n, m)
    io.input_writeln(a)
    io.input_writeln(b)


if __name__ == "__main__":
    main()
