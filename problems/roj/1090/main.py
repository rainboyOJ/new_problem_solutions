#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:17
# update_at: 2026-09-29 18:17

import sys


def solve() -> None:
    """判断 m 能否被 19 整除，且十进制写法里恰好含 k 个数字 3。"""
    m, k = map(int, sys.stdin.buffer.read().split())
    s = str(m)                                    # 十进制写法，数位个数最多 5（m < 100000）
    count_of_3 = s.count('3')                     # 数字 3 出现的次数
    is_multiple_of_19 = m % 19 == 0               # 整除判定
    print('YES' if is_multiple_of_19 and count_of_3 == k else 'NO')


if __name__ == "__main__":
    solve()
