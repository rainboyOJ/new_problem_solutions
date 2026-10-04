#!/usr/bin/env python3
"""P9234 买瓜 随机数据生成器：输出到 stdout。
小数据（n<=10）保证暴力 3^n 能在时限内跑完，用于对拍。
"""
import random


def main():
    random.seed()
    n = random.randint(1, 10)
    # 混合几种尺度：小值、偶数、奇数，覆盖劈半的奇偶边界
    style = random.randint(0, 3)
    if style == 0:
        a = [random.randint(1, 6) for _ in range(n)]
    elif style == 1:
        a = [random.randint(1, 20) for _ in range(n)]
    elif style == 2:
        a = [2 * random.randint(1, 9) for _ in range(n)]
    else:
        a = [random.choice([1, 2, 3, 5, 10, 100]) for _ in range(n)]

    total = sum(a)
    # m 的取值覆盖：可达、刚好等于总和、随机、以及刻意取不可达的值
    mode = random.randint(0, 3)
    if mode == 0:
        m = random.randint(1, total)
    elif mode == 1:
        m = total
    elif mode == 2:
        m = max(1, total // 2)
    else:
        m = random.randint(1, total + 3)

    print(n, m)
    print(" ".join(map(str, a)))


if __name__ == "__main__":
    main()
