#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:25
# update_at: 2026-10-02 08:25

import sys


def solve() -> None:
    """从样例对推导 26 字母的替换置换并译出电报；规则冲突或字母缺失输出 Failed。"""
    cipher, plain, msg = sys.stdin.read().split()

    key: dict[str, str] = {}  # 原字母 -> 密字
    for x, y in zip(plain, cipher):
        conflict = key.setdefault(x, y) != y  # 同一个原字母却给出了两个不同密字
        if conflict:
            print('Failed')
            return

    # 情形 2/3：26 个原字母必须都出现，且密字两两不同（满射即双射）
    is_bijection = len(key) == len(set(key.values())) == 26
    if not is_bijection:
        print('Failed')
        return

    decode = {y: x for x, y in key.items()}  # 反向：密字 -> 原字母
    print(''.join(decode[y] for y in msg))


if __name__ == "__main__":
    solve()
