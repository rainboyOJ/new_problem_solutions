#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:37
# update_at: 2026-10-07 15:37

import sys
from itertools import accumulate

MOD1 = 1000000007  # 第一套哈希的模数
MOD2 = 998244353   # 第二套哈希的模数
BASE1 = 131        # 第一套哈希的进制
BASE2 = 137        # 第二套哈希的进制


def window_keys(text: str, m: int) -> set[int]:
    """返回全部长度为 m 的子串的哈希键集合：同一个键多次出现只留一份。

    前缀哈希 pre[i] 是 text[:i] 的 BASE 进制值，于是窗口 text[i:i + m] 的哈希是
    (pre[i + m] - pre[i] * BASE ** m) mod MOD；两套模哈希打包成一个整数当集合键，
    打包满足单射，所以键相同就当且仅当两套哈希都相同。
    """
    length = len(text)
    window_count = length - m + 1                    # 窗口个数，即子串的总个数
    digits = [ord(ch) - 96 for ch in text]           # 'a' 记成 1，避免前导零的歧义
    pre1 = list(accumulate(digits, lambda acc, c: (acc * BASE1 + c) % MOD1, initial=0))
    pre2 = list(accumulate(digits, lambda acc, c: (acc * BASE2 + c) % MOD2, initial=0))
    factor1 = pow(BASE1, m, MOD1)                    # BASE1 ** m，窗口公式里的固定系数
    factor2 = pow(BASE2, m, MOD2)                    # BASE2 ** m，作用同上
    hashes1 = ((pre1[i + m] - pre1[i] * factor1) % MOD1 for i in range(window_count))  # 各窗口第一套哈希
    hashes2 = ((pre2[i + m] - pre2[i] * factor2) % MOD2 for i in range(window_count))  # 各窗口第二套哈希
    both_hashes = zip(hashes1, hashes2)
    # h1 * MOD2 + h2 是单射打包：键相等当且仅当两套哈希都相等，于是集合天然完成去重
    return {hash1 * MOD2 + hash2 for hash1, hash2 in both_hashes}


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    n, m = int(next(tokens)), int(next(tokens))      # n 就是文章长度，只用于对照题面格式
    text = next(tokens).decode()
    print(len(window_keys(text, m)))


if __name__ == "__main__":
    solve()
