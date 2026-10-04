#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:18
# update_at: 2026-10-01 03:18

import sys

# 每一位只可能是这 4 个数字：偶数与 5 会让末位组成的数被 2 或 5 整除
TAIL_DIGITS = (1, 3, 7, 9)
# 首位从这 4 个里取：1 不是质数，2、3、5、7 都是一位质数
HEAD_DIGITS = (2, 3, 5, 7)


def is_prime(x: int) -> bool:
    """判断 x 是否为质数（试除到 sqrt(x)）。"""
    if x < 2:
        return False
    d = 2
    while d * d <= x:                # 只需试除到 sqrt(x)：合数必有一个不超过 sqrt(x) 的因子
        if x % d == 0:
            return False
        d += 1
    return True


def solve() -> None:
    n = int(sys.stdin.buffer.read().split()[0])

    # 逐位生长：prefix 是已经保证为特殊质数的前缀，往右再接一位再判定
    cur = [p for p in HEAD_DIGITS if is_prime(p)]   # 长度 1 的特殊质数
    for _ in range(n - 1):
        nxt: list[int] = []
        for prefix in cur:
            for d in TAIL_DIGITS:
                x = prefix * 10 + d
                if is_prime(x):                      # 新数仍是质数才留下，往后继续接
                    nxt.append(x)
        cur = nxt
        if not cur:                                  # 这一长度已经没有候选，再长更不可能有
            break

    sys.stdout.write('\n'.join(map(str, cur)) + ('\n' if cur else ''))


if __name__ == "__main__":
    solve()
