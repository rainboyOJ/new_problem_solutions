#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:47
# update_at: 2026-09-30 04:47

import sys

MOD = 12345
HALF = 2 * MOD  # 全程只在模 2*12345 下运算，最后整除 2 就等于对答案做精确减半


def even_count(n: int) -> int:
    """N 位数中含偶数个数字 3 的个数，对 12345 取模。

    允许前导 0 时逐位转移是"9 种非 3 数字保持奇偶 + 数字 3 翻转奇偶"，
    解两状态递推得 偶数个 3 有 e_k=(10^k+8^k)/2 个、奇数个 3 有 (10^k-8^k)/2 个。
    首位换成 1..9（其中只有 3 会翻转奇偶）后：
    答案 = 8*e_{n-1} + o_{n-1} = (9*10^(n-1) + 7*8^(n-1)) / 2。
    """
    doubled = (9 * pow(10, n - 1, HALF) + 7 * pow(8, n - 1, HALF)) % HALF
    return doubled // 2 % MOD  # 括号内恒为偶数，所以整除 2 是真减半而非取整


def solve() -> None:
    n = int(sys.stdin.buffer.read())
    print(even_count(n))


if __name__ == "__main__":
    solve()
