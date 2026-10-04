#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:01
# update_at: 2026-10-02 08:01

import sys
from collections import Counter


def solve() -> None:
    word = sys.stdin.read().split()[0]

    cnt = Counter(word)  # 每个小写字母在单词里出现的次数
    diff = max(cnt.values()) - min(cnt.values())  # maxn - minn

    # 试除判断质数：diff 为 0 或 1 时直接判否，枚举到 sqrt(diff) 为止
    is_prime = diff >= 2 and all(diff % i for i in range(2, int(diff**0.5) + 1))

    if is_prime:
        print("Lucky Word")
        print(diff)
    else:
        print("No Answer")
        print(0)


if __name__ == "__main__":
    solve()
