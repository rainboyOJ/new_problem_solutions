#!/usr/bin/env python3
# gen.py：对拍数据生成器。无输入，stdout 即一组数据。
# 用环境变量参数化，方便覆盖边界与满规模：
#   GEN_N_MAX   n 的上限（默认 8）
#   GEN_K_MAX   k 的上限（默认 10）
#   GEN_ABS     |a| 的值域上限（默认 10）
#   GEN_MODE    small(默认，随机含负数) / neg(全负权) / full(满规模 n=100, |a|=1e9)
#   GEN_K_FIXED 固定 k（优先于随机档位），用于 k=0 或 k>=n(n+1)/2 的专项
# 生成器使用 cyaron 的 randint（与 random.seed 联动，可用 DUPAI_SEED 复现）。

import os
import random
import sys

from cyaron import IO, randint


def main() -> None:
    mode = os.environ.get("GEN_MODE", "small")
    n_max = int(os.environ.get("GEN_N_MAX", "8"))
    k_max = int(os.environ.get("GEN_K_MAX", "10"))
    abs_max = int(os.environ.get("GEN_ABS", "10"))
    k_fixed = os.environ.get("GEN_K_FIXED")

    seed = os.environ.get("DUPAI_SEED")
    random.seed(int(seed) if seed is not None else random.randrange(2**63))

    if mode == "full":
        n = 100
        abs_max = 10**9
    else:
        n = randint(1, n_max)

    # k 覆盖三种档位：k=0、k 超过全部格子数（触发 min(k,n) 截断）、k 介于两者之间
    total = n * (n + 1) // 2
    if k_fixed is not None:
        k = int(k_fixed)
    else:
        pick = random.random()
        if pick < 0.15:
            k = 0
        elif pick < 0.4:
            k = randint(total, total + 5)
        else:
            k = randint(0, k_max)

    io = IO(input_file=sys.stdout, disable_output=True)
    io.input_writeln(n, k)
    for i in range(1, n + 1):
        if mode == "neg":
            row = [randint(-abs_max, -1) for _ in range(i)]
        else:
            row = [randint(-abs_max, abs_max) for _ in range(i)]
        io.input_writeln(row)


if __name__ == "__main__":
    main()
