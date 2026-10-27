#!/usr/bin/env python3
"""U420425 数据生成器：无输入，标准输出就是一组测试数据。

用环境变量调整规模与值域，同一个脚本既能出对拍用的小数据，也能出满规模数据：
    GEN_N / GEN_M           固定 n、m（不给就在 [1, GEN_N_MAX] / [1, GEN_M_MAX] 里随机）
    GEN_N_MAX / GEN_M_MAX   随机规模的上界，默认 12
    GEN_VMAX                初始值的上界，默认 10
    GEN_KMAX                区间加 k 的上界，默认 10
    GEN_DMAX                操作 3 的 d 上界，默认 20
    GEN_OPS                 只出某一种操作，取值 1/2/3/4；默认 mix（四种都出）

数列的初始值、操作 4 的赋值都取正整数，区间加取非负数：题目把操作 3 描述成
「在前缀和数组上做 lower_bound」，这只有在所有元素非负（前缀和单调不减）时才有意义，
也只有在这种数据上，「整段和不够就跳过」的线段树二分才和暴力逐项累加一致。
"""
import os
import sys

from cyaron import IO, randint


def env_int(name, default):
    return int(os.environ.get(name, default))


def main():
    n_max = env_int("GEN_N_MAX", 12)
    m_max = env_int("GEN_M_MAX", 12)
    n = env_int("GEN_N", 0) or randint(1, n_max)
    m = env_int("GEN_M", 0) or randint(1, m_max)
    vmax = env_int("GEN_VMAX", 10)
    kmax = env_int("GEN_KMAX", 10)
    dmax = env_int("GEN_DMAX", 20)
    only_op = os.environ.get("GEN_OPS", "mix")

    io = IO(input_file=sys.stdout, disable_output=True)
    io.input_writeln(n, m)
    io.input_writeln([randint(1, vmax) for _ in range(n)])

    for _ in range(m):
        op = int(only_op) if only_op in ("1", "2", "3", "4") else randint(1, 4)
        if op == 1:
            x = randint(1, n)
            y = randint(1, n)
            if x > y:
                x, y = y, x
            io.input_writeln(1, x, y, randint(0, kmax))
        elif op == 2:
            x = randint(1, n)
            y = randint(1, n)
            if x > y:
                x, y = y, x
            io.input_writeln(2, x, y)
        elif op == 3:
            x = randint(1, n)
            y = randint(1, n)
            if x > y:
                x, y = y, x
            io.input_writeln(3, x, y, randint(1, dmax))
        else:
            io.input_writeln(4, randint(1, n), randint(1, vmax))


if __name__ == "__main__":
    main()
