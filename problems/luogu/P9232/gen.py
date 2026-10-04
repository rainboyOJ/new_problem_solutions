#!/usr/bin/env python3
"""P9232 随机数据生成器：输出一行仅由数字字符组成的字符串 s。

用法：
    python3 gen.py           # 使用固定种子 SEED，结果可复现
    python3 gen.py <seed>    # 指定种子，用于多样本对拍

数据范围贴合题面约束 1 <= n <= 5000。
brute.cpp 是 O(n^3) 的照抄题面做法，所以生成器默认把 n 控制在几百以内，
让对拍能在几秒内跑完；同时用 `python3 gen.py large` 可以生成一组 n 较大的
数据，专门用来检查 main.cpp 的 O(n^2) 递推在满数据下不会超时或越界。
"""
import random
import sys

SEED = 20231003  # 默认固定种子

SMALL_MAX = 12    # 极小数据：方便逐个子串人工核对
MEDIUM_MAX = 60   # 中等数据：覆盖更多子串组合
FULL_N = 5000     # 题面最大规模，只在 `gen.py large` 模式下使用，专供 main.cpp


def gen_small():
    """极小数据：n = 1..12，字母表很小，容易撞出回文结构。"""
    n = random.randint(1, SMALL_MAX)
    alphabet = random.choice(["01", "012", "0123456789"])
    return "".join(random.choice(alphabet) for _ in range(n))


def gen_medium():
    """中等数据：n = 13..60，混合随机串和带结构的串。"""
    n = random.randint(SMALL_MAX + 1, MEDIUM_MAX)
    kind = random.random()
    if kind < 0.5:
        alphabet = random.choice(["01", "012", "0123456789"])
        return "".join(random.choice(alphabet) for _ in range(n))
    if kind < 0.75:
        # 先造一段回文再拼接，保证存在大量长度 >= 2 的回文子串
        half = "".join(random.choice("012") for _ in range((n + 1) // 2))
        return (half + half[::-1])[:n]
    # 单调串：第一处不同几乎总在位置 l，用来检验 s[l] > s[r] 分支
    if random.random() < 0.5:
        return "".join(str((9 - i) % 10) for i in range(n))  # 9420... 递减
    return "".join(str(i % 10) for i in range(n))            # 0123... 递增


def gen_edge():
    """边界数据：n = 1、2、3，全相同字符，前导零，全零，严格单调。"""
    picks = [
        "0",
        "5",
        "10",
        "01",
        "00",
        "11",
        "000",
        "010",
        "101",
        "0000",
        "1111",
        "1234567890",
        "9876543210",
        "0123456789" * 2,
        "0" * 20,
        "9" * 20,
        "11111111111111111111",
    ]
    if random.random() < 0.5:
        return random.choice(picks)
    n = random.randint(1, 6)
    d = random.choice("0123456789")
    return d * n  # 同字符重复：反转后完全不变，答案必须是 0


def gen_large():
    """满规模数据：n = 5000，专供 main.cpp 检验时间与空间。"""
    n = FULL_N
    kind = random.random()
    if kind < 0.6:
        return "".join(random.choice("0123456789") for _ in range(n))
    if kind < 0.8:
        half = "".join(random.choice("01") for _ in range(n // 2))
        return (half + half[::-1])[:n]
    return "".join(str((9 - i) % 10) for i in range(n))


def main():
    mode = None
    seed = SEED
    args = sys.argv[1:]
    if args and args[0] == "large":
        mode = "large"
        args = args[1:]
    if args:
        seed = int(args[0])
    random.seed(seed)

    if mode == "large":
        print(gen_large())
        return

    kind = random.random()
    if kind < 0.4:
        s = gen_small()
    elif kind < 0.75:
        s = gen_medium()
    else:
        s = gen_edge()
    print(s)


if __name__ == "__main__":
    main()
