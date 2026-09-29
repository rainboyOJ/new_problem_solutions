#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:21
# update_at: 2026-09-29 16:21

import sys


BASE_WEIGHT = 1000  # 基本费对应的重量上限（克）
BASE_FEE = 8        # 基本费（元）
UNIT_EXTRA = 500    # 超重计费单元（克）
FEE_PER_UNIT = 4    # 每个超重单元加收费用（元）
URGENT_FEE = 5      # 加急费（元）


def postage(weight: int, urgent: bool) -> int:
    """按重量与是否加急计算邮资。"""
    extra_units = max(weight - BASE_WEIGHT, 0) + (UNIT_EXTRA - 1)  # 不足 500g 向上取整
    extra_fee = extra_units // UNIT_EXTRA * FEE_PER_UNIT
    return BASE_FEE + extra_fee + (URGENT_FEE if urgent else 0)


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    weight = int(data[0])
    urgent = data[1] == b'y'
    print(postage(weight, urgent))


if __name__ == "__main__":
    solve()
