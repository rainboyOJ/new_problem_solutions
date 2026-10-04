#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:38
# update_at: 2026-09-29 20:38

import sys


def solve() -> None:
    data = sys.stdin.read().split()
    s1, s2 = data[0], data[1]

    # 按题面顺序问两次：先问 s1 是否为 s2 的子串，再问反向，两次都没命中才是 No substring
    if s1 in s2:
        print(f"{s1} is substring of {s2}")
    elif s2 in s1:
        print(f"{s2} is substring of {s1}")
    else:
        print("No substring")


if __name__ == "__main__":
    solve()
