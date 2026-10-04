#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:10
# update_at: 2026-09-29 16:10

import sys

DIVISORS = (3, 5, 7)  # 候选除数，按从小到大排列：过滤出的顺序就是输出的顺序


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 待判定的整数，可能为负数或 0
    # 依次测试 3、5、7，能整除的按从小到大留下；负数取余结果仍非负，== 0 判定不受符号影响
    divisors = [d for d in DIVISORS if n % d == 0]
    # 空列表表示一个都整除不了，按题意输出 'n'
    print(' '.join(map(str, divisors)) if divisors else 'n')


if __name__ == "__main__":
    solve()
