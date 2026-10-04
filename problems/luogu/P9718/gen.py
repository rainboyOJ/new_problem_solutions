#!/usr/bin/env python3
"""P9718 随机数据生成器（小数据，供与暴力对拍）。

只生成答案足够小的数据，保证 brute.cpp 的枚举能在限时内跑完：
x < 1000、k <= 3 时答案最大不超过 99900。

默认使用固定种子，这样 verify.sh 反复运行时得到的数据是可复现的；
需要扩大覆盖时可以在命令行传入其它种子：

    python3 gen.py 12345
"""
import random
import sys

DEFAULT_SEED = 20221003


def small_x(rng):
    """生成较小的 x，覆盖全部是 9、部分位是 9、边界值三类情况。"""
    r = rng.random()
    if r < 0.22:
        # 全 9：进位会一直向高位传播，是最容易出错的边界
        return int("9" * rng.randint(1, 3))
    if r < 0.45:
        # 随机挑几位填 9，其余位填 0 或接近 9 的数字
        length = rng.randint(1, 3)
        digits = [str(rng.choice([0, 1, 8, 9, 9])) for _ in range(length)]
        if digits[0] == "0":
            digits[0] = str(rng.randint(1, 9))
        return int("".join(digits))
    if r < 0.65:
        # 手工边界值
        return rng.choice([1, 2, 9, 10, 11, 99, 100, 101, 998, 999])
    return rng.randint(1, 999)


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else DEFAULT_SEED
    rng = random.Random(seed)

    t = rng.randint(5, 10)
    lines = [str(t)]
    for _ in range(t):
        x = small_x(rng)
        k = rng.randint(0, 3)
        lines.append(f"{x} {k}")
    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
