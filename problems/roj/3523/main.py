#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:18
# update_at: 2026-10-02 05:37

import sys

LOG10_2 = 0.30102999566398119521  # log10(2)，用于浮点估计 2^P 的位数
TAIL_MOD = 10 ** 500              # 只关心十进制最后 500 位


def count_digits(power: int) -> int:
    """2^power - 1 的十进制位数；2^power 不是 10 的幂，与 2^power 位数相同。"""
    digits = int(power * LOG10_2) + 1   # 浮点估计
    two_pow = 1 << power                # 精确值，校正浮点误差（至多偏差 1 位）
    while 10 ** digits <= two_pow:
        digits += 1
    while 10 ** (digits - 1) > two_pow:
        digits -= 1
    return digits


def solve() -> None:
    power = int(sys.stdin.readline())

    digits = count_digits(power)
    # 三参数 pow 模快速幂得 2^P 末 500 位；2^P 不含因子 5，模 10^500 不为 0，减 1 不跨模
    tail = str(pow(2, power, TAIL_MOD) - 1).zfill(500)  # 不足 500 位时高位补 0

    lines = [str(digits)] + [tail[i:i + 50] for i in range(0, 500, 50)]  # 10 行 × 50 位
    sys.stdout.write("\n".join(lines))


if __name__ == "__main__":
    solve()
