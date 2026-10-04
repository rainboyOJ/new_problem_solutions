#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:14
# update_at: 2026-10-01 16:14

import sys


def exgcd(a: int, b: int) -> tuple[int, int]:
    """解 a*x + b*y = gcd(a, b)，返回一组整数解 (x, y)。

    递归到子问题 b*x' + (a mod b)*y' = gcd 后，用 a mod b = a - (a//b)*b
    换元回代，即可由 (x', y') 拼出当前层的 (x, y)。
    """
    if b == 0:
        return 1, 0
    x, y = exgcd(b, a % b)
    return y, x - (a // b) * y


def solve() -> None:
    a, b = map(int, sys.stdin.buffer.read().split())
    x, _ = exgcd(a, b)
    # 题目保证 gcd(a, b) = 1，故 a*x ≡ 1 (mod b)；
    # Python 取模结果落在 [0, b)，而 x ≢ 0 (mod b)，所以就是最小正整数解。
    print(x % b)


if __name__ == "__main__":
    solve()
