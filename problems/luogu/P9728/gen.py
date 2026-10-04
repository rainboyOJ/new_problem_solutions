#!/usr/bin/env python3
"""P9728 [EC Final 2022] Dining Professors 随机数据生成器。

用法：
    python3 gen.py                # 随机一个测例，输出到 stdout
    DUPAI_SEED=123 python3 gen.py # 固定种子，可复现

为了能和 brute.cpp（枚举 2^n 种摆法）对拍，这里生成的 n 都很小（3 <= n <= 18）。
8 次运行会覆盖小规模、中等规模以及 a=0 / a=n / 全部能吃辣 / 全部不能吃辣等边界。
另外支持环境变量 DUPAI_SEED（对拍脚本 duipai.py 会传入）以复现同一组数据。
"""
import os
import random
import sys


def build_case(rng: random.Random):
    """返回 (n, a, b)。b 是长度为 n 的 0/1 列表。"""
    mode = rng.randrange(8)

    if mode == 0:
        # 最小规模
        n = 3
    elif mode == 1:
        # 小规模，a 取到两端
        n = rng.randint(3, 6)
    elif mode == 2:
        # 中等规模
        n = rng.randint(7, 12)
    elif mode == 3:
        # 稍大规模，仍能暴力
        n = rng.randint(13, 18)
    else:
        n = rng.randint(3, 18)

    if mode == 4:
        a = 0                      # 全是辣菜
    elif mode == 5:
        a = n                      # 全是不辣菜
    else:
        a = rng.randint(0, n)

    if mode == 6:
        b = [1] * n                # 所有教授都能吃辣
    elif mode == 7:
        b = [0] * n                # 所有教授都不能吃辣
    elif mode == 1:
        # 交替 0101... 或 1010...
        start = rng.randint(0, 1)
        b = [(start + i) % 2 for i in range(n)]
    elif mode == 2:
        # 连续一段能吃辣 / 不能吃辣，制造成块的 0 和 1
        b = [rng.randint(0, 1)] * n
        for i in range(n):
            if rng.random() < 0.25:
                b[i] ^= 1
    elif mode == 5:
        # 单个特殊教授，其余全同
        b = [rng.randint(0, 1)] * n
        b[rng.randrange(n)] ^= 1
    else:
        b = [rng.randint(0, 1) for _ in range(n)]

    return n, a, b


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is not None:
        rng = random.Random(int(seed_text))
    elif len(sys.argv) > 1:
        rng = random.Random(int(sys.argv[1]))
    else:
        rng = random.Random()

    n, a, b = build_case(rng)
    out = [f"{n} {a}", " ".join(map(str, b))]
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
