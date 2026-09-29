#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:34
# update_at: 2026-09-29 16:34

import sys


def solve() -> None:
    # 三边升序排列后只需一次比较：升序解包把"最长边"这个名字直接写进代码
    a, b, c = sorted(map(int, sys.stdin.buffer.read().split()))
    can_form_triangle = a + b > c  # 短边之和严格大于最长边；取等即退化，仍不成三角形
    print("yes" if can_form_triangle else "no")


if __name__ == "__main__":
    solve()
