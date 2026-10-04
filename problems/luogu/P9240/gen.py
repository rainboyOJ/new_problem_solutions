#!/usr/bin/env python3
"""P9240 [蓝桥杯 2023 省 B] 冶炼金属 随机数据生成器。

数据按题目保证「有解」来构造：先随机选一个真实转换率 V，
再为每条记录随机取 A >= V，令 B = A // V，这样 V 一定能解释所有记录。

用法:
    python3 gen.py > in.txt

随机种子默认固定为 20231003 保证可复现；对拍脚本通过环境变量 DUPAI_SEED
传入不同种子时按传入值取种子，从而得到多样的测例。

注意：A 的上界被限制在 2 * 10^5 以内，目的是让暴力解
（枚举候选 V 并逐条验证）在秒级跑完，对拍才有意义。
"""
import os
import random

DEFAULT_SEED = 20231003
A_LIMIT = 200000  # 对拍用的 A 上界，真实题目是 10^9


def build_case(mode):
    """按 mode 生成若干 (A, B) 记录，保证每条记录的 B >= 1。"""
    if mode == "small":
        # 小数据：V 和 A 都很小，重点覆盖多种取整形状。
        n = random.randint(1, 5)
        v = random.randint(1, 6)
        a_hi = random.randint(v, min(30, A_LIMIT))
    elif mode == "medium":
        # 中等数据：V 范围更宽，容易出现「多个 V 解释同一批记录」。
        n = random.randint(1, 6)
        v = random.randint(1, 50)
        a_hi = random.randint(v, min(800, A_LIMIT))
    elif mode == "big_a_small_v":
        # A 很大而 V 很小：B 很大，考察整除区间的大边界。
        n = random.randint(1, 3)
        v = random.randint(1, 4)
        a_hi = random.randint(v, A_LIMIT)
    else:
        # boundary：故意制造 V = 1、A = V、A 取到上界等边界情形。
        n = random.randint(1, 4)
        v = random.choice([1, 1, 2, random.randint(1, 8)])
        a_hi = random.choice([v, v, v + 1, A_LIMIT])
        a_hi = min(max(a_hi, v), A_LIMIT)

    records = []
    for _ in range(n):
        a = random.randint(v, a_hi)
        if a < v:
            a = v
        b = a // v  # 由真实转换率 v 反推产出，保证 B >= 1
        records.append((a, b))

    # 小概率把某条记录的 A 推到上界附近，制造更极端的取整情况。
    if mode != "small" and random.random() < 0.25:
        i = random.randrange(len(records))
        a = random.choice([a_hi, min(a_hi + 1, A_LIMIT), A_LIMIT])
        a = max(a, v)
        records[i] = (a, a // v)

    # 同一批记录里再混入一条「几乎卡边界」的记录：A 恰好是 v 的整数倍。
    if mode != "small" and random.random() < 0.25:
        k = random.randint(1, max(1, A_LIMIT // v))
        a = min(k * v, A_LIMIT)
        a = max(a, v)
        records.append((a, a // v))

    return records


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    random.seed(int(seed_text) if seed_text is not None else DEFAULT_SEED)

    mode = random.choice(["small", "small", "medium", "big_a_small_v", "boundary"])
    records = build_case(mode)

    out = [str(len(records))]
    for a, b in records:
        out.append("%d %d" % (a, b))
    print("\n".join(out))


if __name__ == "__main__":
    main()
