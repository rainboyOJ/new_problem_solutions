#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:27
# update_at: 2026-09-30 20:32

import sys
from functools import cache


def count_mod_sum(x: int, n: int) -> int:
    """[0, x] 中各位数字之和 mod n 为 0 的个数（含 0 本身）。"""
    digits = tuple(map(int, str(x)))  # 上界逐位拆开，len 最多 10

    @cache
    def dfs(pos: int, rem: int, tight: bool) -> int:
        """从高位往低位填数：前缀数字和 mod n 余 rem，当前位是否贴着上界。"""
        if pos == len(digits):  # 位数填满，只剩"数字和是否为 n 的倍数"
            return int(rem == 0)
        limit = digits[pos] if tight else 9  # 贴上界时本位最多填到上界的这一位
        return sum(
            dfs(pos + 1, (rem + d) % n, tight and d == limit)  # 放入数字 d
            for d in range(limit + 1)
        )

    return dfs(0, 0, True)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    while True:  # 多组测试数据，读到文件末尾为止
        try:
            a, b, n = next(data), next(data), next(data)
        except StopIteration:
            break
        lo, hi = (a, b) if a <= b else (b, a)  # 题面只说闭区间 [a, b]，没保证 a 在前
        # 前缀相减：0 在两份计数里各算一次正好抵消，剩下 [a, b] 的答案
        out.append(str(count_mod_sum(hi, n) - count_mod_sum(lo - 1, n)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
