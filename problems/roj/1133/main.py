#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:15
# update_at: 2026-09-29 20:15

import sys


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    s: str = next(data).decode()

    # 环形搭档：第 i 个字符与第 i+1 个配对，末位绕回首字符；一次错位拼接即可全配对
    partner: str = s[1:] + s[:1]

    # 亲朋字符 = 两位 ASCII 值之和对应的字符（ASCII ≤ 63，和 ≤ 126，仍是可打印字符）
    print(''.join(chr(ord(a) + ord(b)) for a, b in zip(s, partner)))


if __name__ == "__main__":
    solve()
