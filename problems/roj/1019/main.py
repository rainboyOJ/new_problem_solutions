#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:31
# update_at: 2026-09-29 13:31


def solve() -> None:
    x = float(input())
    # int() 截断小数部分：正数向下、负数向上，正好就是"向零舍入"
    print(int(x))


if __name__ == "__main__":
    solve()
