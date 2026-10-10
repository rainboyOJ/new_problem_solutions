#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:14
# update_at: 2026-10-07 15:25

import sys

WORK_WEIGHT, TEST_WEIGHT, EXAM_WEIGHT = 2, 3, 5  # 20% / 30% / 50% 各放大 10 倍后的整数权重
FULL_WEIGHT = 10  # 三个整数权重之和，也就是还原成百分制时要除的除数


def solve() -> None:
    """读入作业、小测、期末三项成绩，输出加权后的总成绩。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    work, test, exam = next(data), next(data), next(data)

    # 三项成绩各乘自己的整数权重再相加；权重是整数，全程没有浮点误差
    total = work * WORK_WEIGHT + test * TEST_WEIGHT + exam * EXAM_WEIGHT

    # A、B、C 都是 10 的整数倍，总分必被 10 整除，整数除法不会丢掉小数部分
    print(total // FULL_WEIGHT)


if __name__ == "__main__":
    solve()
