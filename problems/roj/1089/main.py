#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:18
# update_at: 2026-09-29 18:18

import sys


def solve() -> None:
    value = int(sys.stdin.buffer.read())
    sign = "-" if value < 0 else ""     # 负号永远留在最高位，先单独摘出来
    digits = str(abs(value))            # 去掉符号后的数字串，不含前导零

    # 反转数位；原数末尾的 0 现在跑到最前面，lstrip("0") 抹掉它们，
    # 但原数本身是 0 时整串会被抹空，此时要还原成 "0"。
    reversed_digits = digits[::-1].lstrip("0") or "0"
    print(sign + reversed_digits)


if __name__ == "__main__":
    solve()
