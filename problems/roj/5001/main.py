#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 20:41
# update_at: 2026-10-02 20:41

import sys


def a_wins(row: str) -> bool:
    """A 是否必胜：等价于最后一次合并后剩下的是圆(0)。

    记 S 为当前行里 1 的个数。合并 a、b 得到 a XNOR b，而
    a + b + (a XNOR b) ≡ 1 (mod 2)（因为 a+b 与 a XOR b 同奇偶），
    即每合并一次 S 的奇偶性翻转一次。长度为 len 的行恰好合并 len-1 次，
    结束后唯一剩下的图形值 ≡ S + len - 1 (mod 2)，与谁走、怎么选都无关。
    """
    squares = row.count('1')                       # 初始的 S
    last_is_circle = (squares + len(row) - 1) % 2 == 0  # 末位是圆 → A 胜
    return last_is_circle


def solve() -> None:
    data = iter(sys.stdin.read().split())
    T = int(next(data))                            # 组数
    print('\n'.join('Win' if a_wins(next(data)) else 'Lost' for _ in range(T)))


if __name__ == "__main__":
    solve()
