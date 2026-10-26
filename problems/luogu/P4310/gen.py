#!/usr/bin/env python3
"""生成 P4310 的对拍数据：规模与值域用环境变量控制。

无参数运行，数据直接写 stdout，供 duipai.py --gen 调用。

    P4310_MAXN=<int>      n 的上限（默认 8，暴力 O(n^2) 可承受）
    P4310_MAXV=<int>      a_i 的上限（默认 16，位运算稀疏，容易出长链）
    P4310_ZERO=1          允许出现 0（题面只给上界，0 是最坏的"接不上"情形）

手动运行示例：

    P4310_MAXN=20 P4310_MAXV=1023 python3 gen.py
"""

import os
import sys

from cyaron import IO, Vector, randint


def main():
    max_n = int(os.environ.get("P4310_MAXN", "8"))
    max_v = int(os.environ.get("P4310_MAXV", "16"))
    allow_zero = os.environ.get("P4310_ZERO") == "1"

    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(1, max_n)
    io.input_writeln(n)

    low = 0 if allow_zero else 1
    # 位运算题的关键是"有没有公共位"，所以值域故意压小，让 1 位、2 位的数大量出现。
    values = Vector.random(n, [low, max_v])
    io.input_writeln(values)


if __name__ == "__main__":
    main()
