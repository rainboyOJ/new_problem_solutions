#!/usr/bin/env python3
"""生成 P1471 小数据：n 个实数（用整数代替，实数包括整数）的数列 +
区间加 / 平均值 / 方差操作，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 100)
    print(n, m)
    print(*[random.randint(-100, 100) for _ in range(n)])
    for _ in range(m):
        opt = random.randint(1, 3)
        l = random.randint(1, n)
        r = random.randint(l, n)
        if opt == 1:
            # k 也是实数，用整数构造，避免浮点误差干扰对拍。
            k = random.randint(-100, 100)
            print(opt, l, r, k)
        else:
            print(opt, l, r)


if __name__ == "__main__":
    main()
