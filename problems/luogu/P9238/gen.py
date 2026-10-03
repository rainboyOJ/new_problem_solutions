#!/usr/bin/env python3
"""P9238 翻转硬币 随机数据生成器（输出到 stdout）。

数据范围 1 <= n <= 1e18。brute.cpp 是 O(n) 的标记法，n 到 2e7 只需几十毫秒（
它的上限数组是 2e7），所以生成器把 n 控制在 5e6 以内，对应题面 30% 的子任务范围，
既能真正压到暴力解的上限，又不至于让对拍变慢。
n > 5e6 的规模（含 1e18）由 main.cpp 内部逻辑保证，已用独立的分段筛程序单独校验过。

可复现性：对拍脚本传入 DUPAI_SEED 环境变量时使用该种子，同一组种子一定复现同一份数据；
不传时用系统随机种子，这样 verify.sh 连续生成的 8 组数据是互不相同的，覆盖面更广。
"""
import os
import random

# 固定锚点：小边界、完全平方数附近（平方因子最密集）、无平方因子密度变化明显的位置
ANCHORS = [
    1, 2, 3, 4, 5,
    7,              # 题面样例一
    199, 200,
    39600, 39601, 39602,      # 199^2 = 39601 附近
    141420, 141421, 141422,   # 200*sqrt(2) 附近
    199999, 200000, 200001,
    4999999, 5000000, 5000001,   # 上限附近的完全平方数邻域（2236^2 = 4999696）
]


def build_case(rng):
    """按概率挑一个锚点或随机值，返回一个 1..5*10^6 的 n。"""
    r = rng.random()
    if r < 0.25:
        return rng.choice(ANCHORS)
    if r < 0.55:
        return rng.randint(1, 2000)          # 小数据，便于人工核对
    if r < 0.75:
        return rng.randint(1000, 100000)     # 中等规模
    if r < 0.90:
        return rng.randint(10 ** 5, 10 ** 6) # 较大
    return rng.randint(10 ** 6, 5 * 10 ** 6) # 暴力解能承受的上界附近


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    # 不传 DUPAI_SEED 时用系统随机种子；传入时用固定种子，保证可复现
    rng = random.Random(None if seed_text is None else int(seed_text))
    print(build_case(rng))


if __name__ == "__main__":
    main()
