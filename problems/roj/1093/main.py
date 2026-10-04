#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:40
# update_at: 2026-09-29 19:08

import sys
from functools import reduce
from itertools import accumulate, repeat
from operator import add, mul


def solve() -> None:
    x_text, n_text = sys.stdin.buffer.read().split()
    x, n = float(x_text), int(n_text)
    # 前缀积从 1.0 起步再自乘 n 次，依次产出 x^0, x^1, ..., x^n
    powers = accumulate(repeat(x, n), mul, initial=1.0)
    # reduce 是左折叠（((1 + x^0) + x^1) + ...），与参考实现逐步累加的舍入次序一致
    print(f"{reduce(add, powers):.2f}")


if __name__ == "__main__":
    solve()
