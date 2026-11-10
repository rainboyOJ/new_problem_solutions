#!/usr/bin/env python3
"""P1248 对拍数据生成器：无输入，stdout 即一组数据。

duipai.py 会通过环境变量 DUPAI_SEED 给每轮一个种子。
默认生成小规模数据（n <= 8），保证 brute.cpp 的全排列枚举能跑完。
设置环境变量 GEN_N_MAX 可放大 n（此时只能配合 main.cpp 自测，不能对拍）。
"""
import os
import random
import sys

from cyaron import IO, randint


def main() -> None:
    seed = os.environ.get("DUPAI_SEED")
    if seed:
        random.seed(int(seed))

    n_max = int(os.environ.get("GEN_N_MAX", "8"))
    n = randint(1, n_max)

    style = random.choice(["random", "random", "front", "back", "equal"])

    a = []
    b = []
    for _ in range(n):
        if style == "front":
            # 全部属于前段：a <= b
            x = randint(1, 20)
            a.append(x)
            b.append(randint(x, 20))
        elif style == "back":
            # 全部属于后段：a > b
            y = randint(1, 20)
            b.append(y)
            a.append(randint(y + 1, 21))
        elif style == "equal":
            # a == b，落在前段，用于检查相等情形的稳定性
            x = randint(1, 20)
            a.append(x)
            b.append(x)
        else:
            a.append(randint(1, 20))
            b.append(randint(1, 20))

    io = IO(input_file=sys.stdout, disable_output=True)
    io.input_writeln(n)
    io.input_writeln(a)
    io.input_writeln(b)


if __name__ == "__main__":
    main()
