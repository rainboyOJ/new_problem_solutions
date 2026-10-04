#!/usr/bin/env python3
"""P9229 简单九连环 随机数据生成器（输出到 stdout）。

注意：对拍时 brute.cpp 用 2^(n+1) 的状态跑 BFS，所以这里把 n 限制在
1..15，保证暴力能跑完。会覆盖小数据、全 0、全 1、只有末尾为 1、
以及一般的随机 01 串。
"""
import random
import sys

SEED = 20261002


def gen(seed):
    rnd = random.Random(seed)
    mode = rnd.randrange(7)

    if mode == 0:                      # 极小数据
        n = rnd.randint(1, 3)
    elif mode == 1:                    # 小数据
        n = rnd.randint(4, 8)
    else:                              # 中等数据，贴住暴力上限
        n = rnd.randint(9, 15)

    if mode == 2:                      # 全 0
        s = "0" * n
    elif mode == 3:                    # 全 1
        s = "1" * n
    elif mode == 4:                    # 只有末尾为 1（传统九连环）
        s = "0" * (n - 1) + "1"
    elif mode == 5:                    # 只有开头为 1
        s = "1" + "0" * (n - 1)
    else:                              # 一般随机串
        s = "".join(rnd.choice("01") for _ in range(n))

    sys.stdout.write(f"{n}\n{s}\n")


if __name__ == "__main__":
    # 默认固定种子保证可复现；也可传入种子跑多组不同数据
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else SEED
    gen(seed)
