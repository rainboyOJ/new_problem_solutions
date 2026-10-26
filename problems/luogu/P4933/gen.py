#!/usr/bin/env python3
"""P4933 数据生成器：无输入，stdout 即数据。

按环境变量参数化，同一份脚本既能造小数据也能造满规模数据：
  P4933_N       元素个数 n，缺省时随机
  P4933_MAXN    未给 P4933_N 时随机 n 的上界（默认 8）
  P4933_V       高度上限 v，缺省时随机
  P4933_SHAPE   random / equal / inc / dec / arithmetic（默认 random）
"""

import os
import random
import sys

from cyaron import IO, randint


def build_heights(n: int, v: int, shape: str) -> list[int]:
    """按形状造 n 个落在 [0, v] 的高度（夹紧前就保证不越界）。"""
    if shape == "equal":                      # 全相同高度，公差全为 0
        return [randint(0, v)] * n
    elif shape == "inc":                      # 严格递增（v 不够大时退化成非降）
        picks = sorted(random.sample(range(v + 1), min(n, v + 1)))
        return picks + [picks[-1]] * (n - len(picks))
    elif shape == "dec":                      # 严格递减（公差为负）
        picks = sorted(random.sample(range(v + 1), min(n, v + 1)), reverse=True)
        return picks + [picks[-1]] * (n - len(picks))
    elif shape == "arithmetic":               # 整体等差数列，对应题面「另外 20%」
        # 公差要小到整段都塞得进 [0, v]，首项再在剩下的空位里挑
        span = v // max(n - 1, 1)
        d = randint(-span, span)
        low = max(0, -d * (n - 1))
        high = v - max(0, d * (n - 1))
        start = randint(low, high)
        return [start + d * i for i in range(n)]
    return [randint(0, v) for _ in range(n)]


def main() -> None:
    max_n = int(os.environ.get("P4933_MAXN", "8"))
    n = int(os.environ.get("P4933_N", randint(1, max_n)))
    v = int(os.environ.get("P4933_V", randint(0, 10)))
    shape = os.environ.get("P4933_SHAPE", "random")

    heights = build_heights(n, v, shape)

    io = IO(input_file=sys.stdout, disable_output=True)
    io.input_writeln(n)
    io.input_writeln(*heights)


if __name__ == "__main__":
    random.seed()
    main()
