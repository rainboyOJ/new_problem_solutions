#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:09
# update_at: 2026-09-29 16:09

import sys

PASS_LINE = 60  # 及格线：成绩小于 60 记为不及格


def solve() -> None:
    chinese, maths = map(int, sys.stdin.buffer.read().split())
    # 两门课各贡献一次不及格计数，恰好 1 即为"恰好一门不及格"
    failed_cnt = (chinese < PASS_LINE) + (maths < PASS_LINE)
    print(int(failed_cnt == 1))


if __name__ == "__main__":
    solve()
