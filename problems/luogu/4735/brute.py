#!/usr/bin/env python3
"""P4735 最大异或和 的暴力验证程序：直接模拟序列与询问，枚举 p 计算后缀异或。"""

import sys
from itertools import accumulate
from operator import xor

prefix = []
# prefix = list(accumulate(a, xor, initial=0))  # prefix[i] = a[0]^...^a[i-1]


def query(left, right, x):
    """暴力回答询问：后缀异或 a[p..] = 总异或 ^ 前缀异或[p]，枚举 p 取最大。"""
    total = prefix[-1]
    # p 为 0 基起点，对应 1 基区间 [left, right]
    return max(total ^ prefix[p] ^ x for p in range(left - 1, right))


def main():
    global prefix
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    n = int(next(it))
    m = int(next(it))
    a = [int(next(it)) for _ in range(n)]
    prefix = list(accumulate(a, xor, initial=0))

    answers = []
    for _ in range(m):
        op = next(it)
        if op == b"A":
            a.append(int(next(it)))  # 追加操作：直接在末尾加一个数
            prefix.append(prefix[-1] ^ a[-1])
            continue

        left, right, x = int(next(it)), int(next(it)), int(next(it))
        # 询问：max over p in [l, r]（1 基）of (a[p] ^ ... ^ a[N] ^ x)
        answers.append(str(query(left, right, x)))

    print("\n".join(answers))


if __name__ == "__main__":
    main()
