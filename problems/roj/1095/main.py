#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-05-22 19:17
# update_at: 2026-05-22 19:17

import sys


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n = int(data[0])
    # 把 1..n 每个整数转成字符串，累计其中 '1' 的出现次数
    ans = sum(str(i).count("1") for i in range(1, n + 1))
    print(ans)


if __name__ == "__main__":
    solve()
